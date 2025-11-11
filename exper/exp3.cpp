#include<stdio.h>
#include<string.h>

int main(){
    char a[5];
    for (int i=0;i<5;++i){
        scanf("%c", &a[i]);
    }
    for (int i = 0, j= 4; i<j; i++, j--){
        if (a[i] != a[j]){
            printf("No");
            return 0;
        }
    }
    printf("Yes");
    return 0;
}