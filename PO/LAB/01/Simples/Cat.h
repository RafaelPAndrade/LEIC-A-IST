/* Aula LAB PO 01
 *
 * Introducao a objetos/objetos em C
 *
 * Ex. 2 - Gato Simples
 * Ficheiro: Cat.h
 */

# ifndef CAT_H
# define CAT_H

typedef struct cat *Cat;



Cat newCat(const char *name, int age, float weight, int _purrLevel, float 
_flufiness);
void destroyCat(Cat c);

int equalsCat(Cat c1, Cat c2);

char *getCatName(Cat c);
int   getCatAge(Cat c);
float getCatWeight(Cat c);
int   getCatPurrLevel(Cat c);
float getCatFlufiness(Cat c);

void  printCat(Cat c);

# endif
