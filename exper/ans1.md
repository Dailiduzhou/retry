## 4(1)

``` cpp
#include <stdio.h>
int main ( )
{ 
  int a;
  
  scanf("%d", &a);
  if (a >= 0)
	 printf("the number %d is positive number\n", a);
  else
	 printf("the number %d is negative number\n", a);
  
  if (a % 2 == 0) 
	 printf("the number %d is even number\n", a);
  else
	 printf("the number %d is odd number\n", a);
}
```

## 4(4)

``` cpp
#include <stdio.h>

int main( )
{
  char c;

  printf("*****Time*****\n");
  printf("1 morning\n");
  printf("2 afternoon\n");
  printf("3 night\n");
  printf("please enter your choice: ");

  c = getchar();
  switch (c)
  {
    case '1': printf("Good morning\n");
		      break;
    case '2': printf("Good afternoon\n");
		      break;
    case '3': printf("Good night\n");
		      break;
	default : printf("Selection error!\n");
  }
  return 0;
}
```

## 4(5)

``` cpp
#include <stdio.h>

int main( )
{
  int year, month;

  printf("Input year,month: ");
  scanf("%d,%d", &year, &month);

  switch (month)
  {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:  printf("31 days\n"); // I like fallthrough!
		      break;
    case 4:
    case 6:
    case 9:
    case 11:  printf("30 days\n");
		      break;
    case 2:   if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
				 printf("29 days\n");
		      else
				 printf("28 days\n");
			  break;
	default : printf("Input error!\n");
  }
  return 0;
}
```

## 4(8)

``` cpp
#include <stdio.h>

int main( )
{
  int x;

  scanf("%d",&x);
  if ((x % 3 == 0) && (x % 5 == 0) && (x % 7 == 0))
     printf("%d can be devided by 3,5,7\n", x);
  else if ((x % 3 == 0) && (x % 5 == 0))
          printf("%d can be devided by 3,5,\n", x);
  else if ((x % 3 == 0) && (x % 7 == 0))
          printf("%d can be devided by 3,7\n", x);
  else if ((x % 5 == 0) && (x % 7 == 0))
          printf("%d can be devided by 5,7\n", x);
  else if (x % 3 == 0)
          printf("%d can be devided by 3\n", x);
  else if (x % 5 == 0)
          printf("%d can be devided by 5\n", x);
  else if (x % 7 == 0)
          printf("%d can be devided by 7\n", x);
  else
    printf("%d cannot be devided by 3,5,7\n", x);
  return 0;
}
```