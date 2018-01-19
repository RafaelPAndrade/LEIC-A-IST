/* Aula LAB PO 01
 *
 * Introducao a objetos/objetos em C
 *
 * Ex. 3 - Gato Menos Simples
 * Ficheiro: main.c [retirado do wiki]
 */


#include <stdio.h>
#include "../Simples/Cat.h"

int main() {
Cat c1 = newCat("Tareco", 12, 3.4, 3, 3.1);
Cat c2 = newCat("Pantufa", 1, 12.3, 2, 2.7);

printCat(c1);
printCat(c2);

printf("c1==c1? %s\n", equalsCat(c1, c1) ? "yes" : "no");
printf("c1==c2? %s\n", equalsCat(c1, c2) ? "yes" : "no");

destroyCat(c1);
destroyCat(c2);

return 0;
}
