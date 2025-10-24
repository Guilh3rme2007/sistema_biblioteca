#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>
#include <time.h>

#define MAX_LIVROS 100
#define MAX_AUTOR_NOME 50
#define MAX_LIVRO_TITULO 200
#define MAX_GENERO 20
#define MAX_CODIGO 10
#define FILENAME "Biblioteca.dat"

typedef struct {
  char nome_autor[MAX_AUTOR_NOME];
  char nome_livro[MAX_LIVRO_TITULO];
  char genero_livro[MAX_GENERO];
  char codigo_livro[MAX_CODIGO];
} Livros;

Livros agenda[MAX_LIVROS];

int numLivros = 0;

void limparbuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void carregarLivro() {
  FILE *file = fopen(FILENAME, "rb");
  if (file == NULL) {
    printf("\nSistema não encontrado\n");
    printf("Abrindo novo sistema\n");
    return;
  }
  numLivros = fread(agenda, sizeof(Livros), MAX_LIVROS, file);
  fclose(file);

  printf("Carregando a biblioteca ...\n");
}

void salvarLivros() {
  FILE *file = fopen(FILENAME, "wb");
  if (file == NULL) {
    printf("\nErro ao salvar arquivo\n");
    return;
  }
  fwrite(agenda, sizeof(Livros), numLivros, file);
  fclose(file);
  printf("\nBiblioteca salva com sucesso\n");
}

void gerarRegistroLivro(char *codigoDestino) {
  int numcodigo;
  int unico;
  int i;
  do {
    unico = 1;
    numcodigo = 100000 + (rand() % 900000);
    sprintf(codigoDestino, "%d", numcodigo);
    for (i = 0; i < numLivros; i++) {
      if (strcmp(agenda[i].codigo_livro, codigoDestino) == 0) {
        unico = 0;
        break;
      }
    }

  } while (!unico);
}

void adicionarLivros() {
  if (numLivros >= MAX_LIVROS) {
    printf("Quantidade total de livros atingida\n");
    return;
  }

  printf("Digite o nome do autor: ");
  scanf("%49[^\n]", agenda[numLivros].nome_autor);
  limparbuffer();

  printf("Digite o nome do livro: ");
  scanf("%199[^\n]", agenda[numLivros].nome_livro);
  limparbuffer();

  printf("Digite o genero do livro: ");
  scanf("%19[^\n]", agenda[numLivros].genero_livro);
  limparbuffer();

  gerarRegistroLivro(agenda[numLivros].codigo_livro);

  printf("\n=====Novo Livro=====\n");
  printf(" Autor: %s\n", agenda[numLivros].nome_autor);
  printf(" Título: %s\n", agenda[numLivros].nome_livro);
  printf(" Genero: %s\n", agenda[numLivros].genero_livro);
  printf(" Codigo: %s\n", agenda[numLivros].codigo_livro);
  numLivros++;
}

void buscarLivros() {
  char titulobusca[MAX_LIVRO_TITULO];
  char codigoBusca[MAX_CODIGO];
  int encotrados = 0;
  int tipoBusca, i;
  if (numLivros == 0) {
    printf("\nNenhum livro na biblioteca\n");
    return;
  }
  printf("\n");
  printf("=====Tipo de Busca=====\n");
  printf(" 1 - Titulo\n");
  printf(" 2 - Codigo\n");
  printf("=======================\n");
  scanf("%d", &tipoBusca);
  limparbuffer();
  switch (tipoBusca) {
  case 1:
    printf("\n");
    printf("Digite o titulo do livro: ");
    scanf("%199[^\n]", titulobusca);
    limparbuffer();
    printf("\nBuscando por %s... \n", titulobusca);
    for (i = 0; i < numLivros; i++) {
      if (strstr(agenda[i].nome_livro, titulobusca) != NULL) {
        printf("\n");
        printf("=====Livro encontrado=====\n");
        printf(" Titulo: %s\n", agenda[i].nome_livro);
        printf(" Autor: %s\n", agenda[i].nome_autor);
        printf(" Genero: %s\n", agenda[i].genero_livro);
        printf(" Codigo: %s\n", agenda[i].codigo_livro);
        printf("==========================\n");
        encotrados++;
      }
    }
    if (encotrados == 0) {
      printf("Nenhum livro encontrado com o titulo %s\n", titulobusca);
      return;
    }
    break;
  case 2:
    printf("\n");
    printf("Digite o codigo do livro: ");
    scanf("%9[^\n]", codigoBusca);
    limparbuffer();
    printf("\nBuscando por %s ...\n",codigoBusca);
    for ( i = 0; i < numLivros; i++) {
      if (strstr(agenda[i].codigo_livro, codigoBusca) != NULL) {
        printf("\n");
        printf("=====Livro encontrado=====\n");
        printf(" Titulo: %s\n", agenda[i].nome_livro);
        printf(" Autor: %s\n", agenda[i].nome_autor);
        printf(" Genero: %s\n", agenda[i].genero_livro);
        printf(" Codigo: %s\n", agenda[i].codigo_livro);
        printf("==========================\n");
        encotrados++;
      }
      
    }
    if (encotrados == 0) {
      printf("Nenhum livro encontrado com o codigo %s\n", codigoBusca);
      return;
    }
    
    break;
  default:
    printf("Valor não encontrado");
    break;
  }
}

void listarLivros() {
  int tipo, i;
  int listados = 0;
  char autorBusca[MAX_AUTOR_NOME];
  char generoBusca[MAX_GENERO];
  if (numLivros == 0) {
    printf("\n");
    printf("Biblioteca vazia\n");
    return;
  }
  if (numLivros >= 1) {
    printf("\n");
    printf("A biblioteca tem %d livros\n", numLivros);
    printf("\n=====Tipo de lista=====\n");
    printf(" 1 - Todos os livros\n");
    printf(" 2 - Por autor\n");
    printf(" 3 - Por genero\n");
    printf("=========================\n");
    scanf("%d", &tipo);
    limparbuffer();
    switch (tipo) {
    case 1:
      printf("\n=====Livros salvos=====\n");
      for (i = 0; i < numLivros; i++) {
        printf(" Autor: %s\n", agenda[i].nome_autor);
        printf(" Titulo: %s\n", agenda[i].nome_livro);
        printf(" Genero: %s\n", agenda[i].genero_livro);
        printf(" Codigo: %s\n", agenda[i].codigo_livro);
        printf("=========================\n");
        listados++;
      }
      break;
    case 2:
      printf("\nDigite o nome do autor: ");
      scanf("%49[^\n]", &autorBusca);
      limparbuffer();
      printf("=====Livros de %s=====\n", autorBusca);
      for (i = 0; i < numLivros; i++) {
        if (_stricmp(agenda[i].nome_autor, autorBusca) == 0) {
          printf(" Titulo: %s\n", agenda[i].nome_livro);
          printf(" Genero: %s\n", agenda[i].genero_livro);
          printf(" Codigo: %s\n", agenda[i].codigo_livro);
          printf("======================\n");
          listados++;
        }
      }
      if (listados == 0) {
        printf("\n");
        printf("Nenhum livro de %s encontrado\n", autorBusca);
      }
      break;
    case 3:
      printf("\n");
      printf("Digite o genero: ");
      scanf("%19[^\n]", &generoBusca);
      limparbuffer();
      printf("\n=====Livros do genero %s=====\n", generoBusca);
      for (i = 0; i < numLivros; i++) {
        if (_stricmp(agenda[i].genero_livro, generoBusca) == 0) {
          printf(" Autor: %s\n", agenda[i].nome_autor);
          printf(" Titulo: %s\n", agenda[i].nome_livro);
          printf(" Codigo: %s\n", agenda[i].codigo_livro);
          printf("=======================\n");
          listados++;
        }
      }
      if (listados == 0) {
        printf("\n");
        printf("Nenhum livro do genero %s encontrado\n", generoBusca);
      }
      break;
    default:
      printf("\nValor inválido\n");
      break;
    }
  }
}

void removerLivros() {
  char codigoBusca[MAX_CODIGO];
  int i, j;
  int indiceParaRemover = -1;
  char confirmacao;

  if (numLivros == 0) {
    printf("\nNenhum livro salvo\n");
    return;
  }
  printf("\nDigite o codigo do livro: ");
  scanf("%9[^\n]", codigoBusca);
  limparbuffer();
  for ( i = 0; i < numLivros; i++) {
    if (strcmp(agenda[i].codigo_livro, codigoBusca) == 0) {
      indiceParaRemover = i;
      break;
    }
  }
  if(indiceParaRemover == -1) {
    printf("\nNenhum livro encontrado com ocodigo %s\n", codigoBusca);
    return;
  }

  printf("\n=====Livro encontrado=====\n");
  printf(" Titulo: %s\n", agenda[indiceParaRemover].nome_livro);
  printf(" Autor: %s\n", agenda[indiceParaRemover].nome_autor);
  printf(" Genero: %s\n", agenda[indiceParaRemover].genero_livro);
  printf(" Codigo: %s\n", agenda[indiceParaRemover].codigo_livro);
  printf("==========================\n");
  printf("\nTem certeza que deseja remover esse contato? [S/N]");
  scanf("%c", &confirmacao);
  limparbuffer();
  if (tolower(confirmacao) == 's' || tolower(confirmacao) == 'S') {
    for(j= indiceParaRemover; j< numLivros - 1; j++) {
      agenda[j] = agenda[j + 1];
    }
    numLivros--;
    printf("\nContato removido\n");
  } else {
    printf("\nRemoção cancelada\n");
  }
  
}

int main(void) {
  SetConsoleOutputCP(65001);
  SetConsoleCP(65001);
  srand(time(NULL));
  carregarLivro();
  int opcao;
  do {
    printf("\n");
    printf("=====Biblioteca=====\n");
    printf(" 1 - Adicionar livros\n");
    printf(" 2 - Buscar livos\n");
    printf(" 3 - Listar livros\n");
    printf(" 4 - Remover livros\n");
    printf(" 0 - Salvar e Sair\n");
    printf("====================\n");
    scanf("%d", &opcao);
    limparbuffer();
    switch (opcao) {
    case 1:
      adicionarLivros();
      break;
    case 2:
      buscarLivros();
      break;
    case 3:
      listarLivros();
      break;
    case 4:
      removerLivros();
      break;
    case 0:
      salvarLivros();
      printf("\n");
      printf("Saindo do sistema ...\n");
      break;
    default:
      printf("\nValor inválido\n");
      break;
    }
  } while (opcao != 0);
  return 0;
}