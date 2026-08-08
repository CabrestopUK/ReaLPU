void savetoram() {}
void savetorom() {
  FILE *file
  file = fopen(filename, "w");
  if (file == NULL) {
  printf("Could not open file.\n");
  return 1;
}
