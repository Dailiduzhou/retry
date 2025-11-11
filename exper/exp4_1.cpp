#include<stdio.h>
#include<math.h>
int main(){
    double t;
    printf("please type an integer:\n");
    // verification
    if (scanf("%lf", &t) != 1){
        printf("error: not a number, exit");
        return 0;
    }
    // isfloat
    if ((int)t != t){
        printf("error: not an integer, exit");
        return 0;
    }
    // isnegtive
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
    int sum = 0;
    int d = digits-1;
    for (int i=0;i<digits;i++){
        sum += pow(10, d) * b[i];
        d--;
    }
    // pow(10, d)取10的d次幂
    printf("%d", sum);
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

    for (int i=digits-1;i>=0;i--){
        printf("%d", b[i]);
    }
    printf("\nmin:");
    sum = 0;
    d = digits-1;
    for (int i=0;i<digits;i++){
        sum += pow(10, d) * b[i];
        d--;
    }
    printf("%d", sum);
    printf("\n");
}