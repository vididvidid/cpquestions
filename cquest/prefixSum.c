#include <stdio.h>

#define MAXN 200005

int a[MAXN];
int t[4*MAXN];
int n;

void build(int a[], int v, int tl, int tr){
    if(tl==tr){
        t[v] = a[tl];
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
        t[v] = new_val;
    } else {
        int tm = (tl+tr)/2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else 
            update(v*2+1, tm+1, tr, pos, new_val);
            
        t[v] = t[v*2] + t[v*2+1];
    }
}

long long query_sum(int v, int tl, int tr, int l, int r){
    if (l>r) return 0;
    if (l==tl && r==tr) return t[v];
    int tm = (tl+tr)/2;
    return query_sum(v*2, tl, tm, l, (r<tm?r:tm)) + 
           query_sum(v*2+1, tm+1, tr, (l>tm+1?l:tm+1),r);
}

// Debug version: Prints the logic trace
int find_prefix_bs(int target_sum) {
    printf("\n--- Starting Binary Search for Target: %d ---\n", target_sum);
    
    // Safety Check: Is the total sum even enough?
    long long total_sum = t[1]; // Root holds total sum
    if (total_sum < target_sum) {
        printf("Total sum (%lld) is less than target. Returning -1.\n", total_sum);
        return -1;
    }

    int l = 1, r = n, ans = -1;
    
    while (l <= r) {
        int mid = (l + r) / 2;
        
        // Query sum from index 1 to mid
        long long current_sum = query_sum(1, 1, n, 1, mid);
        
        printf("Checking range [1...%d]: Sum = %lld ", mid, current_sum);
        
        if (current_sum >= target_sum) {
            printf(">= Target. (Possible Answer! Trying smaller index)\n");
            ans = mid;
            r = mid - 1; // Try to look to the left
        } else {
            printf("< Target. (Need more elements)\n");
            l = mid + 1; // Need to move right
        }
    }
    printf("Final Answer: %d\n", ans);
    return ans;
}

int find_prefix_descent(int v, int tl, int tr, long long k){
    if (k>t[v]) return -1;
    if (tl==tr) return tl;
    int tm = (tl+tr)/2;
    if(t[v*2]>=k){
        return find_prefix_descent(v*2,tl,tm,k);
    } else{
        return find_prefix_descent(v*2+1,tm+1,tr,k-t[v*2]);
    }
}
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    
    build(a,1,1,n);
    int target = 5;
    printf("Target Sum: %d\n",target);
    int idx1 = find_prefix_bs(target);
    printf("Method 1 (Binary Search): Index %d\n",idx1);
    
    int idx2;
    if(t[1]<target) idx2 = -1;
    else idx2 = find_prefix_descent(1,1,n,target);
    printf("Method 2 (Tree Descent): Index %d\n",idx2);
}


int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
    return 0;
}







