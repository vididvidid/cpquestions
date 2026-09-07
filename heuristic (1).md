# Edge–Cloud Collaborative Scheduling — Final Heuristic Specification

**Status.** This document is the single source of truth. It is self-contained: an implementer who
reads only this file can build the complete scheduler. The failure analyses (`M0`–`M15`), the
corrected heuristic, the cross-component analysis, the new-hypothesis list and the external-research
notes were *inputs* to this document and are not dependencies of it.

**Experimental status.** No experiment-results file exists. **Nothing in this document has been
experimentally validated.** Every claim is tagged:

| Tag | Meaning |
|---|---|
| `FORCED` | follows directly from the words of the problem statement |
| `DERIVED` | arithmetic on quantities the statement guarantees |
| `MODEL` | a modelling choice that is theoretically supported but empirically untested |
| `SPECULATIVE` | plausible, weakly supported; must be ablatable with one switch |

**Design principle used throughout.** A simple mechanism that can actually be implemented beats a
sophisticated one that cannot. Where two rules were doing the same job, one was deleted. Where a
special case could be made to *emerge* from a general rule, the special case was deleted. The final
policy has **one pricing function, one residual estimator, one admission controller, one offline
grid search, and nine tuned constants.**

---

## Table of contents

1. Problem understanding
2. Objective and scoring interpretation
3. Core intuition
4. System model and rate ceilings
5. Available, hidden, and estimable information
6. Important hidden quantities and how the policy copes
7. State variables
8. Decision timeline (one frame)
9. The offline plan
10. The marginal-price function (the single arbitration rule)
11. Admission / gating policy
12. Binding / routing policy
13. Local ordering policy
14. Remote ordering policy and the `P PROC` split
15. Group formation
16. Wait-or-fire
17. The prefill big-object gate
18. Safety kernel: liveness, legality, fallback
19. Frame-budget and wall-clock guard
20. Priority hierarchy
21. Estimation methodology
22. Parameters: definition, derivation, values
23. Component interactions
24. Corner-case behaviour (the 50 cases)
25. Adversarial attack and remaining weaknesses
26. Computational complexity
27. Implementation-ready pseudocode
28. Validation and experiment plan
29. Confidence register
30. Rejected mechanisms and why

---

## 1. Problem understanding

One **local** machine `E` (the edge) and `K ≤ 8` identical **remotes** `C_0..C_{K-1}`. Every machine
runs at most one task at a time; a task assigned at `t` with table duration `dur` occupies its
machine over `[t, t + S + dur]`. The schedule cost `S` is paid **once per task**, including once per
`P PROC` piece and once per output group. Transfers pay no `S`.

One shared link with **two independent FIFO queues**, `UP` (local→remote) and `DOWN`
(remote→local). Both may be active at once; within a direction, transfers complete in enqueue
order. Transfer time is

```
xfer(len) = lat + 8·len·bpt / (bw·1e6)          ms          [FORCED]
```

`R ≤ 2000` requests arrive over time; **`R` is never announced and there is no end-of-stream
signal.** Request `i` arrives at `a_i` with `Lin_i ∈ [1,4096]` known and `Lout_i ∈ [1,512]`
**hidden until its `FIN`**. `ΣLout ≤ 2·10⁵`.

Lifecycle (solid = tasks you schedule, dashed = automatic transfers):

```
ARR i (Lin known, Lout hidden)
   │
   ▼
P PRE  (local)  ── fixes the remote binding, IRREVOCABLE
   ┆ UP  xfer(Lin)
   ▼
P PROC (remote) ── one or more ascending gap-free part ranges [ls,le)
   ┆                duration of a piece = (le-ls)/N_L · prefill_proc(Lin)
   ┆ DOWN xfer(Lin)   ← queued by the LAST piece only
   ▼
P POST (local)  ── TDR STOPS HERE.  Request becomes ready for output.
   │
   ├──────────────── repeat Lout_i times ────────────────┐
   ▼                                                     │
D PRE  (local, may group requests across DIFFERENT remotes)
   ┆ UP  one transfer per distinct remote in the group, len = that remote's member count
   ▼
D PROC (remote, all members bound to that remote)
   ┆ DOWN one transfer per group, len = group size
   ▼
D POST (local, may group across remotes) ── one token per member; FIN with the last token
   └─────────────────────────────────────────────────────┘
```

**Task durations.** A six-column table (`prefill_pre`, `prefill_proc`, `prefill_post`, `decode_pre`,
`decode_proc`, `decode_post`) indexed by `batch_size`. For the three prefill columns `batch_size`
means `Lin`; for the three decode columns it means the **member count** of the group. Each column is
interpolated **independently** over that column's non-missing rows (missing = `-1`), linearly between
listed sizes and **clamped constant** below the smallest and above the largest listed size. Rows
arrive in arbitrary order. `2 ≤ N ≤ 4096` rows.

**What the scheduler controls — the complete list.** `FORCED`

1. Which legal task to start on each free machine, at each frame.
2. The remote binding of a request, fixed at its `P PRE`, irrevocable.
3. How to cut a `P PROC` into consecutive part ranges.
4. Which ready requests to combine into each `D PRE` / `D PROC` / `D POST` group.
5. **The choice to leave a free machine idle.** Waiting is a first-class action.

**What it does not control.** Transfers (automatic, FIFO, no priority, no cancellation), event
times, arrivals, and `Lout`. There is **no self-wake**: a decision can only be taken at a frame, and
frames occur only for events you caused plus arrivals you cannot predict.

**Hard limits.** 15 s wall clock, 256 MB, at most `2·10⁶` frames per test.

**Zero-score conditions.** Assigning to a busy machine; two tasks on one resource in one response;
missing predecessor; using a finished or in-flight rid; wrong remote; illegal piece range; malformed
group or output; a **stuck state** (unfinished work, nothing in flight, nothing scheduled); time or
memory limit. There is no partial credit.

---

## 2. Objective and scoring interpretation

```
Score = 1000 · [ w_tp · clamp(tp; tp_base, tp_UB) + w_c · clamp(dist; dist_base, 0) ]

tp    = ΣLout / (last token time − earliest arrival time)
tdr   = mean over ALL requests of (P POST completion − arrival)
tpot  = pooled mean of consecutive token gaps, over all requests
dist  = sqrt(excess_tdr² + excess_tpot²),  excess_x = max(0,(x − SLO_x)/SLO_x)

clamp(tp; tp_base,tp_UB) = clip01((tp − tp_base)/(tp_UB − tp_base))
clamp(dist; dist_base,0) = max(0, 1 − dist/dist_base)     if dist_base > 0
                         = 1 if dist == 0 else 0          if dist_base == 0
```

### S1 · `tpot` telescopes into per-request spans — `FORCED`

For request `i` with token times `e_1<…<e_{Lout}`, the gaps sum telescopes:

```
                 Σ_i ( e_last,i − e_first,i )        Σ_i span_i
   tpot   =    ───────────────────────────────  =  ───────────────
                    Σ_i ( Lout_i − 1 )                    G
```

Three consequences, all `FORCED`:

* **Gap variance is not scored.** Only the first-to-last-token *span* of each request is charged.
  Every cadence-smoothing, fairness, virtual-runtime, slack-ascending or per-token-deadline
  mechanism optimises a quantity that does not appear in the objective.
* **A request that has produced no token has no span.** Holding a *ready but never started* request
  costs exactly zero on `tpot`, and its TDR clock already stopped at `P POST`. **Parking is free.**
* **Once a request has produced its first token, its span accrues whether or not you serve it.** So
  among started requests, finishing them sooner is strictly better; there is no benefit in slowing
  any of them down.

### S2 · Little's law is the entire latency/throughput trade-off — `DERIVED`

A request's decode steps are strictly serial: token `k+1` cannot start before token `k`'s `D POST`
completes. Let `A` be the set of requests currently allowed to produce tokens and `RT` the mean
round-trip of one decode iteration. Then

```
tp   = min( tp_max , |A| / RT )
tpot ≈ max( RT , |A| / tp_max )
N*   = tp_max · RT          ← the concurrency at which the bottleneck saturates
```

Concurrency **above** `N*` buys zero throughput and costs `tpot` linearly. Concurrency **below**
`N*` costs throughput and buys nothing (`tpot` is already at its floor `RT`). This is the
bandwidth-delay product of the decode pipeline, and it is the reason a working-set cap exists.

### S3 · Group size `m` and working-set size `|A|` are independent dials — `DERIVED`

`m` amortises `S` and the per-transfer `lat` over more tokens; it affects `RT` only through the
`τ(·,m)` growth and the byte terms. `|A|` is what sets `tpot`. Conflating them ("batching") makes it
impossible to explain why batching raises throughput without raising latency.

### S4 · Rate ceilings, computable from the table alone — `DERIVED`

At operating point `(m, Keff)` — group size `m` spread over `Keff` active remotes, so `m_k = m/Keff`
members per remote:

```
tp_local (m,Keff) = m / ( 2S + τ_dpre(m) + τ_dpost(m) )
tp_remote(m,Keff) = m / ( S + τ_dproc(m/Keff) )
tp_up    (m,Keff) = m / ( Keff·lat + 8·m·bpt/(bw·1e6) )
tp_down  (m,Keff) = m / ( Keff·lat + 8·m·bpt/(bw·1e6) )
tp_max   (m,Keff) = min of the four
tp_link_abs       = bw·1e6 / (8·bpt)     ← every token crosses each direction exactly once
```

`tp_link_abs` is a single division and is often decisive: with `bw = 0.001`, `bpt = 10⁶` one token's
bytes take 8000 ms, so `tp ≤ 1.25·10⁻⁴` tokens/ms no matter what any scheduler does.

Modelled round trip for the average member:

```
RT(m,Keff) = 3S + τ_dpre(m) + τ_dproc(m/Keff) + τ_dpost(m)
           + (Keff + 1) · ( lat + 8·m·bpt/(Keff·bw·1e6) )
```

The `(Keff+1)` factor is the average queueing position of a member's own transfer inside the wave of
`Keff` per-remote transfers, counted once for `UP` and once for `DOWN`. `MODEL`

### S5 · Gradient structure of `dist` — `DERIVED`

`∂dist/∂excess_x = excess_x / dist`. Therefore the **larger excess owns the gradient**; driving an
excess to zero has vanishing marginal value near zero; and for a fixed sum of excesses, balanced is
better than concentrated. When `dist_base = 0` the component is a step function — never ride the
boundary, hold a margin.

### S6 · The exchange rate between the two waiting metrics — `FORCED`

Each excess is normalised by its own SLO. **One ms of `tpot` is worth `SLO1/SLO2` ms of `tdr`.**
Both SLOs range over `[10⁻³, 10⁹]`, so this ratio spans twelve orders of magnitude. Any rule that
ranks prefill against decode without this factor is wrong on most of the parameter space.

### S7 · A zero is correlated across the twenty final tests — `DERIVED`

The final score is the arithmetic mean of 20 frozen tests, and a protocol error, stuck state or
timeout scores 0 with no partial credit. One codebase runs all twenty, so a latent `O(n²)` hot path
or an off-by-one on `FIN` handling removes a correlated block of tests, not an independent 5 %.
**Correctness and the frame budget therefore outrank every scoring heuristic absolutely.**

### S8 · Ordering local work is makespan-neutral when both phases share a bottleneck — `DERIVED`

Total work on each resource is fixed by the input. If prefill and decode are limited by the *same*
resource, then any work-conserving order produces the same makespan, so prefill-first is free for
`tp` and strictly better for `tdr` (earlier `P POST`) and for `tpot` (spans are not contaminated by
prefill blocking). If they are limited by *different* resources, prefill-first serialises what could
have overlapped and costs makespan. **This is why the policy needs a work-conservation override and
not a hard-coded phase order** (§13, rule R3).

---

## 3. Core intuition

> **Prefill promptly. Decode a small, stable working set to completion. Park the rest at zero cost.
> Never let the throughput bottleneck idle. Price every ordering decision by the delay it inflicts
> on the other class, multiplied by that class's exact population.**

Parking is free (S1). Holding `|A|` near `N*` saturates the bottleneck without paying `tpot` (S2).
Grouping buys throughput almost for free (S3). And every remaining decision — prefill vs decode on
the local machine, `D PROC` vs `P PROC` on a remote, whether to enqueue a huge prefill transfer — is
the *same* decision: which class do I delay, for how long, and what does that delay cost? That single
question is answered by one function (§10).

The single most damaging thing a scheduler can do here is **round-robin the ready pool**: sweeping
"whoever waited longest" across a large ready set gives each request a token once every `pool/m`
cycles and inflates `tpot` by that factor, with no compensating gain anywhere in the objective.

---

## 4. System model and rate ceilings

Notation used throughout:

| Symbol | Meaning |
|---|---|
| `S, lat, bw, bpt, N_L, K` | schedule cost, latency ms, Gb/s, bytes per token, `num_layers`, remote count |
| `τ_c(x)` | clamped piecewise-linear lookup on column `c` at size `x` |
| `xfer(len)` | `lat + 8·len·bpt/(bw·1e6)` |
| `m` | decode group size (local stages) |
| `m_k` | decode group size on one remote |
| `Keff` | number of remotes the working set is spread over, `1 ≤ Keff ≤ K` |
| `A` | working set: requests currently allowed to produce tokens |
| `P` | parked pool: prefill-complete requests deliberately not yet in `A` |
| `RT` | measured (or modelled) decode round trip |
| `N*` | `tp_max · RT`, the saturation concurrency |
| `n_pend` | arrived requests whose `P POST` has not completed — the exact `tdr` population |
| `n_span` | requests with `tokens ≥ 1` and not `FIN` — the exact `tpot` population |

**Why `Keff` is a real lever and `r` (spread per group) is not.** `MODEL`
A `D PRE` group spanning `r` remotes enqueues exactly the same set of `UP` transfers as `r` separate
per-remote `D PRE` tasks, but pays `S` once instead of `r` times. So **always group `D PRE` and
`D POST` across every ready remote** — spread-per-group is not a decision. What *is* a decision is
how many remotes the working set is bound to at all: each additional active remote adds one `lat`
per direction per wave (up to `2·8·50 = 800 ms` per wave at `lat = 50`, `K = 8`) and splits the
per-remote `D PROC` group, which matters when the `decode_proc` column has a clamp-below floor.
`Keff` therefore trades remote parallelism against link latency and group efficiency, and it is
chosen by the offline grid (§9).

---

## 5. Available, hidden, and estimable information

**Known exactly, before any event.** `K, S, lat, bw, bpt, N_L`; `SLO1, SLO2, tp_UB, tp_base,
dist_base, w_tp, w_c`; the full task table. All durations and all transfer times are therefore
**computable in closed form** — the scheduler can predict every completion time it causes.

**Known exactly, online.** Every arrival with its `Lin`; every task completion with its echoed
duration; every transfer completion with its byte count and rid list; every `FIN`. From these, and
from its own actions, the scheduler knows **exactly**: which machines are free, the contents and
completion times of both FIFO queues, the busy time of every resource, `n_pend`, `n_span`, every
completed request's `tdr`, every request's token times and hence every span, `tp` so far, and the
next completion time `t_wake` over everything in flight.

**Hidden permanently until revealed.** `Lout_i` (until `FIN`), `R`, the arrival process, whether the
stream has ended, and `G = Σ(Lout_i − 1)`.

**Estimable.** `R̂` = highest rid seen + 1 (a lower bound); `Ĝ` = observed gaps so far (a lower
bound); `rem̂(k)` = expected remaining tokens given `k` produced, from the empirical distribution of
observed `Lout` values; `RT` measured as the interval between consecutive tokens of the same request;
projected `tdr` including the waits of currently pending requests.

**Irreversible decisions.** (a) The remote binding at `P PRE`. (b) Producing a first token — after
that the request's span accrues until it finishes, so it must never be de-prioritised to nothing.
Everything else is reversible at the next frame.

**Unavailable, and therefore forbidden as an input to any rule.** Future arrivals, `R`, `Lout` of an
unfinished request, whether the stream has ended, and any timer or self-wake.

---

## 6. Important hidden quantities and how the policy copes

| Hidden quantity | Where it would be used | Substitute actually used | If the substitute is wrong |
|---|---|---|---|
| `R` (final request count) | denominator of `tdr` | `R̂` = max rid + 1 | prefill/decode price ratio biased; absorbed by hysteresis and by the fact that only the ratio matters |
| `G = Σ(Lout−1)` | denominator of `tpot` | `Ĝ` = observed gaps | same |
| `Lout_i` | binding, admission order, group choice | never forecast for an irreversible decision; only `rem̂` as a *load correction* | binding imbalance, bounded by the fact that `rem̂` errors are common to all remotes and so mostly cancel in a comparison |
| end of stream | when to stop batching | never inferred; every wait is bounded by `W_max` frames and by exact liveness | at worst one extra frame of waiting |
| true `RT` and `tp_max` | `N*` | modelled offline, then **replaced by measurement**, then corrected by feedback (§11) | AIMD recovers in `O(epoch)` frames in both directions |

---

## 7. State variables

```
Per request i:
  stage        NEW | ARRIVED | PPRE_RUN | UP_PRE | PPROC_ARMED | PPROC_RUN | DOWN_PRE
               | RD_PPOST | PPOST_RUN | PARKED | RD_DPRE | DPRE_RUN | UP_DEC | RD_DPROC
               | DPROC_RUN | DOWN_DEC | RD_DPOST | DPOST_RUN | FINISHED
               (ARRIVED and RD_PPOST are the two prefill-class local candidate pools;
                RD_DPRE and RD_DPOST are the two decode-class local candidate pools)
  arrival      a_i                          (frame timestamp of its ARR)
  Lin          known at ARR
  remote       sticky binding, set at P PRE, never changed
  tokens       tokens produced so far
  tFirst,tLast token times; span_i = tLast − tFirst  (0 when tokens ≤ 1)
  piece        next P PROC piece start (ascending, gap-free)
  inA          membership of the working set
  passOver     consecutive group formations in which this ready member was skipped
  holdFrames   frames this prefill task has been held by R9 / passed over by SPT
  tdrDone      whether P POST has completed (defines n_pend)

Machines:
  localBusy, remoteBusy[K], and for each, the predicted completion time of the running task

Link (shadow queues — exact, reconstructed from own actions):
  qUP, qDOWN : deque of { bytes, isPrefill, rids, startTime, finishTime }
  upFreeAt, downFreeAt : predicted time the direction next becomes idle

Populations and metrics (all exact unless marked):
  n_pend, n_span, |A|, |P|, unfinished
  tdr_sum_done, n_tdr_done, sum_a_pending      → projected tdr (§21)
  span_sum, gap_count                          → running tpot
  tokens_total, firstArrival                   → running tp
  RT_ewma                                      → measured round trip
  u_local, u_remote[k], u_up, u_down           → exact busy fractions over the last epoch
  histLout[0..512], nFin                       → empirical Lout distribution → rem̂
  load[k]                                      → residual work bound to remote k  (ONE object)
  frames_seen, cpu_elapsed                     → budget guard

Policy vector (from the offline plan, refreshed on re-grid):
  m_pre, m_proc, m_post, Keff, A_target, mode-free derived constants
  fallbackLatched
```

**One residual object.** `load[k]` is the *only* residual-work estimate in the system. It is
consumed by binding (§12), by the end-game cap lift (§11) and by the group-selection key (§15).
Nothing else recomputes a residual. This was the single most valuable finding of the
cross-component analysis: three independent residual estimators fed by the same `FIN` stream diverge
after the first long completions and then lock in an imbalance that no local rule can repair.

---

## 8. Decision timeline — exactly what happens in one frame

```
read timestamp t
read event count e
read all e event lines into a buffer                        ← never decide mid-frame
──────────────────────────────────────────────── PHASE 1 (collect, mutate nothing)
  freedMachines  := servers of every TDN in the buffer      ← including the LAST line
  finishedRids   := rids of every FIN in the buffer
  arrivals, tdnFacts, xdnFacts collected
──────────────────────────────────────────────── PHASE 2 (mutate once, in a fixed order)
  1. apply ARR         : create request, n_pend++, sum_a_pending += a_i
  2. apply XDN         : pop the matching shadow-queue head, advance listed rids' stages
  3. apply TDN         : mark machine free, advance stage, enqueue any triggered transfer
  4. apply FIN LAST    : remove rid from A, from every ready list, from load[k];
                         histLout[tokens]++, nFin++, recompute rem̂ suffix sums
  5. commit counters   : n_pend, n_span, span_sum, gap_count, tokens_total
──────────────────────────────────────────────── PHASE 3 (decide, mutate nothing)
  signals   : projected tdr/tpot/tp, excesses, prices, utilisations, t_wake, load[k]
  admission : resize A, admit from P in arrival order              (§11)
  remotes   : for each free remote, at most one task               (§14)
  local     : at most one task                                     (§13)
──────────────────────────────────────────────── PHASE 4 (guard, then emit)
  legality sweep over every planned assignment                     (§18)
  liveness guard: if plan empty and inflight == 0 and work remains → inject (§18)
  order the lines: token-producing / decode-triggering first
  print n, print the lines, flush
```

**Why this order is load-bearing.**

* Two-phase apply makes `FIN` handling mechanical. `FIN` always arrives beside the final `D POST`
  `TDN` of that request; a naive line-by-line handler will happily place that rid in a task in the
  same response, which is an instant zero. `FORCED`
* A machine freed by the **last** event line is legally usable in this response. Collecting freed
  machines in phase 1 makes that automatic rather than accidental. `FORCED`
* Admission runs before candidate generation because `A` membership is what makes a request eligible
  for `D PRE` at all.
* Liveness runs after the plan is complete, because it may need to inject into an empty plan.
* The legality sweep runs against post-ingest state, never against remembered state.

Printed timestamps are **nondecreasing, not strictly increasing**: two consecutive frames can print
the same `t`. Never key state on timestamp equality; key it on frame sequence. `FORCED`

---

## 9. The offline plan (`PLAN`) — everything computable before the first event

No event has arrived, so this computation is free. It runs once at start-up and is **re-run online**
at most every `4096` frames with measured quantities substituted (§21).

### 9.1 Building the six curves

```
for each of the 6 columns:
    collect (batch_size, value) for every row with value != -1
    sort by batch_size, deduplicate
τ_c(x) = value at x if listed
       = linear interpolation between the two bracketing listed sizes
       = value of the smallest listed size   if x < smallest      ← CLAMP BELOW
       = value of the largest listed size    if x > largest       ← CLAMP ABOVE
```

The statement guarantees every column has at least one non-missing entry, so every curve is
well-defined. **Never mix columns**: prefill columns are indexed by `Lin`, decode columns by member
count. Mixing them is a silent correctness bug that produces plausible-looking nonsense.

Two structural facts are read off each decode column and used later:

* **Clamp-below ⇒ an efficiency floor.** If the smallest listed size of a decode column is `f > 1`,
  every group smaller than `f` costs exactly the same as a group of `f`. Forming groups below `f` is
  strictly wasteful *when more members are available*. `FORCED`
* **Clamp-above ⇒ unbounded per-token gain.** If the largest listed size is `g` and more than `g`
  members can be formed, `τ` is constant above `g`, so the per-token cost keeps falling. The optimal
  group is then the entire eligible set. `FORCED`

Both facts are consumed automatically by the size rule below; neither needs a special case.

### 9.2 Per-column throughput-optimal group size

```
for each decode column c:  m*_c = argmax over x in [1, 4096] of  x / (S + τ_c(x))
```

This is one linear scan of 4096 points per column (~12k evaluations, once). It is correct for
non-monotonic, sparse, sawtooth and clamped tables alike, because it makes **no assumption about the
shape of the curve** — it simply maximises tokens per millisecond of machine occupancy. It
subsumes clamp-below (`m*_c ≥ f`) and clamp-above (`m*_c = 4096`, i.e. "take everything"). `DERIVED`

### 9.3 The operating-point grid search

```
best = −∞
for m    in {1,2,3,4,6,8,12,16,24,32,48,64,96,128,192,256,384,512,768,1024,1536,2000}:
  for Keff in 1..K:
    for Ahat in {m, 2m, 3m, 4m, 6m, 8m, 12m, 16m, 24m, 32m}  ∩ [1, 2000]:
        tpmax   = min( m/(2S+τ_dpre(m)+τ_dpost(m)),
                       m/(S+τ_dproc(ceil(m/Keff))),
                       m/(Keff·lat + 8·m·bpt/(bw·1e6)) )          // UP and DOWN coincide
        RT      = 3S + τ_dpre(m) + τ_dproc(ceil(m/Keff)) + τ_dpost(m)
                    + (Keff+1)·( lat + 8·m·bpt/(Keff·bw·1e6) )
        tp_hat  = min( tpmax, Ahat / RT )
        tpot_hat= max( RT, Ahat / tpmax )
        ex_tpot = max(0, (tpot_hat − SLO2t)/SLO2)                 // SLO2t: see below
        dist    = sqrt( ex_tdr_now² + ex_tpot² )                  // ex_tdr_now = 0 offline
        sc      = w_tp·clip01((tp_hat − tp_base)/(tp_UB − tp_base)) + w_c·waitComponent(dist)
        keep the argmax; tie-break towards SMALLER Ahat, then smaller m
```

with

```
SLO2t = SLO2·(1 − μ)  if dist_base == 0   else  SLO2        // μ = binary margin
waitComponent(d) = max(0, 1 − d/dist_base)   if dist_base > 0
                 = 1 if d == 0 else 0        if dist_base == 0
```

Output: `m*, Keff, A_target0`. Then

```
m_pre  = min(m*, m*_dpre_column) if that is larger than m* use m* ... precisely:
m_pre  = m*   (the local stages are what the grid priced)
m_post = m*
m_proc = max(1, ceil(m*/Keff))
```
and each is additionally allowed to grow to its column's `m*_c` when more members happen to be ready
and the group's `RT` contribution is not the binding constraint (§15).

**WHY this replaces a mode table.** `DERIVED`
Earlier versions of this design classified the test into one of six discrete modes
(THROUGHPUT / LATENCY / BINARY / FORGIVING / latency-dead / throughput-dead) and *rewrote the
weights* accordingly. Every one of those modes is already a region of the objective above:

* `w_c = 0` ⇒ the `waitComponent` term vanishes ⇒ the grid maximises `tp` ⇒ largest useful `m`, `A`.
* `w_tp = 0` ⇒ the `tp` term vanishes ⇒ the grid picks the smallest `A` and `m` that minimise `tpot`.
* `tp_max ≤ tp_base` ⇒ every candidate scores 0 on throughput ⇒ the grid optimises waiting only.
* `tp_max ≥ tp_UB` ⇒ the throughput term saturates ⇒ ties are broken towards smaller `A` ⇒ slack is
  automatically handed to waiting.
* `dist_base = 0` ⇒ `waitComponent` is a step ⇒ the grid picks the largest `(m,A)` that still meets
  both targets **with margin**, and if that is infeasible everywhere it silently becomes pure
  throughput.
* `dist_base ≫` achievable `dist` ⇒ `waitComponent ≈ 1` for all candidates ⇒ ties resolve on `tp`.

A discrete classifier can be *wrong* at a boundary and then locks a weight rewrite for the whole
run — the highest-severity failure mode found in the `M0` analysis. A grid over the true objective
cannot be wrong in that way, is re-runnable with measured inputs, costs ~1800 evaluations, and
removes six rules, one weight-rewrite mechanism and two thresholds. **The mode table is deleted.**

### 9.4 The only genuinely discrete offline decision

```
binaryMode := (dist_base == 0)
```

`FORCED` from the statement: when `dist_base = 0` the waiting component is `1` at `dist = 0` and `0`
at any positive `dist`. There is no gradient, so the online price function needs a *virtual*
gradient (§10) and the grid needs a margin `μ`. Nothing else about the test is classified.

### 9.5 Static budget floor

```
events_per_wave ≈ 2 + 3·Keff        (D PRE TDN, per-remote UP XDN, D PROC TDN, DOWN XDN, D POST TDN)
m_io_static     = max(1, ceil( 2·10⁵ · (2 + 3·K) / 1.5·10⁶ ))
```

With `K = 8` this is `4`. It is a floor on group size only when there are that many members ready;
it never causes waiting. The dynamic escalation of §19 is what actually protects the frame budget.

---

## 10. The marginal-price function — the single arbitration rule

Everything the scheduler chooses between is the same choice: **serving class X now delays class Y by
the duration of the task I start.** Price it.

### 10.1 Prices

```
ex_tdr  = max(0, (tdr_proj  − SLO1t)/SLO1)          SLO1t = SLO1·(1−μ) if binaryMode else SLO1
ex_tpot = max(0, (tpot_proj − SLO2t)/SLO2)          SLO2t = SLO2·(1−μ) if binaryMode else SLO2
D       = sqrt(ex_tdr² + ex_tpot²)
DB      = dist_base > 0 ? dist_base : μ             ← virtual reference in binary mode

P_TDR   = (D > 0 && D < DB) ?  w_c·(ex_tdr /D)/(DB·SLO1·R̂) : 0
P_TPOT  = (D > 0 && D < DB) ?  w_c·(ex_tpot/D)/(DB·SLO2·Ĝ) : 0
```

`P_TDR` is the score lost **per millisecond of delay applied to one pending request**; `P_TPOT` is
the score lost per millisecond of delay applied to one mid-span request. Both are exact derivatives
of the published objective except for the two lower-bound denominators `R̂`, `Ĝ`.

### 10.2 The comparison (Smith's rule / `cμ`)

Given a candidate prefill task of duration `d_P = S + τ(prefill step, Lin)` and a candidate decode
task of duration `d_D = S + τ(decode step, m)`, over a population `(n_pend, n_span)` — global for
the local machine, per-remote for a remote:

```
cost_if_prefill_first = d_P · n_span · P_TPOT      // decode class waits d_P
cost_if_decode_first  = d_D · n_pend · P_TDR       // prefill class waits d_D

choose PREFILL  iff  cost_if_prefill_first · (1+η) < cost_if_decode_first
choose DECODE   iff  cost_if_decode_first  · (1+η) < cost_if_prefill_first
otherwise                                          keep the previous frame's class (hysteresis)
```

> **RULE R2 — priced class arbitration**
> **WHY.** With one server and two job classes, the order minimising the weighted sum of completion
> times is Smith's rule: highest `weight/duration` first. Here the weight of a class is exactly
> `population × per-request score derivative`, and both populations are known exactly.
> **TRIGGER.** Any free machine with candidates from both classes.
> **ACTION.** Compute the two costs above; pick the cheaper; hysteresis band `η` on ties.
> **FAILURE PREVENTED.** (i) A fixed ladder that is wrong for half of every run — the correct order
> genuinely flips as `n_pend` falls and `n_span` rises. (ii) The "large `Lin` is a maintenance
> window" failure: a `P PRE`/`P POST` whose duration reaches `10⁴ ms` would freeze the only machine
> that can run `D PRE`/`D POST`, adding that duration to `n_span` spans **simultaneously**. Because
> `d_P` multiplies the cost, a huge prefill loses this comparison automatically. The previous design
> needed a separate rule (`R5`, "maintenance window") with its own threshold `β`; **that rule is now
> deleted — it is a consequence of including duration in the comparison.**
> **AVAILABLE INFORMATION.** `n_pend`, `n_span` exact; durations exact from the table; `R̂`, `Ĝ`
> lower bounds; excesses from projections (§21).
> **IF ESTIMATE IS WRONG.** `R̂` and `Ĝ` are lower bounds with different biases, so the ratio can be
> off by a constant factor. The consequence is a systematically shifted class boundary, not
> oscillation. Hysteresis `η` and the work-conservation override (R3) bound the damage.
> **TRADEOFF.** When the ratio is biased towards prefill, `tpot` rises; towards decode, `tdr` rises.
> **CONFIDENCE.** 0.80 — mechanism `DERIVED`, estimator quality `MODEL`.

### 10.3 Degenerate prices

When `w_c = 0`, or `D = 0` (both means comfortably inside their targets), or `D ≥ DB` (the waiting
component is already 0 and cannot be recovered — only possible when `dist_base > 0`), both prices are
zero and R2 is silent. Then the fallback ladder applies, in this order:

```
1. whatever keeps the throughput bottleneck busy                      (R3)
2. downstream stages before upstream ones: D POST > D PRE, P POST > P PRE
3. decode before prefill if |A| ≥ A_target, else prefill
```

Rule 2 is standard pipeline discipline: completing downstream work reduces work-in-progress, and
`D POST` is the only local task that actually produces tokens.

### 10.4 The three call sites

| Site | Populations | Prefill candidate | Decode candidate |
|---|---|---|---|
| Local machine (§13) | global `n_pend`, `n_span` | best `P POST`/`P PRE` | best `D POST`/`D PRE` |
| Remote `k` (§14) | `n_pend[k]`, `n_span[k]` | next `P PROC` piece | `D PROC` group on `k` |
| Prefill transfer gate (§17) | global `n_span` restricted to those awaiting a decode transfer | the triggered transfer's `xfer(Lin)` | — |

Using the same function at all three sites is what removes the "two pricing systems on one budget"
bug: there is exactly one budget and exactly one price for it.

---

## 11. Admission / gating policy — the working set `A`

> **RULE R1 — bounded working set with feedback**
> **WHY.** `tpot ≈ |A|/tp` (S2) and parking is free (S1). Concurrency above `N*` is pure `tpot` cost
> with zero throughput gain; concurrency below `N*` is pure throughput loss.
> **TRIGGER.** Every `P POST` completion, every `FIN`, and every admission epoch.
> **ACTION.** Maintain `A_target`; admit from the parked pool `P` in **arrival order** until
> `|A| = A_target`; never evict.
> **FAILURE PREVENTED.** Sweeping the whole ready pool, which inflates `tpot` by `|pool|/m`.
> **AVAILABLE INFORMATION.** `|A|`, `|P|`, exact utilisations, measured `RT`, measured `tp`.
> **IF ESTIMATE IS WRONG.** The AIMD law below corrects both directions from *observed* idleness and
> *observed* excess, so a wrong `N*` costs `O(one epoch)` of throughput or `tpot`, not the run.
> **TRADEOFF.** Too small `A` ⇒ throughput lost; too large ⇒ `tpot` inflated.
> **CONFIDENCE.** 0.88 — mechanism `DERIVED`, controller `MODEL`.

### 11.1 The control law

```
A_target ← A_target0                                     (from the offline grid)

every ADM_EPOCH = 256 frames, or on any FIN:

  # GROW — only when capacity is demonstrably wasted AND work exists to fill it
  if  bottleneck_idle_fraction_last_epoch > ε_idle
      and |P| > 0
      and not (the idleness was caused by having no arrived work at all):
          A_target ← A_target + max(1, A_target/8)

  # SHRINK — only when the bottleneck is saturated and tpot is what is costing score
  else if  ex_tpot ≥ ex_tdr  and  P_TPOT > 0
           and bottleneck_idle_fraction_last_epoch ≤ ε_idle:
          A_target ← max(A_floor, A_target − 1)

  A_floor = max(1, m_proc, m_io_dynamic)
  A_target ← min(A_target, 2000)
```

**Never evict.** A request with `tokens ≥ 1` stays in `A` until it finishes. `FORCED` by S1: its
span accrues whether or not you serve it, so removing it from service is strictly negative. When
`|A| > A_target` the set shrinks only by attrition on `FIN`.

**Why growth requires `|P| > 0` and real work.** `DERIVED`
If the bottleneck is idle because nothing has arrived, `tp`'s denominator is set by the arrival
process and no amount of admission helps. Requiring parked work to exist makes the controller
silent on arrival-bound tests instead of ratcheting `A` upward and paying `tpot` for nothing. This
single condition replaces the "arrival-bound regime" rule of the previous design.

**Stability.** Growth is triggered only by observed idleness; shrink only by observed saturation
plus `tpot` dominance. The two conditions are mutually exclusive by construction, so the loop cannot
oscillate on its own; the epoch length bounds its bandwidth well below the system's response time.

### 11.2 End-game cap lift

> **RULE R10 — end-game admission lift**
> **WHY.** `tp`'s denominator is the time of the **last** token over all requests. A long request
> admitted very late runs partly alone at `1/RT` and can single-handedly stretch the makespan.
> **TRIGGER.**
> `residual_total ≤ Λ · A_target · rem̂_mean` when the hazard table is mature (`nFin ≥ N_conf`),
> otherwise `unfinished ≤ Λ · A_target`.
> **ACTION.** `A_target ← unfinished` (admit everything).
> **FAILURE PREVENTED.** The straggler tail on cases 15, 27, 47, 48.
> **AVAILABLE INFORMATION.** `unfinished`, `load[k]`, `rem̂`.
> **IF ESTIMATE IS WRONG.** Lifting too early costs `tpot` for the remainder of the run — bounded,
> because by then only `Λ·A_target` requests remain. Lifting too late costs makespan.
> **TRADEOFF.** `tpot` against `tp`. `Λ` is the knob; raise it in throughput-weighted tests.
> **CONFIDENCE.** 0.75 — `MODEL`. This is the single highest-sensitivity parameter in the design.

The lift is **reversible**: if new arrivals push `unfinished` back above the threshold, the target
returns to the controller's value. There is exactly one lift mechanism, so the "double lift"
interaction identified in the cross-component analysis (soft-DRAIN lift × residual-Λ lift firing
together and overshooting `|A|`) **cannot occur** — the `DRAIN` phase concept is deleted and its
only real effect (lift the cap near the end) is this rule.

### 11.3 What was deleted here and why

* **The `OPENING / STEADY / DRAIN` phase machine.** `OPENING` was "no request has reached `P POST`
  yet", in which case decode candidates do not exist and every rule already degenerates correctly.
  `DRAIN` was silence + shrinking pool + small pool, used to lift the cap and stop splitting — R10
  lifts the cap on a *state* condition rather than a *silence* condition, which is strictly better
  because `R` is unknown and a lull is indistinguishable from the end. Two phases, three
  parameters and a hysteresis window removed.
* **The `all-Lout=1` detector.** When every request finishes on its first token, `n_span` is never
  positive (the `FIN` arrives beside that same `D POST`), so `tpot_proj = 0`, `ex_tpot = 0`,
  `P_TPOT = 0` and the whole `tpot` half of the policy switches itself off. No detector, no
  threshold, no detection latency. `FORCED`

---

## 12. Binding / routing policy

> **RULE R7 — least-residual-work binding with immediate self-update**
> **WHY.** The binding at `P PRE` is irrevocable and fixes where every future `D PROC` for that
> request runs. The quantity that creates makespan on a remote is *residual tokens*, not request
> count.
> **TRIGGER.** Every `P PRE` assignment.
> **ACTION.**
> ```
> load[k] = Σ_{i bound to k, unfinished}  w_i
>    where w_i = rem̂(tokens_i)                    if i has produced tokens
>              = rem̂_0                            if i is prefill-pending or parked
> bind to argmin over the Keff active remotes of load[k]; ties by a rotating counter
> load[r_i] += rem̂_0 immediately, at bind time
> ```
> **FAILURE PREVENTED.** (a) Hidden-`Lout` imbalance: one remote silently accumulating the long
> requests (cases 11, 12, 15, 48). (b) The classic bug of tie-breaking by *lowest index*, which at
> `t = 0` — when every load is zero — binds an entire opening burst to `C_0`. The immediate
> self-update makes that impossible without any burst detector.
> **AVAILABLE INFORMATION.** Exact per-remote membership and tokens produced; `rem̂` from observed
> `FIN`s only.
> **IF ESTIMATE IS WRONG.** `rem̂` errors are *common to all remotes*, so they largely cancel in an
> argmin comparison — the ranking survives even when the absolute values do not. Before the hazard
> table matures (`nFin < N_conf`) all `w_i` equal `rem̂_0`, and the rule degenerates exactly to
> **join-shortest-queue by count**, which for a contiguous arrival window is round-robin.
> **TRADEOFF.** A biased `rem̂` can concentrate new work on a remote that is genuinely about to
> become hot. Bounded because each binding adds only `rem̂_0`.
> **CONFIDENCE.** 0.80 — mechanism `DERIVED` (least-work-left / JSQ), estimator `MODEL`.

**Why this single rule replaces three.** The previous design had round-robin as the primary rule, a
load correction, a separate burst detector with its own per-burst counters, and an imbalance
exclusion threshold `θ_reb`. Least-work-left with an immediate self-update *is* round-robin when all
weights are equal, *is* an exclusion rule when one remote's residual is large (it simply never wins
the argmin), and is immune to stale load during a burst because the update happens at bind time
rather than at `FIN` time. Three mechanisms and two parameters removed. `DERIVED`

**`rem̂`, and why it is never a forecast.** Maintain `histLout[v]` = number of observed `FIN`s with
`Lout = v`. Then

```
rem̂(k) = Σ_{v>k} (v−k)·histLout[v] / Σ_{v>k} histLout[v]      (empirical mean residual life)
rem̂_0  = rem̂(0), cold-started at 1 until nFin ≥ N_conf
```

This is nonparametric, assumes nothing about the `Lout` distribution, and is only ever used as a
*weight in a comparison*, never as a point forecast steering an irreversible decision on its own.
Recomputing the suffix sums costs `O(512)` per `FIN`, i.e. `≤ 10⁶` operations for a whole run.

**`Keff` and which remotes are active.** New bindings are restricted to the `Keff` remotes chosen by
the grid (§9.3), by index. `Keff < K` is chosen only when the grid finds that fewer remotes score
better — which happens when `Keff·lat` per wave dominates, or when `decode_proc` has a clamp-below
floor that a thin per-remote group cannot reach. If measured remote utilisation on the active set
exceeds `0.8` for a full epoch, `Keff` is increased by one (up to `K`) and stays there. `MODEL`

---

## 13. Local ordering policy

The local machine touches four of the six task shapes and can start **at most one task per frame**.
Almost everything expensive in this problem is a local allocation decision.

```
candidates:
  DEC_POST = requests at RD_DPOST                              (decode DOWN has landed)
  DEC_PRE  = members of A at RD_DPRE                           (parked requests excluded)
  PRE_POST = requests at DOWN_PRE  (prefill DOWN has landed)
  PRE_PRE  = requests at ARRIVED
```

```
1. If no candidates at all → emit nothing for the local machine.
2. R3 WORK-CONSERVATION OVERRIDE (see below).
3. Otherwise R2 price comparison between the best prefill candidate and the best decode candidate.
4. Within DECODE:  D POST if available, else D PRE.       (downstream first; D POST makes tokens)
5. Within PREFILL: P POST if available, else P PRE by SPT + aging (R13).
```

> **RULE R3 — work-conservation override**
> **WHY.** `tp` is set by the busiest resource. An idle bottleneck millisecond is unrecoverable; a
> mis-priced millisecond is not. Also, by S8, this is precisely the mechanism that makes the
> scheduler interleave prefill and decode when they are limited by *different* resources and
> prefill-first when they share one — without any explicit phase policy.
> **TRIGGER.** A remote or a link direction is idle (or will be idle before the next completion),
> **and only one of the two classes can feed it**, **and** the throughput component is live
> (`w_tp > 0` and `tp_running < tp_UB`).
> **ACTION.** Choose that class regardless of R2.
> **FAILURE PREVENTED.** Remote/link starvation during long prefill-only or decode-only stretches;
> the fill/drain bubbles of cases 41, 45, 46.
> **AVAILABLE INFORMATION.** Exact machine states and exact shadow queues.
> **IF ESTIMATE IS WRONG.** It cannot be — idleness is observed, not predicted.
> **TRADEOFF.** Can spend a local millisecond that R2 would have priced differently. Bounded to the
> frames where a bottleneck would otherwise idle.
> **CONFIDENCE.** 0.85 — `DERIVED`.

> **RULE R13 — SPT with score-unit aging inside the prefill class**
> **WHY.** `tdr` is a *mean flow time on a contended single server*. Shortest-processing-time is the
> textbook optimum for that objective, not a tie-break.
> **TRIGGER.** Two or more `P PRE` candidates.
> **ACTION.** Pick the smallest `S + τ_ppre(Lin) + τ_ppost(Lin)`. **Override:** if any candidate has
> been waiting longer than `γ·SLO1`, take the longest-waiting such candidate instead.
> **FAILURE PREVENTED.** SPT starving one `Lin = 4096` request behind an endless stream of tiny
> ones. Its own TDR enters the same mean, and in binary mode one blown request zeroes the entire
> waiting component — so the clamp is mandatory, not cosmetic.
> **AVAILABLE INFORMATION.** `Lin`, arrival times, `SLO1`, the table.
> **IF ESTIMATE IS WRONG.** Not an estimate; `Lin` and the table are exact.
> **TRADEOFF.** Aging admits a large prefill into a live decode window; R2 still prices it, and the
> aging override is applied *within* the prefill class, so a huge prefill only runs when the prefill
> class has already won the class comparison.
> **CONFIDENCE.** 0.85 — `DERIVED` mechanism, `MODEL` aging threshold.

The aging threshold is expressed in **score units** (`γ·SLO1`) rather than in frames, because frames
are not time: at `lat = 0.001` a frame may be microseconds, at `lat = 50` it may be a hundred
milliseconds. A frame-count threshold means completely different things on different tests. This
replaces the old `H_age = 32 frames`.

---

## 14. Remote ordering policy and the `P PROC` split

Each free remote is arbitrated independently; remotes are coupled only through the shared link and
through binding.

```
for each free remote k:
    Cd = members of A bound to k at RD_DPROC        (their decode UP XDN has landed)
    Cp = requests bound to k whose next P PROC piece is armable
    if both empty  → leave k idle (legal; the liveness guard re-checks)
    if one empty   → take the other
    if both        → R2 with per-remote populations n_pend[k], n_span[k]
                     STARVATION BOUND: if the last T_star = 8 choices on k were all decode
                     and Cp is non-empty, force one P PROC piece.
```

> **RULE R8 — `P PROC` splitting**
> **WHY.** `τ_pproc(Lin)` reaches `10⁴ ms`. A full piece monopolises a remote for that long, and
> every decode member bound to that remote accrues span for the whole duration. Splitting lets
> decode interleave. But each extra piece costs `S` of **remote** time plus `S` on that request's
> own TDR — and the local machine pays nothing, which flips the trade-off whenever the remote is the
> bottleneck.
> **TRIGGER.** A `P PROC` piece is about to be armed on remote `k`.
> **ACTION.**
> ```
> if N_L == 1                          → full piece (no choice exists)
> if no member of A is bound to k, or none can reach RD_DPROC before a full piece
>    would finish (checked against the SHADOW QUEUE: is a decode UP transfer for k
>    already enqueued, or is a D PRE containing a k-member in flight?)
>                                      → FULL PIECE   [hard no-split]
> otherwise:
>    Δ        = time until that decode data is predicted to land on k (exact when the
>               transfer is already queued; one RT_ewma otherwise)
>    parts    = clamp( floor( N_L · Δ / τ_pproc(Lin) ), 1, remaining_parts )
>    n_max    = 1 + floor( σ_split · τ_pproc(Lin) / S )     ← overhead cap
>    parts    = max( parts, ceil( remaining_parts / n_max ) )
> ```
> **FAILURE PREVENTED.** (a) Over-splitting: with `S = 10` and `N_L = 64`, splitting into 64 pieces
> burns `630 ms` of the scarce remote for nothing (case 16). The `n_max` cap makes the total
> splitting overhead at most `σ_split` of the piece's own work — a **derived** bound, not a tuned
> one. (b) Under-splitting: a huge prefill blocking live decode on the same remote (cases 17, 41,
> 46).
> **AVAILABLE INFORMATION.** Exact shadow queues, exact table durations, exact `A` membership.
> **IF ESTIMATE IS WRONG.** If `Δ` is optimistic the piece is too large and one decode wave is
> delayed by at most one piece; if pessimistic, a few extra `S` are paid. Both bounded.
> **TRADEOFF.** Splitting delays the request's own DOWN transfer and therefore its own TDR.
> **CONFIDENCE.** 0.80 — hard-no-split branch `DERIVED`, sizing `MODEL`.

**Only the last piece queues the DOWN transfer.** `FORCED` — so the last piece is also a prefill
transfer trigger and passes through the gate of §17.

---

## 15. Group formation

Three **independent** sizes. `FORCED` by the protocol: a `D PROC` may mix members from different
`D PRE` groups and different UP transfers, and a `D POST` may mix members from different `D PROC`
groups. The three columns have independent curves and independent clamps, so there is no reason for
the three optimal sizes to be equal.

```
D PRE   : across ALL remotes, size = min( |ready ∩ A|, max(m_pre , m*_dpre_column) )
D PROC  : within remote k,    size = min( |ready on k| , max(m_proc, m*_dproc_column) )
D POST  : across ALL remotes, size = min( |ready|      , max(m_post, m*_dpost_column) )
all sizes are additionally floored at min(m_io_dynamic, |ready|)
```

**Always group `D PRE` and `D POST` across remotes.** `DERIVED` — a `D PRE` spanning `r` remotes
enqueues the same `r` UP transfers as `r` separate `D PRE` tasks would, but pays `S` once. The
saving is pure. There is no counter-consideration.

**Member selection.**

```
primary   : ascending rem̂(tokens_i)          — only when nFin ≥ N_conf   [SPECULATIVE, ablatable]
fallback  : arrival order
starvation: any ready member with passOver ≥ 8 is force-included
banned    : slack-ascending, hazard-descending, time-since-last-token, virtual runtime,
            or any other rotation of the ready pool
```

**WHY the primary key is `ascending rem̂`.** By S1, `Σ span` over started requests is a sum of flow
times, and the policy minimising a sum of flow times with known sizes is shortest-remaining-first.
`rem̂` is the best available proxy. **WHY it is marked speculative:** it only binds when the ready
pool exceeds the group cap, which at `|A| ≈ N*` is uncommon; the gain is second-order and the
estimator is weak. Implement it behind one switch and ablate it first.

**WHY the rotations are banned.** They implement round-robin over the ready pool. By S1 gap variance
is not scored, so the entire benefit they target does not exist, while the cost — `tpot` inflated by
`pool/m` — is real. This was the largest single error in the prior research corpus.

**Never commit a cohort.** A group is a *sweep* of whoever is ready at this instant. Nothing is ever
reserved for a member that might finish first.

---

## 16. Wait-or-fire

**You cannot wait `Δ`. You can only wait until the next frame.** There is no self-wake, so the only
available wait is "idle this resource and re-decide when the next event arrives". `FORCED`

```
fire_or_wait(resource, ready_count, target_size):
  if ready_count ≥ target_size                                   → FIRE
  if ready_count ≥ m_io_dynamic and ready_count ≥ m_floor_col    → FIRE   (already efficient)
  t_wake = min completion time over ALL in-flight tasks AND ALL queued transfers
  if t_wake does not exist                                       → FIRE   (waiting IS the stuck state)
  if the event at t_wake cannot add a member to THIS pool        → FIRE   (dominated; no arithmetic)
  Δ = t_wake − t
  BENEFIT = (S + τ(step, ready)) / ready − (S + τ(step, ready+g)) / (ready+g)   per member,
            where g = members the t_wake event will add, times the members served
  COST    = Δ · ( n_span·P_TPOT + n_pend·P_TDR )
            + Δ · (this resource is the throughput bottleneck ? marginal tp term : 0)
  if BENEFIT ≤ COST                                              → FIRE
  if deferred already W_max consecutive frames                   → FIRE   (anti-starvation)
  otherwise                                                      → WAIT one frame
```

> **RULE R6 — bounded, relevance-filtered waiting**
> **WHY.** Larger groups amortise `S` and `lat`, but every millisecond of waiting is charged to both
> populations at exactly the prices of §10.
> **TRIGGER.** A free resource with fewer ready members than the target size.
> **ACTION.** As above.
> **FAILURE PREVENTED.** (a) Waiting for an event that cannot help — the single most common source
> of pure idle in reactive schedulers, and the cause of the "many XDN, no TDN" trap (case 38).
> (b) The stuck state: waiting with nothing in flight is fatal, and the first test forbids it.
> **AVAILABLE INFORMATION.** Exact `t_wake` (durations are echoed and the transfer formula is closed
> form), exact ready counts, exact prices.
> **IF ESTIMATE IS WRONG.** `g` (how many members the next event adds) may be over-estimated; the
> `W_max` clamp bounds the damage to `W_max` frames.
> **TRADEOFF.** Smaller groups (more `S` paid) versus latency.
> **CONFIDENCE.** 0.85 — `DERIVED`.

**Interaction with the liveness guard.** A deliberate wait is safe **exactly when something is in
flight**, which is the same condition the liveness guard checks. If nothing is in flight the guard
fires a task, which is correct — waiting there would be the stuck state. Therefore the "intentional
idle bit" proposed by the cross-component research is **unnecessary**: no bit, no generation stamp,
no race. `DERIVED`

---

## 17. The prefill big-object gate

Transfers are automatic and FIFO — no priority, no cancellation, no reordering. But every transfer
is triggered by a task whose start time you choose, so there are exactly four enqueue-control points:

| Queue | Transfer | Enqueued when | Controllable? |
|---|---|---|---|
| UP | prefill, `len = Lin` | `P PRE` completes | **yes** — by when you start `P PRE` |
| UP | decode, `len = m_k` | `D PRE` completes | never valve — it is on the metered path |
| DOWN | prefill, `len = Lin` | the **last** `P PROC` piece completes | **yes** |
| DOWN | decode, `len = m` | `D PROC` completes | never valve |

> **RULE R9 — hold a prefill transfer that would head-of-line a live decode wave**
> **WHY.** With `Lin = 4096`, `bpt = 10⁶`, `bw = 0.001` one prefill transfer takes `3.3·10⁷ ms` and
> a one-token transfer takes `8·10³ ms`: a single prefill enqueue can delay every decode transfer
> behind it by four thousand token-times, adding that delay to the span of every mid-span request.
> **TRIGGER.** A task about to be emitted would enqueue a prefill transfer of duration
> `X = xfer(Lin)`, **and** `X > xfer(m_k_current)` (it is larger than one decode wave), **and**
> at least one member of `A` is mid-span and awaiting a transfer in that direction.
> **ACTION.** Apply R2 with `d_P := X` against the decode side; if prefill loses, hold the task for
> one frame. Force-release when: this request has been held for a cumulative `ρ_hold·SLO1`; or its
> own projected TDR has no slack (`tdr_proj·(1+μ) ≥ SLO1`); or the direction would otherwise be idle
> with no decode demand; or the liveness guard needs it.
> **FAILURE PREVENTED.** Downlink and uplink head-of-line blocking (cases 1, 2, 3, 5, 13, 41, 43,
> 49, 50).
> **AVAILABLE INFORMATION.** Exact queue contents, exact transfer durations, exact `A` membership.
> **IF ESTIMATE IS WRONG.** Over-holding costs TDR and is bounded by `ρ_hold·SLO1`; under-holding
> costs the span inflation the rule exists to prevent.
> **TRADEOFF.** `tdr` against `tpot`, priced explicitly.
> **CONFIDENCE.** 0.70 — mechanism `DERIVED`, trigger `MODEL`. Ablate this before anything else if
> `tdr` regresses.

**Note on when prefill transfers are free.** Before any request has reached `P POST`, `n_span = 0`,
so `P_TPOT = 0` and R2 always releases prefill. The old "OPENING phase, never valve" rule is
therefore a consequence of the price and needs no phase machine. `DERIVED`

**Do not run two pricing systems on one budget.** R9 uses the same prices as R2, evaluated after
this frame's local-machine decision, so it sees the post-admission budget. A second, independently
tuned valve (sojourn targets, virtual queues, dual ascent) would double-spend the TDR budget for no
benefit.

---

## 18. Safety kernel — liveness, legality, fallback

By S7 this section outranks every scoring rule in the document.

### 18.1 The exact liveness rule

```
respond with 0 assignments   ⟺   inflight > 0   OR   no unfinished request exists

inflight = (tasks assigned whose TDN has not arrived) + (transfers queued whose XDN has not arrived)
```

`inflight` is computed **entirely from the scheduler's own actions**, so this rule is exact, not
heuristic. `DERIVED`

If the plan is empty, `inflight == 0`, and unfinished requests exist, a legal task **always** exists:
with nothing in flight no machine is busy, so every unfinished request's next task has its
predecessor satisfied. Inject one, choosing by the fallback ladder of §10.3 (which is score-aware
and costs nothing extra):

```
1. any D POST        (produces tokens, triggers no transfer)
2. any D PROC        (already holds link bytes in flight)
3. any D PRE, size = min(ready, m_pre)
4. any P POST
5. any P PRE
6. any P PROC piece
```

The statement does note that *while future arrivals remain*, responding with 0 is safe, because
time advances to the next arrival. That is true and useless: `R` is never announced and there is no
end-of-stream signal, so "future arrivals remain" is precisely the one thing that cannot be known.
The rule above is therefore deliberately conservative — it never waits on a hypothetical arrival. Its
entire cost is that, during a genuine lull, it may start one task slightly earlier than an oracle
would; its benefit is that the stuck state becomes unreachable rather than merely unlikely.

### 18.2 Print-time legality sweep

Immediately before printing, re-validate **every** assignment against post-ingest state:

```
machine is free per the post-ingest free-set                     (including last-line TDNs)
at most one assignment per machine in this response
every member: has arrived, is not FIN, is not in another in-flight or same-response task,
              is at exactly this step of exactly this iteration
sticky remote matches for P PROC / P POST / D PROC; P PRE remote in [0,K)
piece range non-empty, within [0,N_L], ascending, gap-free, last ends exactly at N_L
group m ≥ 1 with distinct ids
n ≤ K+1
```

Any failure ⇒ **drop that assignment** and raise the fallback flag. If dropping empties the plan
while `inflight == 0`, re-run the liveness guard.

### 18.3 Latched fallback

```
TRIGGERS: echoed duration or task spec does not match my record
          an XDN that does not match my shadow-queue head
          an event for a request/machine in an impossible state
          an assignment dropped by the legality sweep
          the per-frame time budget exceeded twice
ACTION  : latch permanently (never un-latch mid-run) into:
          immediate dispatch, never idle a free machine, groups = whatever is ready,
          no waiting, no valve, no splitting (full pieces), round-robin binding
```

This policy is provably legal and provably live: it never idles while legal work exists, so
`inflight > 0` whenever work remains. **A slow legal 600 beats a brilliant illegal 0, and by S7 the
illegal outcome is correlated across all twenty final tests.** `DERIVED`

---

## 19. Frame-budget and wall-clock guard

Events per decode wave ≈ `2 + 3·Keff`. With `ΣLout = 2·10⁵`, `K = 8` and `m = 1` that is `5·10⁶`
frames against a `2·10⁶` cap and a 15 s wall clock. A timeout is a correlated zero (S7).

```
static floor:   m_io_static = max(1, ceil( 2e5·(2+3K) / 1.5e6 ))          ≈ 4 at K = 8

dynamic escalation (checked every 1024 frames):
    frames_seen > 6.0e5  or  cpu_elapsed > 6 s   →  m_io_dynamic = max(m_io_dynamic, 4)
    frames_seen > 1.0e6  or  cpu_elapsed > 9 s   →  m_io_dynamic = max(m_io_dynamic, 16),
                                                    disable P PROC splitting
    frames_seen > 1.5e6  or  cpu_elapsed > 12 s  →  m_io_dynamic = max(m_io_dynamic, 64),
                                                    latch the fallback with large groups
```

> **RULE R11 — budget escalation outranks all scoring logic**
> **WHY.** S7. There is no partial credit for an unfinished test.
> **TRIGGER.** Observed frame count or observed CPU time, never an estimate of `ΣLout`.
> **ACTION.** Raise the group-size floor; then stop splitting; then latch.
> **FAILURE PREVENTED.** Case 39 and every transfer-dominated test with tiny task times.
> **AVAILABLE INFORMATION.** Frame counter and a monotonic clock — both exact.
> **IF ESTIMATE IS WRONG.** It is not an estimate. The ladder only ever activates under real risk,
> so on tests that were never in danger it is inert.
> **TRADEOFF.** Raising the group floor forces `|A| ≥ floor` and can raise `tpot` — accepted,
> because the alternative is a zero.
> **CONFIDENCE.** 0.95 — `DERIVED`.

Because escalation is driven by *observed* pressure rather than by a predicted `ΣLout`, it never
penalises a test that does not need it. This is strictly better than the previous design's
`m_io = 5·ΣLout_est/F_target`, which required an estimate of a hidden quantity.

---

## 20. Priority hierarchy — what wins when rules conflict

```
1  LEGALITY          drop anything illegal                                       §18.2
2  LIVENESS          never create a stuck state                                  §18.1
3  BUDGET            frame / wall-clock escalation                               §19
4  WORK CONSERVATION never idle the throughput bottleneck (R3, confidence-gated) §13
5  ADMISSION         hold |A| at its target; never evict a started request       §11
6  PRICE             R2 marginal-price class choice, hysteresis η                §10
7  WITHIN-CLASS      downstream first; SPT + aging in prefill; group sizes       §13,§15
8  REFINEMENT        R8 split, R9 transfer gate, R6 waiting                      §14,§17,§16
9  TIE-BREAK         smaller duration → lower load[k] → arrival order → lowest index
```

Levels 1–3 are hard constraints. Level 4 is gated: the override fires only when the same resource
has been the utilisation argmax for `W_bn = 4` consecutive epochs **and** leads the second by a
margin — a single shared "bottleneck confidence" value computed once per epoch and read by R3, R6
and the admission controller. No module computes its own bottleneck test. This is the one
consolidation kept from the cross-component hypotheses (H-CC4), because it *removes* code rather
than adding it.

**Free ordering levers, zero cost.**
* Tasks assigned in one response that complete simultaneously enter the FIFO in **your printed line
  order** — print the token-producing / decode-triggering assignment first.
* One `D PRE` spanning `r` remotes enqueues its UP transfers in **increasing remote index**. With
  `lat = 50` and `r = 8` that is up to `350 ms` of systematic skew. Order the group so that the
  remote holding the most mid-span members has the lowest index.

---

## 21. Estimation methodology

Every estimator below is either exact or an explicit lower bound with a stated bias.

```
tdr_proj  = ( Σ_{done} (tPPost_i − a_i)  +  n_pend·t − Σ_{pending} a_i )
            / ( n_done + n_pend )
```
This is an **exact lower bound on the final `tdr`** given the current state: it charges every
pending request for the wait it has already accrued. It is far less biased than the mean over
completed requests only, which systematically under-reports because fast requests finish first. Cost:
two running sums. `DERIVED`

```
tpot_proj = (n_span > 0 or gap_count > 0) ? max( span_sum / max(1, gap_count), RT_ewma ) : 0
```
The `max` with `RT_ewma` reflects that each mid-span request will contribute further gaps of about
`RT`. When every request has `Lout = 1`, `n_span` is never positive and `gap_count` stays 0, so
`tpot_proj = 0` exactly as the statement requires. `MODEL`

```
tp_run    = tokens_total / max(ε, t − firstArrival)
RT_ewma   ← 0.9·RT_ewma + 0.1·(t − tPrevToken_i)   on every token of a request with tokens ≥ 2
u_x       = busy_time_of_x_in_epoch / epoch_length                 (exact; epoch = 256 frames)
R̂         = highest rid seen + 1                                   (lower bound)
Ĝ         = Σ_i max(0, tokens_i − 1)                               (lower bound)
rem̂(k)    = empirical mean residual life from histLout             (§12)
load[k]   = Σ_{i bound to k, unfinished} w_i                        (§12) — the ONE residual object
```

**Confidence gating.** A single flag

```
mature = (nFin ≥ N_conf) and (gap_count ≥ N_conf)
```

gates *every* estimator-driven refinement: `rem̂` weights in `load[k]` (else all weights equal), the
residual form of the end-game lift (else the count form), and the `rem̂` selection key in §15 (else
arrival order). One flag, one threshold, all consumers. Prices (R2) are **not** gated, because
`n_pend` and `n_span` are exact and the denominators only shift the class boundary by a constant.

**Utilisation is exact, not laggy.** The scheduler knows exactly when every machine and every
transfer starts and ends, because it assigns the tasks and the durations are echoed and the transfer
formula is closed-form. The prior design classified `u_*` as "reactive, laggy, never a per-frame
decision"; that under-rated a signal that is in fact exact up to the current instant. It is still
averaged over an epoch before use, to avoid reacting to a single task boundary.

---

## 22. Parameters — definition, derivation, value

Nine constants. Every one has a stated phenomenon, a direction of effect, and a safe range.

| # | Symbol | Controls | Default | Range | Derivation | Effect of increasing |
|---|---|---|---|---|---|---|
| 1 | `Λ` | end-game admission lift threshold (R10) | `4` | 2–10 | none — genuinely tuned | ↑ protects makespan, ↓ protects `tpot` |
| 2 | `μ` | binary-mode margin and virtual `dist_base` | `0.15` | 0.05–0.30 | none | ↑ safer under `dist_base = 0`, ↓ throughput |
| 3 | `η` | price hysteresis band (R2) | `0.10` | 0.05–0.25 | none | ↑ more stable class choice, slower adaptation |
| 4 | `γ` | prefill aging trigger as a fraction of `SLO1` (R13) | `0.5` | 0.25–0.9 | score-unit | ↑ later forcing, worse worst-case TDR |
| 5 | `σ_split` | max split overhead as a fraction of piece work (R8) | `0.25` | 0.1–0.5 | derives `n_max` | ↑ more pieces allowed |
| 6 | `ε_idle` | idle fraction that triggers admission growth | `0.05` | 0.02–0.15 | none | ↑ slower growth of `|A|` |
| 7 | `W_max` | max consecutive wait deferrals (R6) | `2` | 1–4 | none | ↑ bigger groups, ↑ latency |
| 8 | `ρ_hold` | max cumulative hold of one prefill as a fraction of `SLO1` (R9) | `0.25` | 0.1–0.5 | score-unit | ↑ protects `tpot`, ↓ protects `tdr` |
| 9 | `N_conf` | `FIN`s / gaps before estimator-driven refinements engage | `20` | 10–50 | none | ↑ safer early, slower adaptation |

Secondary structural constants that are **derived, not tuned**: `m*_c` per column (§9.2), `n_max`
(from `σ_split`), `m_io_static` (from the frame cap), `T_star = 8` (remote starvation bound),
`W_bn = 4` (bottleneck confidence window), `ADM_EPOCH = 256` frames, `A_target0`, `m*`, `Keff` (all
from the grid).

**Highest sensitivity, in order:** `A_target` (it *is* the latency/throughput trade-off), the budget
ladder (a zero/non-zero switch), `Λ`, `μ`.

**Tuning discipline.** One lever per preliminary submission; write the predicted sign **before**
submitting; if the sign is wrong, the *model* is wrong — fix the model, not the constant. Never
auto-tune on the 50 corner cases; they are mechanism probes, not a training set.

---

## 23. Component interactions

```
        ┌──────────────── one residual object: load[k], rem̂ ───────────────┐
        │                                                                  │
  binding (R7) ──► per-remote composition ──► remote arbitration (R2/§14)  │
        ▲                                             │                    │
        │                                             ▼                    │
  admission (R1/R10) ◄── |A|, parked ────► group sizes (§15) ──► RT_ewma ──┘
        ▲                                             │
        │                                             ▼
  utilisation epoch ──► bottleneck confidence ──► R3 override, R6 cost, growth gate
        ▲                                             │
        │                                             ▼
   n_pend / n_span (exact) ──► prices (§10) ──► local (R2), remote (R2), transfer gate (R9)
```

**Loops that exist, and why each is stable.**

1. *Admission → `RT` → `N*` → admission.* Growing `|A|` raises measured `RT` (queueing), which would
   raise `N*` and invite more growth. Broken because growth is gated on **observed idleness of the
   bottleneck**, which disappears as soon as `|A|` is sufficient. `MODEL`
2. *Binding → residual → binding.* Immediate self-update at bind time means the loop has no lag;
   without it, several bindings in one burst would all see the same stale minimum and herd.
   `DERIVED`
3. *Prices → class choice → populations → prices.* Choosing prefill drains `n_pend` and raises
   `n_span`, which then favours decode. This is negative feedback and is the mechanism working as
   intended; `η` prevents chatter at the crossover.
4. *Hold (R9) → slower prefill → smaller `|A|` → lower decode demand → less holding.* Negative
   feedback, bounded by `ρ_hold`.
5. *Split (R8) → more remote tasks → more residual on that remote → binding avoids it → fewer
   decode members → hard-no-split branch fires → fewer splits.* Negative feedback. The
   cross-component analysis feared a positive "forced-P → exclusion → more forced-P" cycle; that
   cycle required a *separate* residual estimator inside the binder that counted forced prefill work
   as permanent load. With one shared object in which prefill-pending work carries weight `rem̂_0`
   (not the piece durations), the cycle does not close. `DERIVED`

**Interactions deliberately removed.** Two lift mechanisms sharing one cap (§11.2); two pricing
systems sharing one TDR budget (§17); three residual estimators sharing one `FIN` stream (§7); five
modules each computing their own bottleneck argmax (§20); two snapshots of ready-membership (§8,
single mutation point per frame).

---

## 24. Corner-case behaviour

Grouped by phenomenon, because the point is the generalisation and not the fix. Cases refer to the
50-case adversarial set.

| Cases | Phenomenon | What the policy does | Residual risk |
|---|---|---|---|
| 1, 3, 5, 31, 35 | UP/DOWN FIFO contention | R1 caps how many decode transfers can exist at all; R9 keeps huge prefill transfers out of a live decode wave; larger `m_k` pays `lat` once for more tokens | if bytes genuinely dominate, nothing helps — `tp_link_abs` says so honestly and the grid stops paying for throughput |
| 2, 18, 41, 46 | one huge prefill blocks everything | R8 sizes pieces to the next due decode landing; R9 gates the last piece's DOWN transfer; R2 prices the unsplittable `P PRE`/`P POST` by duration | `N_L = 1` leaves only R2 and R9 |
| 4, 26, 29 | burst arrival flood | prefill the burst while `n_span = 0` (free by S1), then park all but `A_target`; R7's immediate self-update spreads the burst without a burst detector | none material |
| 6, 7, 33, 39 | local machine and `S` domination | `m*_c` maximises `m/(S+τ)` per column; `D PRE`/`D POST` always group across remotes; budget ladder raises the floor | if `S` is huge and `SLO2` tight the objectives genuinely conflict; the grid resolves it by scoring both |
| 8, 28, 30 | fragmented or trickling arrivals | R6 fires whenever the next event cannot enlarge the pool; `W_max` bounds every wait; admission growth is silent when there is no parked work | over-waiting is structurally impossible |
| 9, 48 | mixed short/long, hidden long tail | run-to-completion keeps long requests resident while short ones churn; R7 spreads residual; R10 lifts the cap before the tail | binding is irrevocable, so a pathological `Lout`↔arrival-order correlation can still hurt |
| 10, 13, 19, 32 | prefill-dominated compute | R2 prices prefill against decode continuously; R3 keeps remotes fed; R7 spreads `P PROC` load | none material |
| 11, 12, 15 | hidden `Lout` imbalance | `load[k]` with `rem̂` weights; ties by rotation; `Keff` from the grid | `rem̂` is weak before `N_conf` `FIN`s; until then the rule is plain JSQ |
| 14, 50 | `K = 1` | `Keff = 1`; splitting is the only interleave lever; `|A|` bounded by that remote's rate | serialisation is real; expect a reduced but not collapsed score |
| 16, 20 | over-splitting | hard-no-split when no decode member is bound to that remote; `n_max` caps overhead at `σ_split` | none |
| 17 | splitting to interleave | piece sized to the exact predicted landing time of the next decode UP transfer | none |
| 21, 44 | tight SLO vs large batches | the grid maximises the **actual** score over `(m, Keff, |A|)`; smaller `|A|` is preferred on ties | model error in `RT`, corrected by the online re-grid with `RT_ewma` |
| 22 | `w_c = 0` | prices vanish; fallback ladder plus R3; `A_target` grows on any observed idle | none |
| 23 | `dist_base = 0` | `μ` margin in the grid and a virtual gradient in the prices; never boundary-ride | one pathological late arrival can still zero it; the margin is the only defence |
| 24 | all `Lout = 1` | `n_span` never becomes positive, so the whole `tpot` half switches itself off with no detector | none |
| 25, 34, 49 | non-monotonic or sparse table | per-column curves, both clamps, `m*_c` by direct argmax — no monotonicity assumed anywhere | none |
| 27, 36, 38, 40 | protocol and stuck-state traps | exact liveness rule; frames containing only `XDN` still schedule; the legality sweep enforces one task per resource | none — these sit at priority levels 1–2 |
| 37 | `FIN` in the same frame | `FIN` applied in phase 2 step 4, before any decision, purging `A`, ready lists and `load[k]` | none |
| 39 | frame-rate blowup | observed-pressure escalation ladder; `O(K + Δstate)` per frame; the grid runs at most every 4096 frames | none |
| 42, 43, 45, 47, 49 | everything at once | the policy is priced rather than case-based, so it degrades continuously instead of falling off a rule boundary | honest expectation: improved, not solved |

**Two cross-cutting axes the 50 only reveal in aggregate.**

* *Tail owner* (15, 27, 47, 48, 50). `tp`'s denominator is a single `max` over the last token time.
  One late-admitted long request craters it. Handled by R10, not by per-case logic.
* *Repeated bursts* (4, 26, 29). The second burst's binding decisions are made against a load signal
  that has not converged since the first. Handled by the bind-time self-update in R7.

---

## 25. Adversarial attack and remaining weaknesses

Constructed by asking: *what would I build to destroy this policy?*

1. **`SLO2` so tight that `SLO2·tp_max < Keff`.** The working set cannot cover one request per
   remote, so remotes must idle to meet TPOT. **Handled** — the grid evaluates `|A| < K` against the
   real score and accepts the throughput loss when `w_c` pays for it; and `Keff` can shrink to match.
   A hard-coded "never idle a remote" would fail here, which is why R3 is gated on `w_tp > 0`.
2. **`Lout` perfectly correlated with arrival order** (all long requests arrive last). FIFO admission
   means they are admitted last and run partly alone. **Partially handled** by R10. `Λ` is the knob.
   **Named residual risk.**
3. **A table where `decode_post` is superlinear while `decode_pre` is sublinear.** Forces
   `m*_post ≠ m*_pre`. **Handled** by three independent sizes; a single-`m` policy is wrong on at
   least one stage. Note this also invalidates the frequently-stated rule "`D POST` should always
   take every ready member" — with a superlinear `decode_post` that is wrong, and §9.2's argmax gets
   it right.
4. **`N = 2` rows at sizes 1 and 4096 with durations `0.001` and `10⁴`.** Interpolation makes
   per-token cost roughly flat, so `m` is nearly free and the binding constraints become the budget
   ladder and the link. **Handled** — no rule assumes a knee exists.
5. **All 2000 arrive at `t = 0`, `w_c = 1`, `dist_base > 0`, `SLO1` tight.** Optimal is to prefill as
   fast as the local machine allows and decode `N*` at a time. R2 produces exactly that, because
   `n_span` starts at 0 and grows only as requests are admitted.
6. **A single request, `Lout = 512`, `K = 1`, `N_L = 64`.** `|A| = 1`, `tpot = RT` at its floor, and
   the only lever is minimising `RT`. Every wait rule degenerates to "fire now"; R8 interleaves the
   prefill pieces with nothing, so it takes the full piece. **Handled trivially.**
7. **Oscillation attack:** parameters tuned so `ex_tdr ≈ ex_tpot` throughout, flipping the gradient
   every frame. **Handled** by `η` and by never applying two corrections in one frame.
8. **Starvation attack:** an endless stream of tiny-`Lin` requests plus one `Lin = 4096`. SPT would
   starve it forever. **Handled** by the `γ·SLO1` aging override — and the cost of leaving it
   starved is not `1/R` of the mean but its full unbounded TDR, which is why the clamp is mandatory.
9. **Frame-budget attack:** `ΣLout = 2·10⁵` with a table making `m = 1` optimal on every column.
   **Handled** by the escalation ladder at priority level 3. Accepted cost: `tpot` rises.
10. **`R = 1`, `Lout = 1`.** Six tasks, no grouping, no waiting. Every wait rule degenerates to fire;
    the liveness guard guarantees no stuck state.
11. **A test where the throughput bottleneck flips mid-run** (e.g. prefill-bound early, link-bound
    late). `W_bn = 4` epochs of confidence delays the switch. **Partially handled**; the delay is
    bounded and the price rule is unaffected because it uses populations, not bottleneck identity.

### Known remaining weaknesses — stated, not hidden

* **`Λ` and the end-game lift are unvalidated.** The right threshold depends on the hidden `Lout`
  distribution. This is the largest single tuning risk in the design.
* **`R̂` and `Ĝ` are lower bounds with different biases.** The class boundary in R2 is therefore
  shifted by an unknown constant. Hysteresis contains it; it does not remove it.
* **The offline `RT` model ignores queueing and the local machine's prefill share.** `A_target0` is
  therefore optimistic; the AIMD controller and the online re-grid with `RT_ewma` are what make this
  survivable.
* **Binding is irrevocable and `Lout` is hidden at bind time.** No policy can fully solve
  case 11/12-style adversarial correlations; `load[k]` only reduces the variance.
* **R9's estimate of "decode demand in this direction" is coarse.** It over-holds when the mid-span
  members are all already past their transfer stage.
* **The `rem̂` selection key in §15 is speculative** and should be the first thing ablated.
* **No mechanism defends against a test where the *only* way to score is a global reordering
  discovered by lookahead.** Per-frame search is unaffordable (§26); this design is deliberately
  myopic-plus-feedback.

---

## 26. Computational complexity

| Stage | Cost | Note |
|---|---|---|
| Offline curve build | `O(N log N + 6·4096)` | once |
| Offline grid | `~22 × 8 × 10 ≈ 1800` evaluations | once, plus at most every 4096 frames |
| Frame ingest | `O(e)` | `e` = events in the frame |
| `FIN` handling | `O(512)` for the `rem̂` suffix sums | ≤ 2000 times per run |
| Admission | `O(admitted)` amortised | intrusive list + deque |
| Binding | `O(Keff)` | `Keff ≤ 8` |
| Group formation | `O(group size)` | ready sets are vectors; no sorting on the hot path |
| Local/remote arbitration | `O(K)` | a handful of comparisons |
| Legality sweep | `O(n·group size)`, `n ≤ K+1` | |
| **Per frame** | **`O(K + e + group size)`** | no scan of `R`, no search, no sorting |

Memory: `2000` request records, two shadow deques bounded by the number of in-flight transfers, a
`513`-entry histogram, six curves of at most `4096` points. Far inside 256 MB.

**I/O is the real cost at `10⁶` frames.** Use `ios::sync_with_stdio(false)`, `cin.tie(nullptr)`, a
hand-rolled unsigned/double reader, and one output buffer flushed once per response. At the frame
counts this problem reaches, I/O discipline is the difference between finishing and a correlated
zero.

Explicitly rejected on complexity grounds: per-frame grid search or rollout, bipartite matching for
group formation, min-cost flow for binding, and any per-frame `O(R)` scan.

---

## 27. Implementation-ready pseudocode

C++-flavoured. Types are illustrative; every branch that matters is spelled out.

### 27.1 Configuration and derived plan

```cpp
// ── read once ────────────────────────────────────────────────────────────────
int    K; double S, lat, bw; long bpt; int NL;
double SLO1, SLO2, tpUB, tpBase, distBase, wTp, wC;

struct Curve { vector<int> x; vector<double> y; };   // sorted, non-missing only
Curve col[6];                                        // PPRE PPROC PPOST DPRE DPROC DPOST

double tau(int c, double x) {                        // clamped piecewise linear
    const Curve& q = col[c];
    if (x <= q.x.front()) return q.y.front();         // CLAMP BELOW  → m_floor effect
    if (x >= q.x.back())  return q.y.back();          // CLAMP ABOVE  → take everything
    int j = upper_bound(q.x.begin(), q.x.end(), (int)x) - q.x.begin();   // q.x[j-1] < x <= q.x[j]
    double t = (x - q.x[j-1]) / double(q.x[j] - q.x[j-1]);
    return q.y[j-1] + t * (q.y[j] - q.y[j-1]);
}
double xfer(double len) { return lat + 8.0*len*bpt/(bw*1e6); }

// ── derived ──────────────────────────────────────────────────────────────────
int    mStar[3];        // argmax of x/(S+tau) for DPRE, DPROC, DPOST
int    mPre, mProc, mPost, Keff, Atarget;
bool   binaryMode;      // distBase == 0
int    mIoStatic, mIoDyn;

void build_plan(double exTdrNow, double rtMeasured /*<=0 if none*/) {
    for (int c = 0; c < 3; ++c) {                    // decode columns 3,4,5
        double best = -1; int arg = 1;
        for (int x = 1; x <= 4096; ++x) {
            double v = x / (S + tau(3+c, x));
            if (v > best) { best = v; arg = x; }
        }
        mStar[c] = arg;
    }
    double bestScore = -1;
    static const int MS[] = {1,2,3,4,6,8,12,16,24,32,48,64,96,128,192,256,384,512,768,1024,1536,2000};
    for (int m : MS) for (int ke = 1; ke <= K; ++ke) {
        int mk = max(1, (m + ke - 1) / ke);
        double tpLocal  = m / (2*S + tau(3,m) + tau(5,m));
        double tpRemote = m / (S + tau(4,mk));
        double tpLink   = m / (ke*lat + 8.0*m*bpt/(bw*1e6));
        double tpMax    = min(tpLocal, min(tpRemote, tpLink));
        double RT = 3*S + tau(3,m) + tau(4,mk) + tau(5,m)
                  + (ke + 1) * (lat + 8.0*m*bpt/(ke*bw*1e6));
        if (rtMeasured > 0) RT = max(RT, rtMeasured);           // never optimistic online
        for (int mult : {1,2,3,4,6,8,12,16,24,32}) {
            int A = min(2000, m*mult);
            double tpHat   = min(tpMax, A / RT);
            double tpotHat = max(RT, A / tpMax);
            double slo2t   = binaryMode ? SLO2*(1-MU) : SLO2;
            double exTpot  = max(0.0, (tpotHat - slo2t)/SLO2);
            double d       = sqrt(exTdrNow*exTdrNow + exTpot*exTpot);
            double wait    = (distBase > 0) ? max(0.0, 1.0 - d/distBase) : (d == 0 ? 1.0 : 0.0);
            double sc = wTp*clip01((tpHat - tpBase)/(tpUB - tpBase)) + wC*wait;
            if (sc > bestScore + 1e-12) {            // strict: ties keep the SMALLER A, m
                bestScore = sc; mPre = mPost = m; mProc = mk; Keff = ke; Atarget = A;
            }
        }
    }
    mIoStatic = max(1, (int)ceil(2e5*(2+3*K)/1.5e6));
}
```

### 27.2 Per-request state and the frame loop

```cpp
enum Stage { NEW, ARRIVED, PPRE_RUN, UP_PRE, PPROC_ARMED, PPROC_RUN, DOWN_PRE, RD_PPOST,
             PPOST_RUN, PARKED, RD_DPRE, DPRE_RUN, UP_DEC, RD_DPROC, DPROC_RUN,
             DOWN_DEC, RD_DPOST, DPOST_RUN, FINISHED };
// readyPPre = requests at ARRIVED;  readyPPost = requests at RD_PPOST.

struct Req {
    Stage st = NEW; double a; int Lin, remote = -1;
    int tokens = 0; double tFirst = 0, tLast = 0, tPrevTok = 0;
    int piece = 0; bool inA = false; int passOver = 0; double heldSince = -1, heldTotal = 0;
};
vector<Req> req;                       // indexed by rid, grown on ARR

bool localBusy; bool remBusy[8];
deque<int> parked;                     // arrival order
vector<int> Aset;                      // working set (intrusive list in practice)
vector<int> rdDPre, rdDPost;           // ready pools, local stages
vector<int> rdDProc[8], armPProc[8];   // ready pools, per remote
struct Xfer { double bytes; bool prefill; vector<int> rids; double fin; int remote; };
deque<Xfer> qUp, qDown; double upFreeAt = 0, downFreeAt = 0;
long long inflight = 0;                // tasks assigned w/o TDN + transfers queued w/o XDN

int main() {
    read_config(); read_table(); binaryMode = (distBase == 0.0);
    build_plan(/*exTdrNow=*/0.0, /*rtMeasured=*/-1);
    for (;;) {
        string line;
        if (!getline_fast(line)) return 0;           // EOF: exit 0, never block, never crash
        if (line == "END") return 0;
        double t = parse_double(line);
        int e = read_int();
        Frame f = read_events(e);                    // read ALL lines first
        apply_frame(t, f);                           // phases 1 and 2
        update_signals(t);
        Plan p = decide(t);                          // phase 3
        legality_sweep(t, p);                        // phase 4
        liveness_guard(t, p);
        emit(p);                                     // print n, lines, flush
    }
}
```

### 27.3 Frame application (two phases)

```cpp
void apply_frame(double t, const Frame& f) {
    // ---- PHASE 1: collect only -------------------------------------------------
    // freedServers, finishedRids, arrivals, tdns, xdns are already separated by read_events.

    // ---- PHASE 2: mutate, in this exact order ----------------------------------
    for (auto& ev : f.arrivals) {                    // 1. ARR
        ensure_size(ev.rid); req[ev.rid] = Req{};
        req[ev.rid].st = ARRIVED; req[ev.rid].a = t; req[ev.rid].Lin = ev.Lin;
        nPend++; sumAPending += t; if (firstArrival < 0) firstArrival = t;
        Rhat = max(Rhat, ev.rid + 1);
    }
    for (auto& ev : f.xdns) {                        // 2. XDN
        deque<Xfer>& q = ev.up ? qUp : qDown;
        if (q.empty() || !matches(q.front(), ev)) { latch_fallback(); }
        else q.pop_front();
        inflight--;
        for (int rid : ev.rids) {
            Req& r = req[rid];
            if (ev.prefill) r.st = ev.up ? PPROC_ARMED : RD_PPOST;   // prefill UP lands → armable
            else            r.st = ev.up ? RD_DPROC    : RD_DPOST;   // prefill DOWN lands → P POST
            if (ev.up && ev.prefill) armPProc[r.remote].push_back(rid);
            if (ev.up && !ev.prefill) rdDProc[r.remote].push_back(rid);
            if (!ev.up && !ev.prefill) rdDPost.push_back(rid);
        }
    }
    for (auto& ev : f.tdns) {                        // 3. TDN
        if (ev.server < 0) localBusy = false; else remBusy[ev.server] = false;
        inflight--;
        switch (ev.kind) {
        case T_PPRE:  { Req& r = req[ev.rid]; r.st = UP_PRE;
                        enqueue(qUp, r.Lin, /*prefill=*/true, {ev.rid}, r.remote, t); } break;
        case T_PPROC: { Req& r = req[ev.rid]; r.piece = ev.le;
                        if (ev.le == NL) { r.st = DOWN_PRE;
                            enqueue(qDown, r.Lin, true, {ev.rid}, r.remote, t); }
                        else { r.st = PPROC_ARMED; armPProc[r.remote].push_back(ev.rid); } } break;
        case T_PPOST: { Req& r = req[ev.rid]; r.st = PARKED; parked.push_back(ev.rid);
                        nPend--; sumAPending -= r.a; tdrSum += (t - r.a); nTdrDone++; } break;
        case T_DPRE:  { for (int k : distinct_remotes(ev.rids))               // ASCENDING index
                            enqueue(qUp, count_on(ev.rids,k), false, members_on(ev.rids,k), k, t);
                        for (int rid : ev.rids) req[rid].st = UP_DEC; } break;
        case T_DPROC: { enqueue(qDown, ev.rids.size(), false, ev.rids, ev.server, t);
                        for (int rid : ev.rids) req[rid].st = DOWN_DEC; } break;
        case T_DPOST: { for (int rid : ev.rids) { Req& r = req[rid];
                            r.tokens++; tokensTotal++;
                            if (r.tokens == 1) { r.tFirst = t; nSpan++; }
                            else { spanSum += (t - r.tLast); gapCount++;
                                   rtEwma = 0.9*rtEwma + 0.1*(t - r.tLast); }
                            r.tLast = t; r.st = RD_DPRE; rdDPre.push_back(rid); } } break;
        }
    }
    for (int rid : f.finishedRids) {                 // 4. FIN — LAST, and unconditional
        Req& r = req[rid];
        r.st = FINISHED; if (r.tokens >= 1) nSpan--;
        erase_from(Aset, rid); erase_from(rdDPre, rid); erase_from(rdDPost, rid);
        erase_from(rdDProc[r.remote], rid); erase_from(parked, rid);
        load[r.remote] -= weight_of(r);              // the ONE residual object
        histLout[min(512, r.tokens)]++; nFin++; recompute_remhat();     // O(512)
        unfinished--;
    }
    framesSeen++;
}
```

**Every `FIN` is applied after every `TDN`, unconditionally, and purges the rid from every container
in one closed loop.** This single ordering constraint is what makes "a finished rid appears in my
response" — an instant zero — structurally impossible.

### 27.4 Signals and prices

```cpp
void update_signals(double t) {
    tdrProj  = (nTdrDone + nPend > 0)
             ? (tdrSum + nPend*t - sumAPending) / (nTdrDone + nPend) : 0.0;
    tpotProj = (gapCount > 0 || nSpan > 0)
             ? max(spanSum / max(1LL, gapCount), rtEwma) : 0.0;
    tpRun    = tokensTotal / max(1e-9, t - firstArrival);

    double slo1t = binaryMode ? SLO1*(1-MU) : SLO1;
    double slo2t = binaryMode ? SLO2*(1-MU) : SLO2;
    exTdr  = max(0.0, (tdrProj  - slo1t)/SLO1);
    exTpot = max(0.0, (tpotProj - slo2t)/SLO2);
    double D  = sqrt(exTdr*exTdr + exTpot*exTpot);
    double DB = (distBase > 0) ? distBase : MU;
    bool live = (D > 0) && (D < DB) && (wC > 0);
    Ghat = max(1LL, gapCount);
    P_TDR  = live ? wC*(exTdr /D)/(DB*SLO1*max(1,Rhat)) : 0.0;
    P_TPOT = live ? wC*(exTpot/D)/(DB*SLO2*Ghat)        : 0.0;

    if (++epochFrames >= 256) { close_epoch(t); }    // utilisations, bottleneck confidence, AIMD
    mature = (nFin >= N_CONF) && (gapCount >= N_CONF);
    budget_ladder();                                  // §19
}

// cost of delaying the OTHER class, per §10.2
inline bool prefer_prefill(double dP, double dD, long nPendPop, long nSpanPop, int& memo) {
    double costPref = dP * nSpanPop * P_TPOT;         // choosing prefill delays decode by dP
    double costDec  = dD * nPendPop * P_TDR;          // choosing decode delays prefill by dD
    if (costPref == 0 && costDec == 0) return memo == 1;             // degenerate → caller ladder
    if (costPref * (1+ETA) < costDec) { memo = 1; return true;  }
    if (costDec  * (1+ETA) < costPref){ memo = 0; return false; }
    return memo == 1;                                                 // hysteresis: hold
}
```

### 27.5 Admission

```cpp
void close_epoch(double t) {
    for each resource x: u[x] = busy[x] / (t - epochStart); busy[x] = 0;
    bottleneck = argmax_x u[x];
    bnStreak = (bottleneck == prevBottleneck) ? bnStreak+1 : 0;  prevBottleneck = bottleneck;
    bnConfident = (bnStreak >= W_BN) && (u[bottleneck] > 1.15 * second_largest(u));

    double idleFrac = 1.0 - u[bottleneck];
    bool workExists = !parked.empty();
    if (idleFrac > EPS_IDLE && workExists)               Atarget += max(1, Atarget/8);
    else if (exTpot >= exTdr && P_TPOT > 0 && idleFrac <= EPS_IDLE)
                                                        Atarget = max(Afloor(), Atarget - 1);
    Atarget = min(2000, Atarget);
    if ((framesSeen % 4096) == 0) build_plan(exTdr, rtEwma);   // online re-grid
}

int Afloor() { return max(1, max(mProc, mIoDyn)); }

void admit(double t) {
    long long resid = mature ? residual_total() : unfinished;
    long long thresh = mature ? (long long)(LAMBDA * Atarget * remHat0) : (long long)(LAMBDA*Atarget);
    if (resid <= thresh) Atarget = max(Atarget, (int)unfinished);      // R10 end-game lift
    while ((int)Aset.size() < Atarget && !parked.empty()) {
        int rid = parked.front(); parked.pop_front();
        Aset.push_back(rid); req[rid].inA = true;
        req[rid].st = RD_DPRE; rdDPre.push_back(rid);
    }
    // NEVER evict. |A| shrinks only on FIN.
}
```

### 27.6 The decision pass

```cpp
Plan decide(double t) {
    Plan p;
    admit(t);

    // ── remotes: independent, at most one task each ────────────────────────────
    for (int k = 0; k < K; ++k) {
        if (remBusy[k] || planned_on(p,k)) continue;
        bool haveD = !rdDProc[k].empty(), haveP = !armPProc[k].empty();
        if (!haveD && !haveP) continue;
        bool doP;
        if (!haveD)      doP = true;
        else if (!haveP) doP = false;
        else if (consecD[k] >= T_STAR) doP = true;                     // starvation bound
        else {
            int mk = min((int)rdDProc[k].size(), max(mProc, mStar[1]));
            double dD = S + tau(4, mk);
            int rid   = armPProc[k].front();
            double dP = S + piece_duration(rid, k);
            doP = prefer_prefill(dP, dD, nPendOn[k], nSpanOn[k], memoRemote[k]);
        }
        if (doP) {
            int rid = armPProc[k].front();
            auto pc = choose_piece(rid, k, t);                          // R8
            if (pc.le == NL && gate_holds_prefill_transfer(rid, /*down=*/true, t)) continue;  // R9
            p.add(PPROC, k, rid, pc.ls, pc.le); consecD[k] = 0;
        } else {
            int cap = min((int)rdDProc[k].size(), max(mProc, mStar[1]));
            if (!fire_or_wait(RES_REMOTE(k), rdDProc[k].size(), cap, t)) continue;   // R6
            p.add(DPROC, k, pick(rdDProc[k], cap)); consecD[k]++;
        }
    }

    // ── local: exactly one task ────────────────────────────────────────────────
    if (!localBusy) {
        bool haveDec = !rdDPost.empty() || !rdDPre.empty();
        bool havePre = !readyPPost.empty() || !readyPPre.empty();
        int  choice  = -1;                                              // 0 = decode, 1 = prefill
        if (!haveDec && !havePre) return p;
        else if (!haveDec) choice = 1;
        else if (!havePre) choice = 0;
        else if (wTp > 0 && tpRun < tpUB && bnConfident && starving_bottleneck_feedable_by(1))
             choice = 1;                                                // R3
        else if (wTp > 0 && tpRun < tpUB && bnConfident && starving_bottleneck_feedable_by(0))
             choice = 0;                                                // R3
        else {
            double dP, dD; int repP = best_prefill(dP), repD = best_decode(dD);
            if (P_TDR == 0 && P_TPOT == 0)                              // §10.3 fallback ladder
                 choice = (!rdDPost.empty()) ? 0
                        : (Aset.size() >= (size_t)Atarget ? 0 : (havePre ? 1 : 0));
            else choice = prefer_prefill(dP, dD, nPend, nSpan, memoLocal) ? 1 : 0;
        }
        if (choice == 0) {                                              // DECODE, downstream first
            if (!rdDPost.empty()) {
                int cap = min((int)rdDPost.size(), max(mPost, mStar[2]));
                if (fire_or_wait(RES_LOCAL, rdDPost.size(), cap, t))
                    p.add(DPOST, pick(rdDPost, cap));
            } else {
                int cap = min((int)rdDPre.size(), max(mPre, mStar[0]));
                if (fire_or_wait(RES_LOCAL, rdDPre.size(), cap, t))
                    p.add(DPRE, pick_ordered_by_remote(rdDPre, cap));
            }
        } else {                                                        // PREFILL, downstream first
            if (!readyPPost.empty()) p.add(PPOST, pick_spt(readyPPost));
            else {
                int rid = pick_spt_with_aging(readyPPre, t);            // R13
                if (!gate_holds_prefill_transfer(rid, /*down=*/false, t))   // R9
                    p.add(PPRE, bind(rid), rid);                        // R7 binds here
            }
        }
    }
    return p;
}
```

### 27.7 Binding, split, gate, wait

```cpp
int bind(int rid) {                                                     // R7
    int best = -1; double bl = 1e300;
    for (int k = 0; k < Keff; ++k) {
        double l = load[k] + tieRot[k]*1e-9;                            // rotation breaks ties
        if (l < bl) { bl = l; best = k; }
    }
    tieRot[best] = ++rotCounter;
    load[best] += remHat0;                                              // IMMEDIATE self-update
    req[rid].remote = best;
    return best;
}

double weight_of(const Req& r) {
    if (!mature) return 1.0;
    return (r.tokens > 0) ? remHat(r.tokens) : remHat0;
}

Piece choose_piece(int rid, int k, double t) {                          // R8
    int rem = NL - req[rid].piece;
    if (NL == 1 || splitDisabled) return {req[rid].piece, NL};
    double full = tau(1, req[rid].Lin) * rem / (double)NL;
    double delta = next_decode_landing_on(k, t);                        // exact if queued, else rtEwma
    if (delta >= full || !any_A_member_on(k)) return {req[rid].piece, NL};   // HARD NO-SPLIT
    int parts = (int)floor(NL * delta / max(1e-9, tau(1, req[rid].Lin)));
    parts = clamp(parts, 1, rem);
    int nMax = 1 + (int)floor(SIGMA_SPLIT * tau(1, req[rid].Lin) / S);   // overhead cap
    parts = max(parts, (rem + nMax - 1) / nMax);
    return {req[rid].piece, req[rid].piece + parts};
}

bool gate_holds_prefill_transfer(int rid, bool down, double t) {        // R9
    double X = xfer(req[rid].Lin);
    if (X <= xfer(max(1, mProc))) return false;                          // not a big object
    long demand = count_A_members_awaiting_transfer(down);
    if (demand == 0) return false;
    if (req[rid].heldTotal >= RHO_HOLD * SLO1) return false;             // force release
    if (tdrProj * (1 + MU) >= SLO1)             return false;            // no TDR slack left
    bool hold = !prefer_prefill(/*dP=*/X, /*dD=*/S + tau(5, mPost),
                                nPend, demand, memoGate);
    if (hold) { if (req[rid].heldSince < 0) req[rid].heldSince = t; return true; }
    if (req[rid].heldSince >= 0) { req[rid].heldTotal += t - req[rid].heldSince;
                                   req[rid].heldSince = -1; }
    return false;
}

bool fire_or_wait(int res, size_t ready, int cap, double t) {           // R6
    if ((int)ready >= cap)                       return true;
    if ((int)ready >= mIoDyn && at_or_above_column_floor(res, ready)) return true;
    double tw = t_wake();                        // min completion over tasks AND queued transfers
    if (tw == INF)                               return true;   // waiting IS the stuck state
    if (!event_can_enlarge_pool(tw, res))        return true;   // dominated
    double dlt = tw - t;
    double benefit = per_member_saving(res, ready, expected_gain(tw, res)) * ready;
    double cost    = dlt * (nSpan*P_TPOT + nPend*P_TDR)
                   + ((res == bottleneckRes && wTp > 0) ? dlt*marginal_tp_term() : 0.0);
    if (benefit <= cost)                         return true;
    if (++deferCount[res] > W_MAX) { deferCount[res] = 0; return true; }
    return false;                                               // WAIT one frame
}
```

### 27.8 Guards and emission

```cpp
void legality_sweep(double t, Plan& p) {
    for (auto it = p.begin(); it != p.end(); ) {
        bool ok = machine_free_post_ingest(it->server)
               && !second_assignment_to(it->server, p)
               && all_members_arrived_not_fin_not_inflight_at_this_step(*it)
               && remote_field_matches_binding(*it)
               && piece_range_legal(*it)          // non-empty, ⊆[0,NL], ascending, gap-free
               && distinct_ids(*it) && it->m >= 1;
        if (!ok) { latch_fallback(); it = p.erase(it); } else ++it;
    }
}

void liveness_guard(double t, Plan& p) {
    if (!p.empty() || inflight > 0 || unfinished == 0) return;
    // A legal task ALWAYS exists here: nothing is in flight, so no machine is busy.
    for (int shape : {DPOST, DPROC, DPRE, PPOST, PPRE, PPROC})
        if (inject_any_legal(shape, p, t)) return;
    latch_fallback();                              // unreachable if state is consistent
}

void emit(const Plan& p) {
    order_lines(p);                                // decode / token-producing first
    out << p.size() << '\n';
    for (auto& a : p) out << a.text() << '\n';     // e.g. "E D PRE -1 3 7 9 12"
    cout << out.str() << flush; out.str("");
    for (auto& a : p) { mark_busy(a); inflight++; apply_optimistic_state(a); }
}
```

`apply_optimistic_state` sets each member's stage to the `*_RUN` variant and removes it from the
ready pool, so no request can appear in two tasks in the same or the next response.

### 27.9 Build order for an implementer

```
STEP 1  Read §2. Nothing else in this document makes sense without S1 and S2.
STEP 2  Frame loop + state machine + legality sweep + liveness guard + latched fallback.
        CHECKPOINT: a LEGAL FINISHER on every test — m = 1, immediate dispatch, RR binding.
        This alone scores; everything after it only improves the number.
STEP 3  §9 offline plan: curves, m*_c, the grid. Free, and it sets every target.
STEP 4  §11 admission control (R1 + R10). The single highest-value scoring change.
STEP 5  §10 prices + §13 local arbitration + §15 group sizes.
STEP 6  §12 binding (R7), §16 wait-or-fire (R6).
STEP 7  §14 split (R8), §17 transfer gate (R9).
STEP 8  Re-read §30 (rejected mechanisms) before every submission.
STEP 9  One lever per preliminary; predicted sign written FIRST.
```

---

## 28. Validation and experiment plan

**There are no experimental results yet.** Every mechanism below is `THEORETICALLY SUPPORTED,
EMPIRICALLY UNTESTED` unless marked otherwise. Experiments are ordered by

```
expected information gain × expected score impact ÷ testing cost
```

| # | Experiment | Change under test | Primary observable | Predicted direction | What it settles |
|---|---|---|---|---|---|
| E1 | Legal-finisher soak on all 22 preliminaries | nothing (step-2 build only) | zero protocol errors, zero timeouts, frame counts | all tests complete | whether the correctness kernel and the frame budget are safe. **Run this before any scoring experiment.** |
| E2 | Admission on/off | `A_target` from §11 vs `A_target = ∞` | `tpot` component and `tp` component **separately** | `tpot` ↓ strongly, `tp` ≈ flat | the central claim S2 of the whole design |
| E3 | `Λ` sweep `{2,4,8,∞}` | end-game lift only | last-token time; `tp` and `tpot` separately | interior optimum | the highest-sensitivity parameter |
| E4 | Price rule vs fixed ladder | R2 vs "prefill until `|A|` full, then decode" | `tdr` and `tpot` separately, class-run lengths | R2 better on mixed weights | whether duration-weighted pricing earns its complexity |
| E5 | Duration term in R2 | `d_P·n_span·P_TPOT` vs `n_span·P_TPOT` | `tpot` spikes after large-`Lin` admissions | duration form removes the spikes | whether deleting the old `R5` maintenance-window rule was safe |
| E6 | Binding ablation | `load[k]` weights on vs all-equal (pure JSQ) | max−min residual across remotes; last-token time | small `tp` gain | whether `rem̂` earns its place |
| E7 | `Keff` sweep `{1, K}` on a high-`lat` test | grid choice vs forced | `RT`, `tpot`, remote utilisation | interior optimum at high `lat` | whether `Keff` is a real lever or noise |
| E8 | R9 gate on/off | prefill transfer hold | `tdr` and `tpot` separately on a link-bound large-`Lin` test | `tpot` ↓, `tdr` ↑ | whether the gate's trigger is calibrated |
| E9 | §15 `rem̂` selection key on/off | group member choice | Σ span, `tpot` | small `tpot` ↓ | the most speculative rule in the design |
| E10 | Budget ladder stress | `ΣLout = 2·10⁵`, tiny durations | frames, wall clock | no timeout | the S7 correlated-zero risk |

**Rules for reading results.** Always compare the two score *components* separately, never the
total: a mechanism that trades `tp` for `tpot` will look neutral in aggregate on one test and
decisive on another. Write the predicted sign before submitting. If a sign is wrong, the model is
wrong — change the model, not the constant.

**Diagnostics worth logging on every run** (cheap, and they make every experiment interpretable):
final `tp`/`tdr`/`tpot` and both components; `|A|` trajectory against `A_target` and `N*`; max−min
`load[k]`; class-choice run lengths; count of R3 overrides, R9 holds, R6 deferrals, R8 splits;
legality-sweep drops by cause; liveness injections; frames and wall clock.

---

## 29. Confidence register

| Mechanism | Basis | Confidence | Ablate if |
|---|---|---|---|
| S1 telescoping identity, and everything it kills | `FORCED` | 0.99 | never |
| Correctness kernel (§18) and budget ladder (§19) | `FORCED`/`DERIVED` | 0.97 | never |
| Two-phase apply with `FIN` last (§8) | `FORCED` | 0.97 | never |
| Bounded working set `A` (R1) | `DERIVED` + `MODEL` controller | 0.88 | `tp` falls while `tpot` is already inside `SLO2` |
| Per-column `m*_c` by direct argmax (§9.2) | `DERIVED` | 0.90 | never |
| Grid over the true objective replacing the mode table (§9.3) | `DERIVED` | 0.85 | a preliminary shows a mode-specific collapse |
| Duration-weighted price rule R2 (§10) | `DERIVED` mechanism, `MODEL` estimators | 0.80 | class-run lengths oscillate or one metric collapses |
| Work-conservation override R3 | `DERIVED` | 0.85 | never (but keep the `w_tp > 0` gate) |
| SPT + score-unit aging R13 | `DERIVED` | 0.85 | worst-case TDR regresses ⇒ lower `γ` |
| Least-residual-work binding R7 | `DERIVED` + `MODEL` | 0.80 | max−min `load` does not improve over pure JSQ |
| Wait-or-fire R6 | `DERIVED` | 0.85 | idle fraction rises |
| Split rule R8 | `DERIVED` no-split branch, `MODEL` sizing | 0.80 | remote utilisation falls with splitting on |
| End-game lift R10 | `MODEL` | 0.75 | `tpot` regresses without a makespan gain |
| Prefill transfer gate R9 | `DERIVED` mechanism, `MODEL` trigger | 0.70 | `tdr` regresses — **ablate this first** |
| `rem̂` selection key in §15 | `SPECULATIVE` | 0.55 | **ablate this second**, or simply ship without it |
| `Keff < K` concentration | `MODEL` | 0.65 | remote utilisation is high and `tp` falls |

---

## 30. Rejected mechanisms, and why

Rejection is the main work of this document. Each item below was proposed somewhere in the research
corpus or in the external-systems material and is deliberately absent.

**Rejected as optimising a quantity that does not exist (S1).**
Virtual-runtime / CFS fairness ranking; cadence smoothing; slack-ascending or
time-since-last-token ranking inside a group; per-token deadlines; straggler promotion within a
group. The score contains no fairness or variance term, and these rankings *are* round-robin over
the ready pool — the single most expensive available mistake.

**Rejected as a second pricing system on the same budget.**
CoDel-style sojourn-target admission as the primary valve; Lyapunov / dual-ascent price updates;
separate `price_admission` / `price_binding` / `price_ordering` (the DistServe "separate objectives"
analogy). The objective has exactly two components and closed-form gradients every frame; one price
function evaluated at three call sites is sufficient and cannot desynchronise. DistServe's real
lesson — that prefill and decode contend — is captured by R2 and R3, not by duplicating the pricing.

**Rejected as unimplementable within the constraints.**
Per-frame rollout or portfolio simulation; bipartite / min-cost matching for group formation; active
BBR-style probing of `N*` by deliberately perturbing `|A|` (it costs score on a live metric under
`dist_base = 0`, where the component is a step function); any lookahead requiring future arrivals or
`Lout`. At `~10⁶` frames the per-frame budget is a few microseconds including I/O (§26).

**Rejected as a discrete classifier that can be wrong and then latch.**
The six-cell mode table with internal weight rewrites (`w_c := 0`, `w_tp := 0`); the five-way
bottleneck regime vote with its own policy per regime; the `all-Lout=1` detector; the `tp_UB` latch
that permanently zeroes `w_tp`. All are regions of the objective the grid already evaluates (§9.3),
and each carries a permanent-latch failure mode that the grid does not.

**Rejected because the general rule already covers it.**
`R5` "large `Lin` is a maintenance window" — subsumed by including duration in R2. `OPENING` phase
"never valve prefill" — subsumed, since `n_span = 0` makes `P_TPOT = 0`. `DRAIN` phase — subsumed by
R10 on a state condition. Separate round-robin binding plus load correction plus burst detector plus
`θ_reb` exclusion — subsumed by least-work-left with a bind-time self-update. "`D POST` always takes
every ready member" — subsumed by, and sometimes contradicted by, `m*_dpost`. "Never split when
`K > 1`" — conflates the interleaving reason with the transfer reason.

**Rejected cross-component hypotheses.** (All from `NEW_HYPOTHESES.md`; none had experimental
support.)

* *H-CC3, intentional-idle bit with a generation stamp.* The race it fixes does not exist once the
  liveness rule is `inflight > 0`: a deliberate wait is safe exactly when something is in flight,
  which is the same condition the guard tests. **Rejected as unnecessary machinery.**
* *H-CC7, snapshot identity contract with generation ids.* Solved for free by having exactly one
  mutation point per frame (§8) and reading live state afterwards. **Rejected as unnecessary.**
* *H-CC2, coordinated cap-lift budget.* There is only one lift mechanism (R10), so nothing needs
  coordinating. **Rejected by construction.**
* *H-CC6, forced-`P` residual credit.* The starvation cycle it patches required the binder's
  residual to count forced prefill work as permanent load; the shared object weights prefill-pending
  work at `rem̂_0` and never at piece durations, so the cycle does not close. **Rejected as
  unnecessary.**
* *H-CC1 (single residual object), H-CC4 (single bottleneck-confidence bit), H-CC5 (single maturity
  flag)* — **accepted**, because all three *remove* code: three residual estimators become one
  (§7, §12), five bottleneck tests become one (§20), and several confidence thresholds become the
  single `mature` flag (§21).

**Rejected external analogies (with the reason, not just the verdict).**

* *CockroachDB / Impala admission control.* The **principle** — admission responds to observed
  pressure rather than a fixed constant — is adopted in §11.1. The **mechanisms** (token grants,
  queue-priority tiers, per-tenant fairness) address multi-tenant fairness, which is absent here.
* *vLLM chunked prefill budgets.* The **principle** — a scheduling budget trades TTFT against decode
  latency — is exactly R2 with durations. A separate "prefill token budget" knob would be a second
  controller on the same trade-off.
* *Sarathi-Serve chunking.* Directly applicable and adopted as R8, but with the cost the paper does
  not pay: here each chunk costs a full `S` of the *remote*, so the overhead cap `n_max` is essential.
* *Power-of-`d` choices.* The motivation is avoiding a global load scan. With `K ≤ 8` and exact
  per-remote state, the full argmin is cheaper than the sampling machinery and strictly better.
  **Principle adopted (route by predicted work, not count); algorithm rejected.**
* *Stale-information load balancing.* The warning is real but the cause is absent: the bind-time
  self-update means the binder never reads a stale count.
* *Feedback control of `Λ` / of every parameter.* Adopted for `A_target` only, where the signal
  (observed bottleneck idleness) is exact and the actuator is fast. Rejected everywhere else,
  because feedback on a noisy signal with a slow actuator oscillates, and each extra loop multiplies
  the interactions that must be reasoned about.

---

## Appendix — one-page summary

```
OFFLINE : build 6 clamped curves → m*_c per decode column → grid over (m, Keff, |A|) on the TRUE
          score expression → m_pre/m_proc/m_post, Keff, A_target0, binaryMode, m_io_static.

PER FRAME:
  read whole frame → apply ARR, XDN, TDN, then FIN last → commit counters
  → admit up to A_target from the parked pool in arrival order (lift the cap near the end)
  → each free remote: D PROC vs P PROC by the price rule (starvation bound T*), split by R8
  → local machine: work-conservation override, else the price rule; downstream stage first;
    SPT + aging inside prefill; group sizes from the three columns; wait only if the next event
    can help and the wait is cheaper than the group saving
  → hold a prefill transfer that would head-of-line a live decode wave (bounded by ρ_hold·SLO1)
  → legality sweep → liveness guard (inflight > 0 or nothing unfinished ⇒ 0 is safe) → print, flush

INVARIANTS: never evict a started request · never rank the ready pool by anything rotational ·
            never valve a decode transfer · never forecast Lout for an irreversible decision ·
            never search per frame · legality and liveness outrank every scoring rule.
```
