#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structAnimal.h"

void readAllNorm(int size, int type) {
  Animal *buffer = (Animal *)malloc(sizeof(Animal));
  FILE *file;
  if (type == 0) {
    file = fopen("animalsNormBin", "rb");
    // printf("Size of animal - %lu\n", sizeof(Animal));
    for (int i = 0; i < size; i++) {
      fread(buffer, sizeof(Animal), 1, file);
      printf("%d,%s,%s,%d,%d\n", buffer->id, buffer->name,
             buffer->type, buffer->numLegs,
             buffer->active);
    }
  }
  if (type == 1) {
    file = fopen("animalsNormTxt.txt", "r");
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

void permaRemoveNorm(FILE *file, int size, int type) {
  int i = 0;
  Animal *subbuff = (Animal *)malloc(sizeof(Animal));
  FILE *temp;
  if (type == 0) {
    file = fopen("animalsNormBin", "r");
    temp = fopen("tempBin", "wb");
    while (i < size) {
      fread(subbuff, sizeof(Animal), 1, file);
      if (subbuff->active == 1) {
        fwrite(subbuff, sizeof(Animal), 1, temp);
      }
      i++;
    }
    fclose(temp);

    remove("animalsNormBin");
    rename("tempBin", "animalsNormBin");
  }

  if (type == 1) {
    file = fopen("animalsNormTxt.txt", "r");
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
    remove("animalsNormTxt.txt");
    rename("tempTxt.txt", "animalsNormTxt.txt");
    fclose(temp);
  }
}

void createAnimalNorm(Animal *animal, int type) {
  FILE *file;

  if (type == 0) { // Means it will be binary
    file = fopen("animalsNormBin", "ab");
    fwrite(animal, sizeof(Animal), 1, file);

  } else if (type == 1) { // Means it will be binary
    file = fopen("animalsNormTxt.txt", "a");
    fprintf(file, "%d,%s,%s,%d,%d\n", animal->id, animal->name,
            animal->type, animal->numLegs, animal->active);
  }
  fclose(file);
}

void readAnimalNorm(int id, int type) {
  FILE *file;
  Animal *buffer = (Animal *)malloc(sizeof(Animal));

  if (type == 0) {
    file = fopen("animalsNormBin", "rb");
    while (!feof(file) && !ferror(file)) {
      fread(buffer, sizeof(Animal), 1, file);
      if (buffer->id == id) {
        printf("Norm: %d,%s,%s,%d,%d\n", buffer->id, buffer->name,
               buffer->type, buffer->numLegs,
               buffer->active);
        return;
      }
    }
  }

  else if (type == 1) {
    file = fopen("animalsNormTxt.txt", "r");
    while (!feof(file) && !ferror(file)) {
      fscanf(file, "%d,%[^,],%[^,],%d,%d", &buffer->id, buffer->name,
             buffer->type, &buffer->numLegs,
             &buffer->active);
      if (buffer->id == id) {
        printf("Norm: %d,%s,%s,%d,%d\n", buffer->id, buffer->name,
               buffer->type, buffer->numLegs,
               buffer->active);
        return;
      }
    }
  }
}

void UpdateAnimalNorm(int id, int size, int type) {
  FILE *file;
  char string[48] = "Amphibian";
  Animal *buffer = (Animal *)malloc(sizeof(Animal));
  if (type == 0) {
    FILE *temp = fopen("tempBin", "wb");
    file = fopen("animalsNormBin", "rb");
    for(int i = 0; i < size; i++) {
      fread(buffer, sizeof(Animal), 1, file);
      if (buffer->id == id) {
        strcpy(buffer->type, string);
      }
      fwrite(buffer, sizeof(Animal), 1, temp);
    }
    remove("animalsNormBin");
    rename("tempBin", "animalsNormBin");
    fclose(temp);
  }

  else if (type == 1) {
    FILE *temp = fopen("tempTxt.txt", "w");
    file = fopen("animalsNormTxt.txt", "r");
    for(int i = 0; i < size; i++) {
      fscanf(file, "%d,%[^,],%[^,],%d,%d", &buffer->id, buffer->name,
             buffer->type, &buffer->numLegs,
             &buffer->active);
      if (buffer->id == id) {
        strcpy(buffer->type, string);
      }
      fprintf(temp, "%d,%s,%s,%d,%d\n", buffer->id, buffer->name,
       buffer->type, buffer->numLegs,
       buffer->active);
    }
    remove("animalsNormTxt.txt");
    rename("tempTxt.txt", "animalsNormTxt.txt");
    fclose(temp);
  }

}

void deleteAnimalNorm(int id, int size, int type) {
  FILE *file;
  Animal *buffer = (Animal *)malloc(sizeof(Animal));
  if (type == 0) {
    FILE *temp = fopen("tempBin", "wb");
    file = fopen("animalsNormBin", "rb");
    for(int i = 0; i < size; i++) {
      fread(buffer, sizeof(Animal), 1, file);
      if (buffer->id == id) {
        buffer->active = 0;
      }
      fwrite(buffer, sizeof(Animal), 1, temp);
    }
    remove("animalsNormBin");
    rename("tempBin", "animalsNormBin");
    fclose(temp);
  }

  else if (type == 1) {
    FILE *temp = fopen("tempTxt.txt", "w");
    file = fopen("animalsNormTxt.txt", "r");
    for(int i = 0; i < size; i++) {
      fscanf(file, "%d,%[^,],%[^,],%d,%d", &buffer->id, buffer->name,
             buffer->type, &buffer->numLegs,
             &buffer->active);
      if (buffer->id == id) {
        buffer->active = 0;
      }
      fprintf(temp, "%d,%s,%s,%d,%d\n", buffer->id, buffer->name,
       buffer->type, buffer->numLegs,
       buffer->active);
    }
    remove("animalsNormTxt.txt");
    rename("tempTxt.txt", "animalsNormTxt.txt");
    fclose(temp);
  }

}