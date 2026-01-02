#include <stdio.h>
#include<stdlib.h>
int main()
{
    int num;
    int n1,n2,n3,n4;
    scanf_s("%d", &num);
    n1 = (num /1000);
    n2 = (num/100%10);
    n3 = (num/10%10);
    n4 = (num%10);
    if (n1 <= 0){
        return 0;
    }
    printf("%d%d%d%d", n4, n3, n2, n1);

    return 0;
}