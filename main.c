#include <string.h>
#include "playlist.h"


int main(int argc, char *argv[]){
  printf("INICIANDO TRABALHO ED - ARVORE B+\n");
  int t = 2;
	printf("Informe o valor de t: ");
	scanf("%d", &t);
	TABM *arvore = Inicializa();
  char *arquivo;
  printf("Informe o nome do arquivo: ");
  scanf("%s", arquivo);
  arvore = LerArquivo(arvore, arquivo);	
  int escolha = 1;

  while(escolha){
    setbuf(stdin, NULL);
    printf("\n-------------------------------MENU-----------------------------\n");
    printf("\n1 - Imprimir arvore\n");
    printf("\n2 - Imprimir playlist completa\n");
    printf("\n3 - Remover album\n");
    printf("\n4 - Buscar discografia do artista\n");
    printf("\n5 - Buscar Album\n");
    printf("\n6 - Remover um artista e sua discografia\n");
    printf("\n7 - Editar album\n");
    printf("\n8 - Liberar Arvore\n");
    printf("\nQualquer outro numero para sair\n\n");
    printf("-----------------------------------------------------------------\n");

    printf("\nEscolha uma opção: ");
    scanf(" %d", &escolha);
    printf("\n");

    if(escolha== 1 ){
      printf("\nIMPRIMINDO ARVORE B+\n\n");
      Imprime(arvore, 0);
    }

    else if(escolha== 2){
      printf("\nIMPRIMINDO PLAYLIST COMPLETA\n\n");
      ImprimeDados(arvore, 0);
    }

    else if(escolha== 3){
      setbuf(stdin, NULL);
      char chave[200];
      printf("\nDigite o nome da chave que voce quer remover: ");
      scanf("%[^\n]", chave);
      printf("\nREMOVENDO CHAVE: %s\n",chave);
      remover(arvore, chave, t);      
    }
    else if(escolha== 4){
      char cantor[100];
      setbuf(stdin, NULL);
      printf("Digite o cantor: ");
      scanf("%[^\n]s", cantor);
      printf("\n");
      BuscaDiscografia(arvore, cantor);      
    }
    else if(escolha==5 ){
      char chave[200];
      printf("Informe a chave: ");
      setbuf(stdin, NULL);
      scanf("%[^\n]s", chave);
      TFolha *dado;
      dado = BuscaDado(arvore, chave);
    }
    else if(escolha== 6){
      char cantor[100];
      setbuf(stdin, NULL);
      printf("Digite o cantor: ");
      scanf("%[^\n]s", cantor);
      printf("\n");
      arvore = RemoverDiscografia(arvore, cantor,t); 
    }
    else if(escolha== 7){
      char chave[200];
      printf("Informe a chave: ");
      setbuf(stdin, NULL);
      scanf("%[^\n]s", chave);
      EditarDado(arvore, chave);      
    }

    else if(escolha==8 ){
      arvore = Libera(arvore);
    }
  
  } 
return 0;
}