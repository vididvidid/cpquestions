/*user:vididvidid
*author:yashKumarKasaudhan
*mail:vididvidid@gmail.com
*/
#include<cstdint>
#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<deque>
#include<map>
#include<set>
#include<algorithm>
#include<iomanip>
#include<sstream>
#include<cmath>
#include<chrono>
#include<unistd.h>
#include<cerrno>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
struct Params{
double LAMBDA=1.75;
double MU=0.15;
double ETA=0.10;
double GAMMA=0.5;
double SIGMA_SP=0.05;
double EPS_IDLE=0.05;
int W_MAX=2;
double RHO_HOLD=0.25;
int N_CONF=20;
};
static constexpr int ADM_EPOCH=64;
static constexpr int T_STAR=8;
static constexpr int W_BN=1;
static constexpr int REGRID_INTERVAL=4096;
namespace policy{
struct ClassArbitration{
static constexpr double tdrCliffTrip=0.85;
static constexpr bool chargePendingEdgeSerial=true;
static constexpr bool backpressureBinary=true;
static constexpr int backpressureMinR=16;
static constexpr bool backpressureRemote=true;
};
struct PriceRecovery{
static constexpr double margin=0.85;
static constexpr bool useLittleLawFloor=true;
static constexpr int refreshFrames=64;
};
struct WorkConservation{
static constexpr double tpotCliffTrip=0.85;
static constexpr bool guardEnabled=true;
static constexpr int downFeeders=0;
static constexpr bool requireWholeBottleneckIdle=true;
};
struct RemoteBinding{
static constexpr int prefillMode=3;
};
struct PieceSplit{
static constexpr bool seesReadyDecode=true;
static constexpr bool seesParkedOnRemote=true;
static constexpr bool bottleneckYieldsToReadyDecode=false;
};
struct TransferGate{
static constexpr bool remoteGateEnabled=false;
};
struct Admission{
static constexpr bool growOnFin=false;
static constexpr int shrinkDivisor=8;
};
struct GroupWait{
static constexpr bool seesQueuedFeeder=true;
static constexpr bool latDomTakeAll=true;
static constexpr bool postSeesUpstreamDecode=true;
};
struct RemotePrefill{
static constexpr bool guardEnabled=true;
static constexpr double windowMargin=8.0;
};
struct ProtocolTrust{
static constexpr int xferMismatchLatch=32;
static constexpr int echoMismatchLatch=32;
};
}
static constexpr double RT_ALPHA=0.1;
static constexpr double BN_MARGIN=1.15;
static constexpr double KEFF_UTIL_THRESH=0.8;
static constexpr int BUDGET_CHECK=1024;
static constexpr int PASSOVER_THRESH=8;
enum Stage:uint8_t{
NEW,ARRIVED,PPRE_RUN,UP_PRE,PPROC_ARMED,PPROC_RUN,DOWN_PRE,
RD_PPOST,PPOST_RUN,PARKED,RD_DPRE,DPRE_RUN,UP_DEC,RD_DPROC,
DPROC_RUN,DOWN_DEC,RD_DPOST,DPOST_RUN,FINISHED
};
enum TaskType:uint8_t{T_PPRE,T_PPROC,T_PPOST,T_DPRE,T_DPROC,T_DPOST};
enum Resource:uint8_t{
RES_LOCAL=0,RES_REMOTE0=1,RES_UP=9,RES_DOWN=10
};
struct Piece{int ls,le;};
struct Curve{
vector<int>xs;
vector<double>ys;
double tau(double x)const{
if(xs.empty())return 0;
if(x<=xs.front())return ys.front();
if(x>=xs.back())return ys.back();
size_t hi=(size_t)(upper_bound(xs.begin(),xs.end(),(int)floor(x))-xs.begin());
if(hi==0)return ys.front();
if(hi>=xs.size())return ys.back();
size_t lo=hi-1;
if(xs[hi]==xs[lo])return ys[lo];
double f=(x-xs[lo])/double(xs[hi]-xs[lo]);
return ys[lo]+f*(ys[hi]-ys[lo]);
}
};
struct Req{
Stage stage=NEW;
double arrival=0;
int Lin=0;
int remote=-1;
int tokens=0;
double tFirst=0;
double sptKey=0;
double tLast=0;
int piece=0;
bool inA=false;
long long readyStamp=0;
int skips=0;
double heldSince=-1;
double heldTotal=0;
};
struct XferEntry{
double bytes;
bool isPrefill;
vector<int>rids;
double startTime;
double finishTime;
int remote;
};
struct Assignment{
TaskType type;
int server;
vector<int>rids;
int ls=0,le=0;
int remote=-1;
int m=0;
int emitPriority()const{
if(type==T_DPOST)return 1;
if(type==T_DPROC)return 2;
if(type==T_DPRE)return 3;
if(type==T_PPOST)return 4;
if(type==T_PPROC)return 5;
return 6;
}
static void putInt(string&o,long long v){
if(v<0){o.push_back('-');v=-v;}
char tmp[20];int n=0;
do{tmp[n++]=char('0'+v % 10);v/=10;}while(v);
while(n)o.push_back(tmp[--n]);
}
void appendTo(string&o)const{
const long long cnt=(long long)rids.size();
if(type==T_PPRE){
o+="E P PRE ";putInt(o,remote);o.push_back(' ');putInt(o,rids[0]);
}else if(type==T_PPROC){
o.push_back('C');putInt(o,remote);o+=" P PROC ";
putInt(o,ls);o.push_back(' ');putInt(o,le);o.push_back(' ');
putInt(o,remote);o.push_back(' ');putInt(o,rids[0]);
}else if(type==T_PPOST){
o+="E P POST ";putInt(o,remote);o.push_back(' ');putInt(o,rids[0]);
}else if(type==T_DPRE){
o+="E D PRE -1 ";putInt(o,cnt);
for(int r:rids){o.push_back(' ');putInt(o,r);}
}else if(type==T_DPROC){
o.push_back('C');putInt(o,remote);o+=" D PROC ";
putInt(o,remote);o.push_back(' ');putInt(o,cnt);
for(int r:rids){o.push_back(' ');putInt(o,r);}
}else if(type==T_DPOST){
o+="E D POST -1 ";putInt(o,cnt);
for(int r:rids){o.push_back(' ');putInt(o,r);}
}
o.push_back('\n');
}
};
struct Plan{
vector<Assignment>assignments;
bool usedLocal=false;
bool usedRemote[8]={};
void reset(){assignments.clear();usedLocal=false;for(int i=0;i<8;++i)usedRemote[i]=false;}
void addLocal(Assignment a){assignments.push_back(a);usedLocal=true;}
void addRemote(int k,Assignment a){assignments.push_back(a);usedRemote[k]=true;}
bool empty()const{return assignments.empty();}
auto begin(){return assignments.begin();}
auto end(){return assignments.end();}
void erase(decltype(assignments.begin())it){assignments.erase(it);}
size_t size()const{return assignments.size();}
};
struct ArrEvent{int rid;int Lin;};
struct TdnEvent{int server;TaskType kind;int rid;vector<int>rids;int ls=0,le=0;double dur;};
struct XdnEvent{bool up;int remote;bool prefill;vector<int>rids;double bytes;};
struct Frame{
double t;
vector<ArrEvent>arrivals;
vector<XdnEvent>xdns;
vector<TdnEvent>tdns;
vector<int>finishedRids;
void clear(){arrivals.clear();xdns.clear();tdns.clear();finishedRids.clear();}
};
struct EpochStats{
double busyTime[11]={};
double epochStart=0;
int epochFrames=0;
int bottleneck=-1;
int prevBn=-1;
int bnStreak=0;
bool bnConfident=false;
double util[11]={};
unsigned bnMask=0;
bool bnHas(int res)const{return bnConfident&&res>=0&&(bnMask>>res)&1u;}
};
struct Occupancy{
vector<pair<double,double>>iv;
double openStart=-1;
void addInterval(double a,double b){
if(b<=a)return;
iv.push_back({a,b});
}
void openAt(double a){openStart=a;}
void closeAt(double b){
if(openStart>=0){addInterval(openStart,b);openStart=-1;}
}
double drain(double lo,double hi){
double acc=0;
vector<pair<double,double>>keep;
keep.reserve(iv.size());
for(auto&p:iv){
double a=max(p.first,lo),b=min(p.second,hi);
if(b>a)acc+=(b-a);
if(p.second>hi)keep.push_back(p);
}
iv.swap(keep);
if(openStart>=0){
double a=max(openStart,lo);
if(hi>a)acc+=(hi-a);
}
return acc;
}
};
namespace fastin{
static char buf[1<<16];
static int len=0,pos=0;
static bool eofFlag=false;
inline int getc_(){
if(pos==len){
if(eofFlag)return-1;
ssize_t r=::read(0,buf,sizeof(buf));
if(r<=0){eofFlag=true;return-1;}
len=(int)r;pos=0;
}
return(unsigned char)buf[pos++];
}
inline bool token(char*out,int cap){
int c=getc_();
while(c==' '||c=='\n'||c=='\r'||c=='\t')c=getc_();
if(c<0)return false;
int n=0;
while(c>' '){if(n+1<cap)out[n++]=(char)c;c=getc_();}
out[n]=0;
return true;
}
inline bool readInt(long long&v){
char t[32];
v=0;
if(!token(t,sizeof(t)))return false;
int i=0;bool neg=false;
if(t[0]=='-'){neg=true;i=1;}else if(t[0]=='+')i=1;
long long x=0;
for(;t[i];++i)x=x*10+(t[i]-'0');
v=neg?-x:x;
return true;
}
inline bool readDouble(double&v){
char t[64];
v=0.0;
if(!token(t,sizeof(t)))return false;
v=strtod(t,nullptr);
return true;
}
}
class Scheduler{
public:
void run();
private:
int K,NL;
double S,lat,bw;
long bpt;
double SLO1,SLO2,tpUB,tpBase,distBase,wTp,wC;
Curve col[6];
Params P;
int mStar[3]={1,1,1};
int mPre=1,mProc=1,mPost=1;
int Keff=1;
bool latDomLink=false;
double sumLinArr=0.0;
long long nLinArr=0;
double sumRemPrefillWork=0.0;
double sumLocPrefillWork=0.0;
double locPrefillDone=0.0;
double sumLinkPrefillWork=0.0;
double lastT=0.0;
int AtargetCtrl=0;
bool binaryMode=false;
bool plannedOnce=false;
bool aimdOnFinPath=false;
bool linkBinding=false;
long long lastRegrid=0;
int mIoStatic=1;
int mIoDyn=1;
Req req[2005];
int reqCount=0;
bool localBusy=false;
double localFreeAt=0;
TaskType localBusyType=T_PPRE;
bool remBusy[8]={};
double remFreeAt[8]={};
deque<XferEntry>qUp,qDown;
double upFreeAt=0,downFreeAt=0;
vector<int>readyPPre;
vector<int>readyPPost;
vector<int>rdDPre;
vector<int>rdDPost;
vector<int>rdDProc[8];
vector<int>armPProc[8];
deque<int>parked;
vector<int>Aset;
int nPend=0,nSpan=0,unfinished=0;
int nPendOn[8]={},nSpanOn[8]={};
double tdrSumDone=0;
int nTdrDone=0;
double sumAPending=0;
double spanSum=0;
long long gapCount=0;
long long tokensTotal=0;
double firstArrival=-1;
double rtEwma=0;
int histLout[513]={};
int nFin=0;
double remHat0=1.0;
double remHatCache[513]={};
double load[8]={};
double preLoad[8]={};
int rotCounter=0;
int tieRot[8]={};
int fallbackRR=0;
int Rhat=0;
long long Ghat=0;
bool mature=false;
double gapsFutureHat=0;
long long gapsFutureFrame=-1;
double exTdr=0,exTpot=0;
double pTDR=0,pTPOT=0;
double tdrProj=0,tpotProj=0;
double tpRun=0;
int memoLocal=-1,memoGate=-1;
int memoRemote[8]={-1,-1,-1,-1,-1,-1,-1,-1};
EpochStats epoch;
Occupancy occ[11];
double resBusyStart[11]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int consecD[8]={};
int deferCount[11]={};
vector<unsigned>finMark;
unsigned finEpoch=0;
void finishingClear(){++finEpoch;}
void finishingAdd(int rid){
if(rid<0)return;
if((int)finMark.size()<=rid)finMark.resize(rid+1,0u);
finMark[rid]=finEpoch;
}
bool finishingHas(int rid)const{
return rid>=0&&rid<(int)finMark.size()&&finMark[rid]==finEpoch;
}
bool finThisFrame=false;
mutable long long dupMark[2005]={},accMark[2005]={};
mutable long long dupEpoch=0,accEpoch=0;
int xferMismatch=0;
long long framesSeen=0;
std::clock_t cpuOriginCpu=std::clock();
std::chrono::steady_clock::time_point cpuOrigin=std::chrono::steady_clock::now();
double cpuElapsed()const{
return double(std::clock()-cpuOriginCpu)/(double)CLOCKS_PER_SEC;
}
double wallElapsed()const{
return std::chrono::duration<double>(
std::chrono::steady_clock::now()-cpuOrigin).count();
}
bool splitDisabled=false;
long long inflightNow()const{
long long n=(localBusy?1:0)+(long long)qUp.size()+(long long)qDown.size();
for(int k=0;k<K;++k)if(remBusy[k])++n;
return n;
}
bool fallbackLatched=false;
int echoMismatch=0;
struct DeferredGate{int k;int rid;Piece pc;bool tStarForced;bool canDecode;};
vector<DeferredGate>deferredGates;
struct DeferredLocalUpGate{int rid;bool canDecode;};
bool hasDeferredLocalUpGate=false;
DeferredLocalUpGate deferredLocalUpGate{};
bool waitOnly=false;
bool waitMid()const{return!waitOnly&&wC>wTp&&distBase>10.0;}
void readConfig();
void readTable();
bool readFrameHeader(double&t);
void readEvents(int e);
Frame frameBuf;
vector<pair<int,int>>tdnByRem;
vector<int>tdnGroup;
Plan planBuf;
double parseDouble(const string&s){return stod(s);}
int parseInt(const string&s){return stoi(s);}
void buildPlan(double exTdrNow,double rtMeasured);
void applyFrame(double t,const Frame&f);
void applyARR(double t,const ArrEvent&e);
void applyXDN(const XdnEvent&e,double t);
void applyTDN(double t,const TdnEvent&e);
void checkEchoedDuration(const TdnEvent&e){
double expect=-1;
switch(e.kind){
case T_PPRE:expect=col[0].tau(req[e.rid].Lin);break;
case T_PPROC:expect=(double)(e.le-e.ls)/max(1,NL)*col[1].tau(req[e.rid].Lin);break;
case T_PPOST:expect=col[2].tau(req[e.rid].Lin);break;
case T_DPRE:expect=col[3].tau((int)e.rids.size());break;
case T_DPROC:expect=col[4].tau((int)e.rids.size());break;
case T_DPOST:expect=col[5].tau((int)e.rids.size());break;
}
if(expect<0)return;
double denom=max(1e-9,max(fabs(expect),fabs(e.dur)));
if(fabs(expect-e.dur)/denom>1e-6){
if(++echoMismatch>=policy::ProtocolTrust::echoMismatchLatch)latchFallback();
}else if(echoMismatch>0){
--echoMismatch;
}
}
void applyFIN(int rid);
int passOverOf(int rid)const{return req[rid].skips;}
void updateRtEwma(double t,int rid);
void closeEpoch(double t);
void aimdOnFin(double t);
int bind(int rid);
int peekBind()const;
int fallbackBind(int rid);
void aimdControl(double t);
void checkKeffExpansion();
void raiseKeffForPrefill();
void recomputeRemHat();
void processDeferredGates(double t,Plan&plan);
double remHat(int k)const;
double weightOf(const Req&r)const;
double perTokenRemoteMs()const;
double bindCost(int k)const;
bool bindBetter(int k,int b)const;
double futureGaps();
void updateSignals(double t);
void admit(double t);
void decideRemotes(double t,Plan&plan);
bool evalR2(double dp,double dd,int n_p,int n_s,int site);
bool wouldBlowWaiting(bool delayingDecode,double delay);
bool resIdle(int res,double t)const;
bool bnSetStarved(double t)const;
void decideLocal(double t,Plan&plan);
double residualTotal()const{
double s=0;
for(int k=0;K>0&&k<K;++k)s+=load[k];
return s;
}
double remHatMean()const{
if(unfinished==0)return 1.0;
double sum=0;
for(int i=0;i<reqCount;++i){
if(req[i].stage==FINISHED||req[i].stage==NEW)continue;
sum+=remHat(req[i].tokens);
}
return sum/unfinished;
}
bool anyAMemberOn(int k)const{return aOn[k]>0;}
double nextDecodeLandingOn(int k,double t)const{
if(policy::PieceSplit::seesReadyDecode&&!rdDProc[k].empty())return 0.01;
for(const auto&xf:qUp){
if(xf.isPrefill||xf.remote!=k)continue;
return max(0.01,xf.finishTime-t);
}
if(rtEwma>0)return rtEwma;
return S+col[3].tau(max(1,mPre))+xfer(max(1,mProc));
}
double tWake(double t)const{
double best=-1;
auto consider=[&](double x){if(x>=t&&(best<0||x<best))best=x;};
if(localBusy)consider(localFreeAt);
for(int k=0;k<K;++k)if(remBusy[k])consider(remFreeAt[k]);
if(!qUp.empty())consider(qUp.front().finishTime);
if(!qDown.empty())consider(qDown.front().finishTime);
return best;
}
bool eventCanEnlargePool(double tw,int resource,TaskType shape)const{
const double EPSt=1e-9;
if(shape==T_DPOST){
if(!qDown.empty()&&!qDown.front().isPrefill
&&qDown.front().finishTime<=tw+EPSt)return true;
if(policy::GroupWait::seesQueuedFeeder&&latDomLink)
for(const auto&x:qDown)if(!x.isPrefill)return true;
if(policy::GroupWait::postSeesUpstreamDecode&&latDomLink
&&unfinished>(int)rdDPost.size())return true;
return false;
}
if(shape==T_DPRE){
if(resource==RES_LOCAL){
if(localBusy)
return localFreeAt<=tw+EPSt
&&(localBusyType==T_PPOST||localBusyType==T_DPOST);
if(!readyPPost.empty()||!rdDPost.empty())return true;
if(!qDown.empty()&&qDown.front().finishTime<=tw+EPSt)return true;
if(latDomLink&&unfinished>(int)rdDPre.size())return true;
return false;
}
return false;
}
if(shape==T_DPROC){
int k=resource-RES_REMOTE0;
if(!qUp.empty()&&!qUp.front().isPrefill&&qUp.front().remote==k
&&qUp.front().finishTime<=tw+EPSt)return true;
if(policy::GroupWait::seesQueuedFeeder&&latDomLink)
for(const auto&x:qUp)if(!x.isPrefill&&x.remote==k)return true;
return false;
}
return false;
}
bool fireOrWait(int resource,int readyCount,int target,int colIdx,
TaskType shape,double t);
Piece choosePiece(int rid,int k,double t);
bool gateHoldsPrefillTransfer(int rid,bool isDown,double t);
int countAMembersAwaitingTransfer(bool down)const{return down?awaitDown:awaitUp;}
int groupCap(int readyCount,int mGrid,int mStarCol)const{
int ceilM=linkBinding?mGrid:max(mGrid,mStarCol);
if(policy::GroupWait::latDomTakeAll&&latDomLink)
ceilM=max(ceilM,readyCount);
int cap=min(readyCount,ceilM);
cap=max(cap,min(max(mIoDyn,mIoStatic),readyCount));
return max(1,cap);
}
int pickSptWithAging(const vector<int>&cands,double t)const;
void legalitySweep(double t,Plan&plan);
bool isAssignmentLegal(const Assignment&a,const vector<const Assignment*>&acc)const;
vector<const Assignment*>sweepAcc;
void livenessGuard(double t,Plan&plan);
bool injectAnyLegal(TaskType shape,Plan&plan,double t);
void latchFallback(){fallbackLatched=true;}
void decideFallback(double t,Plan&plan);
void budgetLadder();
void emit(const Plan&plan,double t);
string outBuf;
void applyOptimisticState(const Assignment&a,double t);
void enqueueTransfer(deque<XferEntry>&q,double&freeAt,double len,bool prefill,const vector<int>&rids,int remote,double t);
double xfer(double len)const{return lat+8.0*len*bpt/(bw*1e6);}
double predictedDuration(const Assignment&a)const{
switch(a.type){
case T_PPRE:return col[0].tau(req[a.rids[0]].Lin);
case T_PPROC:return(double)(a.le-a.ls)/max(1,NL)*col[1].tau(req[a.rids[0]].Lin);
case T_PPOST:return col[2].tau(req[a.rids[0]].Lin);
case T_DPRE:return col[3].tau((int)a.rids.size());
case T_DPROC:return col[4].tau((int)a.rids.size());
case T_DPOST:return col[5].tau((int)a.rids.size());
}
return 0.0;
}
vector<int>sgForced,sgRest,sgOrdered;
vector<int>selectGroup(const vector<int>&pool,int cap){
if((int)pool.size()<=cap){
for(int rid:pool){req[rid].readyStamp=framesSeen;req[rid].skips=0;}
return pool;
}
vector<int>&forced=sgForced;vector<int>&rest=sgRest;
forced.clear();rest.clear();
forced.reserve(pool.size());rest.reserve(pool.size());
for(int rid:pool){
if(passOverOf(rid)>=PASSOVER_THRESH)forced.push_back(rid);
else rest.push_back(rid);
}
if(mature){
stable_sort(rest.begin(),rest.end(),[&](int a,int b){
return remHat(req[a].tokens)<remHat(req[b].tokens);
});
}else{
stable_sort(rest.begin(),rest.end(),[&](int a,int b){
return req[a].arrival<req[b].arrival;
});
}
vector<int>&ordered=sgOrdered;
ordered.clear();
ordered.insert(ordered.end(),forced.begin(),forced.end());
ordered.insert(ordered.end(),rest.begin(),rest.end());
int n=min((int)ordered.size(),cap);
vector<int>chosen(ordered.begin(),ordered.begin()+n);
for(int rid:chosen){req[rid].readyStamp=framesSeen;req[rid].skips=0;}
for(int i=n;i<(int)ordered.size();++i)req[ordered[i]].skips++;
return chosen;
}
int aOn[8]={};
int awaitUp=0,awaitDown=0;
static bool stageAwaitsUp(Stage st){return st==UP_DEC;}
static bool stageAwaitsDown(Stage st){return st==DOWN_DEC;}
void setStage(int rid,Stage ns){
Req&r=req[rid];
if(r.stage==ns)return;
if(r.inA){
if(stageAwaitsUp(r.stage))awaitUp--;
if(stageAwaitsDown(r.stage))awaitDown--;
if(stageAwaitsUp(ns))awaitUp++;
if(stageAwaitsDown(ns))awaitDown++;
}
r.stage=ns;
}
void enterA(int rid){
Req&r=req[rid];
if(r.inA)return;
r.inA=true;
if(r.remote>=0&&r.remote<8)aOn[r.remote]++;
if(stageAwaitsUp(r.stage))awaitUp++;
if(stageAwaitsDown(r.stage))awaitDown++;
}
void leaveA(int rid){
Req&r=req[rid];
if(!r.inA)return;
r.inA=false;
if(r.remote>=0&&r.remote<8)aOn[r.remote]--;
if(stageAwaitsUp(r.stage))awaitUp--;
if(stageAwaitsDown(r.stage))awaitDown--;
}
void eraseFrom(vector<int>&v,int rid){
v.erase(remove(v.begin(),v.end(),rid),v.end());
}
void eraseFromDeque(deque<int>&v,int rid){
v.erase(remove(v.begin(),v.end(),rid),v.end());
}
};
void Scheduler::readConfig(){
long long iv=0;
fastin::readInt(iv);K=(int)iv;
fastin::readDouble(S);fastin::readDouble(lat);fastin::readDouble(bw);
fastin::readInt(iv);bpt=(long)iv;
fastin::readInt(iv);NL=(int)iv;
fastin::readDouble(SLO1);fastin::readDouble(SLO2);fastin::readDouble(tpUB);
fastin::readDouble(tpBase);fastin::readDouble(distBase);
fastin::readDouble(wTp);fastin::readDouble(wC);
K=max(1,min(8,K));
NL=max(1,min(64,NL));
if(bw<=0)bw=1e-3;
latDomLink=(lat>=8.0*(double)bpt/(bw*1e6));
}
void Scheduler::readTable(){
long long iv;int N;
fastin::readInt(iv);N=(int)iv;
for(int i=0;i<N;++i){
int bs=0;
double v[6]={-1,-1,-1,-1,-1,-1};
fastin::readInt(iv);bs=(int)iv;
for(int c=0;c<6;++c)fastin::readDouble(v[c]);
if(bs<=0)continue;
for(int c=0;c<6;++c)
if(v[c]>0){col[c].xs.push_back(bs);col[c].ys.push_back(v[c]);}
}
for(int c=0;c<6;++c){
Curve&cv=col[c];
size_t n=cv.xs.size();
if(n>=2){
vector<size_t>idx(n);
for(size_t i=0;i<n;++i)idx[i]=i;
stable_sort(idx.begin(),idx.end(),
[&](size_t a,size_t b){return cv.xs[a]<cv.xs[b];});
vector<int>sx;sx.reserve(n);
vector<double>sy;sy.reserve(n);
for(size_t i:idx){
if(!sx.empty()&&sx.back()==cv.xs[i])sy.back()=cv.ys[i];
else{sx.push_back(cv.xs[i]);sy.push_back(cv.ys[i]);}
}
cv.xs.swap(sx);
cv.ys.swap(sy);
}
if(cv.xs.empty()){cv.xs.push_back(1);cv.ys.push_back(1e-3);}
}
}
bool Scheduler::injectAnyLegal(TaskType shape,Plan&plan,double t){
(void)t;
if(shape==T_DPOST&&!localBusy&&!plan.usedLocal&&!rdDPost.empty()){
Assignment a;a.type=T_DPOST;a.server=-1;
a.rids=selectGroup(rdDPost,groupCap((int)rdDPost.size(),mPost,mStar[2]));
a.m=(int)a.rids.size();
if(a.m>0){plan.addLocal(a);return true;}
}
if(shape==T_DPROC){
for(int k=0;k<K;++k){
if(!remBusy[k]&&!plan.usedRemote[k]&&!rdDProc[k].empty()){
Assignment a;a.type=T_DPROC;a.server=k;a.remote=k;
a.rids=selectGroup(rdDProc[k],groupCap((int)rdDProc[k].size(),mProc,mStar[1]));
a.m=(int)a.rids.size();
if(a.m>0){plan.addRemote(k,a);return true;}
}
}
}
if(shape==T_DPRE&&!localBusy&&!plan.usedLocal&&!rdDPre.empty()){
Assignment a;a.type=T_DPRE;a.server=-1;
a.rids=selectGroup(rdDPre,min((int)rdDPre.size(),mPre));
a.m=(int)a.rids.size();
if(a.m>0){plan.addLocal(a);return true;}
}
if(shape==T_PPOST&&!localBusy&&!plan.usedLocal&&!readyPPost.empty()){
Assignment a;a.type=T_PPOST;a.server=-1;
a.rids.push_back(readyPPost.front());
a.remote=req[a.rids[0]].remote;
plan.addLocal(a);return true;
}
if(shape==T_PPRE&&!localBusy&&!plan.usedLocal&&!readyPPre.empty()){
Assignment a;a.type=T_PPRE;a.server=-1;
int rid=pickSptWithAging(readyPPre,t);
if(rid<0)rid=readyPPre.front();
a.rids.push_back(rid);
a.remote=fallbackLatched?fallbackBind(rid):bind(rid);
plan.addLocal(a);return true;
}
if(shape==T_PPROC){
for(int k=0;k<K;++k){
if(!remBusy[k]&&!plan.usedRemote[k]&&!armPProc[k].empty()){
Assignment a;a.type=T_PPROC;a.server=k;a.remote=k;
int rid=armPProc[k].front();
a.ls=req[rid].piece;a.le=NL;
a.rids.push_back(rid);
plan.addRemote(k,a);return true;
}
}
}
return false;
}
bool Scheduler::readFrameHeader(double&t){
char tk[64];
if(!fastin::token(tk,sizeof(tk)))return false;
if(tk[0]=='E'&&tk[1]=='N'&&tk[2]=='D')return false;
t=strtod(tk,nullptr);
return true;
}
void Scheduler::readEvents(int e){
Frame&f=frameBuf;
f.clear();
char tk[64];long long iv=0;
for(int i=0;i<e;++i){
fastin::token(tk,sizeof(tk));
if(tk[0]=='A'){
ArrEvent ev;
fastin::readInt(iv);ev.rid=(int)iv;
fastin::readInt(iv);ev.Lin=(int)iv;
f.arrivals.push_back(ev);
}else if(tk[0]=='T'){
TdnEvent ev;
fastin::token(tk,sizeof(tk));
ev.server=(tk[0]=='E')?-1:atoi(tk+1);
char t1[8],t2[8];
fastin::token(t1,sizeof(t1));
fastin::token(t2,sizeof(t2));
bool isP=(t1[0]=='P');
if(isP&&t2[1]=='R'&&t2[2]=='E'){
ev.kind=T_PPRE;
fastin::readInt(iv);
fastin::readInt(iv);ev.rid=(int)iv;
fastin::readDouble(ev.dur);
}else if(isP&&t2[1]=='R'&&t2[2]=='O'){
ev.kind=T_PPROC;
fastin::readInt(iv);ev.ls=(int)iv;
fastin::readInt(iv);ev.le=(int)iv;
fastin::readInt(iv);
fastin::readInt(iv);ev.rid=(int)iv;
fastin::readDouble(ev.dur);
}else if(isP){
ev.kind=T_PPOST;
fastin::readInt(iv);
fastin::readInt(iv);ev.rid=(int)iv;
fastin::readDouble(ev.dur);
}else{
if(t2[1]=='R'&&t2[2]=='E')ev.kind=T_DPRE;
else if(t2[1]=='R'&&t2[2]=='O')ev.kind=T_DPROC;
else ev.kind=T_DPOST;
fastin::readInt(iv);
long long m=0;fastin::readInt(m);
ev.rids.reserve((size_t)m);
for(long long j=0;j<m;++j){fastin::readInt(iv);ev.rids.push_back((int)iv);}
fastin::readDouble(ev.dur);
}
f.tdns.push_back(ev);
}else if(tk[0]=='X'){
XdnEvent ev;
char dir[8],kind[8];
fastin::token(dir,sizeof(dir));
fastin::readInt(iv);ev.remote=(int)iv;
fastin::readDouble(ev.bytes);
fastin::token(kind,sizeof(kind));
long long m=0;fastin::readInt(m);
ev.up=(dir[0]=='U');
ev.prefill=(kind[0]=='P');
ev.rids.reserve((size_t)m);
for(long long j=0;j<m;++j){fastin::readInt(iv);ev.rids.push_back((int)iv);}
f.xdns.push_back(ev);
}else if(tk[0]=='F'){
fastin::readInt(iv);
f.finishedRids.push_back((int)iv);
}
}
}
void Scheduler::applyFrame(double t,const Frame&f){
finishingClear();
for(int rid:f.finishedRids)finishingAdd(rid);
finThisFrame=!f.finishedRids.empty();
for(auto&ev:f.arrivals)applyARR(t,ev);
for(auto&ev:f.xdns)applyXDN(ev,t);
for(auto&ev:f.tdns)applyTDN(t,ev);
for(int rid:f.finishedRids)applyFIN(rid);
finishingClear();
}
void Scheduler::applyARR(double t,const ArrEvent&e){
if(e.rid<0||e.rid>=(int)(sizeof(req)/sizeof(req[0])))return;
if(firstArrival<0)firstArrival=t;
sumAPending+=t;
setStage(e.rid,ARRIVED);
req[e.rid].arrival=t;
req[e.rid].Lin=e.Lin;
sumLinArr+=e.Lin;nLinArr++;
double locPre=2.0*S+col[0].tau(e.Lin)+col[2].tau(e.Lin);
req[e.rid].sptKey=locPre;
sumRemPrefillWork+=S+col[1].tau(e.Lin);
sumLocPrefillWork+=locPre;
sumLinkPrefillWork+=2.0*xfer(e.Lin);
raiseKeffForPrefill();
readyPPre.push_back(e.rid);
nPend++;
unfinished++;
if(e.rid>=reqCount)reqCount=e.rid+1;
}
void Scheduler::applyXDN(const XdnEvent&e,double t){
deque<XferEntry>&q=e.up?qUp:qDown;
double&freeAt=e.up?upFreeAt:downFreeAt;
if(q.empty()){
latchFallback();
}else{
const XferEntry&head=q.front();
if(!(head.isPrefill==e.prefill&&head.rids==e.rids)){
if(++xferMismatch>=policy::ProtocolTrust::xferMismatchLatch)latchFallback();
}else if(xferMismatch>0){
--xferMismatch;
}
q.pop_front();
}
if(t>freeAt)freeAt=t;
int rem=(e.remote>=0&&e.remote<K)?e.remote:0;
for(int rid:e.rids){
if(rid<0||rid>=reqCount)continue;
if(e.prefill){
if(e.up){setStage(rid,PPROC_ARMED);armPProc[rem].push_back(rid);}
else{setStage(rid,RD_PPOST);readyPPost.push_back(rid);}
}else{
req[rid].readyStamp=framesSeen;
if(e.up){setStage(rid,RD_DPROC);rdDProc[rem].push_back(rid);}
else{setStage(rid,RD_DPOST);rdDPost.push_back(rid);}
}
}
}
void Scheduler::enqueueTransfer(deque<XferEntry>&q,double&freeAt,double len,bool prefill,
const vector<int>&rids,int remote,double t){
double st=max(t,freeAt);
double ft=st+xfer(len);
q.push_back({len,prefill,rids,st,ft,remote});
freeAt=ft;
occ[(&q==&qUp)?RES_UP:RES_DOWN].addInterval(st,ft);
}
void Scheduler::applyTDN(double t,const TdnEvent&e){
int resIdx=(e.server<0)?RES_LOCAL:(RES_REMOTE0+e.server);
occ[resIdx].closeAt(t);
resBusyStart[resIdx]=-1;
if(resIdx==RES_LOCAL){localFreeAt=t;localBusy=false;}
else{remFreeAt[e.server]=t;remBusy[e.server]=false;}
checkEchoedDuration(e);
if(e.kind==T_PPRE){
setStage(e.rid,UP_PRE);
Req&r=req[e.rid];
enqueueTransfer(qUp,upFreeAt,r.Lin,true,{e.rid},r.remote,t);
}else if(e.kind==T_PPROC){
Req&r=req[e.rid];
if(r.remote>=0&&r.remote<K){
preLoad[r.remote]-=(double)(e.le-e.ls)/max(1,NL)*col[1].tau(r.Lin);
if(preLoad[r.remote]<0)preLoad[r.remote]=0;
}
r.piece=e.le;
if(e.le==NL){
setStage(e.rid,DOWN_PRE);
enqueueTransfer(qDown,downFreeAt,r.Lin,true,{e.rid},r.remote,t);
}else{
setStage(e.rid,PPROC_ARMED);
armPProc[r.remote].push_back(e.rid);
}
}else if(e.kind==T_PPOST){
Req&r=req[e.rid];
locPrefillDone+=2.0*S+col[0].tau(r.Lin)+col[2].tau(r.Lin);
setStage(e.rid,PARKED);
parked.push_back(e.rid);
tdrSumDone+=(t-r.arrival);
nTdrDone++;
sumAPending-=r.arrival;
nPend--;
if(r.remote>=0&&r.remote<8)nPendOn[r.remote]--;
}else if(e.kind==T_DPRE){
tdnByRem.clear();
tdnByRem.reserve(e.rids.size());
for(int rid:e.rids){
setStage(rid,UP_DEC);
tdnByRem.push_back({req[rid].remote,rid});
}
stable_sort(tdnByRem.begin(),tdnByRem.end(),
[](const pair<int,int>&a,const pair<int,int>&b){return a.first<b.first;});
for(size_t i=0;i<tdnByRem.size();){
size_t j=i;
tdnGroup.clear();
while(j<tdnByRem.size()&&tdnByRem[j].first==tdnByRem[i].first)
tdnGroup.push_back(tdnByRem[j++].second);
enqueueTransfer(qUp,upFreeAt,(double)tdnGroup.size(),false,
tdnGroup,tdnByRem[i].first,t);
i=j;
}
}else if(e.kind==T_DPROC){
for(int rid:e.rids)setStage(rid,DOWN_DEC);
enqueueTransfer(qDown,downFreeAt,(double)e.rids.size(),false,e.rids,e.server,t);
}else if(e.kind==T_DPOST){
tokensTotal+=e.rids.size();
for(int rid:e.rids){
Req&r=req[rid];
double oldW=weightOf(r);
r.tokens++;
if(r.remote>=0&&r.remote<K)
load[r.remote]+=weightOf(r)-oldW;
if(r.tokens==1){
nSpan++;
if(r.remote>=0&&r.remote<K)nSpanOn[r.remote]++;
r.tFirst=t;
r.tLast=t;
}else{
updateRtEwma(t,rid);
Ghat++;
}
if(finishingHas(rid))continue;
setStage(rid,RD_DPRE);
r.readyStamp=framesSeen;
rdDPre.push_back(rid);
}
}
}
void Scheduler::applyFIN(int rid){
Req&r=req[rid];
nFin++;
histLout[min(512,r.tokens)]++;
recomputeRemHat();
if(r.remote>=0&&r.remote<K){
load[r.remote]-=weightOf(r);
if(nSpanOn[r.remote]>0)nSpanOn[r.remote]--;
}
if(r.tokens>=1&&nSpan>0)nSpan--;
setStage(rid,FINISHED);
leaveA(rid);
eraseFrom(Aset,rid);
eraseFrom(rdDPre,rid);
eraseFrom(rdDPost,rid);
if(r.remote>=0&&r.remote<K)eraseFrom(rdDProc[r.remote],rid);
eraseFromDeque(parked,rid);
unfinished--;
}
void Scheduler::decideFallback(double t,Plan&plan){
(void)t;
while(!parked.empty()){
int rid=parked.front();
parked.pop_front();
Aset.push_back(rid);
setStage(rid,RD_DPRE);
enterA(rid);
req[rid].readyStamp=framesSeen;
rdDPre.push_back(rid);
}
if(!localBusy){
if(!rdDPost.empty()){
Assignment a;a.type=T_DPOST;a.server=-1;
int take=rdDPost.size();
for(int i=0;i<take;++i)a.rids.push_back(rdDPost[i]);
a.m=take;plan.addLocal(a);
}else if(!rdDPre.empty()){
Assignment a;a.type=T_DPRE;a.server=-1;
int take=(int)rdDPre.size();
for(int i=0;i<take;++i)a.rids.push_back(rdDPre[i]);
a.m=take;plan.addLocal(a);
}else if(!readyPPost.empty()){
Assignment a;a.type=T_PPOST;a.server=-1;
a.rids.push_back(readyPPost.front());
a.remote=req[a.rids[0]].remote;plan.addLocal(a);
}else if(!readyPPre.empty()){
Assignment a;a.type=T_PPRE;a.server=-1;
int rid=readyPPre.front();
a.rids.push_back(rid);
a.remote=fallbackBind(rid);
plan.addLocal(a);
}
}
for(int k=0;k<K;++k){
if(!remBusy[k]){
if(!rdDProc[k].empty()){
Assignment a;a.type=T_DPROC;a.server=k;a.remote=k;
int take=rdDProc[k].size();
for(int i=0;i<take;++i)a.rids.push_back(rdDProc[k][i]);
a.m=take;plan.addRemote(k,a);
}else if(!armPProc[k].empty()){
Assignment a;a.type=T_PPROC;a.server=k;a.remote=k;
int rid=armPProc[k].front();
a.ls=req[rid].piece;a.le=NL;
a.rids.push_back(rid);plan.addRemote(k,a);
}
}
}
}
bool Scheduler::fireOrWait(int resource,int readyCount,int target,int colIdx,
TaskType shape,double t){
if(readyCount<=0)return false;
if(readyCount>=target)return true;
if(mIoDyn>1&&readyCount>=mIoDyn)return true;
double tw=tWake(t);
if(tw<0)return true;
if(!eventCanEnlargePool(tw,resource,shape))return true;
if(deferCount[resource]>=max(P.W_MAX,target))return true;
int relieved=(shape==T_DPRE)?RES_UP:(shape==T_DPROC?RES_DOWN:-1);
bool priceless=(pTDR==0.0&&pTPOT==0.0);
bool tpTermLive=(wTp>0.0&&tpUB>tpBase
&&(epoch.bnHas(resource)||epoch.bnHas(relieved)));
if(priceless&&!tpTermLive)return true;
double dt=tw-t;
if(dt<=0)return true;
const int g=1;
double nowCost=(S+col[colIdx].tau(readyCount))/readyCount;
double laterCost=(S+col[colIdx].tau(readyCount+g))/(readyCount+g);
double benefitMs=(nowCost-laterCost)*(readyCount+g);
if(relieved>=0&&epoch.bnHas(relieved))benefitMs+=lat;
if(benefitMs<=0)return true;
double elapsedNow=max(1e-9,t-firstArrival);
double dScore_dMs=(wTp>0.0&&tpUB>tpBase&&tpRun>0.0&&firstArrival>=0)
?wTp*(tpRun/elapsedNow)/(tpUB-tpBase):0.0;
double benefit=benefitMs;
if(dScore_dMs>0.0&&epoch.bnConfident){
bool savesMakespan=epoch.bnHas(resource)
||(relieved>=0&&epoch.bnHas(relieved));
benefit=savesMakespan?benefitMs*dScore_dMs:0.0;
}
double cost=dt*(nSpan*pTPOT+nPend*pTDR);
if(epoch.bnHas(resource)&&wTp>0.0&&tpUB>tpBase)cost+=dt*dScore_dMs;
return benefit<=cost;
}
Piece Scheduler::choosePiece(int rid,int k,double t){
Req&r=req[rid];
int ls=r.piece;
int remaining=NL-ls;
Piece full{ls,NL};
if(NL==1||splitDisabled||remaining<=1)return full;
if(waitOnly)return full;
if(!anyAMemberOn(k)){
bool parkedOnK=false;
if(policy::PieceSplit::seesParkedOnRemote)
for(int q:parked)if(req[q].remote==k){parkedOnK=true;break;}
if(!parkedOnK)return full;
}
if(epoch.bnHas(RES_REMOTE0+k)&&wTp>0.0&&tpUB>tpBase
&&!(policy::PieceSplit::bottleneckYieldsToReadyDecode&&!rdDProc[k].empty()))return full;
double tauFull=col[1].tau(r.Lin);
if(tauFull<=0)return full;
double tauRemaining=tauFull*(double)remaining/(double)NL;
double delta=nextDecodeLandingOn(k,t);
if(delta>=S+tauRemaining)return full;
int parts=(int)floor((double)remaining*delta/tauRemaining);
parts=max(1,min(parts,remaining));
int n_max=max(1,1+(int)floor(P.SIGMA_SP*tauRemaining/S));
int minParts=(int)ceil((double)remaining/n_max);
parts=max(parts,minParts);
parts=min(parts,remaining);
int leftover=remaining-parts;
if(leftover>0&&tauFull*(double)leftover/(double)NL<S)return full;
return Piece{ls,ls+parts};
}
bool Scheduler::gateHoldsPrefillTransfer(int rid,bool isDown,double t){
const Req&r=req[rid];
double X=xfer(r.Lin);
double wave=xfer(max(1,isDown?mPost:mProc));
if(waitOnly)return false;
if(X<=wave)return false;
int demand=countAMembersAwaitingTransfer(isDown);
if(demand<=0)return false;
if(tdrProj*(1.0+P.MU)>=SLO1)return false;
double heldNow=r.heldTotal+(r.heldSince>=0?(t-r.heldSince):0.0);
if(heldNow>P.RHO_HOLD*SLO1)return false;
return!evalR2(X,wave,nPend,demand,9);
}
int Scheduler::pickSptWithAging(const vector<int>&cands,double t)const{
if(cands.empty())return-1;
int bestRid=cands.front();
double bestKey=1e300;
int agedRid=-1;
double agedExcess=P.GAMMA;
const double invSLO1=1.0/max(1e-12,SLO1);
for(int rid:cands){
const Req&r=req[rid];
if(r.sptKey<bestKey){bestKey=r.sptKey;bestRid=rid;}
double waitNorm=(t-r.arrival)*invSLO1;
if(waitNorm>agedExcess){agedExcess=waitNorm;agedRid=rid;}
}
return(agedRid>=0)?agedRid:bestRid;
}
void Scheduler::legalitySweep(double t,Plan&plan){
(void)t;
vector<const Assignment*>&acc=sweepAcc;
acc.clear();
bool dropped=false;
size_t w=0;
for(size_t i=0;i<plan.assignments.size();++i){
const Assignment&a=plan.assignments[i];
if(isAssignmentLegal(a,acc)){
if(w!=i)plan.assignments[w]=std::move(plan.assignments[i]);
acc.push_back(&plan.assignments[w]);
++w;
}else{
dropped=true;
}
}
plan.assignments.resize(w);
if(dropped)latchFallback();
plan.usedLocal=false;
for(int k=0;k<8;++k)plan.usedRemote[k]=false;
for(const auto&a:plan.assignments){
if(a.server==-1)plan.usedLocal=true;
else plan.usedRemote[a.server]=true;
}
}
bool Scheduler::isAssignmentLegal(const Assignment&a,const vector<const Assignment*>&acc)const{
if(a.server<-1||a.server>=K)return false;
if(a.server==-1&&localBusy)return false;
if(a.server>=0&&remBusy[a.server])return false;
++accEpoch;
for(const Assignment*op:acc){
const Assignment&other=*op;
if(other.server==a.server)return false;
for(int orid:other.rids)
if(orid>=0&&orid<(int)(sizeof(accMark)/sizeof(accMark[0])))accMark[orid]=accEpoch;
}
for(int rid:a.rids)
if(rid>=0&&rid<(int)(sizeof(accMark)/sizeof(accMark[0]))&&accMark[rid]==accEpoch)
return false;
if(a.rids.empty())return false;
if(a.type==T_DPRE||a.type==T_DPROC||a.type==T_DPOST){
if(a.m!=(int)a.rids.size())return false;
if(a.rids.size()>1u&&(a.type==T_PPRE||a.type==T_PPROC||a.type==T_PPOST))
return false;
}else if(a.rids.size()!=1u){
return false;
}
++dupEpoch;
for(int rid:a.rids){
if(rid<0||rid>=(int)(sizeof(dupMark)/sizeof(dupMark[0])))return false;
if(dupMark[rid]==dupEpoch)return false;
dupMark[rid]=dupEpoch;
}
for(int rid:a.rids){
if(rid<0||rid>=reqCount)return false;
const Req&r=req[rid];
if(r.stage==FINISHED)return false;
if(a.type==T_PPRE&&r.stage!=ARRIVED)return false;
if(a.type==T_PPROC&&r.stage!=PPROC_ARMED)return false;
if(a.type==T_PPOST&&r.stage!=RD_PPOST)return false;
if(a.type==T_DPRE&&r.stage!=RD_DPRE)return false;
if(a.type==T_DPROC&&r.stage!=RD_DPROC)return false;
if(a.type==T_DPOST&&r.stage!=RD_DPOST)return false;
if(a.type==T_PPROC||a.type==T_PPOST||a.type==T_DPROC){
if(r.remote!=a.remote)return false;
if(a.type==T_DPROC&&a.server!=a.remote)return false;
}
}
if(a.type==T_PPRE&&(a.remote<0||a.remote>=K))return false;
if(a.type==T_PPROC){
const Req&r=req[a.rids[0]];
if(a.ls<0||a.le>NL)return false;
if(a.ls>=a.le)return false;
if(a.ls!=r.piece)return false;
if(r.piece>=NL)return false;
}
return true;
}
void Scheduler::livenessGuard(double t,Plan&plan){
if(!(plan.empty()&&inflightNow()==0&&unfinished>0))return;
if(injectAnyLegal(T_DPOST,plan,t))return;
if(injectAnyLegal(T_DPROC,plan,t))return;
if(injectAnyLegal(T_DPRE,plan,t))return;
if(injectAnyLegal(T_PPOST,plan,t))return;
if(injectAnyLegal(T_PPRE,plan,t))return;
if(injectAnyLegal(T_PPROC,plan,t))return;
latchFallback();
decideFallback(t,plan);
}
void Scheduler::emit(const Plan&plan,double t){
static vector<const Assignment*>ord;
ord.clear();
for(const auto&a:plan.assignments)ord.push_back(&a);
if(ord.size()>1)
sort(ord.begin(),ord.end(),[](const Assignment*a,const Assignment*b){
return a->emitPriority()<b->emitPriority();
});
if((int)ord.size()>K+1)ord.resize(K+1);
outBuf.clear();
Assignment::putInt(outBuf,(long long)ord.size());
outBuf.push_back('\n');
for(const Assignment*a:ord){
a->appendTo(outBuf);
applyOptimisticState(*a,t);
}
const char*p=outBuf.data();
size_t left=outBuf.size();
while(left>0){
ssize_t w=::write(1,p,left);
if(w<=0){if(errno==EINTR)continue;_exit(0);}
p+=w;left-=(size_t)w;
}
}
void Scheduler::applyOptimisticState(const Assignment&a,double t){
double predDur=predictedDuration(a);
if(a.server==-1){
localBusy=true;
localBusyType=a.type;
resBusyStart[RES_LOCAL]=t;
occ[RES_LOCAL].openAt(t);
localFreeAt=t+S+predDur;
}else{
remBusy[a.server]=true;
resBusyStart[RES_REMOTE0+a.server]=t;
occ[RES_REMOTE0+a.server].openAt(t);
remFreeAt[a.server]=t+S+predDur;
}
for(int rid:a.rids){
switch(a.type){
case T_PPRE:setStage(rid,PPRE_RUN);eraseFrom(readyPPre,rid);break;
case T_PPROC:setStage(rid,PPROC_RUN);eraseFrom(armPProc[a.server],rid);break;
case T_PPOST:setStage(rid,PPOST_RUN);eraseFrom(readyPPost,rid);break;
case T_DPRE:setStage(rid,DPRE_RUN);eraseFrom(rdDPre,rid);break;
case T_DPROC:setStage(rid,DPROC_RUN);eraseFrom(rdDProc[a.server],rid);break;
case T_DPOST:setStage(rid,DPOST_RUN);eraseFrom(rdDPost,rid);break;
}
}
}
void Scheduler::buildPlan(double exTdrNow,double rtMeasured){
if(!plannedOnce){
for(int c=0;c<3;++c){
double bestRate=-1;
int bestM=1;
for(int m=1;m<=4096;++m){
double rate=m/(S+col[c+3].tau(m));
if(rate>bestRate){bestRate=rate;bestM=m;}
}
mStar[c]=bestM;
}
}
binaryMode=(distBase==0.0);
waitOnly=(wC>=0.95&&wC>=wTp);
mIoStatic=max(1,(int)ceil(2e5*(2+3*K)/1.5e6));
double edgeForDecode=1.0;
if(plannedOnce&&firstArrival>=0){
double elapsed=max(1e-9,lastT-firstArrival);
double duty=locPrefillDone/elapsed;
edgeForDecode=max(0.1,1.0-min(0.9,duty));
}
double maxScore=-1.0;
int bestK=1,bestA=1,bestMGrid=1;
static const int m_vals[]={1,2,3,4,6,8,12,16,24,32,48,64,96,128,192,256,384,512,768,1024,1536,2000};
static const int mult_vals[]={1,2,3,4,6,8,12,16,24,32};
double targetSLO2=binaryMode?SLO2*(1.0-P.MU):SLO2;
double exTdrGrid=max(0.0,exTdrNow);
for(int m:m_vals){
double tpre=S+col[3].tau(m);
double tpost=S+col[5].tau(m);
for(int keff=1;keff<=K;++keff){
double m_k=ceil((double)m/keff);
double tproc=S+col[4].tau(m_k);
double tpmax1=m/(tpre+tpost)*edgeForDecode;
double tpmax2=m/tproc;
double tpmax3=m/(keff*lat+8.0*m*bpt/(bw*1e6));
double tpmax=min({tpmax1,tpmax2,tpmax3});
double RT=tpre+tproc+tpost
+(keff+1)*(lat+8.0*m*bpt/(keff*bw*1e6));
if(rtMeasured>0)RT=max(RT,rtMeasured);
for(int mult:mult_vals){
int Ahat=m*mult;
if(Ahat>2000)continue;
double tpot_hat=max(RT,Ahat/tpmax);
double excess_tpot=max(0.0,(tpot_hat-targetSLO2)/SLO2);
double dist=sqrt(exTdrGrid*exTdrGrid+excess_tpot*excess_tpot);
double wait_score=(distBase>0)?max(0.0,1.0-dist/distBase)
:((dist==0)?1.0:0.0);
double tp_hat=min(tpmax,Ahat/RT);
double tp_score=max(0.0,min(1.0,(tp_hat-tpBase)/(tpUB-tpBase)));
double curScore=wTp*tp_score+wC*wait_score;
bool better=false;
if(curScore>maxScore+1e-12)better=true;
else if(curScore>maxScore-1e-12){
if(wTp>wC&&distBase>10.0){
if(Ahat>bestA)better=true;
else if(Ahat==bestA&&m>bestMGrid)better=true;
}else{
if(Ahat<bestA)better=true;
else if(Ahat==bestA&&m<bestMGrid)better=true;
}
}
if(better){maxScore=curScore;bestK=keff;bestA=Ahat;bestMGrid=m;}
}
}
}
Keff=plannedOnce?max(Keff,bestK):bestK;
Keff=min(K,max(1,Keff));
if(!plannedOnce)AtargetCtrl=max(1,bestA);
else AtargetCtrl=max(AtargetCtrl,max(1,bestA));
plannedOnce=true;
mPre=bestMGrid;
mPost=bestMGrid;
mProc=max(1,(int)ceil((double)bestMGrid/Keff));
if(wTp>wC&&distBase>10.0){
P.LAMBDA=max(P.LAMBDA,2.5);
mPre=max(mPre,mStar[0]);
mPost=max(mPost,mStar[2]);
mProc=max(mProc,max(1,(int)ceil((double)max(bestMGrid,mStar[1])/max(1,Keff))));
AtargetCtrl=max(AtargetCtrl,bestA);
}
{
double m_k=ceil((double)bestMGrid/Keff);
double c1=bestMGrid/(S+col[3].tau(bestMGrid)+S+col[5].tau(bestMGrid));
double c2=bestMGrid/(S+col[4].tau(m_k));
double c3=bestMGrid/(Keff*lat+8.0*bestMGrid*bpt/(bw*1e6));
linkBinding=(c3<=min(c1,c2)*(1.0+1e-9));
}
if(waitOnly&&!linkBinding&&K>Keff){
Keff=K;
mProc=max(1,(int)ceil((double)bestMGrid/Keff));
}
}
void Scheduler::run(){
readConfig();
readTable();
buildPlan(0.0,-1.0);
double t;
while(readFrameHeader(t)){
lastT=t;
long long e=0;
fastin::readInt(e);
readEvents((int)e);
applyFrame(t,frameBuf);
updateSignals(t);
planBuf.reset();
Plan&plan=planBuf;
deferredGates.clear();
hasDeferredLocalUpGate=false;
if(fallbackLatched){
decideFallback(t,plan);
}else{
admit(t);
decideRemotes(t,plan);
decideLocal(t,plan);
processDeferredGates(t,plan);
}
legalitySweep(t,plan);
size_t beforeGuard=plan.size();
livenessGuard(t,plan);
if(plan.size()!=beforeGuard){
legalitySweep(t,plan);
if(plan.empty()){
livenessGuard(t,plan);
legalitySweep(t,plan);
}
}
emit(plan,t);
framesSeen++;
}
}
int main(){
ios::sync_with_stdio(false);
cin.tie(nullptr);
Scheduler s;
s.run();
return 0;
}
void Scheduler::updateRtEwma(double t,int rid){
Req&r=req[rid];
if(r.tokens>=2){
double gap=t-r.tLast;
rtEwma=(rtEwma==0.0)?gap:(0.9*rtEwma+0.1*gap);
spanSum+=gap;
gapCount++;
}
r.tLast=t;
}
void Scheduler::closeEpoch(double t){
for(int k=0;k<8;++k){nPendOn[k]=0;nSpanOn[k]=0;}
for(int i=0;i<reqCount;++i){
const Req&r=req[i];
if(r.stage==FINISHED||r.stage==NEW)continue;
if(r.remote<0||r.remote>=K)continue;
if(r.tokens>=1)nSpanOn[r.remote]++;
else if(r.stage<PARKED)nPendOn[r.remote]++;
}
double epochSpan=max(1e-9,t-epoch.epochStart);
double lo=epoch.epochStart;
epoch.epochFrames=0;
epoch.epochStart=t;
double maxUtil=-1.0;
int curBn=-1;
for(int i=0;i<11;++i){
epoch.util[i]=min(1.0,occ[i].drain(lo,t)/epochSpan);
epoch.busyTime[i]=0;
if(epoch.util[i]>maxUtil){maxUtil=epoch.util[i];curBn=i;}
}
unsigned mask=0;
double outsideBest=0.0;
for(int i=0;i<11;++i){
if(maxUtil>0.0&&epoch.util[i]*BN_MARGIN>=maxUtil)mask|=(1u<<i);
else outsideBest=max(outsideBest,epoch.util[i]);
}
epoch.bnMask=mask;
epoch.bottleneck=curBn;
epoch.bnStreak=(curBn==epoch.prevBn)?epoch.bnStreak+1:0;
epoch.prevBn=curBn;
epoch.bnConfident=(epoch.bnStreak>=W_BN&&maxUtil>0.0&&
maxUtil>=BN_MARGIN*outsideBest);
checkKeffExpansion();
}
void Scheduler::aimdOnFin(double t){
aimdOnFinPath=true;
aimdControl(t);
aimdOnFinPath=false;
}
void Scheduler::budgetLadder(){
if(framesSeen % BUDGET_CHECK!=0||framesSeen==0)return;
double elapsed=max(cpuElapsed(),wallElapsed());
if(framesSeen>1.5e6||elapsed>12.0){
mIoDyn=max(mIoDyn,64);
splitDisabled=true;
latchFallback();
}else if(framesSeen>1.0e6||elapsed>9.0){
mIoDyn=max(mIoDyn,16);
splitDisabled=true;
}else if(framesSeen>6.0e5||elapsed>6.0){
mIoDyn=max(mIoDyn,4);
}
}
double Scheduler::futureGaps(){
if(gapsFutureFrame<0||framesSeen-gapsFutureFrame>=policy::PriceRecovery::refreshFrames){
gapsFutureFrame=framesSeen;
double sum=0;
for(int i=0;i<reqCount;++i){
const Req&r=req[i];
if(r.stage==FINISHED||r.stage==NEW)continue;
sum+=(r.tokens>0)?remHat(r.tokens):remHat0;
}
gapsFutureHat=sum;
}
return gapsFutureHat;
}
void Scheduler::updateSignals(double t){
budgetLadder();
if(firstArrival<0)return;
double denomTdr=nTdrDone+nPend;
tdrProj=(denomTdr>0)?(tdrSumDone+nPend*t-sumAPending)/denomTdr:0.0;
tpotProj=(nSpan>0||gapCount>0)
?max(gapCount>0?spanSum/gapCount:0.0,rtEwma)
:0.0;
tpRun=tokensTotal/max(0.001,t-firstArrival);
bool epochBoundary=(framesSeen % ADM_EPOCH==0&&framesSeen>0);
if(epochBoundary)closeEpoch(t);
Rhat=reqCount;
if(!mature)mature=(nFin>=P.N_CONF)&&(gapCount>=P.N_CONF);
double SLO1t=binaryMode?SLO1*(1.0-P.MU):SLO1;
double SLO2t=binaryMode?SLO2*(1.0-P.MU):SLO2;
exTdr=max(0.0,(tdrProj-SLO1t)/SLO1);
exTpot=max(0.0,(tpotProj-SLO2t)/SLO2);
if(framesSeen-lastRegrid>=REGRID_INTERVAL&&framesSeen>0){
lastRegrid=framesSeen;
buildPlan(exTdr,rtEwma>0?rtEwma:-1.0);
}
double D=sqrt(exTdr*exTdr+exTpot*exTpot);
double DB=(distBase>0)?distBase:P.MU;
bool dead=(wC==0.0)||(D==0.0);
if(!dead&&distBase>0&&D>=DB){
double gapFloor=rtEwma;
if(policy::PriceRecovery::useLittleLawFloor&&tpRun>0.0&&nSpan>0)
gapFloor=max(gapFloor,nSpan/tpRun);
double gf=futureGaps();
double gTot=(double)gapCount+gf;
double tpotBest=(gTot>0)?(spanSum+gf*gapFloor)/gTot:tpotProj;
if(tpotBest<gapFloor)tpotBest=gapFloor;
double exTpotBest=max(0.0,(tpotBest-SLO2t)/SLO2);
double Dmin=sqrt(exTdr*exTdr+exTpotBest*exTpotBest);
dead=(Dmin>=DB*policy::PriceRecovery::margin);
}
if(dead){
pTDR=0;
pTPOT=0;
}else{
double Ghat_eff=max(1.0,(double)gapCount+futureGaps());
pTDR=wC*(exTdr/D)/(DB*SLO1*max(1,Rhat));
pTPOT=wC*(exTpot/D)/(DB*SLO2*Ghat_eff);
}
if(finThisFrame&&framesSeen>0)aimdOnFin(t);
else if(epochBoundary)aimdControl(t);
}
void Scheduler::recomputeRemHat(){
if(nFin==0)return;
long long sufCount=0,sufWeighted=0;
remHatCache[512]=1.0;
for(int k=511;k>=0;--k){
int v=k+1;
sufCount+=histLout[v];
sufWeighted+=(long long)v*histLout[v];
remHatCache[k]=(sufCount>0)
?((double)sufWeighted-(double)k*sufCount)/(double)sufCount
:1.0;
}
remHat0=mature?remHatCache[0]:1.0;
for(int k=0;k<K;++k){load[k]=0;preLoad[k]=0;}
for(int i=0;i<reqCount;++i){
const Req&r=req[i];
if(r.stage==FINISHED||r.stage==NEW)continue;
if(r.remote<0||r.remote>=K)continue;
load[r.remote]+=weightOf(r);
if(r.stage<DOWN_PRE)
preLoad[r.remote]+=(double)(NL-r.piece)/max(1,NL)*col[1].tau(r.Lin);
}
}
double Scheduler::remHat(int k)const{
if(!mature)return 1.0;
return remHatCache[max(0,min(512,k))];
}
double Scheduler::weightOf(const Req&r)const{
return(r.tokens>0)?remHat(r.tokens):remHat0;
}
double Scheduler::perTokenRemoteMs()const{
int m=max(1,mProc);
return(S+col[4].tau(m))/(double)m;
}
double Scheduler::bindCost(int k)const{
return load[k]*perTokenRemoteMs()+preLoad[k];
}
bool Scheduler::bindBetter(int k,int b)const{
bool msMode=(policy::RemoteBinding::prefillMode==2);
if(policy::RemoteBinding::prefillMode==3)
msMode=(sumRemPrefillWork>sumLocPrefillWork)
&&(sumRemPrefillWork>sumLinkPrefillWork);
if(msMode){
double ck=bindCost(k),cb=bindCost(b);
if(ck<cb-1e-12)return true;
if(ck>cb+1e-12)return false;
return tieRot[k]<tieRot[b];
}
if(load[k]<load[b]-1e-12)return true;
if(load[k]>load[b]+1e-12)return false;
if(policy::RemoteBinding::prefillMode>=1){
if(preLoad[k]<preLoad[b]-1e-12)return true;
if(preLoad[k]>preLoad[b]+1e-12)return false;
}
return tieRot[k]<tieRot[b];
}
int Scheduler::peekBind()const{
int bestK=0;
for(int k=1;k<Keff;++k)if(bindBetter(k,bestK))bestK=k;
return bestK;
}
int Scheduler::bind(int rid){
int bestK=peekBind();
tieRot[bestK]++;
rotCounter++;
req[rid].remote=bestK;
load[bestK]+=remHat0;
preLoad[bestK]+=col[1].tau(req[rid].Lin);
nPendOn[bestK]++;
return bestK;
}
int Scheduler::fallbackBind(int rid){
int k=fallbackRR % K;
fallbackRR++;
req[rid].remote=k;
return k;
}
void Scheduler::raiseKeffForPrefill(){
if(Keff>=K)return;
if(waitOnly&&!linkBinding){Keff=K;return;}
if(sumLocPrefillWork<=1e-12)return;
int need=(int)ceil(sumRemPrefillWork/sumLocPrefillWork-1e-9);
if(need>Keff)Keff=min(K,need);
}
void Scheduler::checkKeffExpansion(){
if(Keff>=K)return;
double maxActive=0.0;
for(int i=0;i<Keff;++i)maxActive=max(maxActive,epoch.util[RES_REMOTE0+i]);
if(maxActive>KEFF_UTIL_THRESH)Keff++;
}
void Scheduler::aimdControl(double t){
(void)t;
double bnUtil=(epoch.bottleneck>=0)?epoch.util[epoch.bottleneck]:0.0;
double idleFrac=1.0-bnUtil;
int aFloor=max(1,max(mProc,mIoDyn));
bool tpotBinding=(exTpot>=exTdr&&pTPOT>0);
if(idleFrac>P.EPS_IDLE&&!parked.empty()&&unfinished>0
&&!tpotBinding
&&(policy::Admission::growOnFin||!aimdOnFinPath)){
AtargetCtrl+=max(1,AtargetCtrl/8);
}else if(tpotBinding&&wC>=wTp){
AtargetCtrl=max(aFloor,AtargetCtrl-max(1,AtargetCtrl/policy::Admission::shrinkDivisor));
}
AtargetCtrl=max(aFloor,min(AtargetCtrl,2000));
}
void Scheduler::admit(double t){
(void)t;
int effAtarget=AtargetCtrl;
if(unfinished<=P.LAMBDA*effAtarget)effAtarget=unfinished;
while(!parked.empty()&&(int)Aset.size()<effAtarget){
int rid=parked.front();
parked.pop_front();
Aset.push_back(rid);
setStage(rid,RD_DPRE);
enterA(rid);
req[rid].readyStamp=framesSeen;
rdDPre.push_back(rid);
}
}
bool Scheduler::resIdle(int res,double t)const{
if(res==RES_LOCAL)return!localBusy;
if(res==RES_UP)return qUp.empty()||qUp.front().finishTime<=t+1e-9;
if(res==RES_DOWN)return qDown.empty()||qDown.front().finishTime<=t+1e-9;
if(res>=RES_REMOTE0&&res<RES_REMOTE0+K)return!remBusy[res-RES_REMOTE0];
return false;
}
bool Scheduler::bnSetStarved(double t)const{
if(!epoch.bnConfident)return false;
for(int i=0;i<11;++i){
if(!((epoch.bnMask>>i)&1u))continue;
if(i>=RES_REMOTE0+K&&i<RES_UP)continue;
if(!resIdle(i,t))return false;
}
return true;
}
bool Scheduler::wouldBlowWaiting(bool delayingDecode,double delay){
if(wC<=0.0||delay<=0.0)return false;
if(delayingDecode){
if(exTpot>0.0||nSpan<=0)return false;
double Ge=max(1.0,(double)gapCount+futureGaps());
double SLO2t=binaryMode?SLO2*policy::WorkConservation::tpotCliffTrip:SLO2;
return tpotProj+(double)nSpan*delay/Ge>SLO2t;
}
if(exTdr>0.0||nPend<=0)return false;
double denom=(double)nTdrDone+(double)nPend;
if(denom<=0.0)return false;
double SLO1t=binaryMode?SLO1*policy::ClassArbitration::tdrCliffTrip:SLO1;
return tdrProj+(double)nPend*delay/denom>SLO1t;
}
bool Scheduler::evalR2(double dp,double dd,int n_p,int n_s,int site){
int&memo=(site==0)?memoLocal:((site==9)?memoGate:memoRemote[site-1]);
if(wC==0.0||(pTDR==0&&pTPOT==0)){
if(site==0){
if(wC>0.0&&exTdr==0.0&&exTpot==0.0&&nPend>0&&dd>dp){
double denomTdr=nTdrDone+nPend;
if(denomTdr>0.0){
double serial=policy::ClassArbitration::chargePendingEdgeSerial
?dp*nPend*(nPend+1)*0.5/denomTdr:0.0;
double projPref=tdrProj+serial;
double projDec=projPref+nPend*dd/denomTdr;
double SLO1t=binaryMode?SLO1*policy::ClassArbitration::tdrCliffTrip:SLO1;
if(projDec>SLO1t&&projPref<=SLO1t)return true;
}
}
if(policy::ClassArbitration::backpressureBinary
&&(binaryMode||reqCount>policy::ClassArbitration::backpressureMinR)){
double up=(double)qUp.size();
double dPre=(double)rdDPre.size();
double wPPre=readyPPre.empty()?-1e18:(double)readyPPre.size()-up;
double wPPost=readyPPost.empty()?-1e18:(double)readyPPost.size()-dPre;
double wDPre=rdDPre.empty()?-1e18:dPre-up;
double wDPost=rdDPost.empty()?-1e18:(double)rdDPost.size();
double wPref=max(wPPre,wPPost),wDec=max(wDPre,wDPost);
if(wPref>-1e17||wDec>-1e17)return wPref>wDec;
}
if(!rdDPost.empty())return false;
if((int)Aset.size()<AtargetCtrl&&!readyPPost.empty())return true;
}else if(site>=1&&site<=8){
if(policy::ClassArbitration::backpressureRemote
&&(binaryMode||reqCount>policy::ClassArbitration::backpressureMinR)){
int k=site-1;
double wPref=armPProc[k].empty()?-1e18
:(double)armPProc[k].size()-(double)readyPPost.size();
double wDec=rdDProc[k].empty()?-1e18
:(double)rdDProc[k].size()-(double)rdDPost.size();
if(wPref>-1e17||wDec>-1e17)return wPref>wDec;
}
}else{
if(n_s>0)return false;
}
return(Aset.size()<(size_t)AtargetCtrl);
}
double costPref=dp*n_s*pTPOT;
double costDec=dd*n_p*pTDR;
if(costPref*(1.0+P.ETA)<costDec){memo=1;return true;}
if(costDec*(1.0+P.ETA)<costPref){memo=0;return false;}
if(memo==-1){
bool pf=costPref<=costDec;
memo=pf?1:0;
return pf;
}
return memo==1;
}
void Scheduler::decideLocal(double t,Plan&plan){
if(localBusy)return;
bool canPrefill=!readyPPre.empty()||!readyPPost.empty();
bool canDecode=!rdDPre.empty()||!rdDPost.empty();
if(!canPrefill&&!canDecode)return;
int prefRid=-1;
bool prefIsPost=false;
double dPref=0.0;
if(!readyPPost.empty()){
prefRid=pickSptWithAging(readyPPost,t);
prefIsPost=true;
dPref=S+col[2].tau(req[prefRid].Lin);
}else if(!readyPPre.empty()){
prefRid=pickSptWithAging(readyPPre,t);
dPref=S+col[0].tau(req[prefRid].Lin);
}
bool decIsPost=!rdDPost.empty();
int decCol=0;
int decTake=0;
TaskType decShape=T_DPRE;
if(decIsPost){
decTake=groupCap((int)rdDPost.size(),mPost,mStar[2]);
decCol=5;decShape=T_DPOST;
}else if(!rdDPre.empty()){
decTake=groupCap((int)rdDPre.size(),mPre,mStar[0]);
decCol=3;decShape=T_DPRE;
}
double dDec=(decTake>0)?S+col[decCol].tau(decTake):0.0;
bool doPrefill;
if(canPrefill&&!canDecode)doPrefill=true;
else if(!canPrefill&&canDecode)doPrefill=false;
else if(waitOnly&&canPrefill&&nPend>0)doPrefill=true;
else{
doPrefill=evalR2(dPref,dDec,nPend,nSpan,0);
if(epoch.bnConfident&&wTp>0.0&&tpRun<tpUB){
int bn=epoch.bottleneck;
bool bnIdle=false;
if(bn==RES_LOCAL)bnIdle=!localBusy;
else if(bn==RES_UP)bnIdle=qUp.empty()||qUp.front().finishTime<=t+1e-9;
else if(bn==RES_DOWN)bnIdle=qDown.empty()||qDown.front().finishTime<=t+1e-9;
else if(bn>=RES_REMOTE0&&bn<RES_REMOTE0+K)bnIdle=!remBusy[bn-RES_REMOTE0];
if(policy::WorkConservation::requireWholeBottleneckIdle&&!waitMid()&&bnIdle)bnIdle=bnSetStarved(t);
if(bnIdle){
bool prefillFeeds=false,decodeFeeds=false;
if(bn==RES_LOCAL){
prefillFeeds=canPrefill;
decodeFeeds=canDecode;
}else if(bn==RES_UP){
prefillFeeds=!readyPPre.empty();
decodeFeeds=!rdDPre.empty();
}else if(bn==RES_DOWN){
if(waitMid()||policy::WorkConservation::downFeeders==1){
prefillFeeds=!readyPPre.empty();
decodeFeeds=!rdDPre.empty();
}else if(policy::WorkConservation::downFeeders==2){
prefillFeeds=!readyPPost.empty();
decodeFeeds=!rdDPost.empty();
}else{
prefillFeeds=false;
decodeFeeds=false;
}
}else if(bn>=RES_REMOTE0&&bn<RES_REMOTE0+K){
int bk=bn-RES_REMOTE0;
int predictedBind=-1;
for(int r:readyPPre){
if(req[r].remote==bk){prefillFeeds=true;break;}
if(req[r].remote==-1){
if(predictedBind==-1)predictedBind=peekBind();
if(predictedBind==bk){prefillFeeds=true;break;}
}
}
for(int r:rdDPre)if(req[r].remote==bk){decodeFeeds=true;break;}
}
if(prefillFeeds!=decodeFeeds){
bool want=prefillFeeds;
bool blocked=policy::WorkConservation::guardEnabled&&want!=doPrefill
&&wouldBlowWaiting(want,want?dPref:dDec);
if(!blocked)doPrefill=want;
}
}
}
}
auto runPrefill=[&](){
if(prefIsPost){
Assignment a;a.type=T_PPOST;a.server=-1;
a.rids.push_back(prefRid);
a.remote=req[prefRid].remote;
plan.addLocal(a);
}else{
hasDeferredLocalUpGate=true;
deferredLocalUpGate={prefRid,canDecode};
}
};
if(doPrefill&&prefRid>=0){runPrefill();return;}
if(decTake<=0)return;
vector<int>&pool=decIsPost?rdDPost:rdDPre;
int mGrid=decIsPost?mPost:mPre;
int mStarCol=decIsPost?mStar[2]:mStar[0];
int target=linkBinding?mGrid:max(mGrid,mStarCol);
if(!fireOrWait(RES_LOCAL,(int)pool.size(),target,decCol,decShape,t)){
deferCount[RES_LOCAL]++;
if(prefRid>=0)runPrefill();
return;
}
deferCount[RES_LOCAL]=0;
Assignment a;
a.type=decShape;
a.server=-1;
a.rids=selectGroup(pool,decTake);
a.m=(int)a.rids.size();
if(a.m>0)plan.addLocal(a);
}
void Scheduler::decideRemotes(double t,Plan&plan){
for(int k=0;k<K;++k){
if(remBusy[k])continue;
bool canPrefill=!armPProc[k].empty();
bool canDecode=!rdDProc[k].empty();
if(!canPrefill&&!canDecode)continue;
int ready=(int)rdDProc[k].size();
int decCap=canDecode?groupCap(ready,mProc,mStar[1]):0;
Piece pc{0,0};
double dPref=0.0;
if(canPrefill){
int rid=armPProc[k].front();
pc=choosePiece(rid,k,t);
dPref=S+(double)(pc.le-pc.ls)/max(1,NL)*col[1].tau(req[rid].Lin);
}
double dDec=canDecode?S+col[4].tau(decCap):0.0;
bool doPrefill;
if(canPrefill&&!canDecode)doPrefill=true;
else if(!canPrefill&&canDecode)doPrefill=false;
else{
doPrefill=evalR2(dPref,dDec,nPendOn[k],nSpanOn[k],k+1);
if(epoch.bnConfident&&wTp>0.0&&tpRun<tpUB){
int bn=epoch.bottleneck;
bool bnIdle=false;
if(bn==RES_REMOTE0+k)bnIdle=!remBusy[k];
else if(bn==RES_DOWN)bnIdle=qDown.empty()||qDown.front().finishTime<=t+1e-9;
else if(bn==RES_UP)bnIdle=qUp.empty()||qUp.front().finishTime<=t+1e-9;
else if(bn==RES_LOCAL)bnIdle=!localBusy;
if(bnIdle&&(bn==RES_DOWN||bn==RES_LOCAL)){
bool prefillFeeds=canPrefill&&pc.le==NL;
if(prefillFeeds&&!canDecode)doPrefill=true;
else if(canDecode&&!prefillFeeds)doPrefill=false;
}
}
}
bool tStarForced=canPrefill&&!doPrefill&&consecD[k]>=T_STAR;
if(tStarForced)doPrefill=true;
if(doPrefill&&policy::RemotePrefill::guardEnabled&&nSpanOn[k]>0&&wC>0.0
&&exTdr==0.0&&exTpot==0.0){
double window=nextDecodeLandingOn(k,t);
if(dPref>policy::RemotePrefill::windowMargin*window){
double Ge=max(1.0,(double)gapCount+futureGaps());
double SLO2t=binaryMode?SLO2*policy::WorkConservation::tpotCliffTrip:SLO2;
if(tpotProj+(double)nSpanOn[k]*(dPref-window)/Ge>SLO2t)
doPrefill=false;
}
}
if(doPrefill){
int rid=armPProc[k].front();
if(pc.le==NL){
deferredGates.push_back({k,rid,pc,tStarForced,canDecode});
continue;
}
Req&rr=req[rid];
rr.heldSince=-1;
rr.heldTotal=0;
consecD[k]=0;
Assignment a;a.type=T_PPROC;a.server=k;a.remote=k;
a.ls=pc.ls;a.le=pc.le;
a.rids.push_back(rid);
plan.addRemote(k,a);
continue;
}
if(!canDecode||decCap<=0)continue;
int target=linkBinding?mProc:max(mProc,mStar[1]);
if(!fireOrWait(RES_REMOTE0+k,ready,target,4,T_DPROC,t)){
deferCount[RES_REMOTE0+k]++;
continue;
}
deferCount[RES_REMOTE0+k]=0;
consecD[k]++;
Assignment a;a.type=T_DPROC;a.server=k;a.remote=k;
a.rids=selectGroup(rdDProc[k],decCap);
a.m=(int)a.rids.size();
if(a.m>0)plan.addRemote(k,a);
}
}
void Scheduler::processDeferredGates(double t,Plan&plan){
for(auto&dg:deferredGates){
int rid=dg.rid;
int k=dg.k;
bool canDecode=dg.canDecode;
const Piece&pc=dg.pc;
if(plan.usedRemote[k])continue;
if(policy::TransferGate::remoteGateEnabled&&gateHoldsPrefillTransfer(rid,true,t)){
Req&rr=req[rid];
rr.heldTotal+=(rr.heldSince>=0?(t-rr.heldSince):0.0);
rr.heldSince=t;
if(!canDecode){
Assignment a;a.type=T_PPROC;a.server=k;a.remote=k;
a.ls=pc.ls;a.le=pc.le;
a.rids.push_back(rid);
plan.addRemote(k,a);
}else{
int ready=(int)rdDProc[k].size();
int decCap=canDecode?groupCap(ready,mProc,mStar[1]):0;
if(canDecode&&decCap>0){
int target=linkBinding?mProc:max(mProc,mStar[1]);
if(fireOrWait(RES_REMOTE0+k,ready,target,4,T_DPROC,t)){
deferCount[RES_REMOTE0+k]=0;
consecD[k]++;
Assignment a;a.type=T_DPROC;a.server=k;a.remote=k;
a.rids=selectGroup(rdDProc[k],decCap);
a.m=(int)a.rids.size();
if(a.m>0)plan.addRemote(k,a);
}else{
deferCount[RES_REMOTE0+k]++;
}
}
}
}else{
Req&rr=req[rid];
rr.heldSince=-1;rr.heldTotal=0;
consecD[k]=0;
Assignment a;a.type=T_PPROC;a.server=k;a.remote=k;
a.ls=pc.ls;a.le=pc.le;
a.rids.push_back(rid);
plan.addRemote(k,a);
}
}
deferredGates.clear();
if(hasDeferredLocalUpGate){
int rid=deferredLocalUpGate.rid;
bool canDecode=deferredLocalUpGate.canDecode;
if(gateHoldsPrefillTransfer(rid,false,t)){
Req&rr=req[rid];
rr.heldTotal+=(rr.heldSince>=0?(t-rr.heldSince):0.0);
rr.heldSince=t;
if(canDecode&&!localBusy&&!plan.usedLocal){
bool decIsPost=!rdDPost.empty();
int decCap=0,decCol=0;
TaskType decShape=T_DPRE;
if(decIsPost){
decCap=groupCap((int)rdDPost.size(),mPost,mStar[2]);
decCol=5;decShape=T_DPOST;
}else if(!rdDPre.empty()){
decCap=groupCap((int)rdDPre.size(),mPre,mStar[0]);
decCol=3;decShape=T_DPRE;
}
if(decCap>0){
vector<int>&pool=decIsPost?rdDPost:rdDPre;
int ready=(int)pool.size();
int mGrid=decIsPost?mPost:mPre;
int mStarCol=decIsPost?mStar[2]:mStar[0];
int target=linkBinding?mGrid:max(mGrid,mStarCol);
if(fireOrWait(RES_LOCAL,ready,target,decCol,decShape,t)){
deferCount[RES_LOCAL]=0;
Assignment a;a.type=decShape;a.server=-1;
a.rids=selectGroup(pool,decCap);
a.m=(int)a.rids.size();
if(a.m>0)plan.addLocal(a);
}else{
deferCount[RES_LOCAL]++;
}
}
}
}else if(!localBusy&&!plan.usedLocal){
Req&rr=req[rid];
rr.heldSince=-1;
rr.heldTotal=0;
Assignment a;a.type=T_PPRE;a.server=-1;
a.rids.push_back(rid);
a.remote=bind(rid);
plan.addLocal(a);
}
hasDeferredLocalUpGate=false;
}
}

