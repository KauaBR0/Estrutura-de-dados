#include <stdio.h>
// essa variavel é global
int valorglobal = 50;

// passagem de parametro por valor
void incremento (int valor)
{
  valor = valor + 10;
  printf ("%d\n", valor);
}

// passagem de parametro por referencia
void increporreferencia (int *n)
{
   *n = 100;
  printf("o valor eh %d\n", *n);
}

int main() {
  // n e valor2 sao variaveis locais
    int n;
    int valor2;
    printf("digite o valor \n");
    scanf("%d", &n);
    printf ("o valor %d foi incrementado para ", n);
  //chamando função com passagem de parametro por valor  
  incremento(n);
    //chamando função com passagem de parametro por referencia
  // a principio conceitualmente é passada a referencia ou endereço da variavel de origem na chamada da função
    increporreferencia(&n);
    printf("o valor por referencia eh %d\n", n);
    printf ("o valor global eh %d\n", valorglobal);
    return 0;
}  