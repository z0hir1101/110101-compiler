#include "include/110101.h"
#include "include/lexer.h"

void compile(char* src)
{
  lexer_T* lexer = init_lexer(src);
  token_T* token = 0;

  while ((token = lexer_next_token(lexer))->type != TOKEN_EOF)
    printf("value (%s), type (%d)\n", token->value, token->type);
}
