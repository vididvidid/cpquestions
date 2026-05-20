#include <stdio.h>

#define MAXN 200005
#define MAX(a,b) ((a)>(b)?(a):(b))
#define INF 1e9

int a[MAXN];
int t[4*MAXN];
int n;

void build(int a[], int v, int tl, int tr) {
    if (tl==tr){
        t[v] = a[tl];
    } else {
        int tm = (tl+tr)/2;
        build(a,v*2,tl,tm);
        build(a,v*2+1,tm+1,tr);
        t[v] = MAX(t[v*2],t[v*2+1]);
    }
}

void update(int v, int tl, int tr, int pos, int new_val){
    if (tl==tr) {
        t[v] = new_val;
        a[pos] = new_val;
    } else {
        int tm = (tl+tr)/2;
        if(pos<=tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);

        t[v] = MAX(t[v*2], t[v*2+1]);
    }
}

int get_first(int v,int tl, int tr, int l, int r, int x){
    if (l>r || tl>r || tr<l) return -1;
    if (t[v] <= x) return -1;
    if (tl == tr) return tl;
    int tm = (tl+tr)/2;
    int res = get_first(v*2, tl,tm,l,r,x);
    if(res!=-1) {
        return res;
    }
    return get_first(v*2+1,tm+1,tr,l,r,x);
}

int query(int v, int tl, int tr, int l, int r){
    if (l>r) return -INF;
    if (l==tr && r == tr) return t[v];
    int tm = (tl+tr)/2;
    return MAX(
            query(v*2,tl,tm,l,(r<tm?r:tm)),
            query(v*2+1,tm+1,tr,(l>tm+1?l:tm+1),r)
            );
}

int get_first_bs(int target){
    int maxVal = t[1];
    if (maxVal < target) return -1;
    int l = 1, r=n,ans=-1;
    while(l<=r){
        int mid = (l+r)/2;
        if(query(1,1,n,1,mid)>=target){
            ans = mid;
            r = mid-1;
        }else{
            l = mid+1;
        }
    }
    return ans;
}

void solve(){ 
    n = 5;
    int input[] = {-1, 2, 4, 0, 5, 1};
    for(int i=1;i<=n;i++) a[i] = input[i];
    build(a,1,1,n);

    printf("Array: [2,4,0,5,1]\n");
    int x =3;
    int l = 2, r = 5;
    printf("First > %d in range [%d, %d]: Index %d\n",x,l,r,get_first(1,1,n,l,r,x));
    
    printf("(Binary) First > %d in range [%d, %d]: Index %d\n",x,l,r,get_first_bs(x));

}

int main(){
    solve();
    return 0;
    
}
