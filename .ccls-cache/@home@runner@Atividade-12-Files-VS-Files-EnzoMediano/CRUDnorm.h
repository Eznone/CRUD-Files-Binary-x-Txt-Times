#include <stdio.h>
#include "structAnimal.h"

void readAllNorm(int type, int size);
void createAnimalNorm(Animal* animal, int type);
void readAnimalNorm(int id, int type);
void UpdateAnimalNorm(int id, int size, int type);
void deleteAnimalNorm(int id, int size, int type);
void permaRemoveNorm(FILE *file, int size, int type);
