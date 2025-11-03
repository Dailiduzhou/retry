#include <stdio.h>
	
int main()
{
  int a = 65;
  char b = 'B';
	
  putchar(a); 
  putchar('\n'); 
  puts("is as good as ");
  putc(b, stdout);
  return 0;
}
