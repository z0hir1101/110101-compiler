#ifndef AST_LIST_H
#define AST_LIST_H
#include <stdio.h>
typedef struct LIST_STRUCT {
  void** items;
  size_t size;
  size_t item_size;
} list_T;

list_T* init_list(size_t item_size);
void push_item(list_T* list, void* item);
#endif
