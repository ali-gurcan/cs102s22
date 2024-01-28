#include<stdio.h>
#include "util.h"
int main()
{
    int num1, num2,num3;
    printf("Part1 >>\n");
    printf("Enter the first number:");
    scanf("%d",&num1);
    printf("Enter the second number:");
    scanf("%d", &num2);
    int result = gcd(num1, num2);
    printf("gcd is: %d\n+--+--+--+--+--+--+--+--+--+--+--+--+\n", result);
    printf("Part2 >>\n");
    printf("Enter the first number:");
    scanf("%d", &num1);
    printf("Enter the second number:");
    scanf("%d", &num2);
    part2(num1, num2);
    printf("+--+--+--+--+--+--+--+--+--+--+--+--+\n"); 
    printf("Part3 >>\n");
    printf("Enter the first number:");
    scanf("%d", &num1);
    printf("Enter the second number:");
    scanf("%d", &num2);
    part3(num1, num2);
    printf("+--+--+--+--+--+--+--+--+--+--+--+--+\n");
    printf("Part4 >>\n");
    part4(num3); 
}


