#include<stdio.h>

int var[5]={1,2,3,4,5};
int *p=var;

int main(){
	for (int i=0; i<5; i++){
		p[i]=i;
		printf("Valor = %d\n", p[i]); 
	}
	
	return 0;
}
