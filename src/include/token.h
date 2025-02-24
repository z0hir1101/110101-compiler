#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT {
  char* value;
  enum {
    TOKEN_EOF,
    TOKEN_LITERAL_STR,
    TOKEN_LITERAL_INT,
    TOKEN_ID,
    TOKEN_KEYW_TYPE,
    TOKEN_KEYW_STAT,
    TOKEN_KEYW_LOOP,
    TOKEN_KEYW_RETURN,
    TOKEN_PUNC_SEMI,
    TOKEN_PUNC_LPAREN,
    TOKEN_PUNC_RPAREN,
    TOKEN_PUNC_LBRACE,
    TOKEN_PUNC_RBRACE,
    TOKEN_PUNC_COMMA,
    TOKEN_OPRT_ARITH,
    TOKEN_OPRT_LAMBDA,
    TOKEN_OPRT_EQUALS,
    TOKEN_OPRT_COMPAR,
  } type;
} token_T;

token_T* init_token(char* value, int type);
#endif
