#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMO 50

typedef struct {
  int id;
  char nome[MAXIMO];
  char email[MAXIMO];
} Row;

Row *create_row() {
  Row *row = malloc(sizeof(Row));
  return row;
}

void print_db() { printf("db > "); }

Row *rows[50];

int main() {

  char *linha = NULL;
  size_t *tamanho = malloc(sizeof(size_t));
  int quantidade_linhas = 0;

  while (1) {

    print_db();
    getline(&linha, tamanho, stdin);

    char *comando = strtok(linha, "(");
    char *argumentos = strtok(NULL, "(");

    if (strcmp(comando, "insert ") == 0) {

      int len_argumentos = strlen(argumentos);
      argumentos[len_argumentos - 2] = '\0';

      char *nome = strtok(argumentos, ",");
      char *email = strtok(NULL, ",");

      Row *row = create_row();
      row->id = quantidade_linhas + 1;
      strcpy(row->nome, nome);
      strcpy(row->email, email);

      rows[quantidade_linhas] = row;

      quantidade_linhas++;
    }

    if (strcmp(linha, "select\n") == 0) {
      printf("Dados da tabela:\n");

      for (int i = 0; i < quantidade_linhas; i++) {
        Row *row = rows[i];
        printf("%s %s\n", row->nome, row->email);
      }
    }
  }

  return 0;
}
