#include <stdio.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define INTBITS (sizeof(unsigned int) * 8) // assume we know number of bits in integer representation

int multiply_by_adds(int m, int n)
{
   int iterations = MIN(m, n);
   int base = MAX(m, n);
   int result = 0;
   for (int i=0; i < iterations; i++) {
      result += base;
   }
   return result;
}

int multiply_by_shifts_adds(int m, int n)
{
   int multiplier = MIN(m, n);
   int base = MAX(m, n);
   int result = 0;
   for (int i = 0; i < sizeof(unsigned int) * 8 ; i++) {
      if (0x1 << i & multiplier) result += base << i;
   }
   return result;
}

int multiply_by_shifts_adds_opt(int m, int n)
{
   int multiplier = MIN(m, n);
   int base = MAX(m, n);
   int result = 0;

   if (multiplier == 0) return 0;
   int lead_zeros = __builtin_clz(multiplier); // builtin gcc function
   int highest_pow = INTBITS - lead_zeros - 1; 

   for (int i = highest_pow; i >= 0 ; i--) {
      if (0x1 << i & multiplier) result += base << i;
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

   int prod_adds = multiply_by_adds(m, n);
   int prod_shifts_adds = multiply_by_shifts_adds(m, n);
   int prod_shifts_adds_opt = multiply_by_shifts_adds_opt(m, n);
   if (sign == -1) {
      prod_adds = -prod_adds;
      prod_shifts_adds = -prod_shifts_adds;
   }
   printf("Using repeated adds implementation, product is \t\t\t%d\n", prod_adds);
   printf("Using bitshift adds implementation, product is \t\t\t%d\n", prod_shifts_adds);
   printf("Using optimized bitshift adds implementation, product is \t%d\n", prod_shifts_adds_opt);

   return 0;
}

