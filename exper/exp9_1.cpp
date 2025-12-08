#include<stdio.h>

int pos[10];
int path[10];
void find(int u){
    if (u > 3) {
        for (int i =1;i<=3;++i) {
            printf("%d", path[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 7; i<=9; i++){
        if (!pos[i]){
            path[u] = i;
            pos[i] = 1;
            find(u+1);
            pos[i] = 0;
        }
    }
}

int main(){
    find(1);
    return 0;
}
