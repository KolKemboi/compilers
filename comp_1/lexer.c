#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_SIZE 100

// NOTE: Token types to be recognized
typedef enum {
  TOKEN_IDENTIFIER,
  TOKEN_NUMBER,
  TOKEN_OPERATOR,
  TOKEN_PAREN,
  TOKEN_SEMICOLON,
  TOKEN_EOF,
  TOKEN_UNKNOWN
} TokenType;

typedef struct {
  TokenType type;
  char value[MAX_TOKEN_SIZE];
} Token;

// NOTE: Global pointer to the input text
const char *input;
int pos = 0;

// NOTE: Look at the current character without advancing
char peek() { return input[pos]; }

// NOTE: Advance to the next character and return the prev one
char advance() { return input[pos++]; }

// NOTE: skip over any whitespaces
void skip_whitespace() {
  while (isspace(peek())) {
    advance();
  }
}

// NOTE: actual tokenization part
Token get_next_token() {
  skip_whitespace();

  char current = peek();
  Token token;
  token.value[0] = '\0'; // Clear token value

  // NOTE: if end of file/input
  if (current == '\0') {
    token.type = TOKEN_EOF;
    return token;
  }

  // NOTE: Identifier: starts with a letter, can contain digits
  if (isalpha(current)) {
    int i = 0;
    while (isalnum(peek())) {
      token.value[i++] = advance();
    }
    token.value[i] = '\0';
    token.type = TOKEN_IDENTIFIER;
    return token;
  }

  // NOTE: Numbers: only digits (no floating poin yet)
  if (isdigit(current)) {
    int i = 0;
    while (isdigit(peek())) {
      token.value[i++] = advance();
    }
    token.value[i] = '\0';
    token.type = TOKEN_NUMBER;
    return token;
  }

  // NOTE: Operator
  if (strchr("+-*/=", current)) {
  token.type = TOKEN_OPERATOR;
    token.value[0] = advance();
    token.value[1] = '\0';
    return token;
  }

  // NOTE: Paranthesis
  if (current == '(' || current == ')') {
  token.type = TOKEN_PAREN;
    token.value[0] = advance();
    token.value[1] = '\0';
    return token;
  }

  // NOTE: if token is semicolon
  if (current == ';'){
    token.type = TOKEN_SEMICOLON;
    token.value[0] = advance();
    token.value[1] = '\0';
    return token;
  }

  // NOTE: Unknown token or unsurported token
  token.type = TOKEN_UNKNOWN;
  token.value[0] = advance();
  token.value[1] = '\0';
  return token;
}

// NOTE: printing out the token
void print_token(Token token){
  const char* type_name[] = {
    "IDENTIFIER",
    "NUMBER",
    "OPERATOR",
    "PAREN",
    "SEMICOLON",
    "EOF",
    "UNKNOWN"
  };
    printf("Token(Type: %s, Value '%s')\n", type_name[token.type], token.value);
}

// NOTE: file reading
char *read_file(const char *filename) {
  FILE *f = fopen(filename, "r");
  if (!f) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }

  fseek(f, 0, SEEK_END);
  long length = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *buffer = (char *)malloc(length + 1);
  if (!buffer) {
    perror("could not allocate memory");
    exit(EXIT_FAILURE);
  }
  fread(buffer, 1, length, f);
  buffer[length] = '\0';
  fclose(f);
  return buffer;
}

int main(int argc, char *argv[]) {
  // NOTE: ensures file is loaded
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file.sf>\n", argv[0]);
    return 1;
  }

  // NOTE: checks if the file has the right extension
  const char *filename = argv[1];
  const char *ext = strrchr(filename, '.');
  if (!ext || strcmp(ext, ".sf") != 0) {
    fprintf(stderr, "Error: improper file extension\n");
    return 1;
  }

  // NOTE: reads the input file contents
  input = read_file(filename);

  // NOTE: reading through my tokens
  Token token;
  do{
    token = get_next_token();
    print_token(token);
  }while (token.type != TOKEN_EOF);

  free((void *)input);

  return 0;
}
