#include <stdio.h>
#include <stdbool.h>

#define MAXN 2000005
int n,m,h;
int arr[MAXN],trr[MAXN];
bool check(){
    for(int i=1;i<=n;i++){
        if(trr[i]>=h){
            return true;
        }
    }
    return false;
}

void solve(){
    scanf("%d %d %d",&n,&m,&h);
    for(int i=1;i<=n;i++){ scanf("%d",&arr[i]); trr[i] = arr[i];}
    while(m--){
        int b,c;
        scanf("%d %d",&b,&c);
        arr[b] = c;
        if(check){
            for(int j=1;j<=n;j++){
                trr[j] = arr[j];
            }
        }
    }
    for(int i=1;i<n;i++){
        printf("%d ",trr[i]);
    }
    printf("\n");
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
    return 0;
}
