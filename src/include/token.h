#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT {
  char* value;
  enum {
    TOKEN_EOF,          //0
    TOKEN_LITERAL_STR,  //1
    TOKEN_LITERAL_INT,  //2
    TOKEN_ID,           //3
    TOKEN_KEYW_TYPE,    //4
    TOKEN_KEYW_STAT,    //5
    TOKEN_KEYW_LOOP,    //6
    TOKEN_KEYW_RETURN,  //7
    TOKEN_PUNC_SEMI,    //8
    TOKEN_PUNC_LPAREN,  //9
    TOKEN_PUNC_RPAREN, //10
    TOKEN_PUNC_LBRACE, //11
    TOKEN_PUNC_RBRACE, //12
    TOKEN_PUNC_COMMA,  //13
    TOKEN_OPRT_ARITH,  //14
    TOKEN_OPRT_LAMBDA, //15
    TOKEN_OPRT_EQUALS, //16
    TOKEN_OPRT_COMPAR, //17
  } type;
} token_T;

token_T* init_token(char* value, int type);
#endif
