#include <stdio.h>

void fatorial(void) {
  int fat, n;
printf("Insira um valor : ");
scanf("%d", &n);

for(fat = 1; n > 1; n = n - 1)
fat = fat * n;

printf("\nFatorial calculado: %d", fat);

}

int main() {

  fatorial();
  
return 0;
}