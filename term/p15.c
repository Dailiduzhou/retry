#include<stdio.h>
#include<stdlib.h>

int cnt[10];

void cal(int n){
    char buf[6];
    sprintf(buf, "%d", n);

    int product = 1, i = 0;
    while (*(buf+i) != '\0'){
        if (*(buf+i) != '0'){
            product *= *(buf+i) - '0';
        } 
        i++;
    }
    
    if (product >= 1 && product <= 9){
        cnt[product]++;
    }
}

int main(){
    for (int i = 1; i < 10000; i++){
        cal(i);
    }
    
    printf("乘积根为1-9的数字个数：\n");
    for (int i = 1; i <= 9; i++){
        printf("乘积根为%d的数有: %d个\n", i, cnt[i]);
    }
    
    return 0;
}