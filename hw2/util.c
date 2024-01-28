#include <stdio.h>
#include <math.h>
#include "util.h"

void part1(int year){
    printf("Please enter a year:");
    scanf("%d",&year);
    if (year % 400 == 0) /* if the year is divisible by 400. If it is, then it is a leap year.*/
        printf("%d is a leap year.\n", year);
    else if (year % 100 == 0) /* if the year is  divisible by 400 but is also divisible by 100,it is not a leap year.*/
        printf("%d is not a leap year.\n", year);
    else if (year % 4 == 0) /* if the year is not divisible by 400 or 100 but is divisible by 4,it is a leap year.*/
        printf("%d is a leap year.\n", year);
    else /* if the year is not divisible by 400, 100, or 4,it's not a leap year.*/
        printf("%d is not a leap year.\n", year);
}
void part2(char output){
    char operation;
    int m, n;
    double result;
    printf("Enter the format  of output (s or i):");
    scanf(" %c", &output);
    if (output == 's'){
        double num1, num2;
        int factorialcounter=0;
        printf("Enter m and n values:");
        scanf("%d %d", &m, &n);
        if (n > m) /* warning to avoid m-n<0*/
        {
            printf("n is bigger than m,the program is restarting...\n");
            return part2(output);
        }
        printf("Enter the operation(+,-,/,*,%%,!,^):");
        scanf(" %c", &operation);
        printf("Enter the first operand:");
        scanf("%lf", &num1);
        if (operation != '!'){
            printf("Enter the second operand:"); /* if user choose factorial, num2 is not displayed*/
             scanf(" %lf", &num2);
         }
         switch (operation)
         {
         case '+':
             result = num1 + num2;
             break;
         case '-':
             result = num1 - num2;
             break;
         case '*':
             result = num1 * num2;
             break;
         case '/':
             result = num1 / num2;
             break;
         case '!':
             int fact = 1;
             for (int i = 1; i <= num1; i++)
             {
                 fact = fact * i;
             }
             result = fact;
             factorialcounter = 1; /* this is a counter,it indicates that the user has selected factorial*/
            break;
        case '^':
            result = pow(num1, num2);
            break;
        case '%':
            result = fmod(num1, num2);
            break;
        }
        if (factorialcounter==0){
            printf("%.f%c%.f=", num1, operation, num2);
        }
        else{
            printf("%.f%c =", num1, operation); /* if user choose factorial, num2 is not displayed*/
        }
        part2sresult(result, m, n); /* to get s result*/
    }
    if (output == 'i'){
        int num1, num2;
        int factorialcounter=0;
        printf("Enter the operation(+,-,/,*,%%,!,^):");
        scanf(" %c", &operation);
        printf("Enter the first operand:");
        scanf("%d", &num1);
        if (operation != '!'){
            printf("Enter the second operand:");
            scanf("%d", &num2);
        }
        switch (operation){
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            result = num1 / num2;
            break;
        case '!':
            int fact = 1;
            for (int i = 1; i <= num1; i++){
                fact = fact * i;
            }
            result = fact;
            factorialcounter=1;
            break;
        case '^':
            result = pow(num1, num2);
            break;
        case '%':
            result = num1 % num2;
            break;
        }
        //int printing
        int iresult = result; /* converting result to int*/
        if (factorialcounter==0){/*if factorial count is not equals to 1,that means factorial is not selected*/
            printf("%d%c%d=%d\n", num1, operation, num2, iresult);
        }
        else{
            printf("%d%c =%d\n", num1, operation, iresult); /* if user choose factorial, num2 is not displayed*/
        }
    }
}
void part2sresult(double result, int m, int n)
{
    for(int i=1;i<m-n;i++){/* %e works with one integer part,the loop works to get (m-n) integerpart digit.*/
        printf("0");
    }
    printf("%*.*e\n", m - n, n, result); /* m,n and e values are always correct.*/
}
void part3(int exam1, int exam2, int exam3,int a1,int a2)
{
    printf("Enter 3 exam grades of student:");
    scanf("%d %d %d",&exam1,&exam2,&exam3);
    if(exam1>100 ||exam2>100 || exam3>100){
        printf("Invalid value.");
        return part3(exam1,exam2,exam3,a1,a2);}//for invalid grade 
    printf("Enter 2 assignment grades of student:");
    scanf("%d %d", &a1, &a2);
    if (a1 > 100 || a2 > 100){
        printf("Invalid value.Enter 2 assignment grades of student:"); /* for invalid value ,that works one time.*/
        scanf("%d %d", &a1, &a2);       
    }    
    float fgrade = ((exam1 + exam2 + exam3)/3*0.6)+((a1+a2)/2*0.4);
    if (fgrade>=60)
        printf("Final Grade: %.1f Passed!\n",fgrade);
    else
        printf("Final Grade: %.1f Failed!\n",fgrade);    
} 