#include<stdio.h>

int like[5][5] = {{0,0,1,1,0}, {1,1,0,0,1}, 
                  {0,1,1,0,1}, {0,0,0,1,0},
                  {0,1,0,0,1}};
int book[5] = {0,0,0,0,0};
int path[5]; // 当前路径，记录第 n 个人分配到的书的编号
void distri(int n) {
    if (n>=5) {
        for (int i=0;i<5;i++){
            printf("%d", path[i]);
        }
        printf("\n");
        return;
    }
    for (int i=0;i<5;i++){
        if (like[n][i] && !book[i]) {
            path[n] = i;
            book[i] = 1;
            distri(n+1);
            book[i] = 0;
        }
    }
}

int main(){
    distri(0);
    return 0;
}