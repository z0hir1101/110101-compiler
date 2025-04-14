#include "include/parser.h"
#include <stdlib.h>

parser_T* init_parser(lexer_T* lexer)
{
  parser_T* parser = malloc(sizeof(parser_T));
  parser->lexer = lexer;
  parser->token = lexer_next_token(lexer);

  return parser;
}

token_T* parser_eat(parser_T* parser, int type)
{
  parser->token = lexer_next_token(parser->lexer);
  if (parser->token->type != type) {
    printf("parser.c [parser_eat]: unexpected token %d\n", type);
    exit(1);
  }
  return parser->token;
}

token_T* parser_advance(parser_T* parser)
{
  parser->token = lexer_next_token(parser->lexer);
  return parser->token;
}

node_T* parser_parse(parser_T* parser)
{
  int type = parser->token->type;
  switch(type) {
  case TOKEN_KEYW_TYPE: return parse_var_declr(parser);
  case TOKEN_KEYW_RETURN: return parse_func_call(parser);
  default:
    printf("parser.c [parser_parse]: unexpected token %d\n", type);
    exit(1);
  }
}

node_T* parse_var_declr(parser_T* parser)
{
  node_T* node_var = init_node(NODE_VARIABLE_DEF, parser->token);

  token_T* token_idnt = parser_eat(parser, TOKEN_ID);
  parser_eat(parser, TOKEN_OPRT_EQUALS);
  token_T* token_litr = parser_eat(parser, TOKEN_LITERAL_INT);
  parser_eat(parser, TOKEN_PUNC_SEMI); 

  push_node(node_var, init_node(NODE_IDENTIFIRE, token_idnt)); 
  push_node(node_var, init_node(NODE_LITERAL, token_litr)); 
  
  return node_var;
}

node_T* parse_func_call(parser_T* parser)
{
  node_T* node_func = init_node(NODE_FUNCTION_CALL, parser->token);

  parser_eat(parser, TOKEN_PUNC_LPAREN);
  parser_advance(parser);

  node_T* node_args = init_node(NODE_ARGUMENTS, NULL);
  push_node(node_args, parse_exprasion(parser));
  parser_eat(parser, TOKEN_PUNC_SEMI);

  push_node(node_func, node_args); 
  
  return node_func;
}

node_T* parse_exprasion(parser_T* parser)
{
  token_T* token = parser->token;
  parser_advance(parser);

  if (token->type == TOKEN_LITERAL_INT)
    return init_node(NODE_LITERAL, token);
  if (token->type == TOKEN_ID)
    return init_node(NODE_IDENTIFIRE, token);
  if (token->type == TOKEN_OPRT_ARITH) {
    node_T* oprt = init_node(NODE_OPERATOR, token);
    push_node(oprt, parse_exprasion(parser));
    push_node(oprt, parse_exprasion(parser));
    return oprt;
  }
  printf("parser.c [parser_expr]: unexpected token %d\n", token->type);
  exit(1);
}

