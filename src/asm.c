#include "include/asm.h"
#include <stdlib.h>
#include <string.h>

char* asm_root(node_T* root)
{
  int i, size = root->size;
  node_T* curr_node;

  char* new_segment = NULL;
  char* _bss = "section .bss\n";
  char* _data = "section .data\n";
  char* _text = "section .text\n"
                "global _start\n"
                "_start:\n";

  for (i = 0; i < size; ++i) {
    curr_node = root->node_list[i];
    switch (curr_node->type) {
    case NODE_VARIABLE_DEF: 
      new_segment = asm_var_declr(curr_node);
      _data = realloc(_data, (strlen(_data) + strlen(new_segment) + 1) * sizeof(char));
      strcat(_data, new_segment);
      break;
    case NODE_FUNCTION_CALL:
      new_segment = asm_func_call(curr_node);
      _text = realloc(_text, (strlen(_text) + strlen(new_segment) + 1) * sizeof(char));
      strcat(_text, new_segment);
      break;
    default:    
      printf("asm.c [asm_root]: unexpected node %d\n", curr_node->type);
      exit(1);
      break;
    }
  }

  return NULL;
}

char* asm_var_declr(node_T* node)
{
}

char* asm_func_call(node_T* node)
{
}

char* asm_exprasion(node_T* node)
{
}
