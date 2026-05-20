#include <stdio.h>

#define MAX(a,b) ((a)>(b)?(a):(b))
#define int long long

int cmp(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}

void solve(){
    int n;
    scanf("%d",&n);
    int arr[n],brr[n];
    for(int i = 0; i < n ;i++) scanf(" %d ",&arr[i]);
    for(int i = 0; i < n ;i++) scanf(" %d ",&brr[i]);
    qsort(arr,n,sizeof(int),cmp);
    for(int i = 0; i < n; i++) printf("%d ",arr[i]);
    printf("\n");
    int ans = -1;
    // x value
    for(int i = 0; i < n; i++){
        int x = arr[i];
        
        int cnt= 0;
        for(int j = 0; j < n;j++){
          if (arr[j] >=x) cnt++;
        }
        printf("x: %d \t cnt: %d\n",x,cnt);
        
        
        int j= 0;
        int lvl = 0;
        while(cnt > 0 && j < n){
            printf("\tcnt: %d \t brr[j]: %d \t lvl: %d\n",cnt,brr[j],lvl);
            if (cnt>=brr[j]){
                printf("\t\t...\n");
                lvl++;
            } 
            cnt -= brr[j++];
            printf("\t\tcnt: %d \t brr[j]: %d \t lvl: %d\n",cnt,brr[j],lvl);
        }
        printf("cleared level : %d\n",lvl);
        int res = x * lvl;
        
        ans = MAX(ans, res);
    }
    printf("The final ans is : %d\n",ans);
}

signed main(){
    int t;
    scanf("%lld",&t);
    while(t--){
        solve();
    }
    return 0;
}
