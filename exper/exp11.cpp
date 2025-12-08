#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* shift(char* ptr, int n, char mode);

int main(){
    char a[9] = "12345678";
    int n;
    scanf("%d", &n);
    shift(a, n, 'L');
    int i =0;
    while(*(a+i) != '\0'){
        printf("%c", *(a+i));
        ++i;
    }
    printf("\n");
    i=0;
    shift(a, n, 'R');
    while(*(a+i) != '\0'){
        printf("%c", *(a+i));
        ++i;
    }
}

char* shift(char* pstr, int n, char mode){
    if (pstr == NULL || strlen(pstr) == 0)
        return pstr;
    if (n == 0)
        return pstr;
    
    switch (mode)
    {
    case 'L':
        n = -n;
        break;
    
    case 'R':
        break;
    default:
        exit(-1);
    }
    int len = strlen(pstr);
    char* temp = (char*)malloc((len+1)*sizeof(char));
    for (int i = 0;i<len; i++){
        temp[(i+n+len)%len] = pstr[i];
    }
    strcpy(pstr, temp);
    free(temp);
    
    return pstr;
}
