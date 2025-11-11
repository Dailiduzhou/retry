## 1
``` cpp
#include <stdio.h>

int main ( )
{
  int i, sum = 0;

  for(i = 2; i <= 100; i += 2)
	sum += i;
  printf("sum = %d\n", sum);
  return 0;
}
```
## 2
``` cpp
#include <stdio.h>

int main ( )
{
  int i;
  long term, sum = 0;

  for (i = 1; i <= 99; i += 2)
  {
	term = i * (i + 1) * (i + 2);
	sum += term;
  }
  printf("sum = %ld\n", sum);
  return 0;
}
```
## 3
``` cpp
#include <stdio.h>

int main ( )
{
  long term, sum = 0;
  int i, j;

  for (i = 1; i <= 10; i++)
  {
	term = 1;
	for (j = 1; j <= i; j++)
	  term *= j;
	sum += term;
  }
  printf("1!+2!+...+10! = %ld\n", sum);
  return 0;
}
```
## 4
``` cpp
#include <stdio.h>

int main(){
  long term = 0, sum = 0;
  int a, i, n;

  printf("Input a, n: ");
  scanf("%d,%d", &a, &n); 

  for (i = 1; i <= n; i++)
  {
	term = term * 10 + a;  
	sum += term;           
  }
  printf("sum = %ld\n", sum);
  return 0;
}
```
## 5
``` cpp
#include <stdio.h>
 
int main( void )
{
  float term, result = 1; 
  int n;

  for (n = 2; n <= 100; n += 2)
  {
	term = (float)(n * n) / ((n - 1) * (n + 1));
	result *= term;
  }
  printf ("result = %f\n", 2 * result);
  return 0;
}
```
## 6
``` cpp
#include <stdio.h>
#include <math.h>
int main()
{
  int n = 1, count = 0;
  float x;
  double sum, term;

  printf ("Input x: ");
  scanf ("%f", &x);
  sum = x;
  term = x;
  do
  {
	term = -term * x * x / ((n+1) * (n+2));
	sum += term;
	n += 2;
	count++;
  } while (fabs(term) >= 1e-5);

  printf ("sin(x) = %f, count = %d\n", sum, count);
  return 0;
}
```
## 7
``` cpp
#include <stdio.h>
#include <math.h>

#define E 0.000001

int main( )
{
  int i, k = 1;
  float x, y, t = 1, s = 0, r;

  printf( "Please enter x = ");
  scanf("%f", &x);
  r = x;
  for(y = x, i = 1; fabs(r) > E; i++)
  {
    s += r;
    k *= -1;
    y *= x * x;
    t *= i;
    r = k * y / (2*i+1) / t;
  }
  printf( "s = %f\n", s);
  return 0;
}
```
## 8
``` cpp
#include <stdio.h>
 
int main( void )
{
  int i, j, k, n;

  printf ("result is: ");
  for (n = 100; n < 1000; n++)
  {
	i = n / 100;            
	j = (n - i *100) / 10;  
	k = n % 10;            
	if (n == i*i*i + j*j*j + k*k*k)
	   printf ("%d ", n);
  }
  printf ("\n");
  return 0;
}
```
## 9
``` cpp
#include <stdio.h>
#include <math.h>
int main()
{
  int i1, i2, i3, i4, k, n;

  printf ("Input data is: ");
  scanf ("%d", &n);
  k = abs(n);       
  i1 = k / 1000; 
  i2 = (k - i1 * 1000) / 100;          
  i3 = (k - i1 * 1000 - i2 * 100) / 10; 
  i4 = k % 10;                           

  printf ("The sum of the toal bit is %d\n", i1 + i2 + i3 +i4);
  return 0;
}
```
## 10
``` cpp
#include <stdio.h>

int main()
{
  int n, m = 0, s, r;

  printf ("Input data is: ");
  scanf ("%d", &n);
  s = n;
  while (s != 0)
  {
	r = s % 10;
	m = 10 * m + r;
    s = s / 10;
  }
  if (m == n)
	 printf ("yes\n");
  else
	 printf ("no\n");
  return 0;
}
```
## 11
``` cpp
#include <stdio.h>

int main()
{
  int x, y, z, count = 0;

  for (x = 1; x <= 28; x++)
	for (y = 1; y <= 73; y++)
	{
	  z = 100 - x - y;
	  if (5*x + 2*y + z == 150)
	  {
		count++;
		printf ("%02d, %02d, %02d   ", x, y, z);
        if (count % 6 == 0)
		   printf ("\n");
	  }
	}
  printf ("count = %d\n", count);
  return 0;
}
```
## 12
``` cpp
#include <stdio.h>

int main ( )
{
  int k = 0, sum = 0, g = 0;
  char thisman = ' ';

  for (k = 0; k <= 3; k++)
  {
	thisman = 'A' + k;
	sum = (thisman != 'A') + (thisman == 'C') + (thisman == 'D') + (thisman != 'D');
	if (sum == 3)
	{
	  printf ("This man is %c\n", thisman);
	  g = 1;
	}
  }
  if (g != 1)
	printf ("Can't found\n");
  return 0;
}
```
## 13
``` cpp
#include <stdio.h>

int main()
{
  int i, j, k;
  
  for (i = 1; i <= 5; i++)
  {
	for (j = 1; j <= 5 - i; j++)
	  printf (" ");
	for (k = 1; k <= 5; k++)
	  printf ("*");
	printf ("\n");
  }
  return 0;
}
```
## 14
``` cpp
#include <stdio.h>

#define CHANGE 1

int main()
{ 
  int c;
  while ((c = getchar()) != '\n')
  { 
    if (CHANGE)
	{
      if ((c >= 'a' && c <= 'x') || (c >= 'A' && c <= 'X'))
        c += 2;
      else if (c == 'y' || c == 'Y' || c == 'z' || c == 'Z')
        c = c - 24;
      putchar(c);
	}
  }
  putchar('\n');
  return 0;
}
```
## 15
``` cpp
#include <stdio.h>
 
int main( )
{
  int n, i;

  printf("Please input a number: ");
  scanf("%d", &n);
  printf("%d = ", n);
  for(i = 2; i <= n; i++)
  {
    while(n != i)
	{
      if(n % i == 0)
	  {   
        printf("%d * ", i);
        n = n / i;
	  }
      else
        break;
	}
  }
  printf("%d\n", n);
  return 0;
}
```
## 16
``` cpp
#include <stdio.h>
#include <math.h>
 
int main() 
{
  double x1, x2;
  float a;
  scanf("%f", &a);
  x2 = 1.0;
  do 
  {
    x1 = x2;
	x2 = (x1 + a / x1) / 2.0;
  } while (fabs(x1 - x2) >= 0.00001);
  printf("%f\n", x2);
  return 0;
}
```
## 17
``` cpp
#include <stdio.h>
#include <math.h>

int main()
{
  double x0, x1 = 1.5, f, f1;

  do
  {
    x0 = x1;
    f = 2 * x0 * x0 * x0 - 4 * x0 * x0 + 3 * x0 - 6;
    f1 = 6 * x0 * x0 - 8 * x0 + 3;
    x1 = x0 - f / f1;
  } while (fabs(x0 - x1) >= 1e-5);
  printf("The root of equation is %5.2f\n", x1);
  return 0;
}
```
## 18
``` cpp
#include <stdio.h>
#include <math.h>

int main( )
{
  float a, b, m, fa, fb, fm;
  a = -10;
  b = 10;
  m = (a + b) / 2;
  fm = 2*m*m*m - 4*m*m + 3*m - 6;
  while(fabs(fm) > 1e-6)
  {
    fa = 2*a*a*a - 4*a*a + 3*a - 6;
    fb = 2*b*b*b - 4*b*b + 3*b - 6;
    if(fa * fm > 0)
      a = m;
	else 
	  b = m;
	m = (a + b) / 2;
	fm = 2*m*m*m - 4*m*m + 3*m - 6;
  }
  printf("the solution of the equation is %.2f.\n", m); 
  return 0;
}
```