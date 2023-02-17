#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.c>
/*Trabalho de FPD 
Professoras Ariane Scarelli e Katia Zambon
Das alunas: 
			Kemily Rafaelly Heleno               nº 18
			Giullia Fernanda Barbosa Ferreira    nº 12
			Emily Bigal Faveri                   nº 09
    Projeto: Consultório de Odontologia
    Nome fictício : Clínica Smile
*/
// estrutura para cadastro de paciente e profissional
struct cadastro
{
	int aleatorio;
	char nome [40];
	int codigo;
	struct struct2
	{
		int dia;
		int mes;
		int ano;
	}nasc;
	char e_mail[25];
	struct struct3
	{
		int ddd;
		int prefixo;
		int numero;
	}telefone;
	char classificacao;
	char clareamento[3];
	char cirurgia[3];
	char aparelho[3];
	char implantes[3];
	char tratamentos[3];
	char excluido;
}agenda;

FILE *comp;
//---------------------------------------------------------------------------------------
//coloca um máximo de números
int getInt(int limite)
{
	char resp[limite+1];
	int aux = 0;
	char letra;
	fflush(stdin);
	while((letra = getch()) != '\r')
	{
		if((letra == 8 || aux > limite) && aux != 0)
		{
			aux--;
			resp[aux] = ' ';
			printf("\b \b");
		}
		if(isdigit(letra) && aux != limite)
		{
			resp[aux] = letra;
			aux++;
			printf("%c", letra);
		}
		fflush(stdin);
		if(letra == 27)
			return -1;
	}
	
	return atoi(resp);
}
//---------------------------------------------------------------------------------------
//função verifica se um código digitado já foi gravado no arquivo
int checar_chave_primaria()
{
	int aux;
	int F; //função verifica se um código digitado já foi gravado no arquivo
	do{
		rewind(comp); //reposiciona o ponteiro no início do arquivo
		F=0;
		textcolor(0); // cor de letra
		textbackground(11);// cor da tela de fundo
		gotoxy(51,9);aux = getInt(4);
		if (aux==0) 
		{
			break; //Condição de encerramento			
		}
		while( (fread( &agenda,sizeof(agenda),1,comp) )== 1 && agenda.codigo != aux );
		
		if(agenda.codigo == aux && agenda.excluido== 'n') 
		{
			F=1;
			gotoxy(25,15);printf("C%cdigo ja cadastrado! Enter para redigitar.",162); //162=ó
			getch();
			gotoxy(51,9);printf("          "); //apaga o código da tela
			gotoxy(25,15);printf("                                           ");
		}
	
	}while(F==1);
	return aux;
}
//---------------------------------------------------------------------------------------
//verifica se  o e-mail possui o caractere @
void valida_email()
{
	if(strchr(agenda.e_mail,'@')==NULL)
	{
		gotoxy(28,12);printf("                        ");
		gotoxy(25,15);printf("e_mail invalido digite novamente");
		gotoxy(28,12);gets(agenda.e_mail);
		gotoxy(25,15);printf("                                ");
		valida_email();
	}	
}
//---------------------------------------------------------------------------------------
//verifica se o telefone é valido
int valida_cel()
{
	textcolor(0); // cor de letra
	textbackground(11); // cor de fundo
	while(agenda.telefone.ddd<00 || agenda.telefone.ddd>99) 
	{
		gotoxy(25,15); printf("telefone invalido, digite novamente...");
		gotoxy(39,10); printf("  "); 
		gotoxy(26,10); printf("  ");
		gotoxy(32,10); printf("             ");
		gotoxy(25,15);printf("                                        ");
		gotoxy(40,10); agenda.telefone.ddd = getInt(2);
		gotoxy(26,10); agenda.telefone.prefixo = getInt(5);
		gotoxy(32,10); agenda.telefone.numero = getInt(4);
	}
	while (agenda.telefone.prefixo<00000 ||agenda.telefone.prefixo>99999)
	{
		gotoxy(25,15); printf("telefone invalido, digite novamente...");
		gotoxy(39,10); printf("  "); 
		gotoxy(26,10); printf("  ");
		gotoxy(32,10); printf("             ");
		gotoxy(25,15);printf("                                        ");
		gotoxy(40,10); agenda.telefone.ddd = getInt(2);
		gotoxy(26,10); agenda.telefone.prefixo = getInt(5);
		gotoxy(32,10); agenda.telefone.numero = getInt(4);
	}
	while (agenda.telefone.numero<0000 ||agenda.telefone.numero>9999)
	{
		gotoxy(25,15); printf("telefone invalido, digite novamente...");
		gotoxy(40,10); printf("  "); 
		gotoxy(26,10); printf("  ");
		gotoxy(32,10); printf("             ");
		gotoxy(25,15);printf("                                        ");
		gotoxy(40,10); agenda.telefone.ddd = getInt(2);
		gotoxy(26,10); agenda.telefone.prefixo = getInt(5);
		gotoxy(32,10); agenda.telefone.numero = getInt(4);
	}
}
//---------------------------------------------------------------------------------------
//verifica se a data de nascimento é valida
int valida_nasc()
{
	textcolor(0); // cor de letra
	textbackground(11); // cor de fundo
	// verifica se a pessoa nasceu antes do ano atual
	while(agenda.nasc.ano>2019)
	{
		gotoxy(25,15); printf("Data invalida, digite novamente...");		
		gotoxy(38,11); printf("  ");
		gotoxy(41,11); printf("  ");
		gotoxy(44,11); printf("             ");
		gotoxy(38,11); agenda.nasc.dia = getInt(2);	
		gotoxy(25,15);printf("                                   ");
		gotoxy(41,11); agenda.nasc.mes = getInt(2);
		gotoxy(44,11); agenda.nasc.ano = getInt(4);
		valida_nasc();
	}
	// verifica se o mes de nascimento existe
	while (agenda.nasc.mes<=0||agenda.nasc.mes>12)
	{
		gotoxy(25,15); printf("Data invalida, digite novamente...");
		gotoxy(38,11); printf("  "); 
		gotoxy(41,11); printf("  ");
		gotoxy(44,11); printf("                ");
		gotoxy(38,11); agenda.nasc.dia = getInt(2);
		gotoxy(25,15);printf("                                   ");
		gotoxy(41,11); agenda.nasc.mes = getInt(2);
		gotoxy(44,11); agenda.nasc.ano = getInt(4);
		valida_nasc();
	}
	// verifica se os meses que possuem 31 dias será colocado um dia válido
	if(agenda.nasc.mes==1||agenda.nasc.mes==3||agenda.nasc.mes==5||agenda.nasc.mes==7||agenda.nasc.mes==8||agenda.nasc.mes==10||agenda.nasc.mes==12)
	{
		while(agenda.nasc.dia<01||agenda.nasc.dia>31)
		{
			gotoxy(25,15); printf("Data invalida, digite novamente...");
			gotoxy(38,11); printf("  "); 
			gotoxy(41,11); printf("  ");
			gotoxy(44,11); printf("                  ");
			gotoxy(38,11); agenda.nasc.dia = getInt(2);
			gotoxy(25,15);printf("                                   ");
			gotoxy(41,11); agenda.nasc.mes = getInt(2);
			gotoxy(44,11); agenda.nasc.ano = getInt(4);
			valida_nasc();
		}
	}
	// verifica se os meses que possuem 30 dias será colocado um dia válido
	if(agenda.nasc.mes==4||agenda.nasc.mes==6||agenda.nasc.mes==9||agenda.nasc.mes==11)
	{
		while(agenda.nasc.dia<01||agenda.nasc.dia>30)
		{
			gotoxy(25,15); printf("Data invalida, digite novamente...");
			gotoxy(38,11); printf("  "); 
			gotoxy(41,11); printf("  ");
			gotoxy(44,11); printf("                  ");
			gotoxy(38,11); agenda.nasc.dia = getInt(2);
			gotoxy(25,15); printf("                                  ");
			gotoxy(41,11); agenda.nasc.mes = getInt(2);
			gotoxy(44,11); agenda.nasc.ano = getInt(4);
			valida_nasc();
		}
	}
	// verifica se fevereiro possui 28 ou 29 dias
	if(agenda.nasc.mes==2)
	{
		while(agenda.nasc.dia<01||agenda.nasc.dia>28||agenda.nasc.dia>29)
		{
			gotoxy(25,15);printf("Data invalida, digite novamente...");
			gotoxy(38,11); printf("  "); 
			gotoxy(41,11); printf("  ");
			gotoxy(44,11); printf("                  ");
			gotoxy(38,11); agenda.nasc.dia = getInt(2);
			gotoxy(25,15); printf("                                  ");
			gotoxy(41,11); agenda.nasc.mes = getInt(2);
			gotoxy(44,11); agenda.nasc.ano = getInt(4);
			valida_nasc();
		}   
	}
}
//---------------------------------------------------------------------------------------
// grava os dados no disco rígido
void salvar_dados()
{
	char conf;
	gotoxy(48,22);printf("Confirma dados para grava%c%co?",135,198);//135 = ç e 198 = ã
	gotoxy(48,23);printf("(S/N) ");
	do 
	{
		gotoxy(54,23); conf = getche ();
	}while(conf!= 's' && conf != 'S'&& conf != 'n' &&conf !='N' );
	if(conf == 's' || conf == 'S')
	{
		if(fwrite( &agenda, sizeof (agenda), 1, comp) !=1)
		{
			gotoxy(48,24); printf("Erro na escrita do arquivo");
		}
		else
		{
			fflush(comp);
			gotoxy(48,24); printf("Dados salvos com sucesso!!!!!");
		}
		getch();
	}
}
//------------------------------------------------------
// manipulação do cursor para que suma
void cursor (int x) 
{ 
	switch (x) 
	{
		case 0: 
		{//ocultar cursor
			CONSOLE_CURSOR_INFO cursor = {1, FALSE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
		case 1: 
		{//apresentar cursor
			CONSOLE_CURSOR_INFO cursor = {1, TRUE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
	}
}
//-------------------------------------------------
// dente
void dente()
{
	textcolor(4);
	textbackground(15);
	gotoxy(35,14); printf("    %c%c%c%c%c   %c%c%c%c",219,219,219,219,219,219,219,219,219,219);
	gotoxy(35,15); printf("   %c     %c%c%c    %c",219,219,219,219,219,219,219);
	gotoxy(35,16); printf("  %c              %c",219,219);
	gotoxy(35,17); printf("  %c              %c",219,219);
	gotoxy(35,18); printf("  %c              %c",219,219);
	gotoxy(35,19); printf("  %c     SMILE    %c",219,219);
	gotoxy(35,20); printf("  %c              %c",219,219);
	gotoxy(35,21); printf("   %c            %c",219,219,219);
	gotoxy(35,22); printf("   %c    %c%c%c%c    %c",219,219,219,219,219,219);
	gotoxy(35,23); printf("   %c    %c  %c    %c",219,219,219,219);
	gotoxy(35,24); printf("   %c   %c    %c   %c",219,219,219,219);
	gotoxy(35,25); printf("   %c%c%c%c      %c%c%c%c",219,219,219,219,219,219,219,219);
	textcolor(0);
	textbackground(11);

}
//---------------------------------------------------------------------------------------
// sorriso 1
void sorriso1()
{
	textcolor(4);
	gotoxy(15,16);printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(15,17);printf("  %c                                %c ",219,219);
	gotoxy(15,18);printf("   %c                              %c  ",219,219,219,219,219,219,219);
	gotoxy(15,19);printf("    %c                            %c   ",219,219);
	textcolor(0);
	gotoxy(20,19);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219);
	textcolor(4);
	gotoxy(15,20);printf("     %c                          %c    ",219,219);
	gotoxy(15,21);printf("      %c                        %c  ",219,219,219,219,219,219,219);
	gotoxy(15,22);printf("       %c                      %c      ",219,219);
	gotoxy(15,23);printf("        %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c       ",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
//----------------------------------------------------------------------------------------------------------------------------------------------------------
	textcolor(715);
	gotoxy(18,17);printf("********************************");
	gotoxy(19,18);printf("******************************");
	gotoxy(21,20);printf("**************************");	
	gotoxy(22,21);printf("************************");
	gotoxy(23,22);printf("**********************");	
}
//---------------------------------------------------------------------------------------
// sorriso 2
void sorriso2()
{
	textcolor(4);
	gotoxy(61,16);printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(61,17);printf("  %c                                %c ",219,219);
	gotoxy(61,18);printf("   %c                              %c  ",219,219,219,219,219,219,219);
	gotoxy(61,19);printf("    %c                            %c   ",219,219);
	textcolor(0);
	gotoxy(66,19);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219);
	textcolor(4);
	gotoxy(61,20);printf("     %c                          %c    ",219,219);
	gotoxy(61,21);printf("      %c                        %c  ",219,219,219,219,219,219,219);
	gotoxy(61,22);printf("       %c                      %c      ",219,219);
	gotoxy(61,23);printf("        %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
//----------------------------------------------------------------------------------------------------------------------------------------------------------
	textcolor(715);
	gotoxy(64,17);printf("********************************");
	gotoxy(65,18);printf("******************************");
	gotoxy(67,20);printf("**********     ***********");	
	gotoxy(68,21);printf("************************");
	gotoxy(69,22);printf("**********************");
	textcolor(0);
	gotoxy(77,20);printf("SMILE");
}
//---------------------------------------------------------------------------------------
// enxaguante bucal
void enxaguante_bucal(int col)
{
    textbackground(11);
	textcolor(4);
	system("cls");
	gotoxy(60,14);printf("     %c%c%c%c%c%c%c ",219,219,219,219,219,219,219,219,219);
	col++;
	gotoxy(61,15);printf("    %c %c %c %c      ",219,219,219,219,219);
	gotoxy(61,16);printf("    %c%c%c%c%c%c%c ",219,219,219,219,219,219,219,219,219);
	textcolor(0);
	textbackground(12);
	col+=6;
	gotoxy(66,15);printf("%c",177);
	col+=2;
	gotoxy(68,15);printf("%c",177);
	col+=2;
	gotoxy(70,15);printf("%c",177);
	textbackground(11);
	textcolor(1);
	col-=9;
	gotoxy(61,17);printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c ",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(61,18);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);	
	gotoxy(61,19);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(61,20);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(61,21);printf("%c             %c",219,219);
	gotoxy(61,22);printf("%c             %c",219,219);
	textcolor(715);
	col++;
    gotoxy(62,21);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",177,177,177,177,177,177,177,177,177,177,177,177,177,177);
    gotoxy(62,22);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",177,177,177,177,177,177,177,177,177,177,177,177,177,177);
    textcolor(0);
    col+=4;
    gotoxy(66,22);printf("SMILE");
    textcolor(1);
    col-=3;
    gotoxy(61,23);printf("%c             %c",219,219);
    textcolor(715);
    col++;
    gotoxy(62,23);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",177,177,177,177,177,177,177,177,177,177,177,177,177,177);
    textcolor(1);
    col--;
	gotoxy(61,24);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(61,25);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);

		
}
//---------------------------------------------------------------------------------------
// escova de dentes
void escova()
{
	textbackground(11);
	textcolor(1);
	gotoxy(54,20);printf("%c%c%c%c%c%c%c%c%c%c%c%c",220,254,220,220,223,223,223,254,254,220,220,220);
	gotoxy(55,21);printf("%c%c%c%c%c%c%c%c%c%c",223,254,220,220,220,220,220,220,254,223);
	textcolor(7);
	gotoxy(57,22);printf("%c%c%c%c%c%c",178,178,178,178,178,178);
	textcolor(4);
	gotoxy(40,23);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
}
//---------------------------------------------------------------------------------------
// abas
void aba_altera()
{
	system("cls");
	clrscr();
	textcolor(4);
	gotoxy(35,1);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(35,2);printf("%c              %c",219,219);
	gotoxy(35,3);printf("%c              %c",219,219);
	gotoxy(35,4);printf("%c              %c",219,219);
	gotoxy(40,3);printf("ALTERA%c%cO",128,199);// 128=Ç e  199=Ã
	gotoxy(35,5);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
}
//---------------------------------------------------------------------------------------
void aba_pesquisa()
{
	system("cls");
	clrscr();
	textcolor(4);
	gotoxy(35,1);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(35,2);printf("%c              %c",219,219);
	gotoxy(35,3);printf("%c              %c",219,219);
	gotoxy(35,4);printf("%c              %c",219,219);
	gotoxy(40,3);printf("PESQUISA");
	gotoxy(35,5);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
}
//---------------------------------------------------------------------------------------
void aba_exclusao()
{
	system("cls");
	clrscr();
	textcolor(4);
	gotoxy(35,1);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(35,2);printf("%c              %c",219,219);
	gotoxy(35,3);printf("%c              %c",219,219);
	gotoxy(35,4);printf("%c              %c",219,219);
	gotoxy(40,3);printf("EXCLUS%cO",199);// 199=Ã
	gotoxy(35,5);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
}
//---------------------------------------------------------------------------------------
void aba_cadastro()
{
	system("cls");
	clrscr();
	textcolor(4);
	gotoxy(35,1);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(35,2);printf("%c              %c",219,219);
	gotoxy(35,3);printf("%c              %c",219,219);
	gotoxy(35,4);printf("%c              %c",219,219);
	gotoxy(40,3);printf("CADASTRO");
}
//---------------------------------------------------------------------------------------
// borda das abas
void borda()
{
	gotoxy(4,5); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	textcolor(0);
	gotoxy(4,6); printf("||");
	gotoxy(80,6); printf("||");
	Sleep(50);
	gotoxy(4,7); printf("||");
	gotoxy(80,7); printf("||");
	Sleep(50);
	gotoxy(4,8); printf("||");
	gotoxy(80,8); printf("||");
	Sleep(50);
	gotoxy(4,9); printf("||");
	gotoxy(80,9); printf("||");
	Sleep(50);
	gotoxy(4,10); printf("||");
	gotoxy(80,10); printf("||");
	Sleep(50);
	gotoxy(4,11); printf("||");
	gotoxy(80,11); printf("||");
	Sleep(50);
	gotoxy(4,12); printf("||");
	gotoxy(80,12); printf("||");
	Sleep(50);
	gotoxy(4,13); printf("||");
	gotoxy(80,13); printf("||");
	Sleep(50);
	gotoxy(4,14); printf("||");
	gotoxy(80,14); printf("||");
	Sleep(50);
	gotoxy(4,15); printf("||");
	gotoxy(80,15); printf("||");
	Sleep(50);
	gotoxy(4,16); printf("||");
	gotoxy(80,16); printf("||");
	Sleep(50);
	gotoxy(4,17); printf("||");
	gotoxy(80,17); printf("||");
	Sleep(50);
	gotoxy(4,18); printf("||");
	gotoxy(80,18); printf("||");
	Sleep(50);
	gotoxy(4,19); printf("||");
	gotoxy(80,19); printf("||");
	Sleep(50);
	gotoxy(4,20); printf("||");
	gotoxy(80,20); printf("||");
	Sleep(50);
	gotoxy(4,21); printf("||");
	gotoxy(80,21); printf("||");
	Sleep(50);
	gotoxy(4,22); printf("||");
	gotoxy(80,22); printf("||");
	Sleep(50);
	gotoxy(4,23); printf("||");
	gotoxy(80,23); printf("||");
	Sleep(50);
	gotoxy(4,24); printf("||");
	gotoxy(80,24); printf("||");
	Sleep(50);
	gotoxy(4,25); printf("||");
	gotoxy(80,25); printf("||");
	textcolor(4);
	gotoxy(4,25); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
}
//-------------------------------------------------
// decoração de abertura de tela
void decoracao_abertura ()
{
	gotoxy(45,7);printf("BEM - VINDO!!");
	textcolor(49);
	gotoxy(5,10);printf("  |||||||  ||        ||   ||||     ||   ||  |||||||  |||||||||");
	gotoxy(5,11);printf("  ||       ||        ||   ||  ||   ||   ||  ||       ||     ||");
	gotoxy(5,12);printf("  ||       ||        ||   ||    || ||   ||  ||       |||||||||");
	gotoxy(5,13);printf("  ||       ||        ||   ||     | ||   ||  ||       ||     ||");
	gotoxy(5,14);printf("  |||||||  |||||||   ||   ||      |||   ||  |||||||  ||     ||");
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	gotoxy(59,15);printf("  |||||||  |||||   |||||   ||  ||       |||||||||");
	gotoxy(59,16);printf("  ||       ||   | |   ||   ||  ||       ||       ");
	gotoxy(59,17);printf("  |||||||  ||    |    ||   ||  ||       ||||||   ");
	gotoxy(59,18);printf("       ||  ||         ||   ||  ||       ||       ");
	gotoxy(59,19);printf("  |||||||  ||         ||   ||  |||||||  |||||||||");
	sorriso1();
}
//---------------------------------------------------------------------------------------
// abre o arquivo
void abrir_arquivo(const char modo[])
{
	if((comp = fopen("Registro Odontológico.bin",modo)) == NULL) 
	{
		gotoxy(18,11);printf("Erro na abertura do arquivo");
	    exit(1);
	}	
}
//-------------------------------------------
// esta é a tela de rosto que aparecerá sempre que for digitar dados do profissional
void tela_de_dados2 ()
{
	system("cls");
	clrscr();
	aba_cadastro();
	borda();
	textcolor(10+2);
	gotoxy(21,7);printf("PROFISSIONAL");
	textcolor(0);
	gotoxy(21,9);printf("C%cdigo (digite 0 para voltar):",224); //224=Ó
	gotoxy(21,10);printf("Nome  : ");
	gotoxy(21,11);printf("Data nascimento:   /  /     ");
	gotoxy(21,12);printf("e-mail: ");
	gotoxy(21,13);printf("Telefone: (  )       -    ");
	sorriso1();
	cursor(1);
}
// esta é a tela de rosto que aparecerá sempre que for digitar dados do cliente
void tela_de_dados1 ()
{
	system("cls");
	clrscr();
	aba_cadastro();
	borda();
	textcolor(10+2);
	gotoxy(21,7);printf("PACIENTE");
	textcolor(0);
	gotoxy(21,9);printf("C%cdigo (digite 0 para voltar):",224); //224=Ó
	gotoxy(21,10);printf("Nome  : ");
	gotoxy(21,11);printf("Data nascimento:   /  /     ");
	gotoxy(21,12);printf("e-mail: ");
	gotoxy(21,13);printf("Telefone: (  )       -    ");
	sorriso1();
	cursor(1);
}
//------------------------------------------------------------------------------------------
// digita dados para alteração
void digitar_dados_alterar()
{
	cursor(1);
	textcolor(0); // cor de letra
	textbackground(11);// cor da tela de fundo
	fflush(stdin);
	gotoxy(29,10);gets (agenda.nome);
	gotoxy(38,11);agenda.nasc.dia=getInt(2);
	gotoxy(41,11);agenda.nasc.mes=getInt(2);
	gotoxy(44,11);agenda.nasc.ano=getInt(4);
	valida_nasc();
	fflush(stdin);
	gotoxy(28,12);gets (agenda.e_mail);
	gotoxy(32,13);agenda.telefone.ddd = getInt(2);
	gotoxy(37,13);agenda.telefone.prefixo = getInt(5);
	gotoxy(43,13);agenda.telefone.numero = getInt(4);
	valida_cel();
	fflush(stdin);
	agenda.excluido = 'n';
}
//-------------------------------------------------------------------------------------------
// mostra os registros ja salvos
void mostra_registro1()
{
	textcolor(11);
	textcolor(0);
	cursor(1);
	gotoxy(30,9);printf("%d",agenda.codigo);
	gotoxy(29,10);printf("%s",agenda.nome);
	int aux;
	agenda.codigo = aux;
	gotoxy(38,11);printf("%d",agenda.nasc.dia);
	gotoxy(41,11);printf("%d",agenda.nasc.mes);
	gotoxy(44,11),printf("%d",agenda.nasc.ano);
	gotoxy(28,12);printf("%s",agenda.e_mail);
	gotoxy(32,13);printf("%d",agenda.telefone.ddd);
	gotoxy(37,13),printf("%d",agenda.telefone.prefixo);
	gotoxy(43,13);printf("%d",agenda.telefone.numero);
}
//------------------------------------------------------------------------------------------
// tela de rosto da alteração
void tela_de_dados_altera ()
{
	system("cls");
	clrscr();
	aba_altera();
	borda();
	textcolor(11);
	textcolor(0);
	gotoxy(21,9);printf("C%cdigo :",224); //224=Ó
	gotoxy(21,10);printf("Nome  : ");
	gotoxy(21,11);printf("Data nascimento:   /  /     ");
	gotoxy(21,12);printf("e-mail: ");
	gotoxy(21,13);printf("Telefone: (  )       -    ");
	sorriso1();
	mostra_registro1();
	textcolor(0);
	textbackground(11);	
	cursor(1);
}
void tela_de_dados_exclusao ()
{
	system("cls");
	clrscr();
	aba_exclusao();
	borda();
	textcolor(11);
	textcolor(0);
	gotoxy(21,9);printf("C%cdigo :",224); //224=Ó
	gotoxy(21,10);printf("Nome  : ");
	gotoxy(21,11);printf("Data nascimento:   /  /     ");
	gotoxy(21,12);printf("e-mail: ");
	gotoxy(21,13);printf("Telefone: (  )       -    ");
	sorriso1();
	mostra_registro1();
	textcolor(0);
	textbackground(11);	
	cursor(1);
}
//------------------------------------------------------------------------------------------------------
//serão digitados aqui dados do profissional
void digitar_dados2()
{
	do
	{
		textcolor(0); // cor de letra
		textbackground(11);// cor da tela de fundo
		tela_de_dados2();
		agenda.codigo = checar_chave_primaria();
		if(agenda.codigo==0)
		{
			cursor(0);
			break;
		}	
		fflush(stdin);
		gotoxy(29,10);gets (agenda.nome);
		gotoxy(38,11);agenda.nasc.dia=getInt(2);
		gotoxy(41,11);agenda.nasc.mes=getInt(2);
		gotoxy(44,11);agenda.nasc.ano=getInt(4);
		valida_nasc();
		fflush(stdin);
		gotoxy(28,12);gets (agenda.e_mail);
		valida_email();
		gotoxy(32,13);agenda.telefone.ddd = getInt(2);
		gotoxy(37,13);agenda.telefone.prefixo = getInt(5);
		gotoxy(43,13);agenda.telefone.numero = getInt(4);
		valida_cel();
		fflush(stdin);
		agenda.excluido = 'n';
		salvar_dados();
	}while(true);
}
//----------------------------------------------------------------------------------------------------------
//serao digitados aqui dados do paciente
void digitar_dados1()
{
	do
	{
		textcolor(0); // cor de letra
		textbackground(11);// cor da tela de fundo
		tela_de_dados1();
		agenda.codigo = checar_chave_primaria();
		if(agenda.codigo==0)
		{
			cursor(0);
			break;
		}	
		fflush(stdin);
		gotoxy(29,10);gets (agenda.nome);
		gotoxy(38,11);agenda.nasc.dia=getInt(2);
		gotoxy(41,11);agenda.nasc.mes=getInt(2);
		gotoxy(44,11);agenda.nasc.ano=getInt(4);
		valida_nasc();
		fflush(stdin);
		gotoxy(28,12);gets (agenda.e_mail);
		valida_email();
		gotoxy(32,13);agenda.telefone.ddd = getInt(2);
		gotoxy(37,13);agenda.telefone.prefixo = getInt(5);
		gotoxy(43,13);agenda.telefone.numero = getInt(4);
		valida_cel();
		fflush(stdin);
		agenda.excluido = 'n';
		salvar_dados();
	}while(true);
}
//---------------------------------------------------------------------------------------------------------
void sobre()
{
	int x;
	system("cls");
	system("cls");
	textbackground(11);
	
	do
	{
		textcolor(13);
		gotoxy(2,3); printf("A EMPRESA");
		textcolor(0);
		gotoxy(2,5); printf("\t\t A Smile %c uma cl%cnica odontol%cgica moderna e bem equipada que atende aos mais altos padr%ces de qualidade.",130,161,162,208);// 130=é, 161=í, 162=ó e 208=ð
		gotoxy(2,6); printf("\t\t Nosso objetivo eh viabilizar o melhor tratamento dentario seja qual for a necessidade.");
		gotoxy(2,7); printf("\t\t A Smile oferece atendimento odontologico especializado em diversas areas da odontologia.");
		textcolor(13);
		gotoxy(2,9); printf("PROPRIETARIAS");
		textcolor(0);
		gotoxy(2,11); printf("\t\t Emily Bigal Faveri \tnº 09");
		gotoxy(2,12); printf("\t\t Giullia Fernanda Barbosa Ferreira \tnº 12");
		gotoxy(2,13); printf("\t\t Kemily Rafaelly Heleno \tnº 18");
		textcolor(13);
		gotoxy(2,15); printf("PROFESSORA ");
		textcolor(0);
		gotoxy(2,17); printf("\t\t Ariane Scarelli");
		x= getche();
		if (x == ' ')
		{
			cursor(0);
			break;
		}
	}while(x==' ');
	
}
//---------------------------------------------------------------------------------------------------------
// Tabelas
// Nome
void tabela_nome()
{
	enxaguante_bucal(80);
	textbackground(11);
	textcolor(4);
	int x=8;
	gotoxy(x,6);printf("___________________________________________________________________________________________________________");
	gotoxy(x,7);printf("|            NOME            |  ID's  |            E-MAIL            |     TELEFONE    |    NASCIMENTO    |",224); //224=Ó
	gotoxy(x,8);printf("___________________________________________________________________________________________________________");
	gotoxy(x,9);printf("|                            |        |                              |                 |                  |");
	gotoxy(x,10);printf("|                            |        |                              |                 |                  |");
	gotoxy(x,11);printf("|                            |        |                              |                 |                  |");
	gotoxy(x,12);printf("|                            |        |                              |                 |                  |");
	gotoxy(x,13);printf("|                            |        |                              |                 |                  |");
	gotoxy(x,14);printf("|                            |        |                              |                 |                  |");
	gotoxy(x,15);printf("|                            |        |                              |                 |                  |");
	gotoxy(x,16);printf("|                            |        |                              |                 |                  |");
	gotoxy(x,17);printf("|                            |        |                              |                 |                  |");
	gotoxy(x,18);printf("|                            |        |                              |                 |                  |");
	gotoxy(x,19);printf("___________________________________________________________________________________________________________");
	textcolor(0);
}
//---------------------------------------------------------------------------------------
// Id
void tabela_id()
{
	escova();
	textcolor(1);
	int x=8;
	gotoxy(x,6);printf("_________________________________________________________________________________________________________");
	gotoxy(x,7);printf("|   ID's   |         NOME          |           E-MAIL              |     TELEFONE    |    NASCIMENTO    |");
	gotoxy(x,8);printf("_________________________________________________________________________________________________________");
	gotoxy(x,9);printf("|          |                       |                               |                 |                  |");
	gotoxy(x,10);printf("|          |                       |                               |                 |                  |");
	gotoxy(x,11);printf("|          |                       |                               |                 |                  |");
	gotoxy(x,12);printf("|          |                       |                               |                 |                  |");
	gotoxy(x,13);printf("|          |                       |                               |                 |                  |");
	gotoxy(x,14);printf("|          |                       |                               |                 |                  |");
	gotoxy(x,15);printf("|          |                       |                               |                 |                  |");
	gotoxy(x,16);printf("|          |                       |                               |                 |                  |");
	gotoxy(x,17);printf("|          |                       |                               |                 |                  |");
	gotoxy(x,18);printf("_________________________________________________________________________________________________________");
	textcolor(0);
}
//---------------------------------------------------------------------------------------
// Consulta
void tabela()
{
	int x0=5;
	textcolor(5);
	gotoxy(x0,10);printf("_________________________________________________________________________________________________________");
	gotoxy(x0,11);printf("|            NOME            |  ID's  |            E-MAIL            |     TELEFONE    |    NASCIMENTO    |",224); //224=|
	gotoxy(x0,12);printf("_________________________________________________________________________________________________________");
	gotoxy(x0,13);printf("|                            |        |                              |                 |                  |");
	gotoxy(x0,14);printf("|                            |        |                              |                 |                  |");
	gotoxy(x0,15);printf("|                            |        |                              |                 |                  |");
	gotoxy(x0,16);printf("|                            |        |                              |                 |                  |");
	gotoxy(x0,17);printf("|                            |        |                              |                 |                  |");
	gotoxy(x0,18);printf("|                            |        |                              |                 |                  |");
	gotoxy(x0,19);printf("|                            |        |                              |                 |                  |");
	gotoxy(x0,20);printf("|                            |        |                              |                 |                  |");
	gotoxy(x0,21);printf("|                            |        |                              |                 |                  |");
	gotoxy(x0,22);printf("|                            |        |                              |                 |                  |");
	gotoxy(x0,23);printf("_________________________________________________________________________________________________________");
}
//---------------------------------------------------------------------------------------
// desenho da consulta
void desenho_consulta()
{
	textcolor(4);
	gotoxy(23,4);printf("|||||||  |||||||  |||   ||  ||||||||  ||    ||  ||    |||||||||  |||||||| ");
	gotoxy(23,5);printf("||       ||   ||  ||||  ||  ||        ||    ||  ||        |      ||    || ");
	gotoxy(23,6);printf("||       ||   ||  || || ||  ||||||||  ||    ||  ||        |      |||||||| ");
	gotoxy(23,7);printf("||       ||   ||  || || ||        ||  ||    ||  ||        |      ||    || ");
	gotoxy(23,8);printf("|||||||  |||||||  ||  ||||  ||||||||  ||||||||  |||||||   |      ||    || ");
}
//---------------------------------------------------------------------------------------
// consulta de id
void consultacad_id()
{
	
	while(!feof(comp))
	{
		int r;
		int pes;
		int lin = 10;
		cursor(1);
		system("cls");
		system("cls");
		fclose(comp);//Fecha o arquivo
		gotoxy(3,2);printf("Digite o ID que deseja pesquisar:");
		scanf("%d", &pes);
		fflush(stdin);
		if((comp = fopen("Registro Odontológico.bin", "rb")) == NULL) /* Abre o arquivo novamente para leitura */
		{
		    gotoxy(25,24);printf("N%co h%c dados cadastrados",198,133); //198=ã e 133=à
		    fflush(stdin);
			getch();
			return;//exit(1);
		}
		while( !feof(comp) )
		{
			if(fread(&agenda, sizeof(agenda), 1, comp) == 1 && agenda.excluido=='n')
			{
				strupr(agenda.nome);
    			if(agenda.codigo== pes)
    			{
					tabela_id();
					gotoxy(10,lin);printf("%d", agenda.codigo);
					gotoxy(21,lin);printf("%s",agenda.nome);
					gotoxy(45,lin);printf("%s",agenda.e_mail);
					gotoxy(77,lin);printf("(%d)",agenda.telefone.ddd);
					gotoxy(100,lin);printf("%d-",agenda.telefone.prefixo);
					gotoxy(105,lin);printf("%d",agenda.telefone.numero);
					gotoxy(109,lin);printf("  | %d",agenda.nasc.dia);
					gotoxy(113,lin);printf("/%d",agenda.nasc.mes);
					gotoxy(117,lin);printf("/%d",agenda.nasc.ano);
					lin++;
				
				}
			}		
		}
		gotoxy(1,24); printf("Digite espa%co para voltar ao menu de pesquisa.",135); //135=|
		r= getche();
		if (r == ' ')
		{
			cursor(0);
			break;
		}	
		fclose(comp);
		abrir_arquivo("rb+");
	}
	
}
//-------------------------------------------------
// mostra todos os dados
void consulta_cad()
{
	int r;
	do
	{
		system("cls");
		gotoxy(1,1); printf("Digite espa%co para voltar ao menu de pesquisa.",135); //135=|
		fclose(comp);//Fecha o arquivo	
		int lin = 13;
		tabela();
		desenho_consulta();
		if((comp = fopen("Registro Odontológico.bin", "rb")) == NULL) /* Abre o arquivo novamente para leitura */
		{
		    gotoxy(25,21);printf("N%co h%c dados cadastrados",198,133); //198=ã e 133=à
		    fflush(stdin);
			getch();
			return;//exit(1);
		}
		while( !feof(comp) )
		{
			if(fread(&agenda, sizeof(agenda), 1, comp) == 1)
			{
				strupr(agenda.nome);
				if(lin>22)
				{
					r= getche();
					system("cls");
					tabela();
					if (r == ' ')
					{
						cursor(0);
						break;
					}	
					
					lin=13;
				}
				gotoxy(7,lin);printf("%s", agenda.nome);
				gotoxy(36,lin);printf("%d",agenda.codigo);
				gotoxy(46,lin);printf("%s",agenda.e_mail);
				gotoxy(76,lin);printf("(%d)",agenda.telefone.ddd);
				gotoxy(100,lin);printf("%d-",agenda.telefone.prefixo);
				gotoxy(105,lin);printf("%d",agenda.telefone.numero);
				gotoxy(109,lin);printf("  | %d",agenda.nasc.dia);
				gotoxy(113,lin);printf("/%d",agenda.nasc.mes);
				gotoxy(117,lin);printf("/%d",agenda.nasc.ano);
				lin++;
			}		
		}
		r= getche();
		if (r == ' ')
		{
			cursor(0);
			break;
		}		
		fclose(comp);
		abrir_arquivo("rb");
	}while(true);
	
}
//---------------------------------------------------------------------------------------
// consulta do nome ou de um caractere
void consultacad_nome()
{
	do
	{
		system("cls");
		fclose(comp);//Fecha o arquivo
		aba_pesquisa();
		char pes[40];
		int lin = 10;
		gotoxy(3,15);printf("Digite o nome/caractere que deseja pesquisar:");
		gets(pes);
		if((comp = fopen("Registro Odontológico.bin", "rb")) == NULL) /* Abre o arquivo novamente para leitura */
		{
		    gotoxy(25,21);printf("Nao ha dados cadastrados");
		    fflush(stdin);
			getch();
			return;//exit(1);
		}
		system("cls");
		aba_pesquisa();
		tabela_nome();
		while( !feof(comp) )
		{
			if(fread(&agenda, sizeof(agenda), 1, comp) == 1 && agenda.excluido=='n')
			{
			
				strupr(agenda.nome);
    			strupr(pes);
			
				if(strstr(agenda.nome,pes) != NULL)
				{
					textcolor(0);
					gotoxy(10,lin);printf("%s", agenda.nome);
					gotoxy(40,lin);printf("%d",agenda.codigo);
					gotoxy(49,lin);printf("%s",agenda.e_mail);
					gotoxy(79,lin);printf("(%d)",agenda.telefone.ddd);
					gotoxy(100,lin);printf("%d-",agenda.telefone.prefixo);
					gotoxy(105,lin);printf("%d",agenda.telefone.numero);
					gotoxy(109,lin);printf("  | %d",agenda.nasc.dia);
					gotoxy(113,lin);printf("/%d",agenda.nasc.mes);
					gotoxy(117,lin);printf("/%d",agenda.nasc.ano);
					lin++;
				}
			}
		}	
		gotoxy(10,23); printf("Digite espa%co para voltar ao menu de pesquisa.",135); //135=ç
		int r= getche();
		if (r == ' ')
		{
			cursor(0);
			break;
		}	
		fclose(comp);
		abrir_arquivo("rb");
	}while(true);
}
//---------------------------------------------------------------------------------------
//exclusao lógica
void excluir_dados() 
{
	system("cls");
	aba_exclusao();
	abrir_arquivo("rb");
	int aux_codigo,F;
	long fposicao;
	char conf;
		
		 if((comp = fopen("Registro Odontológico.bin","rb+")) == NULL) 
		{
			gotoxy(18,11);printf("Erro na abertura do arquivo");
		    exit(1);
		}
	do
	{
		aba_exclusao();
		borda();
		fflush(stdin);
		gotoxy(18,12); printf("Digite o codigo a ser excluido (digite 0 para encerrar): ");
		aux_codigo = getInt(5);
		
		if (aux_codigo!=0)
		{
		 	
		 	
			F = 0;
			rewind(comp);
			do
			{
				
				
				if(fread( &agenda,sizeof(agenda),1,comp) == 1){
				
				
						if ( agenda.codigo == aux_codigo && agenda.excluido =='n' ) //NÃO FOI EXCLUIDO
						{
							
							
							F = 1;
							tela_de_dados_exclusao();
							fposicao = ftell(comp); // guarda a posição do registro atual do arquivo
							gotoxy(25,22); printf("Confirma exclusao ? (S/N): "); 
							fflush(stdin);
							do
							{
							
							
							gotoxy(54,22); conf = getche();
							
							
							}while( conf != 's' && conf != 'S' && conf != 'n' && conf != 'N' );
							
							if( conf == 's' || conf == 'S' )
							{
								
								
								//posiciona o ponteiro do arquivo no registro a ser excluido logicamente
								fseek (comp,fposicao-(sizeof(agenda)),SEEK_SET);
								//SEEK_SET - inácio do arquivo
								agenda.excluido='s';//exclusão logica
								fwrite (&agenda,sizeof(agenda),1,comp);
								fflush (comp);
								agenda.excluido='s';
							
							}
						
						
						}
					
				}
			} while ((!F) && (!feof(comp)));
			
			
		} 
		if (F==0 && aux_codigo!=0 && aux_codigo != agenda.excluido)
		{
			gotoxy(20,15);printf("****** Código não encontrado ******");
			getch();
		}
	}while(aux_codigo!=0);
}
//---------------------------------------------------------------------------------------
//alteração de dados
void alterar_dados()
{
	system("cls");
	if((comp= fopen("Registro Odontológico.bin", "rb+")) == NULL)
	{
		gotoxy(20,20);printf("N%co h%c dados no arquivo ou houve falha na abertura :'(",198,160); //198=ã e 160=á
		getch();
		return;
	}
	cadastro paciente_aux;
	int aux_codigo,F;
	long fposicao;
	char conf;
	do
	{
		system("cls");
		cursor(1);
   		gotoxy(18,12); printf("Digite o código a ser alterado: ");
   		gotoxy(51,12); scanf ("%d",&aux_codigo);
   		do
   		{
				F = 0;
			fread(&agenda,sizeof(agenda),1,comp);
			if ( aux_codigo == agenda.codigo && agenda.excluido == 'n') //SOMENTE SE NÃO FOI EXCLUIDO	
			{
				F = 1;
		   		fposicao = ftell(comp); //guarda a posição do registro atual do arquivo
		   		system("cls");
		   		paciente_aux = agenda;
	   			//	aux_codigo = cliente.rg;//salva os dados do registro atual numa estrutura auxiliar
	   			tela_de_dados_altera ();
	   			digitar_dados_alterar();
	   			aux_codigo = paciente_aux.codigo;
	   			agenda.codigo = aux_codigo;
				if (agenda.nome[0] == '\x0')//checa se cada campo está vazio
				{
					strcpy(agenda.nome, paciente_aux.nome);
				} 
				if (agenda.e_mail[0] == '\x0')
				{
					strcpy(agenda.e_mail, paciente_aux.e_mail);
				}
				if (agenda.nasc.dia == 0)
				{
					 agenda.nasc.dia = paciente_aux.nasc.dia;
				}
				if (agenda.nasc.mes == 0)
				{
					agenda.nasc.mes = paciente_aux.nasc.mes;
				} 
				if (agenda.nasc.ano == 0)
				{
					agenda.nasc.ano = paciente_aux.nasc.ano;
				} 
				if (agenda.telefone.ddd == 0)
				{
					agenda.telefone.ddd = paciente_aux.telefone.ddd;
				}
				if (agenda.telefone.prefixo == 0)
				{
					agenda.telefone.prefixo = paciente_aux.telefone.prefixo;
				}
					
				if (agenda.telefone.numero == 0)
				{
					agenda.telefone.numero = paciente_aux.telefone.numero;
				}
			  	gotoxy(25,22); printf("Confirma alteracao ? (S/N): ");
			  	do 
			  	{
			  			
				   	gotoxy(54,22); conf = getche();
				   	
			 	}while( conf != 's' && conf != 'S' && conf != 'n' && conf != 'N' );
				 	
		   		if( conf == 's' || conf == 'S' )
				{
					//posiciona o ponteiro do arquivo no registro alterado
					fseek (comp,fposicao-(sizeof(agenda)),SEEK_SET);//em stdio.h
					if(fwrite (&agenda,sizeof(agenda),1,comp)==1)
					{
						fflush (comp);
						gotoxy(10,26);printf("Dados alterados com sucesso!");
						getch();	
					}
			
				}	
			}
		}  while ((!F) && (!feof(comp))); //enquanto F for diferente de 1 e não for o fim do arquivo
		if (F==0)
		{
			gotoxy(18,15);printf("****** Código nao encontrado ******");
			getch();
		} 	
	}while (aux_codigo != 0);
}
//---------------------------------------------------------------------------------------
// pesquisa ou consulta de dados
void pesquisa()
{
	int sair=1;
	int lin=5;
	char c;
	textcolor(0);
	textbackground(11);
	system("cls");
	enxaguante_bucal(60);
	textcolor(0);
	textbackground(11);
	do
	{
		gotoxy(10,2); printf("\n\t(Pressione W para subir e S para descer)");
		gotoxy(10,5); printf("PESQUISA POR ID");
		gotoxy(10,7); printf("PESQUISA POR NOME");
		gotoxy(10,9); printf("GERAL");
		gotoxy(10,11); printf("VOLTAR");
		gotoxy(8,lin); printf("%c", 62);
		fflush(stdin);
		c=getch();
		gotoxy(8,lin); printf(" ");
		switch(c)
		{
			case 'w' :
			lin-=2;
			if(lin<5)
			{
				lin=11;	
			}
			gotoxy(8,lin); printf("%c", 62);
			break;
			case 's' : 	
			lin+=2;
			if(lin>11)
			{
				lin=5;
			}
			gotoxy(8,lin); printf("%c", 62);
			break;
		}
	
		switch(c)
		{
				case 13:
				if(lin==5)
				{
					consultacad_id();
					textcolor(0);
					textbackground(11);
					system("cls");
				}
				else
				if(lin==7)
				{
					consultacad_nome();
					textcolor(0);
					textbackground(11);
					system("cls");
				}
				else
				if(lin==9)
				{
					consulta_cad();
					textcolor(0);
					textbackground(11);
					system("cls");
				}
				else
				if(lin==11)
				{
					sair=0;
				}
		}
	}while(sair);
}
//---------------------------------------------------------------------------------------
// inicio lógico
main()
{
	int lin=5;
	char c;
	abrir_arquivo("ab+");
	cursor(0);
	int sair;
	SetConsoleTitle("   Dentista");
	system("mode con:cols=150 lines=100");
	textcolor(0);
	textbackground(11);
	system("cls");	
	decoracao_abertura();
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	Sleep(2000);
	textcolor(0);
	textbackground(11);
	do
	{
		textcolor(0);
		textbackground(11);	
		system("cls");
		clrscr();
		sair =1;
		gotoxy(10,2); printf("\n\t(Pressione W para subir e S para descer)");
		gotoxy(10,5); printf("REGISTRO PACIENTE");
		gotoxy(10,7); printf("REGISTRO PROFISSIONAL");
		gotoxy(10,9); printf("PESQUISA");
		gotoxy(10,11); printf("EXCLUIR DADOS CADASTRADOS");
		gotoxy(10,13); printf("ALTERAR DADOS CADASTRADOS");
		gotoxy(10,15); printf("SOBRE");
		gotoxy(10,17); printf("SAIR");
		sorriso2();
		escova();
		textcolor(0);
		textbackground(11);	
		gotoxy(8,lin); printf("%c", 62);
		c=getch();
		gotoxy(8,lin); printf(" ");
	
		switch(c)
		{
			case 'w' :
			lin-=2;
			if(lin<5)
			{
				lin=17;	
			}
			gotoxy(8,lin); printf("%c", 62);
			break;
			case 's' : 	
			lin+=2;
			if(lin>17)
			{
				lin=5;
			}
			gotoxy(8,lin); printf("%c", 62);
			break;
		}
	
		switch(c)
		{
				case 13:
				if(lin==5)
				{
					cursor(0);
					digitar_dados1();
					system("cls");
					clrscr();
					cursor(0);
				}
				else
				if(lin==7)
				{
					cursor(0);
					digitar_dados2();
					system("cls");
					clrscr();
					cursor(0);
				}
				else
				if(lin==9)
				{
					cursor(0);
					pesquisa();
					system("cls");
					clrscr();
					cursor(0);
				}
				else
				if(lin==11)
				{
					cursor(0);
					excluir_dados();
					system("cls");
					clrscr();
					cursor(0);
				}
				else
				if(lin==13)
				{
					cursor(0);
					alterar_dados();
					system("cls");
					clrscr();
					cursor(0);
				}
				else
				if(lin==15)
				{
				
					cursor(0);
					sobre();
					system("cls");
					clrscr();
					cursor(0);	
					fflush(stdin);
				}
				else
				if(lin==17)
				{
					sair=0;
				}
		}
	}while(sair);
}
