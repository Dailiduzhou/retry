#include<stdio.h>
#include<algorithm>
int main(){
    int a;
    scanf("%d", &a);
    int b[4];
    for (int i=0;i<4;++i){
        b[i]=a%10;
        a/=10;
    }
    for (int i=0;i<4;i++){
        printf("%d", b[i]);
    }
    printf("\nmax:");
    std::sort(b, b+4);
    for (int i=3;i>=0;i--){
        printf("%d", b[i]);
    }
    printf("\nmin:");
    for (int i=0;i<4;++i){
        printf("%d", b[i]);
    }
    printf("\n");
    
}