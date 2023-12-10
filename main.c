#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXIMO 50

void print_db() { printf("db > "); }

typedef struct {
  int id;
  char nome[MAXIMO];
  char email[MAXIMO];
} Row;


Row *create_row() {
  Row *row = malloc(sizeof(Row));
  return row;
}

Row *rows[50];

void salvar_arquivo() {

    int file = open("db", O_RDWR, O_CREAT, S_IWUSR, S_IRUSR);
    lseek(file, 0, SEEK_SET);

    write(file, rows[0], sizeof(Row));

    exit(EXIT_SUCCESS);
}

void ler_arquivo() {

    int file = open("db", O_RDWR, O_CREAT, S_IWUSR, S_IRUSR);
    lseek(file, 0, SEEK_SET);

    Row* row = create_row();
    read(file, row, sizeof(Row));

    rows[0] = row;

}

int main() {

  char *linha = NULL;
  size_t *tamanho = malloc(sizeof(size_t));
  int quantidade_linhas = 0;

  ler_arquivo();

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

      for (int i = 0; i < 50; i++) {
        Row *row = rows[i];
        printf("%s %s\n", row->nome, row->email);
      }
    }

    if(strcmp(linha, ".exit\n") == 0) {
        salvar_arquivo();
    }
  }

  return 0;
}
