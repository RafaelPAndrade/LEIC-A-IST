/* Aula LAB PO 01
 *
 * Introducao a objetos/objetos em C
 *
 * Ex. 1 - Animal Simples
 * Ficheiro: Animal.c
 */

// Note: Full naive with no failsafes implementation

# include "Animal.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define MS 16 //Max Size of string

struct animal {
	char   _name[MS];
	int    _age;
	float  _weight;
};


Animal newAnimal(const char *name, int age, float weight) {

	Animal res = (Animal) malloc(sizeof(struct animal));
	strcpy(res->_name, name); // This is unsafe
	res->_age = age;
	res->_weight = weight;

	return res;
}


void destroyAnimal(Animal a) {

	free(a);
}


int  equalsAnimal(Animal a, Animal b) {

	if( a->_age == b->_age && a->_weight == b->_weight &&
	   !strcmp(a->_name, b->_name)) {

		return 1;

	} else {

		return 0;
	}
}



char *getAnimalName(Animal a) {
	return a->_name;
}


int getAnimalAge(Animal a) {
	return a->_age;
}

float getAnimalWeight(Animal a) {
	return a->_weight;
}


void printAnimal(Animal a) {

	printf("Name:\t%s\n", a->_name);
	printf("Age:\t%d\n", a->_age);
	printf("Weight:\t%.2f\n", a->_weight);

}
