#include "include/parser.h"
#include <stdlib.h>

parser_T* init_parser(lexer_T* lexer)
{
  parser_T* parser = malloc(sizeof(struct PARSER_STRUCT));
  parser->lexer = lexer;
  parser->token = lexer_next_token(lexer);

  return parser;
}

token_T* parser_advance(parser_T* parser, int type)
{
  parser->token = lexer_next_token(parser->lexer);
  if (parser->token->type != type) {
    printf("parser.c: unexpected token %d\n", type);
    exit(1);
  }
  return parser->token;
}

node_T* parser_parse(parser_T* parser)
{
  int type = parser->token->type;
  switch(type) {
  case TOKEN_KEYW_TYPE: return parse_var_declr(parser);
  case TOKEN_KEYW_RETURN: return parse_func_call(parser);
  default:
    printf("parser.c: unexpected token %d\n", type);
    exit(1);
  }
}

node_T* parse_var_declr(parser_T* parser)
{
  node_T* node_var = init_node(NODE_VARIABLE_DEF, parser->token);
  node_T* node_idnt = init_node(NODE_IDENT, parser_advance(parser, TOKEN_IDT));
  parser_advance(parser, TOKEN_OPRT_EQUALS);
  node_T* node_litr = init_node(NODE_LITERAL, parser_advance(parser, TOKEN_LIT));
  parser_advance(parser, TOKEN_PUNC_SEMI); 

  node_var->children = init_list(sizeof(token_T));
  push_item(node_var->children, node_idnt); 
  push_item(node_var->children, node_litr); 
  
  return node_var;
}

node_T* parse_func_call(parser_T* parser)
{
  node_T* node_func = init_node(NODE_FUNCTION_CALL, parser->token);
  parser_advance(parser, TOKEN_PUNC_LPAREN);
  node_T* node_args = init_node(NODE_ARGUMENTS, NULL);
  node_args->children = init_list(sizeof(token_T));
  push_item(node_args->children, parse_expr(parser);
  parser_advance(parser, TOKEN_PUNC_SEMI);

  node_func->children = init_list(sizeof(token_T));
  push_item(node_func->children, node_args); 
  
  return node_func;
}

node_T* parse_expr(parser_T* parser)
{
  node_T* node_oprt = parser_advance(parser);
  type = node_oprt->value->type;

  if (type == TOKEN_LIT)
    return node_oprt;
  if (type == TOKEN_OPRT_ARITH) {
    node_oprt->children = init_list(sizeof(token_T));
    push_item(node_oprt->children, parse_expr(parser);
    return node_oprt;
  }
  printf("parser.c: unexpected token %d\n", type);
  exit(1);
}

