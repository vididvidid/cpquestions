#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}

void solve(){
    int n;
    scanf("%d",&n);
    
    int arr[n];
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    qsort(arr,n,sizeof(int),cmp);
    
    printf("The array after sorting is : \n");
    for(int i=0;i<n;i++) printf("%d ",arr[i]);
    printf("\n");
    
    
    int bn = arr[n-1];
    int brr[bn+1];
    for(int i=0;i<=bn;i++){
        brr[i] = 0;
    }
    
    
    int x = arr[0];
    if(x > 0) x = -1*x;
    for(int i=0;i<n;i++){
        arr[i] += x;
    }
    
    printf("The array after operation with x (%d)  is : \n", x);
    for(int i=0;i<n;i++) printf("%d ",arr[i]);
    printf("\n");
    
    int mex=0;
    for(int i=0;i<n;i++){
        brr[arr[i]] = 1;
    }
    
    printf("The brr array  is : \n");
    for(int i=0;i<=bn;i++) printf("%d ",brr[i]);
    printf("\n");
    
    
    for(int i=0;i<=bn;i++){
        if(brr[i]==0){
            mex = i;
            break;
        }
    }
    printf("%d\n",mex);
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
    return 0;
}

