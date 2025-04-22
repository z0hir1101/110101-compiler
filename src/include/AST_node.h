#ifndef AST_NODE_H
#define AST_NODE_H
#include "token.h"
#include "stdio.h"

typedef struct NODE_STRUCT {
  enum {
    NODE_ARGUMENTS,     //0
    NODE_LITERAL,       //1
    NODE_IDENTIFIRE,    //2
    NODE_VARIABLE_DEF,  //3
    NODE_FUNCTION_DEF,  //4 
    NODE_FUNCTION_CALL, //5
    NODE_KEYWORD,       //6
    NODE_OPERATOR,      //7
    NODE_ROOT,          //8
  } type;
  token_T* token;

  struct NODE_STRUCT** items;
  size_t size;
} node_T;

node_T* init_node(int type, token_T* token);
void push_node(node_T* root, node_T* node);
#endif
