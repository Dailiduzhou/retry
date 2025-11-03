#include <stdio.h>
int main()
{
    int N,M;
    scanf("%d %d",&N,&M);
    int result=(N*(N-1))/2+(M*(M-1))/2;
    printf("%d",result);


    return 0;
}