#include<stdio.h>
#include<algorithm>
int main(){
    double t;
    printf("please type a four-digit integer:\n");
    if (scanf("%lf", &t) != 1){
        printf("error: not a number, exit");
        return 0;
    }
    if ((int)t != t){
        printf("error: not an integer, exit");
        return 0;
    }
    if (t<=0){
        printf("error: not a positive integer, exit");
        return 0;
    }
    int a = t;
    int b[20];
    int digits = 0;
    int i =0;
    while (a){
        b[i]=a%10;
        a/=10;
        i++;
        digits++;
    }
    if (digits != 4) {
        printf("%d-digit integer\n");
        printf("invalid input, exit.");
        return 0;
    }
    for (int i=0;i<4;i++){
        printf("%d", b[i]);
    }
    printf("\nmax:");
    
    // bubbling sort
    for (int i = 0; i < digits - 1; ++i){
        for (int j = i+1; j<digits; ++j){
            int temp = b[i];
            if (b[i] > b[j]){
                b[i] = b[j];
                b[j] = temp;
            }
        }
    }
    for (int i=3;i>=0;i--){
        printf("%d", b[i]);
    }
    printf("\nmin:");
    for (int i=0;i<4;++i){
        printf("%d", b[i]);
    }
    printf("\n");
    
}