#include "include/token.h"
#include <stdlib.h>

token_T* init_token(char* value, int type)
{
  token_T* token = malloc(sizeof(struct TOKEN_STRUCT));
  token->value = value;
  token->type = type;

  return token;
}
