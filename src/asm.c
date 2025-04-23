#include "include/asm.h"
#include <stdlib.h>
#include <string.h>
#include  <ctype.h>

char* asm_root(node_T* root)
{
  const char* data_section = "section .data\n";
  const char* text_section = "section .text\n"
                             "global _start\n"
                             "_start:\n";

  char* new_value = NULL;
  char* value = calloc(1, sizeof(char));
  char* _data = calloc(1, sizeof(char));
  char* _text = calloc(1, sizeof(char));

  _data = realloc(_data, (strlen(_data) + strlen(data_section)) * sizeof(char));
  _text = realloc(_text, (strlen(_text) + strlen(text_section)) * sizeof(char));

  strcat(_data, data_section);
  strcat(_text, text_section);

  for (int i = 0; i < root->size; ++i)
    if (root->items[i]->type == NODE_VARIABLE_DEF) {
      new_value = asm_var_declr(root->items[i]);
      _data = realloc(_data, (strlen(_data) + strlen(new_value) + 1) * sizeof(char));
      strcat(_data, new_value);
    } else { 
      new_value = asm_node(root->items[i]);
      _text = realloc(_text, (strlen(_text) + strlen(new_value) + 1) * sizeof(char));
      strcat(_text, new_value);
    }
  value = realloc(value, (strlen(_data) + strlen(_text) + 1) * sizeof(char));
  strcat(value, _data);
  strcat(value, _text);

  return value;
}

char* asm_node(node_T* node)
{
  char* value = calloc(1, sizeof(char));
  char* new_value = NULL;

  switch (node->type) {
  case NODE_FUNCTION_CALL:
    new_value = asm_func_call(node);
    break;
  default:    
    printf("asm.c [asm_root]: unexpected node %d\n", node->type);
    exit(1);
  }

  value = realloc(value, (strlen(new_value) + 1) * sizeof(char));
  strcat(value, new_value);

  return value;
}

char* asm_var_declr(node_T* node)
{
  if (node->type != NODE_VARIABLE_DEF) {
    printf("asm.c [asm_var_declr]: unexpected node %d\n", node->type);
    exit(1);
  }

  char* s = calloc(1, sizeof(char));
  char* arg1 = NULL;
  char* arg2 = NULL;
  int i = 0;
  
  if (node->items[i]->token->type == TOKEN_ID) {
    const char* template = "%s dd %s\n";

    arg1 = node->size ? node->items[i++]->token->value : NULL;
    arg2 = node->size - 1 ? node->items[i++]->token->value : NULL;

    char* tmp_s = calloc(strlen(template) + 128, sizeof(char));
    sprintf(tmp_s, template, arg1, arg2);
    s = realloc(s, (strlen(tmp_s) + 1) * sizeof(char));
    strcat(s, tmp_s); 
  }
  
  return s;
}

char* asm_func_call(node_T* node)
{
  if (node->type != NODE_FUNCTION_CALL) {
    printf("asm.c [asm_func_call]: unexpected node %d\n", node->type);
    exit(1);
  }

  char* s = calloc(1, sizeof(char));
  char* arg = NULL;
  node_T* curr_node = node->items[0];
  
  if (node->token->type == TOKEN_KEYW_RETURN) {
    const char* template = "mov rax, 60\n"
                           "mov rdi, %s\n" 
                           "syscall\n";
    const char* var_call = "[%s]";

    arg = curr_node->size ? curr_node->items[0]->token->value : NULL;

    if (!isdigit(arg[0])) {
      arg = calloc(strlen(var_call) + 128, sizeof(char));
      sprintf(arg, var_call, curr_node->items[0]->token->value);
    }

    char* tmp_s = calloc(strlen(template) + 128, sizeof(char));
    sprintf(tmp_s, template, arg);
    s = realloc(s, (strlen(tmp_s) + 1) * sizeof(char));
    strcat(s, tmp_s); 
  }

  return s;
}
