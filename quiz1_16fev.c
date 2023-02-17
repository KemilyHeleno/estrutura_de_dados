/* 
Crie um algoritmo para efetuar o cadastro de livros com as informações:
	* Código
	* Título
	* Assunto
	* Número de páginas
	* Ano
	* Editora
Você deverá utilizar o recurso chamado struct ou registro
*/

#include <stdio.h>
#include <locale.h>



struct livros_livros {
int codigo;
	char titulo[50];
	int num_paginas;
	int ano;
	char editor[50];
};

struct livros_livros livro;

int main (void) {
	setlocale(LC_ALL,"");

	printf("Digite o código do livro: \n");
	scanf("%d", &livro.codigo);

	printf("Digite o titulo do livro: \n");
	scanf("%s", livro.titulo);

	printf("Digite o número de páginas: \n");
	scanf("%d", &livro.num_paginas);

	printf("Digite o ano em que o livro foi lançado: \n");
	scanf("%d", &livro.ano);

	printf("Digite o nome da editora do livro: \n");
	scanf("%s", livro.editor);

printf("\n\n----------------------------- Lendo dados da Struct -----------------------------\n\n");

printf("Código do livro: %d\n", livro.codigo);
printf("Título do livro: %s\n", livro.titulo);
printf("Número de páginas do livro: %d\n", livro.num_paginas);
printf("Ano em que o livro foi lançado: %d\n", livro.ano);
printf("Nome da editora do livro: %s\n", livro.editor);
}
