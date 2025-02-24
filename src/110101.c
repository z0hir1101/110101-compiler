#include "include/110101.h"
#include "include/parser.h"

void compile(char* src)
{
  lexer_T* lexer = init_lexer(src);
  parser_T* parser = init_parser(lexer);
  node_T* node_root = init_node(NODE_ROOT, NULL);
  node_root->children = init_list(sizeof(token_T));
   
  while (parser->token->type != TOKEN_EOF) {
    push_item(node_root->children, parser_parse(parser));
    parser_advance(parser);
  }


  /*
  lexer_T* lexer = init_lexer(src);
  token_T* token;

  while ((token = lexer_next_token(lexer))->type != TOKEN_EOF)
    printf(" value\t%s \t\ttype\t%d\n",token->value, token->type);  
  */
}
