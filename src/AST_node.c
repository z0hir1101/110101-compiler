#include "include/AST_node.h"
#include <stdlib.h>

node_T* init_node(int type, token_T* value)
{
  node_T* node = malloc(sizeof(node_T));
  node->type = type;
  node->value = value;
  node->size = 0;
  node->node_list = 0;

  return node;
}

void push_node(node_T* root, node_T* node)
{
  root->size++;
  
  if (!root->node_list)
    root->node_list= calloc(1, sizeof(node_T));
  else 
    root->node_list= realloc(root->node_list, root->size * sizeof(node_T));

  root->node_list[root->size] = node;
}

