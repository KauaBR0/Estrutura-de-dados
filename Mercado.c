#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>  //clrscr

#define BUFFER 64

/* Estrutura da lista declarada para armazenar nossos dados. */
typedef struct lista {
        char *Sigla;
        int Quantidade;
        float Valor;
        struct lista *proximo;
} Dados;


/* Prototipo das funcoes de manuseio dos dados. */
Dados *inicia_dados(char *Sigla, int Quantidade, float Valor);
Dados *insere_dados(Dados *dados, char *Sigla, int Quantidade, float Valor);
void exibe_dados(Dados *dados);
void busca_dados(Dados *dados, char *chave);
Dados *deleta_dados(Dados *dados);
int checa_vazio(Dados *dados);

/* Prototipo das funcoes do menu.*/
void insere(void);
void exibe(void);
void busca(void);
void deleta(void);

/* Inicializa a estrutura de dados. */
Dados *Compra = NULL;
Dados *venda = NULL;

/* Cria a nova lista apontando o proximo no para NULL. */
Dados *inicia_dados(char *Sigla, int Quantidade, float Valor) {

        Dados *novo;

        novo = (Dados *)malloc(sizeof(Dados));
        novo->Sigla = (char *)malloc(strlen(Sigla)+1);
        strncpy(novo->Sigla, Sigla, strlen(Sigla)+1);
        novo->Quantidade = Quantidade;
        novo->Valor = Valor;
        novo->proximo = NULL;

        return novo;
}

/* Como a lista nao esta mais vazia, apontamos o proximo no para lista anterior. */
Dados *insere_dados(Dados *dados, char *Sigla, int Quantidade, float Valor) {

        Dados *novo;

        novo = (Dados *)malloc(sizeof(Dados));
        novo->Sigla = (char *)malloc(strlen(Sigla)+1);
        strncpy(novo->Sigla, Sigla, strlen(Sigla)+1);
        novo->Quantidade = Quantidade;
        novo->Valor = Valor;
        novo->proximo = dados;

        return novo;
}

/* Percorre todos os campos da lista e imprime ate o ponteiro proximo chegar em NULL. */
void exibe_dados(Dados *dados) {

        fprintf(stdout, "Cadastro:\n\n");

        fprintf(stdout, "------------------------\n");

        for (; dados != NULL; dados = dados->proximo) {
                fprintf(stdout, "Sigla: %s\n", dados->Sigla);
                fprintf(stdout, "Quantidade: %d\n", dados->Quantidade);
                fprintf(stdout, "Valor: %.2f\n", dados->Valor);
                fprintf(stdout, "------------------------\n ");
        }
        printf("Pressione uma tecla para continuar.");
        getch();
}

/* Percorre cada ponta comparando o Sigla com a chave. */
void busca_dados(Dados *dados, char *chave) {

        int achou = 0;

        fprintf(stdout, "Cadastro:\n\n");
        for (; dados != NULL; dados = dados->proximo) {
                if (strcmp(chave, dados->Sigla) == 0) {

                        fprintf(stdout, "------------------------\n");
                        fprintf(stdout, "Sigla: %s\n", dados->Sigla);
                        fprintf(stdout, "Quantidade: %d\n", dados->Quantidade);
                        fprintf(stdout, "Valor: %.2f\n", dados->Valor);
                        fprintf(stdout, "------------------------\n");
                        achou++;
                }
        }

        if (achou == 0)
                fprintf(stdout, "Nenhum resultado encontrado.\nPressione uma tecla para continuar.\n");
        else
                fprintf(stdout, "Foram encontrados %d registros. \nPressione uma tecla para continuar.\n", achou);

        sleep(1);
        getch();
}

/* Deleta o ultimo registro inserido. */
Dados *deleta_dados(Dados *dados) {

        Dados *novo;

        novo = dados->proximo;

        free(dados->Sigla);
        free(dados);

        fprintf(stdout, "O ultimo registro inserido foi deletado com sucesso.\\n");
        sleep(1);

        return novo;
}

/* a pena checa se a lista e NULL ou nao. */
int checa_vazio(Dados *dados) {

        if (dados == NULL) {
                fprintf(stdout, "Lista vazia!\\n");
                sleep(1);
                return 1;
        } else
                return 0;
}

/* Obtem os dados necessarios para chamar as funcoes de manuseio de dados. */
void insere(void) {

        char *Sigla;
        int Quantidade;
        float Valor;


        Sigla = (char *)malloc(BUFFER);

        int opcao;
        printf("\n1 - Compra\n2 - Venda\n");
        scanf("%d", &opcao);

        fprintf(stdout, "\n\nDigite o Sigla: \n----> ");
        scanf("%s", Sigla);
        fprintf(stdout, "\n");

        fprintf(stdout, "Digite a Quantidade: \n----> ");
        scanf("%d", &Quantidade);
        fprintf(stdout, "\n");

        fprintf(stdout, "Digite o Valor: \n----> ");
        scanf("%f", &Valor);
        fprintf(stdout, "\n");

        if(opcao == 1){
                if (Compra == NULL) {
                        Compra = inicia_dados(Sigla, Quantidade, Valor);
                }else {
                        Compra = insere_dados(Compra, Sigla, Quantidade, Valor);
                }
        }
        if(opcao == 2){
                if (venda == NULL) {
                        venda = inicia_dados(Sigla, Quantidade, Valor);
                }else {
                        venda = insere_dados(venda, Sigla, Quantidade, Valor);
                }
        }
}

void exibe(void) {

        int opcao;
        printf("\n1 - Compra\n2 - Venda\n");
        scanf("%d", &opcao);

        if(opcao == 1){
                if (!checa_vazio(Compra)) {
                        exibe_dados(Compra);
                }
        }
        if(opcao == 2){
        if (!checa_vazio(venda)) {
                exibe_dados(venda);
        }
        }
}

void busca(void) {

        char *chave;

        int opcao;
        printf("\n1 - Compra\n2 - Venda\n");
        scanf("%d", &opcao);
        if(opcao == 1){
                if (!checa_vazio(Compra)) {

                        chave = (char *)malloc(BUFFER);

                        fprintf(stdout, "Digite a Sigla para buscar: \\n--> ");
                        scanf("%s", chave);

                        busca_dados(Compra, chave);
                        getch();
                }
        }
        if(opcao == 2){
                if (!checa_vazio(venda)) {

                        chave = (char *)malloc(BUFFER);

                        fprintf(stdout, "Digite a Sigla para buscar: \\n--> ");
                        scanf("%s", chave);

                        busca_dados(venda, chave);
                        getch(); 
                }
        }
}

void deleta(void) {

        int opcao;
        printf("\n1 - Compra\n2 - Venda\n");
        scanf("%d", &opcao);

        if(opcao == 1){
                if (!checa_vazio(Compra)) {
                        Compra = deleta_dados(Compra);
                }
        }
        if(opcao == 2){
                if (!checa_vazio(venda)) {
                        venda = deleta_dados(venda);
                }
        }
}

int main(void) {

        char escolha;

        do {
                system("cls"); 
                fprintf(stdout, "\n Cadastro de Titulos\n\n");
                fprintf(stdout, "Escolha uma opcao: \n\n");
                fprintf(stdout, "1 - Insere Titulos\n");
                fprintf(stdout, "2 - Exibe Titulos\n");
                fprintf(stdout, "3 - Busca Titulos\n");
                fprintf(stdout, "4 - Deleta Titulos\n");
                fprintf(stdout, "5 - Sair\n\n");

                scanf("%c", &escolha);

                switch(escolha) {
                        case '1':
                                insere();
                                break;

                        case '2':
                                exibe();
                                break;

                        case '3':
                                busca();
                                break;

                        case '4':
                                deleta();
                                break;

                        case '5':
                                exit(0);
                                break;

                        default:
                                fprintf(stderr,"Digite uma opcao valida!\\n");
                                sleep(1);
                                break;
                }

                //getchar(); 
        }

        while (escolha > 0); /* Loop Compra. */

        return 0;
}
