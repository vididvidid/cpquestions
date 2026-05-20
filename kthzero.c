#include <stdio.h>

#define MAXN 200005

int a[MAXN];
int t[4*MAXN];
int n;

void build(int a[], int v, int tl, int tr){
    if(tl==tr){
        if(a[tl] == 0) t[v] = 1;
        else t[v] = 0;
    } else{
        int tm = (tl+tr)/2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
}

void update(int v, int tl, int tr, int pos, int new_val){
    if(tl==tr){
        a[pos] = new_val;
        if(new_val==0){
            t[v] = 1;
        } else {
            t[v] = 0;
        }
    } else {
        int tm = (tl+tr)/2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else 
            update(v*2+1, tm+1, tr, pos, new_val);
            
        t[v] = t[v*2] + t[v*2+1];
    }
}

int count_zeros(int v, int tl, int tr, int l, int r){
    if (l>r){
        return 0;
    } else if ( l==tl && r==tr){
        return t[v];
    } else {
        int tm = (tl+tr)/2;
        return count_zeros(v*2,tl,tm,l,(r<tm?r:tm))+
               count_zeros(v*2+1, tm+1, tr, (l>tm+1?1:tm+1), r);
    }
}

int find_kth(int v, int tl, int tr, int k){
    if (k>t[v]) return -1;
    if (tl==tr) return tl;
    int tm = (tl+tr)/2;
    int zeros_in_left = t[v*2];
    if(zeros_in_left >= k){
        return find_kth(v*2,tl,tm,k);
    }else{
        return find_kth(v*2+1,tm+1,tr,k-zeros_in_left);
    }
}

void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    
    build(a,1,1,n);
    int k = 2;
    int idx = find_kth(1,1,n,k);
    if(idx!=-1)
        printf("the %d-th zero is at index: %d\n",k,idx);
    else
        printf("there are not enough zeros\n");
    
    printf("Total zeros: %d\n", count_zeros(1,1,n,1,n));
}


int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
    return 0;
}






