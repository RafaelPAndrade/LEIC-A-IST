/* Aula LAB PO 01
 *
 * Introducao a objetos/objetos em C
 *
 * Ex. 2 - Gato Simples
 * Ficheiro: Cat.c
 */

# include "Cat.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

struct cat {

	char  _name[16];
	int   _age;
	float _weight;
	int   _purrLevel;
	float _flufiness;
};



Cat newCat(char *name, int age, float weight, int purrLevel, float flufiness) {

	Cat res = (Cat) malloc(sizeof(struct cat));

	strcpy(res->_name, name);
	res->_age = age;
	res->_weight = weight;
	res->_purrLevel = purrLevel;
	res->_flufiness = flufiness;

	return res;
}


void destroyCat(Cat c) {
	free(c);
}


int equalsCat(Cat c1, Cat c2) {
	return c1->_age == c2->_age &&
	       c1->_weight == c2->_weight &&
	       c1->_purrLevel == c2->_purrLevel &&
	       c1->_flufiness == c2->_flufiness &&
	       !strcmp(c1->_name, c2->_name);
}


char *getCatName(Cat c) {
	return c->_name;
}

int   getCatAge(Cat c) {
	return c->_age;
}

float getCatWeight(Cat c) {
	return c->_weight;
}

int   getCatPurrLevel(Cat c) {
	return c->_purrLevel;
}

float getCatFlufiness(Cat c) {
	return c->_flufiness;
}


void  printCat(Cat c) {

	printf("Name:\t%s\n", c->_name);
	printf("Age:\t%d\n", c->_age);
	printf("Weight:\t%.2f\n", c->_weight);
	printf("Purr Level:\t%d\n", c->_purrLevel);
	printf("Flufiness:\t%.2f\n", c->_flufiness);

}
