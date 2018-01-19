/* Aula LAB PO 01
 *
 * Introducao a objetos/objetos em C
 *
 * Ex. 3 - Gato Menos Simples
 * Ficheiro: Cat.c
 */

// Naive, 'a custa dos outros

# include "../Simples/Cat.h"
# include "../Animal.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

struct cat {


	Animal _animal;
	int   _purrLevel;
	float _flufiness;
};



Cat newCat(const char *name, int age, float weight, int purrLevel, float
flufiness) {

	Cat res = (Cat) malloc(sizeof(struct cat));

	res->_animal = newAnimal(name, age, weight);
	res->_purrLevel = purrLevel;
	res->_flufiness = flufiness;

	return res;
}


void destroyCat(Cat c) {

	destroyAnimal(c->_animal);
	free(c);
}


int equalsCat(Cat c1, Cat c2) {
	return c1->_purrLevel == c2->_purrLevel &&
	       c1->_flufiness == c2->_flufiness &&
	       equalsAnimal(c1->_animal, c2->_animal);
}


char *getCatName(Cat c) {
	return getAnimalName(c->_animal);
}

int   getCatAge(Cat c) {
	return getAnimalAge(c->_animal);
}

float getCatWeight(Cat c) {
	return getAnimalWeight(c->_animal);
}

int   getCatPurrLevel(Cat c) {
	return c->_purrLevel;
}

float getCatFlufiness(Cat c) {
	return c->_flufiness;
}


void  printCat(Cat c) {

	printAnimal(c->_animal);
	printf("Purr Level:\t%d\n", c->_purrLevel);
	printf("Flufiness:\t%.2f\n", c->_flufiness);

}
