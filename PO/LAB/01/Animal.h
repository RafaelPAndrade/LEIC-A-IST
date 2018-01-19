/* Aula LAB PO 01
 *
 * Introducao a objetos/objetos em C
 *
 * Ex. 1 - Animal Simples
 * Ficheiro: Animal.h
 */

# ifndef ANIMAL_H
# define ANIMAL_H


typedef struct animal *Animal;


Animal newAnimal(const char *name, int age, float weight);
void destroyAnimal(Animal);

int  equalsAnimal(Animal a, Animal b);

char *getAnimalName(Animal a);
int   getAnimalAge(Animal a);
float getAnimalWeight(Animal a);

void printAnimal(Animal a);


#endif
