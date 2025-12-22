#include<stdio.h>
#include<string.h>

int main(){
    int num, count = 0;
    printf("输入一个四位数: ");
    scanf("%d", &num);
    
    char str[5];
    sprintf(str, "%04d", num);
    
    
    while(num != 6174 && count < 100) {
        int digits[4];
        for(int i = 0; i < 4; i++) {
            digits[i] = str[i] - '0';
        }
        
        for(int i = 0; i < 3; i++) {
            for(int j = i+1; j < 4; j++) {
                if(digits[i] < digits[j]) {
                    int temp = digits[i];
                    digits[i] = digits[j];
                    digits[j] = temp;
                }
            }
        }
        int desc = digits[0]*1000 + digits[1]*100 + digits[2]*10 + digits[3];
        
        // for(int i = 0; i < 3; i++) {
        //     for(int j = i+1; j < 4; j++) {
        //         if(digits[i] > digits[j]) {
        //             int temp = digits[i];
        //             digits[i] = digits[j];
        //             digits[j] = temp;
        //         }
        //     }
        // }

        // int asc = digits[0]*1000 + digits[1]*100 + digits[2]*10 + digits[3];

        int asc = digits[0] + digits[1]*10+ digits[2]*100+digits[3]*1000;
        
        num = desc - asc;
        count++;
        
        sprintf(str, "%04d", num);
    }
    
    if(num == 6174) {
        printf("\n✓ 成功到达黑洞数: 6174\n");
        printf("共需迭代 %d 次\n", count);
    }
    
    return 0;
}