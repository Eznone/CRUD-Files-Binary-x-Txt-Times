#include "structAnimal.h"

Animal *createAnimal(int id, char *name, char *type,
                 int numLegs, int active) {
  Animal *newAnimal = (Animal *)malloc(sizeof(Animal));
  newAnimal->id = id;
  strcpy(newAnimal->name, name);
  strcpy(newAnimal->type, type);
  newAnimal->numLegs = numLegs;
  newAnimal->active = active;

  return newAnimal;
}

FILE *create_file(char *filename) {
  FILE *file = fopen(filename, "w");
  fclose(file);
  return file;
}