// exp2_3.cpp
#include <stdio.h>

int main()
{
  long a, b;
  short ah, al;

  printf("Input a long integer: ");
  scanf("%lX", &a);

  b = (a << 24) + ((a << 8) & 0x00FF0000) + ((a >> 8) & 0x0000FF00) + ((a >> 24) & 0x000000FF);

  printf("a = %X, b = %X\n", a, b);

}