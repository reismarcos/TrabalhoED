#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

TABM* LerArquivo(TABM *a, char *arquivo){
  FILE *file;
  file = fopen(arquivo, "r");
  int t = 2;
  char linha[256];
  char *token;

  while (fgets(linha, sizeof(linha), file)){
        TFolha *dados = (TFolha *) malloc(sizeof(TFolha));
        token = strtok(linha, "/");
        strcpy(dados->cantor, token);
        token = strtok(NULL, "/");
        char chave[200];
        strcpy(chave, dados->cantor);
        strcat(chave, token);
        dados->ano = atoi(token);
        token = strtok(NULL, "/");
        dados->nfaixas = atoi(token);
        token = strtok(NULL, "/");
        dados->tempo = atoi(token);
        token = strtok(NULL, "/");
        strcpy(dados->album, token);
        a = Insere(a, chave, dados, t);
      }

      return a;
  }
