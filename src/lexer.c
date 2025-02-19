#include "include/lexer.h"
#include "include/macros.h"
#include  <ctype.h>
#include <string.h>
#include <stdlib.h>

lexer_T* init_lexer(char* src)
{
  lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
  lexer->src = src;
  lexer->src_size = strlen(src);
  lexer->i = 0;
  lexer->c = src[lexer->i];

  return lexer;
}

void lexer_advance(lexer_T* lexer)
{
  if (lexer->i < lexer->src_size && lexer->c != '\0') {
    lexer->i++;
    lexer->c = lexer->src[lexer->i];
  }
}

token_T* lexer_advance_with(lexer_T* lexer, token_T* token)
{
  lexer_advance(lexer);
  return token;
}

token_T* lexer_parse_idt(lexer_T* lexer)
{
  char* value = calloc(1, sizeof(char));

  while (isdigit(lexer->c)) {
    value = realloc(value, (strlen(value) + 2) * sizeof(char));
    strcat(value, (char[]){lexer->c, 0});
    lexer_advance(lexer);
  }

  return init_token(value, TOKEN_IDT);
}

token_T* lexer_parse_lit(lexer_T* lexer)
{
  char* value = calloc(1, sizeof(char));

  while (isalpha(lexer->c)) {
    value = realloc(value, (strlen(value) + 2) * sizeof(char));
    strcat(value, (char[]){lexer->c, 0});
    lexer_advance(lexer);
  }

  return init_token(value, TOKEN_LIT);
}

char lexer_peek(lexer_T* lexer, int offset)
{
  return lexer->src[MIN(lexer->i + offset, lexer->src_size)];
}

void lexer_skip_whitespace(lexer_T* lexer)
{
  while (lexer->c == ' ' || lexer->c == '\t')
    lexer_advance(lexer);
}

token_T* lexer_next_token(lexer_T* lexer)
{
  lexer_skip_whitespace(lexer);

  if (lexer->c == EOF || lexer->c == '\n')
    return init_token(0, TOKEN_EOF);

  if (isalpha(lexer->c))
    return lexer_parse_lit(lexer);
  if (isdigit(lexer->c))
    return lexer_parse_idt(lexer);

  switch (lexer->c) {
  case '=': {
    if (lexer_peek(lexer, 1) == '>')
      return lexer_advance_with(lexer, init_token("=>", TOKEN_OPT));
    return lexer_advance_with(lexer, init_token("=", TOKEN_OPT));
  }
  case ':': return lexer_advance_with(lexer, init_token(":", TOKEN_OPT));
  case '+': return lexer_advance_with(lexer, init_token("+", TOKEN_OPT));
  case '-': return lexer_advance_with(lexer, init_token("-", TOKEN_OPT));
  case ',': return lexer_advance_with(lexer, init_token(",", TOKEN_SEP));
  case ';': return lexer_advance_with(lexer, init_token(";", TOKEN_SEP));
  case '(': return lexer_advance_with(lexer, init_token("(", TOKEN_SEP));
  case ')': return lexer_advance_with(lexer, init_token(")", TOKEN_SEP));
  case '{': return lexer_advance_with(lexer, init_token("{", TOKEN_SEP));
  case '}': return lexer_advance_with(lexer, init_token("}", TOKEN_SEP));
  default: 
    printf("lexer.c: unexpected token '%c'\n", lexer->c);
    exit(1);
  }
}
