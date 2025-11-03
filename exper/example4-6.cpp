#include  <stdio.h>
	
int main()
{
  unsigned long no;               //学号
  unsigned int year, month, day;  //生日（年、月、日）
  unsigned char sex;              //性别
  float chinese, math, english;   //语文、数学、英语成绩
  float total, average;           //总分、平均分
	
  printf("input the student's NO: ");
  scanf("%8ld", &no);
  printf("input the student's Birthday(yyyy-mm-dd): ");
  scanf("%4d-%2d-%2d", &year, &month, &day);
  fflush(stdin);                 //清除键盘缓冲区
  printf("input the student's Sex(M/F): ");
  scanf("%c", &sex);
  printf("input the student's Scores(chinese, math, english): ");
  scanf("%f,%f,%f", &chinese, &math, &english);
  total = chinese + math + english;   //计算总分
  average = total / 3;                //计算平均分

  printf("\n===NO=======birthday==sex==chinese==math==english==total==average\n");
  printf("%08ld   %4d-%02d-%02d  %c     %-5.1f  %-5.1f  %-5.1f   %-5.1f   %-5.1f\n", 
	      no, year, month, day, sex, chinese, math, english, total, average);
  return 0;
}
