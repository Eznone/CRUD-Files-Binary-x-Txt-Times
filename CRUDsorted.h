#include <stdio.h>
#include "structAnimal.h"

Animal *readAll(int size, int type, FILE* arq) ;
void readAllSorted(int size, int type);
void buildAnimalBin(Animal *array, int size, FILE *arq);
int binarySearch(Animal* arr, int l, int r, int id);
Animal* createAnimalSorted(Animal*array_animals, Animal* task, int size, int type);
Animal* updateAnimalSorted(int id, int size, int type);
Animal* deleteAnimalSorted(int id, int size, int type);
void readAnimalSorted(int id, int size, int type);
void permaRemoveSort(FILE *file, int size, int type);
void quicksort(Animal *array_animals, int low, int high);
int compare(const void *a, const void *b);