/* 
Crie um algoritmo para efetuar o cadastro de livros com as informa��es:
	* C�digo
	* T�tulo
	* Assunto
	* N�mero de p�ginas
	* Ano
	* Editora
Voc� dever� utilizar o recurso chamado struct ou registro
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

	printf("Digite o c�digo do livro: \n");
	scanf("%d", &livro.codigo);

	printf("Digite o titulo do livro: \n");
	scanf("%s", livro.titulo);

	printf("Digite o n�mero de p�ginas: \n");
	scanf("%d", &livro.num_paginas);

	printf("Digite o ano em que o livro foi lan�ado: \n");
	scanf("%d", &livro.ano);

	printf("Digite o nome da editora do livro: \n");
	scanf("%s", livro.editor);

printf("\n\n----------------------------- Lendo dados da Struct -----------------------------\n\n");

printf("C�digo do livro: %d\n", livro.codigo);
printf("T�tulo do livro: %s\n", livro.titulo);
printf("N�mero de p�ginas do livro: %d\n", livro.num_paginas);
printf("Ano em que o livro foi lan�ado: %d\n", livro.ano);
printf("Nome da editora do livro: %s\n", livro.editor);
}
