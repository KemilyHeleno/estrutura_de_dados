/* Implemente um programa que leia o nome, a idade e o telefone de cinco pessoas e armazene os dados em um vetor de estrutura*/

#include <stdio.h>
#include <locale.h>
#define pessoa 5

struct cadastro {
	char nome[50];
	int idade;
	int telefone;
};

struct cadastro cadastro[pessoa];

void leitura (int pess[pessoa]){
	for (int i = 1; i <= pessoa; i++){
		printf("\nDigite o nome da pessoa %d: ", i);
		scanf("%s", &cadastro[i].nome);
		
		printf("\nDigite a idade da pessoa %d: ", i);
		scanf("%d", &cadastro[i].idade);
		
		printf("\nDigite o telefone da pessoa %d:", i);
		scanf("%d", &cadastro[i].telefone);
	}
}

void mostra_valor (int pois[pessoa]){
	for (int i = 1; i <= pessoa; i++){
		printf("\n\n\nNome da pessoa %d: %s\n", i, cadastro[i].nome);
		printf("Idade da pessoa %d: %d\n", i, cadastro[i].idade);
		printf("Telefone da pessoa %d: %d\n\n\n", i, cadastro[i].telefone);
	}
}

main (){
	int cad[pessoa];
	leitura(cad);
	mostra_valor(cad);
}
