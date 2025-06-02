#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* filename){
  FILE* f = fopen(filename, "r");
  if(!f) {
    perror("could not open file");
    exit(EXIT_FAILURE);
  }

  fseek(f, 0, SEEK_END);
  long len = ftell(f);
  fseek(f, 0, SEEK_SET);

  char* buff = malloc(len + 1);
  if(!buff) {
    perror("Memory allocation failure");
    exit(EXIT_FAILURE);
  }

  fread(buff, 1, len, f);
  buff[len] = '\0';
  fclose(f);
  return buff;


}

int main(int args, char *argv[]) {
  if (args != 2) {
    fprintf(stderr, "usage: %s <file.sf>\n", argv[0]);
    return EXIT_FAILURE;
  }

  char* source = read_file(argv[1]);
  init_lexer(source);

  Token tok;
  do {
  tok = get_next_token();
    print_token(tok);
    }while (tok.type != TOK_EOF);

  free(source);
  return EXIT_SUCCESS;
}
