#include <stdio.h>
#include <conio.h>
	
int main()
{
  char ch1, ch2;
	
  printf("please press two key\n");
  ch1 = getche();
  ch2 = getch();
  printf("\nyou've pressed %c and %c\n",ch1,ch2);
  return 0;
}
