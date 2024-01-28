#include <stdio.h>
#include "util.h"

int gcd(int num1, int num2)
{
    int rem;
    while (num2 != 0)
    {
        rem = num1 % num2;
        num1 = num2;
        num2 = rem;
    }
    return num1;
    }

int part2(int num1, int num2)
    {
        int sum = num1 + num2;
        printf("Result:\n%12d\n%12d\n     +\n     -------\n%12d\n", num1, num2, sum);}

int part3(int num1, int num2)
    {
        int sum1, sum2, sum3;
        sum1 = num1 * (num2 % 10);        //This multiplies the first digit of num2 by num1
        if ((num2 / 10) != 0)             //If there is no second digit, this will not be executed
        sum2 = num1 * ((num2 / 10) % 10); //This multiplies the second digit of num2 by num1
        if ((num2 / 100) != 0)            //If there is no third digit, this will not be executed
        sum3 = num1 * (num2 / 100);       //This multiplies the third digit of num2 by num1
        int lastsum = num1 * num2;
        printf("Result:\n%12d\n%12d\n     *\n     -------\n", num1, num2);
        printf("%12d\n", sum1);
        if (num2 > 9)                      //If the number is not two digit it turns into a bug
        printf("%11d\n", sum2);
        if ((num2 / 100) != 0)             //If the number is not three digit it turns into a bug
        printf("%10d\n", sum3);
        printf("     +\n     -------\n%12d\n", lastsum);
    }

int part4(int num3)
    {
        printf("Enter a number between 1 and 10:\n");
        scanf("%d", &num3);
        if (num3 >= 1 && num3 <= 10)
        {
            if (num3 > 5)
                printf("The integer you entered is greater than 5.\n");
            else
                printf("The integer you entered is less than or equal to 5.\n");
        }
        else
        {
            printf("Invalid input\n");
            return (0);
        }
    }
        