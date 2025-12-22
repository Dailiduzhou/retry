#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#define MAX_N 2000

int prime[MAX_N + 1];      // 存放素数
bool isPrime[MAX_N + 1];   // 标记是否为素数
int cnt = 0;               // 素数个数

// 欧拉筛法（线性筛法）求素数
void eulerSieve(int n) {
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            prime[cnt++] = i;
        }
        for (int j = 0; j < cnt && i * prime[j] <= n; j++) {
            isPrime[i * prime[j]] = false;
            if (i % prime[j] == 0) break;  // 关键：每个合数只被标记一次
        }
    }
}

int main(){
    int target = 1898;

    eulerSieve(MAX_N);

    int start=-1, end = -1;
    for (int i = 0;i<cnt;i++){
        for (int j = i+1;j<cnt;++j){
            if (prime[i]+target==prime[j]){
                start = i;
                end = j;
                break;
            }
        }
    }

    if (start == -1 && end == -1){
        printf("not exists");
        return 0;
    }

    printf("number 1:%d\nnumber 2:%d\n", prime[start], prime[end]);
    return 0;
}