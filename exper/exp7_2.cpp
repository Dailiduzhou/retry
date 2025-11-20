#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(){
    char str[100];
    char res[100];
    int n=0, i=1;

    fgets(str, sizeof(str), stdin);
    
    str[strcspn(str, "\n")] = '\0';

    int flag = 0;
    if (isdigit(str[0])){
        res[n] = str[0];
        n++;
        flag = 1;
    }
    
    while (str[i] != '\0'){
        if (!isdigit(str[i])){
            ++i;
            flag =0;
            continue;
        }
        if (!flag){
            res[n]='*';
            n++;
        }
        res[n] = str[i];
        ++i, ++n;
        flag = 1;
    }
    res[n+1] = '\0';
    printf("%s", res);
}