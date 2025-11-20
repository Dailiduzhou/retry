// #include<stdio.h>
// #include<string.h>

// int main(){
//     char buf[100];

//     scanf("%99[^\n]", buf);
//     getchar();
//     int len = strlen(buf)-1;

//     char flt[100];
//     int i=0;
//     while (char c = getchar()){
//         if (c == '\n'){
//             break;
//         }
//         flt[i] = c;
//         ++i;
//     }

//     int n = 0;
//     char res[100];
//     for (int j = 0;j<len;j++){
//         for (int k=0;k<=i;k++){
//             if (flt[k] == buf[j]){
//                 continue;
//             }
//             res[n] = buf[j];
//             n++;
//         }
//     }

//     for (int j=0;j<=n;j++){
//         printf("%c", res[j]);
//     }
// }

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 70

int main() {
    char str[MAX_LENGTH + 2]; 
    char filter[MAX_LENGTH + 2];
    char result[MAX_LENGTH + 1];
    int i, j, k;
    int found;
    
    fgets(str, sizeof(str), stdin);
    
    fgets(filter, sizeof(filter), stdin);
    
    str[strcspn(str, "\n")] = '\0';
    filter[strcspn(filter, "\n")] = '\0';
    
    k = 0; 
    
    for (i = 0; str[i] != '\0'; i++) {
        found = 0;  
        
        for (j = 0; filter[j] != '\0'; j++) {
            if (str[i] == filter[j]) {
                found = 1;
                break;
            }
        }
    
        if (!found) {
            result[k++] = str[i];
        }
    }
    
    result[k] = '\0';
    
    printf("%s\n", result);
    
    return 0;
}