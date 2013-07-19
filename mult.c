#include <stdio.h>
#include <time.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define BITS_IN_INT (sizeof(unsigned int) * 8) // assume we know number of bits in integer representation

// Finds the difference between two times.
void diff(struct timespec *start, struct timespec *end, struct timespec *result)
{
   if ((end->tv_nsec - start->tv_nsec)<0) { // need to carry subtraction
      result->tv_sec = end->tv_sec - start->tv_sec - 1;
      result->tv_nsec = end->tv_nsec + 1000000000 - start->tv_nsec;
   } else {
      result->tv_sec = end->tv_sec - start->tv_sec;
      result->tv_nsec = end->tv_nsec - start->tv_nsec;
   }
}

// Times a function used to implement multiplication.
void time_multiply(int (*multiply_func)(int, int), const char *description) 
{
   int num_iter = 1000;
   struct timespec time1, time2, time_diff;

   printf("\nTiming implementation using %s\n", description);
   printf("n\ttime(s) to compute n^2\n");
   for (int i = 1; i < 40000; i*=2) {
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
      for (int j = 0; j<num_iter; j++) {
         multiply_func(i, i);
      }
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
      diff(&time1, &time2, &time_diff);
      printf("%d \t%lld.%.9ld\n", i, (long long)time_diff.tv_sec, time_diff.tv_nsec);
   }
}

// Implements multiplication using repeated addition.
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

// Implements multiplication using addition and bit shifting.
int multiply_by_shifts_adds(int m, int n)
{
   int multiplier = MIN(m, n);
   int base = MAX(m, n);
   int result = 0;
   for (int i = 0; i < BITS_IN_INT; i++) {
      if (0x1 << i & multiplier) result += base << i;
   }
   return result;
}

// Implements multiplication using addition and bit shifting.
// Works only over the necessary number of bits
int multiply_by_shifts_adds_opt(int m, int n)
{
   int multiplier = MIN(m, n);
   int base = MAX(m, n);
   int result = 0;

   if (multiplier == 0) return 0;
   int lead_zeros = __builtin_clz(multiplier); // builtin gcc function
   int highest_pow = BITS_IN_INT - lead_zeros - 1; 

   for (int i = highest_pow; i >= 0 ; i--) {
      if (0x1 << i & multiplier) result += base << i;
   }
   return result;
}

int main()
{
   /* Comparing the time of each implementation */
   // time_multiply(multiply_by_adds, "adds");
   // time_multiply(multiply_by_shifts_adds, "shifts and adds");
   // time_multiply(multiply_by_shifts_adds_opt, "shifts and adds, opt");

   int m, n;
   m = 10;
   n = 10;
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
      prod_shifts_adds_opt = -prod_shifts_adds_opt;
   }

   /* For checking that product is implemented correctly */
   printf("Using repeated adds implementation, product is \t\t\t%d\n", prod_adds);
   printf("Using bitshift adds implementation, product is \t\t\t%d\n", prod_shifts_adds);
   printf("Using optimized bitshift adds implementation, product is \t%d\n", prod_shifts_adds_opt);

   return 0;
}

