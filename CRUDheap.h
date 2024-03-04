#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structAnimal.h"
#define PAGE_SIZE 5

typedef struct fileManager {
  int available_page_id;
  int record_count;
}FileManager;

void createAnimalHeap(FILE* file, FileManager* manager, Animal* record, int type);
Animal* readAnimalHeap(FILE* file, FileManager* manager, int record_pos, int type);
Animal* updateAnimalHeap(FILE* file, FileManager* manager, int record_pos, Animal* updated_task, int type);
void deleteAnimalHeap(FILE* file, FileManager* manager, int record_pos, int type);
Animal* readAllAnimalHeap(FILE* file, FileManager* manager, int type);
void permaRemoveHeap(FILE *file, int size, int type);
int getFileSizeTxt(char *filename);
int getFileSizeBin(char *filename);
