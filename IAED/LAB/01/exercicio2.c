#include <stdio.h>

/* Conversao Fahrenheit-Celsius */

int main ()
{
  int fahr, celsius;
  int inferior, superior, passo;

  inferior = 0;
  superior = 300;
  passo = 20;

  fahr = inferior;
  while (fahr <= superior) 
  {
    celsius = 5 * (fahr-32) / 9;
    printf("%d\t%d\n", fahr, celsius);
    fahr = fahr + passo;
  }
  return 0;
}
