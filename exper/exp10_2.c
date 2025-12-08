#include<stdio.h>
#include<stdlib.h>
void fun(int x, int* p, int* n);

int main(){
    int x;
    printf("x:");
    scanf("%d", &x);
    int* p = (int*)malloc(1e6*sizeof(int));
    int* n = (int*)malloc(sizeof(int));
    *n = 0;
    fun(x, p, n);
    printf("n=%d\n", *n);
    if (*n==0){
        free(p);
        free(n);
        return 0;
    }
    for (int i = 0;i < *n;++i){
        printf("%d\n", *(p+i));
    }
    free(p);
    free(n);
}

void fun(int x, int* p, int* n)
{
    if (x&1){
        return;
    }
    for (int i=2; i<=x;i+=2){
        if (x%i==0){
            *(p+*n) = i;
            *n+=1;
        }
    }
}