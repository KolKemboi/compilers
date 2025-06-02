#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static const char* input;
static int pos = 0;

static char peek() {
  return input[pos];
}

static char advance() {
  return input[pos++];
}

static void skip_whitepace() {
  while (isspace(peek())) {
  advance();
  }
}

void init_lexer(const char* source){
  input = source;
  pos = 0;
}

Token get_next_token() {
  skip_whitepace();

  Token token;
  token.value[0] = '\0';
  char current = peek();

  if (current == '\0') {
  token.type = TOK_EOF;
    return token;
  }

  if (isalpha(current)) {
  int i = 0;
    while (isalnum(peek())) {
    token.value[i++] = advance();
    }
    token.value[i] = '\0';
    token.type = TOK_ID;
    return token;
  }

  if (isdigit(current)) {
  int i = 0;
    while (isdigit(peek())) {
    token.value[i++] = advance();
    }
    token.value[i] = '\0';
    token.type = TOK_NUM;
    return token;
  }

  if (strchr("+-*/=", current)) {
    token.type = TOK_OP;
    token.value[0] = advance();
    token.value[1] = '\0';
    return token;
  }

  if (current == '(' || current == ')') {
  token.type = TOK_PAREN;
    token.value[0] = advance();
    token.value[1] = '\0';
    return token;
  }

  if (current == ';') {
    token.type = TOK_SEMI;
    token.value[0] = advance();
    token.value[1] = '\0';
    return token;
  }

  token.type = TOK_UNK;
  token.value[0] = advance();
  token.value[1] = '\0';
  return token;
}


void print_token(Token token) {
  const char* type_name[] = {
    "ID",
    "NUM",
    "OP",
    "PAREN",
    "SEMI",
    "EOF",
    "UNK"
  };
  printf("Token %s, Value '%s'\n", type_name[token.type], token.value);
}











