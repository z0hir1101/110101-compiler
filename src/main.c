#include "include/parser.h"
#include "include/io.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("main.c: please specify input file\n");
    return 1;
  }
  char* src = read_file(argv[1]); 

  /*
  lexer_T* lexer = init_lexer(src);
  parser_T* parser = init_parser(lexer);
  node_T* root = init_node(NODE_ROOT, NULL);
   
  while (parser->token->type != TOKEN_EOF) {
    push(root, parser_parse(parser));
    parser_advance(parser);
  }
  */

  lexer_T* lexer = init_lexer(src);
  token_T* token;

  while ((token = lexer_next_token(lexer))->type != TOKEN_EOF)
    printf(" value\t%s \t\ttype\t%d\n",token->value, token->type);  

  free(src);
  return 0;
}
