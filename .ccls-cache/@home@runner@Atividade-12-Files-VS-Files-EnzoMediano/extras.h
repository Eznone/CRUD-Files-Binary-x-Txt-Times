#include "structAnimal.h"

#ifndef CREATEANIMAL
#define CREATEANIMAL
Animal *createAnimal(int id, char *name, char *type,
 int numLegs, int active);
#endif

#ifndef CREATEFILE
#define CREATEFILE
FILE *create_file(char *filename);
#endif