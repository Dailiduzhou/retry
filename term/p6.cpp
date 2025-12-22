#include<ctype.h>
#include<stdio.h>
#include<string.h>

int ishuiwen(char* a){
    int len = strlen(a);
    char* p1 = a;
    char* p2 = a + len - 1;

    for (;p1<p2;p1++, p2--){
        if (*p1 != *p2){
            return 0;
        }
    }
    return 1;
}

int main(){
    for (int i = 0; i<=200;++i){
        char a[10];
        sprintf(a, "%d", i*i);
        if (ishuiwen(a)){
            printf("%s\n", a);
        }
    }
}