/*
 * Leonardo Deliyannis Constantin
 * Exercício 7 - Lab. Prog. ECP
 * Check Letters

Faça a leitura de uma string via fgets(); esta string deve conter no minimo 30 caracteres e no maximo 70;

Apos, leia uma letra e escreva na tela a string seguido das ocorrencias desta letra sinalizadas com ^ 
(Utilize o caracter 24 ou 30 para desenhar a seta)

Exemplo:
Teste de string de 30 ate 70 caracteres. (Letra 't')
^  ^      ^            ^          ^
1  2      3            4          5

*/

#include <stdio.h>
#include <ctype.h>
#define MAX 72

int main(){
	char s[MAX], letra, oc;
	int i;
	fgets(s, MAX, stdin);
	letra = toupper(getchar());
	printf("%s", s);
	for(i = 0; s[i] != '\0'; i++){
		putchar((toupper(s[i]) == letra) ? '^' : ' ');
	}
	putchar('\n');
	oc = '0';
	for(i = 0; s[i] != '\0'; i++){
		if(oc == '9') oc = '0';
		putchar((toupper(s[i]) == letra) ? ++oc : ' ');
	}
	putchar('\n');
	return 0;
}
