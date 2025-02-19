#include "include/110101.h"
#include "include/io.h"
#include  <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("main.c: please specify input file\n");
    return 1;
  }
  char* src = read_file(argv[1]); 
  compile(src);
  free(src);
}
