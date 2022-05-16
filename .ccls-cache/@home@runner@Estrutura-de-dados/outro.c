#include <stdio.h>

// passagem de parametro por valor
int incremento (int altura)
{
  printf ("digite a altura\n");
  scanf("%d", %altura);
  return altura;
}

// passagem de parametro por referencia
void increporreferencia (int *base)
{
   *base = 100;
  printf("o valor eh %d\n", *n);
}

int main() {
  // n e valor2 sao variaveis locais
    int area, base, altura;
    incremento(altura);
    increporreferencia(base);
    printf ("o valor %d foi incrementado para ", n);
  //chamando função com passagem de parametro por valor  
  incremento(n, base, altura);
    //chamando função com passagem de parametro por referencia
  // a principio conceitualmente é passada a referencia ou endereço da variavel de origem na chamada da função
    increporreferencia(&n);
    printf("o valor por referencia eh %d\n", n);
    return 0;
}  