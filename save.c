// Author: Troy Davies
#include <stdio.h>
#include <string.h>
void savetoram() {}
void savetorom(char filename[256], struct data) {
  FILE *file // Initiallise system
  file = fopen(filename, "w");
  if (file == NULL) {
  printf("Could not open file.\n");
  }
  char file[50000] // Magic number
  return 1;
}
