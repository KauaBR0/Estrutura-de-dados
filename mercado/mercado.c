#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct lista {
        char* Sigla;
        int Quantidade;
        float Valor;
        struct lista* proximo;
} Dados;

// esta função insere um valor no começo da lista, deslocando a cabeça anterior 
// para a segunda posição
// colocando no topo da pilha
Dados* insere_dados(Dados* lista, char* Sigla, int Quantidade, float Valor) {

        Dados* novo;

        novo = (Dados* )malloc(sizeof(Dados));
        novo->Sigla = (char *)malloc(strlen(Sigla)+1);
        strncpy(novo->Sigla, Sigla, strlen(Sigla)+1);
        novo->Quantidade = Quantidade;
        novo->Valor = Valor;
        novo->proximo = lista ;

        return novo;
}

// como funciona a função buscar_sigla
// a função retorna um apontador para a oferta que contem a sigla 
// fornecida como parametro 
// recebe dois parametros : Uma lista na qual será realizada a busca
//                          Uma sigla a ser buscada
// exemplo : buscar_sigla(Compras, "PETR4")
// retorna A ÙLTIMA oferta de compra feita para a sigla PETR4
// outro exemplo:
//    buscar_sigla(Vendas, "LAME3")
// retorna a ÙLTIMA oferta de venda feita para a sigla LAME3 
// último exemplo:
//    buscar_sigla(Ultimaoferta, "PETR4")
// retorna a ÙLTIMA oferta feita aceita para a sigla PETR4


Dados* buscar_sigla(Dados* lista, char* SiglaBuscada ) {
  if (lista == NULL) return NULL;
  int comparacao = strcmp(lista->Sigla,SiglaBuscada );
  if (comparacao == 0 ) return lista;
  return buscar_sigla( lista->proximo , SiglaBuscada);
}


int menor ( int esse , int aquele ) {
  if (esse < aquele ) {return esse;}
  return aquele ;
}

void exibe_lista(Dados* lista ) {

        printf("\nSIGLA  QTDE  VALOR\n");

        while (lista != NULL ) {
            printf("\n%s %5d %6.2f\n", 
                  lista->Sigla,
                  lista->Quantidade, 
                  lista->Valor);
          lista = lista->proximo; 
        }
        fprintf(stdout, "------------------\n ");

        printf("Pressione Enter\n\n");
        getchar();
}

Dados*  verificarOfertas( Dados* ofertasCompra , Dados* ofertasVenda ) {
//Apresentar o último preço da operação realizada (cotação ) por papel

  Dados* qualCompra = ofertasCompra ;
  Dados* listaTemporaria = NULL ;
  
  while ( qualCompra != NULL ) {
    Dados* essaVenda = ofertasVenda;
    
    printf( "Procurando ofertas de venda para %s \n", (qualCompra->Sigla));
    printf("Comprador disposto a comprar %d e pagar %.2f\n",
         qualCompra->Quantidade, 
         qualCompra->Valor);

     while ( essaVenda != NULL ) {
       printf( "Comparando compra de %s com venda de %s\n",
         qualCompra->Sigla,     essaVenda->Sigla );       // testar se é o mesmo papel 
       int resultado = strcmp( essaVenda->Sigla , qualCompra->Sigla );
        if ( resultado == 0 
           && qualCompra->Quantidade > 0 
           && essaVenda->Quantidade > 0   ) { // casou, as siglas são iguais
        if (qualCompra->Valor >= essaVenda->Valor ) {
          float media = (qualCompra->Valor + essaVenda->Valor ) / 2;
          int qtdeAcomprar = menor( qualCompra->Quantidade, essaVenda->Quantidade);
          qualCompra->Quantidade -= qtdeAcomprar;
          essaVenda->Quantidade -= qtdeAcomprar;
          printf( "Comprou %d ações a %.2f valor\n" , qtdeAcomprar , media);
          Dados* onde = buscar_sigla( listaTemporaria , essaVenda->Sigla);
          // se onde for igual a NULL significa que não encontrou 
          // aquela sigla antes na lista, vamos inserí-la
          if ( onde == NULL ) { 
            listaTemporaria = insere_dados(
              listaTemporaria,
              essaVenda->Sigla,
              qtdeAcomprar,
              media
              );
            } else { // já tava na lista, vamos so atualizar os dados
              // mudamos apenas a quantidade e o valor da oferta aceita 
               onde->Quantidade = qtdeAcomprar;
               onde->Valor = media;
               // observe que a variável onde->proximo não foi modificada
            }
          
        }
      }   
      essaVenda = essaVenda->proximo;
     }
    qualCompra = qualCompra->proximo; 
  }
  return (listaTemporaria) ;
  
}

Dados* leArquivo( Dados* lista , char* nomeArquivo ) {
  FILE* filePointer ; 
  filePointer = fopen(nomeArquivo, "r+") ;
  char wSigla[5];
  int wqtde;
  float wvalor;
  
  
  while ( fscanf( filePointer,"%s %d %f", wSigla, &wqtde , &wvalor ) !=-1) {    
    lista = insere_dados( lista , wSigla, wqtde, wvalor);
  }
  fclose(filePointer);
  
  return lista ;
}

int main(void) {

  Dados* Compras = NULL ; 
  Dados* Vendas = NULL ;
  Dados* Ultimaoferta = NULL;

    int opcao;
  
    do {
        //system("clear"); 
        printf("\n Cadastro de Titulos\n\n");
        printf("Escolha uma opcao: \n\n");
        printf("1 - Insere Titulos\n");
        printf("2 - Exibe Titulos\n");
        printf("3 - Verificar Ofertas\n");
        printf("4 - Listar ultimas ofertas realizadas\n");
        printf("5 - Sair\n\n");
        scanf("%d", &opcao);

        switch(opcao) {
                case 1:
                  Compras = leArquivo( NULL , "compras.dat");
                  Vendas = leArquivo( NULL , "vendas.dat");
                  break;

                case 2:
                  system("clear");
                  printf("\nLISTA DE COMPRAS\n");
                  exibe_lista(Compras);
                  printf("\nLISTA DE VENDAS\n");
                  exibe_lista(Vendas);
                  break;

                case 3:
                  system("clear");
                  Ultimaoferta = verificarOfertas( Compras , Vendas );
                  break;
                case 4:
                  system("clear");
                  printf("As ultimas operacoes realizadas foram: \n");
                  exibe_lista(Ultimaoferta);
                  break;
          
                case 5:
                  exit(0);
                  break;

                default:
                  printf("Digite uma opcao valida!\n");
                  sleep(1);
                  break;
        }

        //getchar(); 
    } while (opcao != 5);
  // PETR4, VALE5, ITSA4, USIM5, LAME3.
  // carregando a lista de ofertas de compras do arquivo
  /*Compras = leArquivo( Compras , "compras.dat");
  // carregando a lista de ofertas de venda do arquivo
  Vendas = leArquivo( Vendas , "vendas.dat"); 
  
  printf("Ofertas de compras\n");
  exibe_lista(Compras); 

  printf("Ofertas de vendas\n");
  exibe_lista(Vendas); 

  // vai fazer as transações de compra/venda
  verificarOfertas( Compras, Vendas );

  
  printf("Como ficaram as Ofertas de compras\n");
  exibe_lista(Compras); 

  printf("Como ficaram as Ofertas de vendas\n");
  exibe_lista(Vendas); */

    return 0;
}