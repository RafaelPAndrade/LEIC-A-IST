/* Aula LAB PO 01
 *
 * Introducao a objetos/objetos em C
 *
 * Ex. 1 - Animal Simples
 * Ficheiro: main.c [retirado do wiki]
 */

#include <stdio.h>
#include "Animal.h"

int main() {

	Animal a1 = newAnimal("Tareco", 12, 3.4);  // could be a cat...
	Animal a2 = newAnimal("Piloto", 1, 12.3);  // is it a dog??

	printAnimal(a2);
	printAnimal(a2);

	printf("a1==a1? %s\n", equalsAnimal(a1, a1) ? "yes" : "no");
	printf("a1==a2? %s\n", equalsAnimal(a1, a2) ? "yes" : "no");

	destroyAnimal(a1);
	destroyAnimal(a2);

	return 0;
}
