#include "include/lexer.h"
#include "include/macros.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

lexer_T* init_lexer(char* src)
{
  lexer_T* lexer = malloc(sizeof(struct LEXER_STRUCT));
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

token_T* lexer_parse(lexer_T* lexer)
{
  char* value = calloc(1, sizeof(char));

  while (isdigit(lexer->c) || isalpha(lexer->c) || lexer->c == '"') {
    value = realloc(value, (strlen(value) + 2) * sizeof(char));
    strcat(value, (char[]){lexer->c, 0});
    lexer_advance(lexer);
  }

  if (!strcmp(value, "char") ||
      !strcmp(value, "int") ||
      !strcmp(value, "float"))
    return init_token(value, TOKEN_KEYW_TYPE);
  if (!strcmp(value, "if") ||
      !strcmp(value, "if-else") ||
      !strcmp(value, "else"))
    return init_token(value, TOKEN_KEYW_STAT);
  if (!strcmp(value, "while") ||
      !strcmp(value, "for"))
    return init_token(value, TOKEN_KEYW_LOOP);
  if (!strcmp(value, "return"))
    return init_token(value, TOKEN_KEYW_RETURN);
  if (isdigit(*value))
    return init_token(value, TOKEN_LIT);
  return init_token(value, TOKEN_IDT);
}

char lexer_peek(lexer_T* lexer, int offset)
{
  return lexer->src[MIN(lexer->i + offset, lexer->src_size)];
}

void lexer_skip_whitespace(lexer_T* lexer)
{
  while (lexer->c == ' ' || lexer->c == '\t' || lexer->c == '\n')
    lexer_advance(lexer);
}

token_T* lexer_next_token(lexer_T* lexer)
{
  lexer_skip_whitespace(lexer);

  if (lexer->c == EOF || lexer->c == '\0')
    return init_token(0, TOKEN_EOF);

  if (isalpha(lexer->c) || isdigit(lexer->c) || lexer->c == '"')
    return lexer_parse(lexer);

  switch (lexer->c) {
  case '=':
    if (lexer_peek(lexer, 1) == '>') {
      lexer_advance(lexer);
      return lexer_advance_with(lexer, init_token("=>", TOKEN_OPRT_LAMBDA));
    }
  case ':': return lexer_advance_with(lexer, init_token(":", TOKEN_OPRT_EQUALS));
  case '+': return lexer_advance_with(lexer, init_token("+", TOKEN_OPRT_ARITH));
  case '-': return lexer_advance_with(lexer, init_token("-", TOKEN_OPRT_ARITH));
  case ',': return lexer_advance_with(lexer, init_token(",", TOKEN_PUNC_COMMA));
  case ';': return lexer_advance_with(lexer, init_token(";", TOKEN_PUNC_SEMI));
  case '(': return lexer_advance_with(lexer, init_token("(", TOKEN_PUNC_LPAREN));
  case ')': return lexer_advance_with(lexer, init_token(")", TOKEN_PUNC_RPAREN));
  case '{': return lexer_advance_with(lexer, init_token("{", TOKEN_PUNC_LBRACE));
  case '}': return lexer_advance_with(lexer, init_token("}", TOKEN_PUNC_RBRACE));
  default: 
    printf("lexer.c: unexpected token '%d'\n", lexer->c);
    exit(1);
  }
}
