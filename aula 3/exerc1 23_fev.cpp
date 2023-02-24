/* Crie um algoritmo que atribua o resultado de uma soma de inteiros
a um ponteiro e em seguida efetue a leitura desse ponteiro*/

#include<stdio.h>
#include<locale.h>

int x=5+5;
int *p;

int main(){
	p=&x;
	printf("Var= %d\n", *p);
	
	return 0;
}

