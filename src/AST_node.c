#include "include/AST_node.h"
#include <stdlib.h>

node_T* init_node(int type, token_T* token)
{
  node_T* node = malloc(sizeof(node_T));
  node->type = type;
  node->token = token;
  node->size = 0;
  node->items = 0;

  return node;
}

void push_node(node_T* root, node_T* node)
{
  if (!root->items)
    root->items = calloc(1, sizeof(node_T));
  else 
    root->items = realloc(root->items, root->size * sizeof(node_T));

  root->items[root->size] = node;

  root->size++;
}

