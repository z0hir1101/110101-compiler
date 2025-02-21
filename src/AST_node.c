#include "include/AST_node.h"
#include <stdlib.h>

node_T* init_node(int type, token_T* value)
{
  node_T* node = malloc(sizeof(struct NODE_STRUCT));
  node->type = type;
  node->value = value;

  return node;
}

