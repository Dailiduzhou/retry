#include<bits/stdc++.h>

long long p[25][25][25]={};
long long w(long long a, long long b, long long c){
    if (a<=0 || b<=0 || c<=0) return 1;
    if (a>20 || b>20 || c>20) return w(20, 20, 20);
    if (a<b && b<c) {
        if (p[a][b][c-1]==0)
            p[a][b][c-1] = w(a,b,c-1);
        if (p[a][b-1][c-1]==0)
            p[a][b-1][c-1]=w(a,b-1,c-1);
        if (p[a][b-1][c]==0)
            p[a][b-1][c]=w(a,b-1,c);
        p[a][b][c] = p[a][b][c-1] + p[a][b-1][c-1] - p[a][b-1][c];
    }
    else {
        if (p[a-1][b][c] == 0){
            p[a-1][b][c] = w(a-1, b, c);
        }
        if (p[a-1][b-1][c]==0) {
            p[a-1][b-1][c] = w(a-1,b-1,c);
        }
        if (p[a-1][b][c-1]==0) {
            p[a-1][b][c-1] = w(a-1, b, c-1);
        }
        if (p[a-1][b-1][c-1] == 0){
            p[a-1][b-1][c-1] == w(a-1,b-1,c-1);
        }
        p[a][b][c] = p[a-1][b][c]+p[a-1][b-1][c]+p[a-1][b][c-1]- p[a-1][b-1][c-1];
    }
    return p[a][b][c];
}

int main(){
    long long a,b,c;
    while (scanf("%lld %lld %lld",&a, &b, &c)) {
        if (a==-1 && b==-1 && c==-1) return 0;

        printf("w(%lld, %lld, %lld) = ",a,b,c);
        printf("%lld\n", w(a,b,c));
    }
}

// #include <cstdio>
// #define LL long long

// LL dp[25][25][25];

// LL w(LL a, LL b, LL c)
// {
// 	if(a <= 0 || b <= 0 || c <= 0) return 1;
// 	if(a > 20 || b > 20 || c > 20) return w(20, 20, 20);
	
// 	if(a <b && b < c)
// 	{
// 		if(dp[a][b][c-1] == 0)
// 		{
// 			dp[a][b][c-1] = w(a, b, c-1);
// 		}
// 		if(dp[a][b-1][c-1] == 0)
// 		{
// 			dp[a][b-1][c-1] = w(a, b-1 ,c-1);
// 		}
// 		if(dp[a][b-1][c] == 0)
// 		{
// 			dp[a][b-1][c] = w(a, b-1, c);
// 		}
// 		dp[a][b][c] = dp[a][b][c-1] + dp[a][b-1][c-1] - dp[a][b-1][c];
// 	}
	
// 	else//同上
// 	{
// 		if(dp[a-1][b][c] == 0)
// 		{
// 			dp[a-1][b][c] = w(a-1, b, c);
// 		}
// 		if(dp[a-1][b-1][c] == 0)
// 		{
// 			dp[a-1][b-1][c] = w(a-1, b-1 ,c);
// 		}
// 		if(dp[a-1][b][c-1] == 0)
// 		{
// 			dp[a-1][b][c-1] = w(a-1, b, c-1);
// 		}
// 		if(dp[a-1][b-1][c-1] == 0)
// 		{
// 			dp[a-1][b-1][c-1] = w(a-1, b-1, c-1);
// 		}
// 		dp[a][b][c] = dp[a-1][b][c] + dp[a-1][b][c-1] + dp[a-1][b-1][c] - dp[a-1][b-1][c-1];
// 	}
	
// 	return dp[a][b][c];
// }

// int main()
// {
// 	LL a, b, c;
	
// 	while(scanf("%lld%lld%lld", &a, &b, &c))
// 	{
// 		if(a == -1 && b == -1 && c == -1) return 0;
		
// 		printf("w(%lld, %lld, %lld) = ", a, b, c);
// 		printf("%lld\n", w(a, b, c));
// 	}
// }
