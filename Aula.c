#include <stdio.h>

typedef struct 
{
	int idade;
	float peso;
	float altura;
	
} paciente ;

int main ()
{
	 paciente p;
	
	printf("digite a idade");
	scanf ("%d", &p.idade);
	printf("digite o peso");
	scanf ("%f", &p.peso);
	
	printf("%d\n", p.idade);
	printf("%f\n", p.peso);
	return 0;
	
}