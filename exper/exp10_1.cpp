// #include<stdio.h>

// int* myfunc(int* p, int n);
// void swapInt(int* a, int* b);

// int main(){
//     int n;
//     scanf("%d", &n);
//     int a[n];
//     for (int i = 0;i<n;++i){
//         scanf("%d", &a[i]);
//     }

//     int* b = myfunc(a, n);
//     for (int i=0;i<n;++i){
//         printf("%d ", b[i]);
//     }
//     return 0;
// }

// int* myfunc(int* p, int n)
// {   
//     if (n==1){
//         return p;
//     }
//     for (int i=0;i<n;++i){
//         if (*p == 0){
//             if (n==2){
//                 swapInt(p,p+sizeof(int));
//             }
//             for (int j = i;j<n-1;j++){
//                 swapInt(p, p+sizeof(int));
//                 p = p + sizeof(int);
//             }
//         }
//     }
//     int* b = p;
//     return b;
// }

// void swapInt(int*a, int*b)
// {
//     int* temp;
//     temp = a;
//     a = b;
//     b = temp;
// }

#include<stdio.h>

int* myfunc(int* p, int n);

int main(){
    int n = 7;
    int a[n] = {1,0,3,4,0,-3,5};
    // for (int i = 0;i<n;++i){
    //     scanf("%d", &a[i]);
    // }

    int* b = myfunc(a, n);
    for (int i=0;i<n;++i){
        printf("%d ", b[i]);
    }
    return 0;
}

int* myfunc(int* p, int n)
{
    int left = 0;
    for (int i = 0; i < n; i++){
        if (*(p + i) != 0){
            int temp = *(p + left);
            *(p + left) = *(p + i);
            *(p + i) = temp;
            left++;
        }
    }
    return p;
}
