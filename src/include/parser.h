#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "AST_node.h"
typedef struct PARSER_STRUCT {
  lexer_T* lexer;
  token_T* token;
} parser_T;

parser_T* init_parser(lexer_T* lexer);
token_T* parser_advance_with(parser_T* parser, int type);
token_T* parser_advance(parser_T* parser);

node_T* parser_parse(parser_T* parser);
node_T* parse_var_declr(parser_T* parser);
node_T* parse_func_call(parser_T* parser);
#endif
