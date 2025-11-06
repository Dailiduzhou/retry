
#include <stdio.h>

int main()
{
  long a, b;
  short ah, al;

  printf("Input a long integer: ");
  scanf("%lX", &a);

  al = a;
  ah = a >> 16;
  if (ah % 2 == 0)
	  printf("高16位为偶数!\n");
  else
	  printf("高16位为奇数!\n");
  if (al % 2 == 0)
	  printf("低16位为偶数!\n");
  else
	  printf("低16位为奇数!\n");
  
}