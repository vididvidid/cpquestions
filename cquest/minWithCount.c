/* 
        normal 4*MAXN
            int tm = (tl+tr)/2;
            build(a,v*2,tl,tm);
            build(a,v*2+1,tm+1,tr);
            t[v] = MIN(t[v*2] , t[v*2+1]);
        optimized 2*MAXN
            int tm = (tl+tr)/2;
            int rightChild = v+2*(tm-tl+1);
            build(a,v+1,tl,tm);
            build(a,rightChild,tm+1,tr);
            t[v] = MIN(t[v+1] , t[rightChild]);
*/
        
#include <stdio.h>

#define MAXN 200005
#define INF 1e9
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

int a[MAXN];
int n;

typedef struct {
    int first;
    int second;
} Pair;

Pair t[2*MAXN];

Pair combine(Pair a, Pair b){
    if(a.first < b.first){
        return a;
    }
    if(a.first > b.first){
        return b;
    }
    return (Pair){a.first, a.second + b.second};
}


void build(int a[], int v, int tl, int tr){
    if(tl==tr){
        t[v] = (Pair){a[tl],1};
    } else {
        int tm = (tl+tr)/2;
        int rightChild = v+2*(tm-tl+1);
        build(a,v+1,tl,tm);
        build(a,rightChild,tm+1,tr);
        t[v] = combine(t[v+1],t[rightChild]);
    }
}

Pair mn(int v, int tl, int tr, int l, int r){
    if(l>r){
        return (Pair){-INF, 0};
    }else if (l==tl && r==tr){
        return t[v];
    }else{
        int tm = (tl+tr)/2;
        int rightChild = v+2*(tm-tl+1);
        return combine(mn(v+1,tl,tm,l,MIN(r,tm)) , mn(rightChild,tm+1,tr,MAX(l,tm+1),r));
    }
}

// int sum(int v, int tl, int tr, int l, int r){
//     if(l>r){
//         return 0;
//     }else if (l==tl && r==tr){
//         return t[v];
//     }else{
//         int tm = (tl+tr)/2;
//         int rightChild = v+2*(tm-tl+1);
//         return sum(v+1,tl,tm,l,MIN(r,tm)) + sum(rightChild,tm+1,tr,MAX(l,tm+1),r);
//     }
// }

Pair update(int v,int tl, int tr, int pos, int new_val){
    if(tl==tr){
        t[v] = (Pair){new_val,1};
    }else{
        int tm= (tl+tr)/2;
        int rightChild = v+2*(tm-tl+1);
        if(pos<=tm){
            update(v+1,tl,tm,pos,new_val);
        }else{
            update(rightChild,tm+1,tr,pos,new_val);
        }
        t[v] = combine(t[v+1],t[rightChild]);
    }
}

void debug_tree(int v,int tl, int tr, int depth){
    for(int i=0;i<depth;i++) printf("  ");
    
    if(depth>0) printf(" |--");
    
    printf("node[%d]: a[%d ... %d] = {%d, %d}\n",v,tl,tr,t[v].first, t[v].second);
    
    if(tl!=tr){
        int tm = (tl+tr)/2;
        int rightChild = v+2*(tm-tl+1);
        debug_tree(v+1,tl,tm,depth+1);
        debug_tree(rightChild,tm+1,tr,depth+1);
    }
}


void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    build(a,1,1,n);
    debug_tree(1,1,n,0);
    printf("\n----\n");
    update(1,1,n,1,10);
    debug_tree(1,1,n,0);
    Pair ans = mn(1,1,n,1,n);
    printf("%d %d ",ans.first, ans.second);
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
    return 0;
}
