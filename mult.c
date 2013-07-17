#include <stdio.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

int multiply_by_adding(int m, int n)
{
   int iterations = MIN(m, n);
   int base = MAX(m, n);
   int result = 0;
   for (int i=0; i < iterations; i++) {
      result += base;
   }
   return result;
}

int main()
{
   int m, n;
   printf("Enter two values to multiply together.\n");
   scanf("%d%d", &m, &n);
   
   printf("%d x %d = %d\n", m, n, m*n);

   int sign = 1;
   if (m < 0) {
      sign *= -1;
      m *= -1;
   }
   if (n < 0) {
      sign *= -1;
      n *= -1;
   }

   int prod_add = multiply_by_adding(m, n);
   if (sign == -1) prod_add = -prod_add;
   printf("Using repeated addition implementation, product is %d\n", prod_add);

   return 0;
}

