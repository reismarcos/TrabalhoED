#ifndef _PLAYLISTH_
#define _PLAYLISTH_



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct folha{
  char cantor[40];
  int ano;
  int nfaixas;
  int tempo;
  char album[60];
}TFolha;

typedef struct arvorebm{
  int nchaves, folha;
  char **chave;
  TFolha **dados;
  struct arvorebm **filho, *prox;
}TABM;

TABM *Cria(int t);
TABM *Libera(TABM *a);
void Imprime(TABM *a, int andar);
TABM *Inicializa();
TABM *Divisao(TABM *x, int i, TABM* y, int t);
TABM *Insere_Nao_Completo(TABM *arv, char *chave, TFolha *dados, int t);
TABM *Insere(TABM *T, char *chave, TFolha *dados, int t);
TABM* remover(TABM* arv, char *chave, int t);
TABM* retira(TABM* arv, char *chave, int t);
TABM *Busca(TABM* arv, char *ch);
TFolha *BuscaDado(TABM *arv, char *chave);
void BuscaDiscografia(TABM* a, char *cantor);
TABM* RemoverDiscografia(TABM* a, char *cantor,int t);
void EditarDado(TABM *arv, char *chave);
void ImprimeDados(TABM *a, int andar);
void eFolha(TABM *arv);


//funcoes do arquivo.c
TABM *LerArquivo(TABM *arv, char *arquivo);
TABM *RemoveDadosIntermediarios(TABM *arv);
void BuscaDados(char *cantor, TABM* a);
#endif