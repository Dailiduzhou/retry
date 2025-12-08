#include<stdio.h>
#include<stdlib.h>

int main(){
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    int** a = (int**)malloc(n*sizeof(int*));
    for (int i=0;i<n;++i){
        a[i] = (int*)malloc(m*sizeof(int));
    }

    for (int i= 0;i<n;++i){
        for(int j =0;j<m;++j){
            scanf("%d", &a[i][j]);
        }
    }

    int** at = (int**)malloc(m*sizeof(int*));
    for (int i=0;i<m;++i){
        at[i] = (int*)malloc(n*sizeof(int));
    }

    for (int i =0;i<n;++i){
        for (int j =0;j<m;++j){
            at[j][i] = a[i][j];
        }
    }

    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            printf("%d ", at[i][j]);
        }
        printf("\n");
    }

    for (int i=0;i<n;++i){
        free(a[i]);
    }
    for (int i=0;i<m;++i){
        free(at[i]);
    }
    free(a);free(at);
}