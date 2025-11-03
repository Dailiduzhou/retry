#include <stdio.h>
	
int main()
{
  char ch1, ch2;
  int a;
	
  ch1 = getchar();
  ch2 = getchar();
  scanf("%d",&a);
  printf("ch1 = %c, ch2 = %c\n",ch1,ch2);
  printf("a = %d\n",a);
  return 0;
}
