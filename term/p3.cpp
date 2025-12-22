#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* multiplyStrings(const char* num1, const char* num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    
    if (len1 == 0 || len2 == 0) {
        char* result = (char*)malloc(2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    
    if ((len1 == 1 && num1[0] == '0') || (len2 == 1 && num2[0] == '0')) {
        char* result = (char*)malloc(2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    int maxLen = len1 + len2;
    int* res = (int*)calloc(maxLen, sizeof(int));
    
    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + res[i + j + 1];
            
            res[i + j + 1] = sum % 10;
            res[i + j] += sum / 10;       
        }
    }
    
    char* result = (char*)malloc(maxLen + 1);
    int index = 0;
    int start = 0;
    
    while (start < maxLen && res[start] == 0) {
        start++;
    }
    
    if (start == maxLen) {
        result[0] = '0';
        result[1] = '\0';
        free(res);
        return result;
    }
    
    for (int i = start; i < maxLen; i++) {
        result[index++] = res[i] + '0';
    }
    result[index] = '\0';
    
    free(res);
    return result;
}

int main() {
    
    char num1[101], num2[101];
                
    printf("\n输入第一个数字（不超过100位，无前导零）: ");
    scanf("%s", num1);
                
    printf("输入第二个数字（不超过100位，无前导零）: ");
    scanf("%s", num2);
                
    char* result = multiplyStrings(num1, num2);
    printf("\n计算结果: %s × %s = %s\n", num1, num2, result);
    printf("结果长度: %lu位\n\n", strlen(result));
          
    return 0;
}