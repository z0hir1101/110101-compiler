#ifndef AST_NODE_H
#define AST_NODE_H
#include "token.h"
#include "stdio.h"
typedef struct NODE_STRUCT {
  enum {
    NODE_ARGUMENTS,
    NODE_LITERAL,
    NODE_IDENTIFIRE,
    NODE_VARIABLE_DEF,
    NODE_FUNCTION_DEF,
    NODE_FUNCTION_CALL,
    NODE_KEYWORD,
    NODE_OPERATOR,
    NODE_ROOT,
  } type;
  token_T* value;

  struct NODE_STRUCT** node_list;
  size_t size;
} node_T;

node_T* init_node(int type, token_T* value);
void push_node(node_T* root, node_T* node);
#endif
