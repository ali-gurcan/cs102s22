#include <stdio.h>
#include "util.h"


int main() {

    /* A fractional number: 13/7 */
    int num1 = 13, den1 = 7;
    /* A second fractional number: 13/11 */
    int num2 = 30, den2 = 11;
    /* An unitilized fractional number */
    int num3, den3;

    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    /* We reset the numbers for the next example. */

    printf("\nHi! You need to enter two fractional numbers.\n");
    printf("\nfirst number's numerator: ");
    scanf("%d", &num1);
    printf("\nfirst number's denominator: ");
    scanf("%d", &den1);
    printf("\nsecond number's numerator: ");
    scanf("%d", &num2);
    printf("\nsecond number's denominator: ");
    scanf("%d", &den2);

    if (den1 == 0){
        printf("\nInvalid denominator value,choose another number.");
        scanf("%d", &den1);
        }
    if (den2 == 0) {
        printf("\nInvalid denominator value,choose another number.");
        scanf("%d", &den2);
        }
 
    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    return (0);
}
