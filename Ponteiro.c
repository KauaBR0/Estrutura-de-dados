// Permitindo varias entradas com valores aleatorios

#include <stdio.h>
#include <stdlib.h>

struct tipo
{
	int info;
	struct tipo *prox;

};

typedef struct tipo Paciente;

// cria o inicio da lista
Paciente *inicio=NULL;

Paciente* inserir_lista(Paciente* l, int i)
{
	Paciente* novo= malloc(sizeof(Paciente));
	novo->info = i;
	novo->prox = l;
	return novo;
}

void consultar_lista(Paciente* inicio)
{
	Paciente *referencia;
	for(referencia= inicio;referencia!= NULL; referencia=referencia->prox){
		printf("%d\n", referencia->info);
	}
}

Paciente *retiraInicio(Paciente *LISTA)
{
	if(LISTA->prox == NULL){
		printf("Lista ja esta vazia\n");
		return NULL;
	}else{
		Paciente *tmp = LISTA->prox;
		LISTA->prox = tmp->prox;
		return tmp;
	}
}

Paciente *retiraFim(Paciente *LISTA)
{
	if(LISTA->prox == NULL){
		printf("Lista ja vazia\n\n");
		return NULL;
	}else{
		Paciente *ultimo = LISTA->prox,
		*penultimo = LISTA;
		while(ultimo->prox != NULL){
			penultimo = ultimo;
			ultimo = ultimo->prox;
		}
		penultimo->prox = NULL;
		return LISTA;  
	}
}

Paciente *BuscaDado(int dado, Paciente *ptr)
{
  while (ptr !=NULL) {
    if (ptr->info == dado){
		return (ptr);
	}else{
		ptr = ptr->prox;
	} 
  }
  return NULL;
}

Paciente *RemoveDado(int dado, Paciente *ptr)
{
	Paciente* busca; 
	Paciente* anterior;
	anterior = NULL;
	busca = ptr;
	while (busca != NULL) {
		if (busca->info == dado) {
			if (anterior != NULL){
				anterior->prox = busca -> prox;
				return ptr;
			}else{
				ptr = busca-> prox;
				return ptr;
			}
			free(busca);
			break;	
		}
		anterior = busca;
		busca = busca->prox;
	}
  return NULL;
}


int main() {
	int opcao=0,elemento=0,i=0;
    int dado, entradas;
	Paciente *lista;
	lista = NULL;
    printf("quantas entradas deseja fazer?\n");
    scanf("%d", &entradas);
    while(i<entradas){
        printf("Digite o elemento a ser inserido na lista: ");
        scanf("%d", &dado);
        i++;
        elemento = dado;
        lista = inserir_lista(lista,elemento);
    }
	printf("\nantes da exclusao.....: \n");
	consultar_lista(lista);
	while (opcao!=8)
	{
	printf("\ndigite a opcao:\n1 -excluir no fim\n2 - excluir no inicio\n3 - excluir um elemento pesquisado\n4 - buscar um elemento na lista");
	scanf("%d",&opcao);
	if(opcao==1){
		printf("\ndepois da exclusao no fim.....: \n");
		lista= retiraFim(lista);
		consultar_lista(lista);
	}else if(opcao==2){
		printf("\ndepois da exclusao no inicio.....: \n");
		lista= retiraInicio(lista);
		consultar_lista(lista);
	}else if(opcao==3){
		printf("\ndigite o elemento a ser excluido.....: \n");
		scanf("%d",&elemento);
		lista = RemoveDado(elemento,lista);
		if(lista!=NULL){
			printf("\ndepois da exclusao pelo elemento pesquisado.....: \n");
			consultar_lista(lista);
		}else{
			printf("\nnao foi possivel remover, elemento nao encontrado\n");
		}
	}else if(opcao==4){
		printf("\ndigite o elemento a ser pesquisado.....: \n");
		scanf("%d",&elemento);
		lista = BuscaDado(elemento,lista);
		if(lista==NULL){
			printf("\nelemento nao encontrado\n");
		}else{
			printf("contem o elemento pesquisado ");
		}
	}else
	{
		if (opcao !=8)
		printf("\nopcao invalida\n");
	
		else 
		printf("saindo..\n");
	}
	}
    return 0;
}