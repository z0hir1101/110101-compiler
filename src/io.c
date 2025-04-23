#include "include/io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_file(const char* file)
{
  FILE* fp;
  char* line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(file, "rb");
  if (fp == NULL) {
    printf("io.c [read_file]: cannot read file '%s'\n", file);
    exit(1);
  }

  char* buffer = (char*) calloc(1, sizeof(char));
  buffer[0] = '\0';

  while ((read = getline(&line, &len, fp)) != -1) {
    buffer = (char*) realloc(buffer, (strlen(buffer)+strlen(line)+1) * sizeof(char));
    strcat(buffer, line);
  }
  fclose(fp);
  if (line)
    free(line);

  return buffer;
}

void write_file(const char* file_name, char* outbuffer)
{
  FILE* fp;

  fp = fopen(file_name, "wb");
  if (fp == NULL) {
    printf("io.c [write_file]: cannot open file '%s'\n", file_name);
    exit(1);
  }

  fprintf(fp, outbuffer);

  fclose(fp);
}
