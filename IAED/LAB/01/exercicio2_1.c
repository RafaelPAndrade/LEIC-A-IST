#include <stdio.h>

/* Conversao Fahrenheit-Celsius */

#define UPPER 300
#define LOWER 0
#define STEP 20

int main ()
{
  int fahr;
  float celsius;


  fahr = LOWER;
  while (fahr <= UPPER)
  {
    celsius = 5.0 * (fahr-32) / 9.0;
    printf("%d\t%5.1f\n", fahr, celsius);
    fahr = fahr + STEP;
  }
  return 0;
}
