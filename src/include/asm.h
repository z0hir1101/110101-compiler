#ifndef ASM_H
#define ASM_H
#include "AST_node.h"
char* asm_root(node_T* root);
char* asm_node(node_T* node);

char* asm_var_declr(node_T* node);
char* asm_func_call(node_T* node);
#endif
