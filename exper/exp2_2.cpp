// exp2_2.cpp
#include <stdio.h>

int main()
{
  long a, b;
  short ah, al;

  printf("Input a long integer: ");
  scanf("%lX", &a);

  b = ((a >> 16) & 0x0000FFFF) + (a << 16);

  printf("%#X", b);
}
