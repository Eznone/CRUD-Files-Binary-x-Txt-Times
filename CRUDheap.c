#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "structAnimal.h"
#define MAX_LINE 2048


typedef struct fileManager {
  int available_page_id;
  int record_count;
} FileManager;

// Normalmente em bytes
#define PAGE_SIZE 5
int RECORD_SIZE = sizeof(Animal);

int getFileSizeTxt(char *filename) {
  int size = 0;
  Animal placeholder;
  FILE *arq = fopen(filename, "r");

  if (arq == NULL)
    return -1;

  while (fscanf(arq, "%d,%[^,],%[^,],%d,%d", &placeholder.id,
                placeholder.name, placeholder.type,
                &placeholder.numLegs,
                &placeholder.active) == 6)
    size++;

  fclose(arq);
  return size;
}

int getFileSizeBin(char *filename) {
  FILE *arq = fopen(filename, "r");
  fseek(arq, 0, SEEK_END);
  int qtdbytes = ftell(arq);
  fseek(arq, 0, SEEK_SET);

  int size = qtdbytes / sizeof(Animal);
  return size;
}

void createAnimalHeap(
    FILE *file, FileManager *manager, Animal *animal,
    int type) { // Will need two managers, one for binary and one for Text
  int i;
  int curr_page_id = manager->available_page_id;
  int curr_record_count = manager->record_count;
  int page_offset = curr_page_id * PAGE_SIZE * RECORD_SIZE;
  int record_offset = (curr_record_count % PAGE_SIZE) * RECORD_SIZE;

  if (type == 0) { // Will be binary

    file = fopen("animalsHeapBin", "rb+");

    fseek(file, page_offset + record_offset, 0);
    fwrite(animal, RECORD_SIZE, 1, file);

  } else if (type == 1) {

    file = fopen("animalsHeapTxt.txt", "a");

    fprintf(file, "%d,%s,%s,%d,%d\n", animal->id, animal->name,
            animal->type, animal->numLegs, animal->active);
  }
  manager->record_count += 1;
  if (manager->record_count % PAGE_SIZE == 0) {
    manager->available_page_id += 1;
  }

  fclose(file);
}

Animal *readAllAnimalHeap(FILE *file, FileManager *manager, int type) {
  Animal *aux_record = (Animal *)malloc(manager->record_count * sizeof(Animal));
  if (type == 0) {
    file = fopen("animalsHeapBin", "rb");
    fread(aux_record, RECORD_SIZE, manager->record_count, file);
  }
  if (type == 1) {
    file = fopen("animalsHeapTxt.txt", "r");
    for (int i = 0; i <= manager->record_count; i++) {
      fscanf(file, "%d,%[^,],%[^,],%d,%d", &aux_record[i].id,
             aux_record[i].name, aux_record[i].type,
             &aux_record[i].numLegs,
             &aux_record[i].active);
    }
  }
  return aux_record;
}

void permaRemoveHeap(FILE *file, int size, int type) {
  int i = 0;
  Animal *subbuff = (Animal *)malloc(sizeof(Animal));
  FILE *temp;
  if (type == 0) {
    file = fopen("animalsHeapBin", "r");
    temp = fopen("tempBin", "wb");
    while (i < size) {
      fread(subbuff, sizeof(Animal), 1, file);
      if (subbuff->active == 1) {
        fwrite(subbuff, sizeof(Animal), 1, temp);
      }
      i++;
    }
    fclose(temp);

    remove("animalsHeapBin");
    rename("tempBin", "animalHeapBin");
  }

  if (type == 1) {
    file = fopen("animalsHeapTxt", "r");
    FILE *temp = fopen("tempTxt.txt", "w");
    file = fopen("animalsHeapTxt.txt", "r");

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
    remove("animalsHeapTxt.txt");
    rename("tempTxt.txt", "animalsHeapTxt.txt");
    fclose(temp);
  }
}

Animal *readAnimalHeap(FILE *file, FileManager *manager, int record_pos,
                     int type) {
  if (record_pos >= manager->record_count)
    return NULL;

  int curr_page_id = record_pos / PAGE_SIZE;
  // printf("Page Num: %d\n", curr_page_id);
  int page_offset = curr_page_id * PAGE_SIZE * RECORD_SIZE;
  // printf("Page Offset: %d\n", page_offset);
  int record_offset = record_pos % PAGE_SIZE * RECORD_SIZE;
  // printf("Record Offset: %d\n", record_offset);
  Animal *aux_record = (Animal *)malloc(sizeof(Animal));

  if (type == 0) {
    file = fopen("animalsHeapBin", "rb+");

    fseek(file, page_offset + record_offset, 0);
    fread(aux_record, RECORD_SIZE, 1, file);
  }

  else if (type == 1) {
    int updater = 0;
    file = fopen("animalsHeapTxt.txt", "r+");

    for (int i = 0; i <= (page_offset + record_offset) / 132; i++) {
      fscanf(file, "%d,%[^,],%[^,],%d,%d", &aux_record->id,
             aux_record->name, aux_record->type,
             &aux_record->numLegs, &aux_record->active);
    }
  }
  fclose(file);

  return aux_record;
}

Animal *updateAnimalHeap(FILE *file, FileManager *manager, int record_pos,
                       Animal *updated_animal, int type) {
  if (record_pos >= manager->record_count)
    return NULL;

  int curr_page_id = (record_pos - 1) / PAGE_SIZE;
  // printf("Page Num: %d\n", curr_page_id);
  int page_offset = curr_page_id * PAGE_SIZE * RECORD_SIZE;
  // printf("Page Offset: %d\n", page_offset);
  int record_offset = (record_pos - 1) % PAGE_SIZE * RECORD_SIZE;
  // printf("Record Offset: %d\n", record_offset);

  Animal *aux_record = (Animal *)malloc(sizeof(Animal));

  if (type == 0) {
    file = fopen("animalsHeapBin", "rb+");

    fseek(file, page_offset + record_offset, 0);
    fwrite(updated_animal, RECORD_SIZE, 1, file);
  }
  if (type == 1) {
    FILE *temp = fopen("tempTxt.txt", "w");
    file = fopen("animalsHeapTxt.txt", "r");

    for (int i = 0; i < manager->record_count; i++) {
      fscanf(file, "%d,%[^,],%[^,],%d,%d", &aux_record->id,
             aux_record->name, aux_record->type,
             &aux_record->numLegs, &aux_record->active);
      if (aux_record->id == record_pos) {
        fprintf(temp, "%d,%s,%s,%d,%d\n", record_pos, updated_animal->name,
                updated_animal->type,
                updated_animal->numLegs, updated_animal->active);
      } else {
        fprintf(temp, "%d,%s,%s,%d,%d\n", aux_record->id, aux_record->name,
                aux_record->type,
                aux_record->numLegs, aux_record->active);
      }
    }
    remove("animalsHeap.txt");
    rename("tempTxt.txt", "animalsHeapTxt.txt");
    fclose(temp);
  }
  fclose(file);

  return aux_record;
}

void deleteAnimalHeap(FILE *file, FileManager *manager, int record_pos,
                       int type) {
  if (record_pos >= manager->record_count){
    return;
  }

  int curr_page_id = (record_pos - 1) / PAGE_SIZE;
  // printf("Page Num: %d\n", curr_page_id);
  int page_offset = curr_page_id * PAGE_SIZE * RECORD_SIZE;
  // printf("Page Offset: %d\n", page_offset);
  int record_offset = (record_pos - 1) % PAGE_SIZE * RECORD_SIZE;
  // printf("Record Offset: %d\n", record_offset);

  Animal *aux_record = (Animal *)malloc(sizeof(Animal));
  if (type == 0) {
    file = fopen("animalsHeapBin", "rb+");

    fseek(file, page_offset + record_offset, 0);
    fread(aux_record, RECORD_SIZE, 1, file);
    fseek(file, page_offset + record_offset, 0);
    aux_record->active = 0;
    fwrite(aux_record, RECORD_SIZE, 1, file);
  }

  if (type == 1) {
    FILE *temp = fopen("tempTxt.txt", "w");
    file = fopen("animalsHeapTxt.txt", "r");

    for (int i = 0; i < manager->record_count; i++) {
      fscanf(file, "%d,%[^,],%[^,],%d,%d", &aux_record->id,
             aux_record->name, aux_record->type,
             &aux_record->numLegs, &aux_record->active);
      if (aux_record->id == record_pos) {
        fprintf(temp, "%d,%s,%s,%d,%d\n", record_pos, aux_record->name,
                aux_record->type,
                aux_record->numLegs, 0);
      } else {
        fprintf(temp, "%d,%s,%s,%d,%d\n", aux_record->id, aux_record->name,
                aux_record->type,
                aux_record->numLegs, aux_record->active);
      }
    }
    remove("animalsHeapTxt.txt");
    rename("tempTxt.txt", "animalsHeapTxt.txt");
    fclose(temp);
  }

  fclose(file);

}

