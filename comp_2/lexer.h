#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKEN_SIZE 100

typedef enum{
  TOK_ID,
  TOK_NUM,
  TOK_OP,
  TOK_PAREN,
  TOK_SEMI,
  TOK_EOF,
  TOK_UNK,
} TokenType;


typedef struct {
  TokenType type;
  char value[MAX_TOKEN_SIZE];
} Token;

void init_lexer(const char* source);
Token get_next_token();

void print_token(Token token);
#endif
