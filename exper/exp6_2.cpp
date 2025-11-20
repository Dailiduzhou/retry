#include<stdio.h>

int main(){
    int a[10],b[10];
    printf("array 1\n");
    for (int i=0;i<10;++i){
        scanf("%d", &a[i]);
    }
    printf("array 2\n");
    for (int i=0;i<10;++i){
        scanf("%d", &b[i]);
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
    while (i < 10 && j < 10) {
    if (a[i] > b[j]) {
        if (k == 0 || c[k-1] != a[i]) {
            c[k] = a[i];
            k++;
        }
        i++;
    } else if (a[i] < b[j]) {
        if (k == 0 || c[k-1] != b[j]) {
            c[k] = b[j];
            k++;
        }
        j++;
    } else {
        if (k == 0 || c[k-1] != a[i]) {
            c[k] = a[i];
            k++;
        }
        i++;
        j++;
    }
}

while (i < 10) {
    if (k == 0 || c[k-1] != a[i]) {
        c[k] = a[i];
        k++;
    }
    i++;
}

while (j < 10) {
    if (k == 0 || c[k-1] != b[j]) {
        c[k] = b[j];
        k++;
    }
    j++;
}

    printf("res: \n");
    for (int o=0;o<k;o++){
        printf("%d, ", c[o]);
    }
}