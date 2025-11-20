#include<stdio.h>

int main(){
    int a[10],b[10];
    printf("array 1\n");
    for (int i=0;i<10;++i){
        scanf("%d", a+i);
    }
    printf("array 2\n");
    for (int i=0;i<10;++i){
        scanf("%d", b+i);
    }
    
    for (int i=0;i<9;++i){
        for (int j=i+1;j<10;++j){
            if (a[i] < a[j]){
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }

    for (int i=0;i<9;++i){
        int ith = i;
        for (int j=i+1; j<10;++j){
            if (b[ith] < b[j]){
                ith = j;
            }
        }
        int t = b[i];
        b[i] = b[ith];
        b[ith] = t;
    }

    printf("array 1\n");
    for (int i=0;i<10;++i){
        printf("%d, ", a[i]);
    }
    printf("\n");

    printf("array 2\n");
    for (int i=0;i<10;++i){
        printf("%d, ", b[i]);
    }

    printf("\n");
    int c[20];
    int i= 0, j=0, k=0;
    while (i<10 && j<10){
        if (a[i]>b[j]){
            c[k] = a[i];
            i++;
        } else {
            c[k] = b[j];
            j++;
        }
        k++;
    }
    for (;i<10;i++,k++){
        c[k]=a[i];
    }
    for (;j<10;j++,k++){
        c[k]=b[j];
    }
    printf("res: \n");
    for (int o=0;o<k;o++){
        printf("%d, ", c[o]);
    }
}
