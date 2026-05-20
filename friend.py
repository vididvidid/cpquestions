#
# File: friend.py
# Author: vididvidid 
# Created: 2026-04-15 02:32:00
#

# cook your dish here
#  ____   ____      _     _  __ _   _     _     ____  
# |  _ \ |  _ \    / \   | |/ /| | | |   / \   |  _ \ 
# | |_) || |_) |  / _ \  | ' / | |_| |  / _ \  | |_) |
# |  __/ |  _ <  / ___ \ | . \ |  _  | / ___ \ |  _ < 
# |_|    |_| \_\/_/   \_\|_|\_\|_| |_|/_/   \_\|_| \_\

import sys
import math
import bisect
import heapq
from sys import stdin,stdout
from math import gcd,floor,sqrt,log
from collections import defaultdict
from collections import deque
from collections import Counter
import itertools
import bisect
sys.setrecursionlimit(100000000)

# Basic I/O
inp    =lambda: int(input())
strng  =lambda: input().strip()
strl   =lambda: list(input().strip())
mul    =lambda: map(int,input().strip().split())
mulf   =lambda: map(float,input().strip().split())
ls     =lambda: list(map(int,input().strip().split()))
lsstr  =lambda: list(input().split())
flush  =lambda: stdout.flush()
stdstr =lambda: stdin.readline()
stdint =lambda: int(stdin.readline())
stdpr  =lambda x: stdout.write(str(x))
cases  =lambda x: print("Case #"+str(x)+": ",end="")

# Enhanced I/O
matrix =lambda r,c: [seq() for _ in range(r)]
chars  =lambda: [*input().strip()]
chars2d=lambda r: [chars() for _ in range(r)]

# List operations
unique =lambda l: list(set(l))
maxidx =lambda l: max(range(len(l)),key=lambda i:l[i])
minidx =lambda l: min(range(len(l)),key=lambda i:l[i])
rev    =lambda l: l[::-1]
suml   =lambda l: sum(l)
prodl  =lambda l: reduce(lambda x,y:x*y, l)
mapl   =lambda f,l: list(map(f,l))
filterl=lambda f,l: list(filter(f,l))
sortl  =lambda l,rev=False: sorted(l,reverse=rev)
sortkl =lambda l,k: sorted(l,key=k)
chunk  =lambda l,n: [l[i:i+n] for i in range(0,len(l),n)]

# Math operations
lcm    =lambda x,y: abs(x*y)//gcd(x,y)
fact   =lambda x: math.factorial(x)
nCr    =lambda n,r: fact(n)//(fact(r)*fact(n-r))
nPr    =lambda n,r: fact(n)//fact(n-r)
isqrt  =lambda x: int(sqrt(x))
ipow   =lambda x,p: pow(x,p)
round2 =lambda x,d=0: round(x,d)
issqr  =lambda x: int(sqrt(x))**2==x
is_prime = lambda n: n > 1 and all(n % i != 0 for i in range(2, int(n ** 0.5) + 1)) 

# String operations
ords   =lambda s: [ord(c) for c in s]
chrs   =lambda l: ''.join(map(chr,l))
lowers =lambda s: s.lower()
uppers =lambda s: s.upper()
ispal  =lambda s: s==s[::-1]
concat =lambda l: ''.join(map(str,l))

# 2D Grid operations
dirs4  =lambda: [(0,1),(1,0),(0,-1),(-1,0)]
dirs8  =lambda: [(0,1),(1,1),(1,0),(1,-1),(0,-1),(-1,-1),(-1,0),(-1,1)]
valid  =lambda x,y,r,c: 0<=x<r and 0<=y<c
dist   =lambda x1,y1,x2,y2: abs(x1-x2)+abs(y1-y2)
dist2  =lambda x1,y1,x2,y2: sqrt((x1-x2)**2+(y1-y2)**2)

# Binary operations
countbits=lambda n: bin(n).count('1')
lowestbit=lambda x: x&(-x)
highestbit=lambda x: 1<<(len(bin(x))-3)
ispower2=lambda n: n and not(n&(n-1))

# Dictionary operations
sort_by_keys = lambda d: dict(sorted(d.items(), key=lambda item: item[0]))
sort_by_values = lambda d: dict(sorted(d.items(), key=lambda item: item[1]))
reversed_dict = lambda d: dict(reversed(d.items()))

# Quick debug
debug  =lambda *x: print(*x, file=sys.stderr)
YES    =lambda: print("YES")
NO     =lambda: print("NO")
Yes    =lambda: print("Yes")
No     =lambda: print("No")

mod=1000000007

# main code

n=inp()
lst=ls()
ans=0
curr=0.5
for i in lst:
    j=i*2
    if(curr<0):
        curr+=j 
        if(curr>0):
            ans+=1
    else:
        curr-=j
        if(curr<0):
            ans+=1
print(ans)



    
