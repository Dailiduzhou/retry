## 3.1
``` cpp
#include<stdio.h>
int main{
    unsigned short a, b;

    scanf (" % 4X", &a);

    b = (a & 0x000F) << 12;
    b += (a & 0x00F0) << 4;
    b += (a & 0x0F00) >> 4;
    b += (a & 0xF000) >> 12;

    printf ("%4X\n",b);

    return 0;
}
```
## 3.2
``` cpp
# include < stdio. h>

int main(){



    int a, b;

    scanf ("%d%d", &a, &b);

    printf ("before swap: a = %db = %d\n", a, b);

    a=a+b;

    b= a-b;

    a= a-b;

    printf ("after swap: a = %db = %d\n", a, b); 
    return 0;
}
```
## 3.3
``` cpp
#include<stdio.h>
#define pi 3.14159
int main( )
{
  float r, c, s;

  scanf("%f", &r);
  c = 2 * r * pi;
  s = pi * r * r;
  printf("c = %f  s = %f\n", c, s);
  return 0;
}
```
## 3.4
``` cpp
#include <stdio.h>
int main( )
{
  short int a;

  scanf("%X", &a);
  printf("-%hX\n", -a);
  return 0;
}
```
## 3.5
``` cpp
#include <stdio.h>
#include <math.h>

int main( )
{
  float a, b, c;
  float d;
  float x1, x2;
  
  printf("input a,b,c: ");
  scanf("%f%f%f", &a, &b, &c);
  d = sqrt(b * b - 4 * a *c);
  x1 = (-b + d) / (2 * a);
  x2 = (-b - d) / (2 * a);
  printf("x1 = %.2f  x2 = %.2f\n", x1, x2);
  return 0;
}
```
## 3.6
``` cpp
#include <stdio.h>

int main ( )
{
  unsigned long t, r;
  int d, h, m, s;

  printf("second = ");
  scanf("%d", &t);
  d = t / (24 * 3600);  
  r = t % (24 * 3600);  
  h = r / 3600;         
  m = (r % 3600) / 60;  
  s = (r % 3600) % 60;  
  printf("have passed days is %d, current time is %02d:%02d:%02d\n", d, h, m, s);
  return 0;
}
```
## 3.7
``` cpp
#include <stdio.h>

int main( )
{ 
  char ch;

  ch=getchar();
  printf("%c ASCII code is %d\n", ch-1, ch-1);
  printf("%c ASCII code is %d\n", ch, ch);
  printf("%c ASCII code is %d\n", ch+1, ch+1);
  return 0;
}
```
## 3.8
``` cpp
#include <stdio.h>

int main( )
{ 
  float c, f;

  printf("Input C: ");
  scanf("%f", &c);
  f=(c+32.0)*9.0/5.0;
  printf("F=%.2f\n", f);
  return 0;
}
```
## 3.9
``` cpp
#include <stdio.h>
int main( )
{     
  int n1, n2, a, b, c;

  printf("Input an integer: ");
  scanf("%d", &n1);
  a = n1 / 100;
  b = n1 / 10 % 10;
  c = n1 % 10;
  n2 = a + b * 10 + c * 100;
  printf("the new number is %d\n", n2);
  return 0;
}
``` 
## 3.10
``` cpp
#include<stdio.h>

int main( )
{     
  int a, b, c, t;

  printf("Input three integers: ");
  scanf("%d%d%d", &a, &b, &c);
  t=c; c=b; b=a; a=t;
  printf("After swap: %d %d %d\n",a, b, c);
  return 0;
}
```