#ifndef AST_NODE_H
#define AST_NODE_H
#include "AST_list.h"
#include "token.h"
typedef struct NODE_STRUCT {
  enum {
    NODE_FUNCTION_DEF,
    NODE_FUNCITON_CALL,
    NODE_VARIABLE_DEF,
    NODE_ARGUMENTS,
    NODE_IDENT,
    NODE_KEYWORD,
    NODE_LITERAL,
    NODE_ROOT,
  } type;

  token_T* value;
  list_T* children;
} node_T;

node_T* init_node(int type, token_T* value);
#endif
