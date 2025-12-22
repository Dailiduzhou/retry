#include<stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int x, int y){
        while (y != 0) {
            int temp = y;
            y = x % y;
            x = temp;
        }
        return abs(x);
}

int* findCommonFactors(int a, int b, int* count) {
    if (a == 0 && b == 0) {
        *count = 0;
        return NULL;
    }
    
    int g = gcd(a, b);
    
    if (g == 1) {
        int* result = (int*)malloc(sizeof(int));
        if (result == NULL) return NULL;
        result[0] = 1;
        *count = 1;
        return result;
    }

    int factorCount = 0;
    for (int i = 1; i * i <= g; i++) {
        if (g % i == 0) {
            factorCount++;
            if (i != g / i) {
                factorCount++;
            }
        }
    }

    int* result = (int*)malloc(factorCount * sizeof(int));
    if (result == NULL) {
        *count = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 1; i * i <= g; i++) {
        if (g % i == 0) {
            result[index++] = i;
        }
    }
    
    int tempIndex = index;
    for (int i = sqrt(g); i >= 1; i--) {
        if (g % i == 0 && i != g / i) {
            result[tempIndex++] = g / i;
        }
    }
    
    *count = factorCount;
    return result;
}

int main(){
    int a, b;
    int count;
    printf("a:\n");
    scanf("%d", &a);
    printf("b:\n");
    scanf("%d", &b);
    
    int* res = findCommonFactors(a, b, &count);
    printf("arr = \n");
    for (int i = 0;i<count; ++i){
        printf("%d\n", res[i]);
    }

    free(res);

    printf("\ncount = %d\n", count);
}