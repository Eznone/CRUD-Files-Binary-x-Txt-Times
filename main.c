#include "CRUDheap.h"
#include "CRUDnorm.h"
#include "CRUDsorted.h"
#include "extras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int get_file_size(char *filename) {
  int size = 0;
  Animal placeholder;
  FILE *arq = fopen(filename, "r");

  if (arq == NULL)
    return -1;
  while (fscanf(arq, "%d,%[^,],%[^,],%d,%d", &placeholder.id, placeholder.name, placeholder.type, &placeholder.numLegs, &placeholder.active) == 5)
    size++;

  fclose(arq);
  return size;
}

int main(void) {
  int randomNum, size, sizeSort;
  sizeSort = 0;
  srand(time(0));
  randomNum = rand() % (1000000 + 1 - 9999999) + 9999999;
  Animal* newAnimalNormSort, *array_animalsT, *array_animalsB;
  clock_t start, end;
  float f;

  // Creating files
  FILE* heapFileBin, *heapFileTxt, *normFileTxt, *normFileBin, *sortFileBin, *sortFileTxt;
  heapFileBin = create_file("animalsHeapBin");
  heapFileTxt = create_file("animalsHeapTxt.txt");
  normFileBin = create_file("animalsNormBin");
  normFileTxt = create_file("animalsNormTxt.txt");
  sortFileBin = create_file("animalsSortBin");
  sortFileTxt = create_file("animalsSortTxt.txt");

  // Determining size of files that will be read from

  // Setting Managers for heap files
  FileManager managerBin = {0, 0};
  FileManager managerTxt = {0, 0};
  // FILE* file = fopen("teste.txt", "w");

  // Create------------------------------------------------------------------------------------------
  printf("Create Tests ------------------------------------------------------------------\n\n");
  Animal *newAnimalHeap =
      createAnimal(1, "Tiger", "mammal", 4, 1);
  start = clock();
  createAnimalHeap(heapFileBin, &managerBin, newAnimalHeap, 0);
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Heap Create Binary:\t %f seconds\n\n", f); // HeapCreateBinary - Time
  newAnimalNormSort = createAnimal(randomNum, "Tiger", "mammal", 4, 1);
  start = clock();
  createAnimalNorm(newAnimalNormSort, 0);
  end = clock();
  f = (float)(end-start)/CLOCKS_PER_SEC;
  printf("Norm Create Binary: %f seconds\n\n", f); // NormCreateBinary - Time
  start = clock();
  array_animalsB = createAnimalSorted(array_animalsB, newAnimalNormSort, sizeSort, 0);
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Sort Create Binary: %f seconds\n\n", f); // SortCreateBinary - Time


  start = clock();
  createAnimalHeap(heapFileTxt, &managerTxt, newAnimalHeap, 1);
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Heap Create Text:\t %f seconds\n\n", f); // HeapCreateText - Time
  start = clock();
  createAnimalNorm(newAnimalNormSort, 1);
  end = clock();
  f = (float)(end-start)/CLOCKS_PER_SEC;
  printf("Norm Create Text: %f seconds\n\n", f); //NormCreateText - Time
  start = clock();
  array_animalsT = createAnimalSorted(array_animalsT, newAnimalNormSort, sizeSort, 1);
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Sort Create Text: %f seconds\n\n", f); //SortCreateText - Time

      //Adding second animal to Norm and Sort
  sizeSort++;
  randomNum = rand() % (1000000 + 1 - 9999999) + 9999999;
  newAnimalNormSort = createAnimal(randomNum, "Penguin", "marine bird", 2, 1);
  createAnimalNorm(newAnimalNormSort, 0);
  createAnimalNorm(newAnimalNormSort, 1);
  array_animalsB = createAnimalSorted(array_animalsB, newAnimalNormSort, sizeSort, 0);
  array_animalsT = createAnimalSorted(array_animalsT, newAnimalNormSort, sizeSort, 1);
      //Adding third animal to Norm and Sort
  sizeSort++;
  randomNum = rand() % (1000000 + 1 - 9999999) + 9999999;
  newAnimalNormSort = createAnimal(randomNum, "Frog", "mammal", 4, 1);
  createAnimalNorm(newAnimalNormSort, 0);
  createAnimalNorm(newAnimalNormSort, 1);
  array_animalsB = createAnimalSorted(array_animalsB, newAnimalNormSort, sizeSort, 0);
  array_animalsT = createAnimalSorted(array_animalsT, newAnimalNormSort, sizeSort, 1);
  sizeSort++;
      //Adding second and third to Heap
  newAnimalHeap = createAnimal(2, "Penguin", "marine bird", 2, 1);
  createAnimalHeap(heapFileBin, &managerBin, newAnimalHeap, 0);
  createAnimalHeap(heapFileTxt, &managerTxt, newAnimalHeap, 1);

  newAnimalHeap = createAnimal(3, "Frog", "mammal", 4, 1);
  createAnimalHeap(heapFileBin, &managerBin, newAnimalHeap, 0);
  createAnimalHeap(heapFileTxt, &managerTxt, newAnimalHeap, 1);



  // ReadOne-----------------------------------------------------------------------------------------
  printf("ReadOne Tests ------------------------------------------------------------------\n\n");
  start = clock();
  Animal *foundAnimal = readAnimalHeap(heapFileBin, &managerBin, 2, 0);
  printf("Heap: %d - %s - %s - %d - %d\n", foundAnimal->id,
         foundAnimal->name, foundAnimal->type,
         foundAnimal->numLegs, foundAnimal->active);
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Heap ReadOne Binary: %f seconds\n\n", f); // HeapReadOneBinary - Time
  start = clock();
  readAnimalNorm(randomNum, 0);
  end = clock();
  f = (float)(end-start)/CLOCKS_PER_SEC;
  printf("Norm ReadOne Binary: %f seconds\n\n", f); // NormReadOneBinary - Time
  start = clock();
  readAnimalSorted(randomNum, sizeSort, 0);
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Sort ReadOne Binary: %f seconds\n\n", f); // SortReadOneBinary - Time

  start = clock();
  foundAnimal = readAnimalHeap(heapFileTxt, &managerTxt, 2, 1);
  printf("Heap: %d - %s - %s - %d - %d\n", foundAnimal->id, foundAnimal->name,
         foundAnimal->type,
         foundAnimal->numLegs, foundAnimal->active);
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Heap ReadOne Text:\t %f seconds\n\n", f); // HeapReadOneText - Time
  start = clock();
  readAnimalNorm(randomNum, 1);
  end = clock();
  f = (float)(end-start)/CLOCKS_PER_SEC;
  printf("Norm ReadOne Text: %f seconds\n\n", f); // NormReadOneText - Time
  start = clock();
  readAnimalSorted(randomNum, sizeSort, 1);
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Sort ReadOne Text: %f seconds\n\n", f); // SortReadOneText - Time

  // Update------------------------------------------------------------------------------------------
  printf("Update Tests ------------------------------------------------------------------\n\n");
  Animal *updated_task = readAnimalHeap(heapFileBin, &managerBin, 2, 0);
  strcpy(updated_task->name, "Lion");

  start = clock();
  updateAnimalHeap(heapFileBin, &managerBin, 1, updated_task, 0);
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Heap Update Binary:\t %f seconds\n\n", f); // HeapUpdateBinary - Time
  size = get_file_size("animalsNormTxt.txt");
  start = clock();
  UpdateAnimalNorm(randomNum, size, 0);
  end = clock();
  f = (float)(end-start)/CLOCKS_PER_SEC;
  printf("Norm Update Binary: %f seconds\n\n", f); // NormUpdateBinary - Time
  start = clock();
  array_animalsB = updateAnimalSorted(randomNum, sizeSort, 0);
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Sort Update Binary: %f seconds\n\n", f); // SortUpdateBinary - Time

  start = clock();
  updateAnimalHeap(heapFileBin, &managerBin, 1, updated_task, 1);
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Heap Update Text:\t %f seconds\n\n", f); // HeapUpdateText - Time
  start = clock();
  UpdateAnimalNorm(randomNum, size, 1);
  end = clock();
  f = (float)(end-start)/CLOCKS_PER_SEC;
  printf("Norm Update Text: %f seconds\n\n", f); // NormUpdateText - Time
  start = clock();
  array_animalsT = updateAnimalSorted(randomNum, sizeSort, 1);
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Sort Update Text: %f seconds\n\n", f); // SortUpdateText - Time

  // Delete------------------------------------------------------------------------------------------
  printf("Delete Tests ------------------------------------------------------------------\n\n");
  start = clock();
  deleteAnimalHeap(heapFileTxt, &managerTxt, 2, 1);
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Heap Delete Text:\t %f seconds\n\n", f); // HeapDeleteBinary - Time
  size = get_file_size("animalsNormTxt.txt");
  start = clock();
  deleteAnimalNorm(randomNum, size, 0);
  end = clock();
  f = (float)(end-start)/CLOCKS_PER_SEC;
  printf("Norm Delete Binary: %f seconds\n\n", f); // NormDeleteBinary - Time
  start = clock();
  array_animalsB = deleteAnimalSorted(randomNum, size, 0);
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Sort Delete Binary: %f seconds\n\n", f); // SortDeleteBinary - Time

  start = clock();
  deleteAnimalHeap(heapFileBin, &managerBin, 2, 0);
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Heap Delete Binary:\t %f seconds\n\n", f); // HeapDeleteBinary - Time
  foundAnimal = readAnimalHeap(heapFileBin, &managerBin, 1, 0);
  start = clock();
  deleteAnimalNorm(randomNum, size, 1);
  end = clock();
  f = (float)(end-start)/CLOCKS_PER_SEC;
  printf("Norm Delete Text: %f seconds\n\n", f); // NormDeleteBinary - Time
  start = clock();
  array_animalsT = deleteAnimalSorted(randomNum, size, 1); //No return since binary will happen
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Sort Delete Text: %f seconds\n\n", f); // SortDeleteText- Time

  // ReadAll-----------------------------------------------------------------------------------------
  printf("ReadAll Tests------------------------------------------------------------------\n\n");

  start = clock();
  Animal* heapRecords = readAllAnimalHeap(heapFileBin, &managerBin, 0);
  for (int i = 0; i <= managerBin.record_count - 1; i++) {
    printf("%d - %s - %s - %d - %d\n", heapRecords[i].id,
           heapRecords[i].name, heapRecords[i].type,
           heapRecords[i].numLegs,
           heapRecords[i].active);
  }
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Heap ReadAll Binary:\t %f seconds\n\n", f); // HeapReadAllBinary - Time
  size = get_file_size("animalsNormTxt.txt");
  start = clock();
  readAllNorm(size, 0);
  end = clock();
  f = (float)(end-start)/CLOCKS_PER_SEC;
  printf("Norm ReadAll Binary: %f seconds\n\n", f); // NormReadAllBinary - Time
  readAllSorted(sizeSort, 0);
  end = clock();
  f = (float)(end-start)/CLOCKS_PER_SEC;
  printf("Sort ReadAll Binary: %f seconds\n\n", f); // SortReadAllBinary - Time

  start = clock();
  heapRecords = readAllAnimalHeap(heapFileTxt, &managerTxt, 1);
  for (int i = 0; i <= managerTxt.record_count - 1; i++) {
    printf("%d - %s - %s - %d - %d\n", heapRecords[i].id,
           heapRecords[i].name, heapRecords[i].type,
           heapRecords[i].numLegs,
           heapRecords[i].active);
  }
  end = clock();
  f = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Heap ReadAll Text:\t %f seconds\n\n", f); // HeapReadAllText - Time
  size = get_file_size("animalsNormTxt.txt");
  start = clock();
  readAllNorm(size, 1);
  end = clock();
  f = (float)(end-start)/CLOCKS_PER_SEC;
  printf("Norm ReadAll Text: %f seconds\n\n", f); // NormReadAllText - Time
  readAllSorted(sizeSort, 1);
  end = clock();
  f = (float)(end-start)/CLOCKS_PER_SEC;
  printf("Sort ReadAll Text: %f seconds\n\n", f); // SortReadAllText - Time

  // Removing
  // Permanently----------------------------------------------------------------------------

  permaRemoveHeap(heapFileBin, managerBin.record_count, 0);
  permaRemoveHeap(heapFileTxt, managerTxt.record_count, 1);
  permaRemoveNorm(normFileBin, size, 0);
  permaRemoveNorm(normFileTxt, size, 1);
  permaRemoveSort(sortFileBin, sizeSort, 0);
  permaRemoveSort(sortFileTxt, sizeSort, 1);


  return 0;
}