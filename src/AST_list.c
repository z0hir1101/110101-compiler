#include "include/AST_list.h"
#include <stdlib.h>

list_T* init_list(size_t item_size)
{
  list_T* list = malloc(sizeof(list_T));
  list->item_size = item_size;
  list->size = 0;
  list->items = 0;

  return list;
}

void push_item(list_T* list, void* item)
{
  list->size++;
  
  if (!list->items)
    list->items = calloc(1, list->item_size);
  else 
    list->items = realloc(list->items, list->size * list->item_size);

  list->items[list->size] = item;
}

