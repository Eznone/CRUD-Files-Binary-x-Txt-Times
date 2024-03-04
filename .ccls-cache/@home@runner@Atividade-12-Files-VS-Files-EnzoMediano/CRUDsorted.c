#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structAnimal.h"
#define MAX_LINES 1000
#define MAX_LEN 1000
#define STRING_SIZE 50



void quicksort(Animal *array_animals, int low, int high) //high should be size - 1
{
  Animal temp;
  int pivot, i, j;
  if(low < high) {
    pivot = low; // select a pivot element
    i = low;
    j = high;
    while(i < j) {
      // increment i till you get a number greater than the pivot element
      while(array_animals[i].id <= array_animals[pivot].id && i <= high)
        i++;
      // decrement j till you get a number less than the pivot element
      while(array_animals[j].id > array_animals[pivot].id && j >= low)
        j--;
      // if i < j swap the elements in locations i and j
      if(i < j) {
        temp = array_animals[i];
        array_animals[i] = array_animals[j];
        array_animals[j] = temp;
      }
    }

    // when i >= j it means the j-th position is the correct position
    // of the pivot element, hence swap the pivot element with the
    // element in the j-th position
    temp = array_animals[j];
    array_animals[j] = array_animals[pivot];
    array_animals[pivot] = temp;
    // Repeat quicksort for the two sub-array_animalsays, one to the left of j
    // and one to the right of j
    quicksort(array_animals, low, j-1);
    quicksort(array_animals, j+1, high);
  }
}

int compare(const void *a, const void *b) {

  Animal *taskA = (Animal *)a;
  Animal *taskB = (Animal *)b;

  return (taskA->id - taskB->id);
}

Animal *readAll(int size, int type, FILE* arq) {
  Animal *array_animals;
  int amount, i;
  array_animals = (Animal *)malloc(size * sizeof(Animal));
  if (type == 0) {
    //printf("Size of task - %lu\n", sizeof(Animal));
    amount = fread(array_animals, sizeof(Animal), size, arq);
  }
  if (type == 1) {
    for (i = 0; i < size; i++) {
      fscanf(arq, "%d,%[^,],%[^,],%d,%d", &array_animals[i].id, array_animals[i].name, array_animals[i].type, &array_animals[i].numLegs, &array_animals[i].active);
    }
  }
  return array_animals;
}

void permaRemoveSort(FILE *file, int size, int type) {
  int i = 0;
  Animal *subbuff = (Animal *)malloc(sizeof(Animal));
  FILE *temp;
  if (type == 0) {
    file = fopen("animalsSortBin", "r");
    temp = fopen("tempBin", "wb");
    while (i < size) {
      fread(subbuff, sizeof(Animal), 1, file);
      if (subbuff->active == 1) {
        fwrite(subbuff, sizeof(Animal), 1, temp);
      }
      i++;
    }
    fclose(temp);

    remove("animalsSortBin");
    rename("tempBin", "animalsSortBin");
  }

  if (type == 1) {
    file = fopen("animalsSortTxt.txt", "r");
    FILE *temp = fopen("tempTxt.txt", "w");

    while (i < size) {
      fscanf(file, "%d,%[^,],%[^,],%d,%d", &subbuff->id, subbuff->name,
             subbuff->type, &subbuff->numLegs,
             &subbuff->active);
      if (subbuff->active == 1) {
        fprintf(temp, "%d,%s,%s,%d,%d\n", subbuff->id, subbuff->name,
                subbuff->type, subbuff->numLegs,
                subbuff->active);
      }
      i++;
    }
    remove("animalsSortTxt.txt");
    rename("tempTxt.txt", "animalsSortTxt.txt");
    fclose(temp);
  }
}


void buildAnimalBin(Animal *array, int size, FILE *arq) {
  fwrite(array, sizeof(Animal), size, arq);
  // printf("ftell says - %ld\n", ftell(arq));
  fclose(arq);
}

void buildAnimalTxt(Animal *array_animals, int size, FILE *arq) {
  for (int i = 0; i < size; i++){
    fprintf(arq, "%d,%s,%s,%d,%d\n", array_animals[i].id, array_animals[i].name, array_animals[i].type, array_animals[i].numLegs, array_animals[i].active);
  }
  fclose(arq);
}

int binarySearch(Animal *arr, int l, int r, int id) // left, right, id
{
  while (l <= r) {
    int m = l + (r - l) / 2;

    // Check if x is present at mid
    if (arr[m].id == id)
      return m;

    // If x greater, ignore left half
    if (arr[m].id < id)
      l = m + 1;

    // If x is smaller, ignore right half
    else
      r = m - 1;
  }

  // If we reach here, then element was not present
  return -1;
}

Animal* createAnimalSorted(Animal*array_animals, Animal* task, int size, int type){

  Animal* new_array_animals = (Animal*)realloc(array_animals, (size+1)*sizeof(Animal));
  new_array_animals[size] = *task;
  quicksort(new_array_animals, 0, size);
  //qsort(array_animals, size + 1, sizeof(Animal), compare);

  if(type == 0){ //Written in Binary
    FILE *arq;
    arq = fopen("animalsSortBin", "wb");
    buildAnimalBin(new_array_animals, size + 1, arq);
  }

  if(type == 1){ //Written in Text
    FILE* arq;
    arq = fopen("animalsSortTxt.txt", "w");
    buildAnimalTxt(new_array_animals, size + 1, arq);
  }

  return new_array_animals;
}

void readAnimalSorted(int id, int size, int type){
  Animal *array_animals;
  int i;
  FILE* arq;
  if (type == 1){
    arq = fopen("animalsSortTxt.txt", "r");
  }
  else if (type == 0){
    arq = fopen("animalsSortBin", "rb");
  }
  array_animals = readAll(size, type, arq);

  i = binarySearch(array_animals, 0, size, id);

  //printf("%d found at: %d\n", id, i);

  printf("%d, %s, %s, %d %d\n", array_animals[i].id, array_animals[i].name, array_animals[i].type, array_animals[i].numLegs, array_animals[i].active);
  fclose(arq);
}

Animal*  updateAnimalSorted(int id, int size, int type){
  Animal *array_animals;
  int i;
  FILE* arq;
  if (type == 1){
    arq = fopen("animalsSortTxt.txt", "r");
  }
  else if (type == 0){
    arq = fopen("animalsSortBin", "rb");
  }
  array_animals = readAll(size, type, arq);
  i = binarySearch(array_animals, 0, size, id);
  char newtype[48] = "Amphibian";

  fclose(arq);
  strcpy(array_animals[i].type, newtype);

  if (type == 1){
    arq = fopen("animalsSortTxt.txt", "w");
    buildAnimalTxt(array_animals, size, arq);
  }
  else if (type == 0){
    arq = fopen("animalsSortBin", "wb");
    buildAnimalBin(array_animals, size, arq);
  }
  return (array_animals);
}

Animal* deleteAnimalSorted(int id, int size, int type){
  Animal *array_animals;
  int i;
  FILE* arq;
  if (type == 1){
    arq = fopen("animalsSortTxt.txt", "r");
  }
  else if (type == 0){
    arq = fopen("animalsSortBin", "rb");
  }
  array_animals = readAll(size, type, arq);
  i = binarySearch(array_animals, 0, size, id);
  array_animals[i].active = 0;

  fclose(arq);

  if (type == 1){
    arq = fopen("animalsSortTxt.txt", "w");
    buildAnimalTxt(array_animals, size, arq);
  }
  else if (type == 0){
    arq = fopen("animalsSortBin", "wb");
    buildAnimalBin(array_animals, size, arq);
  }
  return (array_animals);
}

void readAllSorted(int size, int type) {
  Animal *buffer = (Animal *)malloc(sizeof(Animal));
  FILE *file;
  if (type == 0) {
    file = fopen("animalsSortBin", "rb");
    // printf("Size of task - %lu\n", sizeof(Animal));
    for (int i = 0; i < size; i++) {
      fread(buffer, sizeof(Animal), 1, file);
      printf("%d,%s,%s,%d,%d\n", buffer->id, buffer->name,
             buffer->type, buffer->numLegs,
             buffer->active);
    }
  }
  else if (type == 1) {
    file = fopen("animalsSortTxt.txt", "r");
    for (int i = 0; i < size; i++) {
      fscanf(file, "%d,%[^,],%[^,],%d,%d", &buffer->id, buffer->name,
             buffer->type, &buffer->numLegs,
             &buffer->active);
      printf("%d,%s,%s,%d,%d\n", buffer->id, buffer->name,
             buffer->type, buffer->numLegs,
             buffer->active);
    }
  }
}