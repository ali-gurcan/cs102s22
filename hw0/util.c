#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) {
    printf("%d/%d", numerator, denominator);
}  /* end fraction_print */

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 + n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_add */

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1 * d2 - n2 * d1;
    *d3 = d1 * d2;
    fraction_simplify(n3, d3);
} /* end fraction_sub */

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1 * n2;
    *d3 = d1 * d2;
    fraction_simplify(n3, d3);
} /* end fraction_mul */

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1 * d2;
    *d3 = d1 * n2;
    fraction_simplify(n3, d3);
} /* end fraction_div */

/* Simplify the given fraction such that they are divided by their GCD */
void fraction_simplify(int * n, int * d) {
    int i, gcd =0;  
        for ( i = 1; i <= *n &&  i<=*d; i++)
        {
             if (*n%i==0 && *d%i== 0)
             {
                gcd=i;
             }
        }
        if(*n>=*d &&gcd==0){
            *n=0;
            *d=1;
        }

        if (gcd!=0 &&((*n)/(*d)>0)){
            *n = (*n / gcd);
            *d = (*d / gcd);
        }  
        
}
/* end fraction_div */
