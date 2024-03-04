#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef STRUCTANIMAL

#define STRUCTANIMAL

typedef struct animal {
  int id;
  char name[48];
  char type[24];
  int numLegs;
  int active; // bool
} Animal;

#endif

