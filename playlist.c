#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

TABM *Inicializa(){
  return NULL;
}

TABM *Cria(int t){
  TABM* novo = (TABM*)malloc(sizeof(TABM));
  novo->nchaves = 0;
  novo->chave =(char**)malloc(((t*2)-1)*sizeof(char*)); //mudei de sizeof(char**) para sizeof(char*)
  int i;
  for(i=0;i<t*2-1;i++) novo->chave[i] = (char *) malloc((64)*sizeof(char));
  novo->folha=1;
  novo->filho = (TABM**)malloc(sizeof(TABM*)*(t*2));
  //int i;
  for(i=0; i<(t*2); i++) novo->filho[i] = NULL;
  novo->prox = NULL;
  novo->dados = (TFolha**)malloc(sizeof(TFolha*)*((2*t)-1));
  for(i=0;i<(t*2)-1;i++) novo->dados[i] = (TFolha *) malloc(sizeof(TFolha));
  return novo;
}

TABM *Libera(TABM *a){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nchaves; i++) Libera(a->filho[i]);
    }
    free(a->chave);
    free(a->dados);
    free(a->filho);
    free(a);
    return NULL;
  }
}


void Imprime(TABM *a, int andar){
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      Imprime(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      printf("%s\n", a->chave[i]);
    }
    Imprime(a->filho[i],andar+1);
  }
}

void ImprimeDados(TABM *a, int andar){
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      ImprimeDados(a->filho[i],andar+1);
      if(a->folha){
        printf("Cantor: %s\n", a->dados[i]->cantor);
        printf("Ano: %d\n", a->dados[i]->ano);
        printf("Numero de faixas: %d\n", a->dados[i]->nfaixas);
        printf("Tempo de duração do album: %d\n", a->dados[i]->tempo);
        printf("Album: %s\n", a->dados[i]->album);
      }
    }
    ImprimeDados(a->filho[i],andar+1);
  }
}

TFolha *BuscaDado(TABM* arv, char *ch){
  if(!arv){
    return NULL;
  }
  int i = 0;
  while(i < arv->nchaves && strcasecmp(arv->chave[i], ch)<0) i++;
  if((i < arv->nchaves) && strcasecmp(arv->chave[i], ch)==0){
    if(arv->folha){
      printf("Chave: %s \n", arv->chave[i]);
      printf("Nome do album: %s", arv->dados[i]->album);
      printf("Nome do cantor: %s\n", arv->dados[i]->cantor);
      printf("Numero de faixas: %d\n", arv->dados[i]->nfaixas);
      printf("Ano do album: %d\n", arv->dados[i]->ano);
      printf("Tempo de duraçao:: %d\n", arv->dados[i]->tempo);
      return arv->dados[i];
    }
    return BuscaDado(arv->filho[i+1], ch);
  }
  return BuscaDado(arv->filho[i], ch);
}

TABM *Busca(TABM* arv, char *ch){
  if(!arv){
    return arv;
  }
  int i = 0;
  while(i < arv->nchaves && strcasecmp(arv->chave[i], ch)<0) i++;
  if((i < arv->nchaves) && strcasecmp(arv->chave[i], ch)==0){
    if(arv->folha){
      return arv;
    }
    return Busca(arv->filho[i+1], ch);
  }
  return Busca(arv->filho[i], ch);
}

void EditarDado(TABM *arv, char *chave){
  printf("Dados atuais:\n");
  TFolha *dados = BuscaDado(arv, chave);
  printf("\n");
  if(!dados) return;  
  char nomealbum[100];
  printf("Digite as novas informações\n");
  printf("Nome do Album: ");
  scanf("%s", nomealbum);
  strcpy(dados->album, nomealbum);
  printf("Numero de faixas: ");
  scanf("%d", &dados->nfaixas);
  printf("Tempo de duração do album: ");
  scanf("%d", &dados->tempo);
  printf("\n");
}

void eFolha(TABM *arv){
  TABM *teste = arv;
  while(!teste->folha) teste = teste->filho[0];
  while(teste != NULL){
    if(teste->folha) printf("folha\n");
    int i;
    //for(i=0;i<p->nchaves;i++) printf("%s\n", p->chave[i]);
    teste = teste->prox;
  }
}

TABM *Divisao(TABM *x, int i, TABM* y, int t){
  TABM *z = Cria(t);
  if(y->folha){
    TABM *proxAux = y->prox;
    z->nchaves= t;
    z->folha = 1;
    int j;
    for(j=0 ; j<t; j++) {
      strcpy(z->chave[j], y->chave[j+t-1]);
      z->dados[j] = y->dados[j+t-1];
     
    }
    y->nchaves = t - 1;
    for(j=x->nchaves; j>=i; j--) x->filho[j+1] = x->filho[j]; 
    x->filho[i] = z;
    for(j=x->nchaves; j>=i; j--){
      strcpy(x->chave[j], x->chave[j-1]);
      x->dados[j] = x->dados[j-1];
    }
    strcpy(x->chave[i-1], y->chave[t-1]);
    x->dados[i-1] = y->dados[t-1];
    x->nchaves++;
    if((y->folha)&&(z->folha)) y->prox = z;
    if(proxAux) z->prox = proxAux;
    return x;
  }
  z->nchaves= t-1;
  z->folha = 0;
  int j;

  for(j=0;j<t-1;j++){
    strcpy(z->chave[j], y->chave[j+t]);
    z->dados[j] = y->dados[j+t];  
  }

  if(!y->folha){
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }

  y->nchaves = t - 1;
  for(j=x->nchaves; j>=i; j--) x->filho[j+1] = x->filho[j];
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--){
    strcpy(x->chave[j], x->chave[j-1]);
    x->dados[j] = x->dados[j-1];
  }
  strcpy(x->chave[i-1], y->chave[t-1]);
  x->dados[i-1] = y->dados[t-1];
  x->nchaves++;
  return x;
}

TABM *Insere_Nao_Completo(TABM *arv, char *chave, TFolha *dados, int t){
  int i = arv->nchaves-1;
  if(arv->folha){
    while((i>=0) && (strcmp(chave, arv->chave[i]) < 0)) { 
      strcpy(arv->chave[i+1], arv->chave[i]);
      arv->dados[i+1] = arv->dados[i];
      i--;
    }
    strcpy(arv->chave[i+1], chave);
    arv->dados[i+1] = dados;
    arv->nchaves++;
    return arv;
  }
  while((i>=0) && (strcmp(chave, arv->chave[i]) < 0)) i--; 
  i++;
  if(arv->filho[i]->nchaves == ((2*t)-1)){
    arv = Divisao(arv, (i+1), arv->filho[i], t); 
    if(strcmp(chave, arv->chave[i]) > 0) i++;
  }
  arv->filho[i] = Insere_Nao_Completo(arv->filho[i], chave, dados, t);
  return arv;
}


TABM *Insere(TABM *T, char *chave, TFolha *dados, int t){
  if(Busca(T,chave)){
    return T;
  } 
  if(!T){

    T=Cria(t);
    strcpy(T->chave[0], chave);
    T->dados[0]->ano = dados->ano;
    T->dados[0]->nfaixas = dados->nfaixas;
    T->dados[0]->tempo = dados->tempo;
    strcpy(T->dados[0]->cantor, dados->cantor);
    strcpy(T->dados[0]->album, dados->album);

    T->nchaves=1;
    return T;
  }
  if(T->nchaves == (2*t)-1){
    TABM *S = Cria(t);
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = T;
    S = Divisao(S,1,T,t);
    S = Insere_Nao_Completo(S,chave, dados, t);
    return S;
  }
  T = Insere_Nao_Completo(T,chave, dados, t);

  return T;
}

void BuscaDiscografia(TABM* a, char *cantor){
  if(!a) return;
  if(a->filho[0]){
    BuscaDiscografia(a->filho[0], cantor);
  } 
  else if(a->folha){
    printf("Discografia do cantor %s:\n\n",cantor);
    int i;
    int acabou = 0;
    int contador = 0;
    while(!acabou){
      for(i=0; i<(a->nchaves); i++){
        if(strcmp(a->dados[i]->cantor, cantor)==0){
          contador += 1;
          printf("%d) %s\n",contador ,  a->dados[i]->album);
        }
      }
      
      if(a->prox == NULL){
        acabou = 1;
      }
      else{
        a = a->prox;
      }
      
    }
   
  }
}


TABM* RemoverDiscografia(TABM* a, char *cantor,int t){
  if(!a) return a;
  if(a->filho[0]){
    RemoverDiscografia(a->filho[0], cantor, t);
  } 
  else if(a->folha){
    printf("Removendo discografia do cantor %s:\n\n",cantor);
    int i;
    int acabou = 0;
    while(!acabou){
      for(i=0; i<(a->nchaves); i++){
        if(strcmp(a->dados[i]->cantor, cantor)==0){
          printf("Removendo album: %s\n", a->dados[i]->album);
          a = remover(a, a->chave[i], t);
        }
      }
      
      if(a->prox == NULL){
        acabou = 1;
        return a;
      }
      else{
        a = a->prox;
      }
      
    }
    return a;
   
  }
  return a;
}


TABM* remover(TABM *a, char *chave, int t){
	if(!a) return a;
	int i;
	for(i=0; i < a->nchaves && (strcasecmp(a->chave[i], chave) < 0); i++);
	if(i < a->nchaves && strcasecmp(a->chave[i], chave)== 0){
		if(a->folha){
			int j;
			for(j=i; j < a->nchaves-1; j++){
				strcpy(a->chave[j] , a->chave[j+1]);
			}
			a->nchaves--;
			return a;
		}
		i++;
	}
	TABM *y = a->filho[i], *z = NULL;
	if(y->nchaves == t-1){
		if((i < a->nchaves) && (a->filho[i+1]->nchaves >= t)){
			z = a->filho[i+1];
			if(!y->folha){
				strcpy(y->chave[t-1] , a->chave[i]);//strcopy
				strcpy(a->chave[i] , z->chave[0]);//strcopy
			}
			else{
				strcpy(y->chave[t-1] ,z->chave[0]);//strcopy
				strcpy(a->chave[i] , z->chave[1]);//strcopy
			}
			y->nchaves++;
			int j;
			for(j=0; j < z->nchaves-1; j++){
				strcpy(z->chave[j] , z->chave[j+1]);//strcopy
			}
			y->filho[y->nchaves] = z->filho[0];
			for(j=0; j < z->nchaves; j++)
				z->filho[j] = z->filho[j+1];
			z->nchaves--;
			a->filho[i] = remover(a->filho[i], chave, t);
			return a;
		}
		if((i > 0) && (!z) && (a->filho[i-1]->nchaves >= t)){
			z = a->filho[i-1];
			int j;
			for(j = y->nchaves; j > 0; j--){
				strcpy(y->chave[j] , y->chave[j-1]);//strcopy
			}
			for(j = y->nchaves+1; j > 0; j--)
				y->filho[j] = y->filho[j-1];
			if(!y->folha){
				strcpy(y->chave[0] , a->chave[i-1]);//strcopy
				strcpy(a->chave[i-1] , z->chave[z->nchaves-1]);//strcopy
				y->filho[0] = z->filho[z->nchaves];
			}
			else{
				strcpy(y->chave[0] , z->chave[z->nchaves-1]);//strcopy
				strcpy(a->chave[i-1] , z->chave[z->nchaves-1]);//strcopy
			}
			y->nchaves++;
			z->nchaves--;
			a->filho[i] = remover(a->filho[i], chave, t);
			return a;
		}
		if(!z){
			if(i < a->nchaves && a->filho[i+1]->nchaves == t-1){
				z = a->filho[i+1];
				if(!y->folha){
					strcpy(y->chave[t-1] , a->chave[i]);//strcopy
					y->nchaves++;
				}
				int nchavesAtual = y->nchaves;
				int j;
				for(j = 0; j < t-1; j++){
					strcpy(y->chave[j+nchavesAtual] , z->chave[j]);//strcopy
					y->nchaves++;
				}
				if(!y->folha){
					for(j = 0; j < t; j++)
						y->filho[j+t] = z->filho[j];
				}
				else{
					y->prox = z->prox;
				}
				for(j = i; j < a->nchaves-1; j++){
					strcpy(a->chave[j] , a->chave[j+1]);//strcopy
					a->filho[j+1] = a->filho[j+2];
				}
				a->nchaves--;
				a = remover(a, chave, t);
				return a;
			}
			if((i > 0) && (a->filho[i-1]->nchaves == t-1)){
				z = a->filho[i-1];
				if(!z->folha){
					if(i == a->nchaves)
						z->chave[t-1] = a->chave[i-1];
					else
						z->chave[t-1] = a->chave[i];
					z->nchaves++;
				}
				int nchavesAtual = z->nchaves;
				int j;
				for(j = 0; j < t-1; j++){
					z->chave[j+nchavesAtual] = y->chave[j];
					z->nchaves++;
				}
				if(!z->folha){
					for(j = 0; j < t; j++)
						z->filho[j+t] = y->filho[j];
				}
				else{
					z->prox = y->prox;
				}
				a->nchaves--;
				a->filho[i-1] = z;
				a = remover(a, chave, t);
				return a;
			}
		}
	}
	a->filho[i] = remover(a->filho[i], chave, t);
	return a;
}


TABM* retira(TABM *a, char *chave, int t){
	if(!a || !Busca(a, chave))return a;
	return remover(a, chave, t);
}

/*
TABM* retira(TABM* arv, char *chave, int t){
  if(!arv || !Busca(arv, chave)) return arv;
  return remover(arv, chave, t);
}
*/