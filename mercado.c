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

int menor ( int esse , int aquele ) {
  if (esse < aquele ) {return esse;}
  return aquele ;
}

void exibe_lista(Dados* lista ) {

        fprintf(stdout, "Lista:\n\n");

        fprintf(stdout, "SIGLA  QTDE  VALOR\n");

        while (lista != NULL ) {
          fprintf(stdout, "%s %5d %6.2f\n", 
                  lista->Sigla,
                  lista->Quantidade, 
                  lista->Valor);
          lista = lista->proximo; 
        }
        fprintf(stdout, "------------------\n ");
  
        printf("Pressione uma tecla para continuar.");
        getchar();
}

void verificarOfertas( Dados* ofertasCompra , Dados* ofertasVenda ) {

  Dados* qualCompra = ofertasCompra ;

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
          printf( "Comprou %d ações a %f valor\n" , qtdeAcomprar , media);
          
        }
      }   
      essaVenda = essaVenda->proximo;
     }
    qualCompra = qualCompra->proximo; 
  }
  
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

  // PETR4, VALE5, ITSA4, USIM5, LAME3.
  // carregando a lista de ofertas de compras do arquivo
  Compras = leArquivo( Compras , "compras.dat");
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
  exibe_lista(Vendas); 

  
  return 0;
}