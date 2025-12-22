#include<stdio.h>
#include<stdlib.h>

int* moveElements(int* arr, int n, int target){
    for (int i = 0;i<n; i++){
        if (arr[i] == target){
            for (int j = i; j<n-1; j++){
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
        }
    }
    
    return arr;
}

int main(){
    printf("n:\n");
    int n, target;
    scanf("%d", &n);
    printf("arr:\n");
    int a[n];
    for (int i=0;i<n;++i){
        scanf("%d", &a[i]);
    }

    printf("target:\n");
    scanf("%d", &target);

    int* b = (int*)malloc(n* sizeof(int));
    b = moveElements(a, n, target);
    printf("\n");
    for (int i =0;i<n;++i){
        printf("%d ", b[i]);
    }
}
