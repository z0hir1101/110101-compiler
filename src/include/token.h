#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT {
  char* value;
  enum {
    TOKEN_IDT,
    TOKEN_KEY,
    TOKEN_SEP,
    TOKEN_OPT,
    TOKEN_LIT,
    TOKEN_CMT,
    TOKEN_WSP,
    TOKEN_EOF,
  } type;
} token_T;

token_T* init_token(char* value, int type);
#endif
