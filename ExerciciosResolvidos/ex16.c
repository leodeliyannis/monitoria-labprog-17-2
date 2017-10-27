/*
 * Leonardo Deliyannis Constantin
 * Exercicio 16 - Lab. Prog. ECP 2017-2
 * Word Hunter!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef enum direcao_ { horz, vert, diag } direcao;

char **alocaMatriz(int lin, int col){
    char **p;
    int i, j;
    p = (char**)(malloc(lin * sizeof(char*)));
    if(p == NULL) return NULL;
    for(i = 0; i < lin; i++){
        p[i] = (char*)(malloc((col + 1) * sizeof(char)));
        if(p[i] == NULL){
            for(j = 0; j < i; j++)
                free(p[j]);
            free(p);
            return NULL;
        }
    }
    return p;
}

void zeraMatriz(char **p, int lin, int col){
    int i;
    for(i = 0; i < lin; i++){
        memset(p[i], ' ', col + 1);
        p[i][col] = 0;
    }
}

void preencheMatriz(char **p, int lin, int col){
    srand(time(NULL));
    int i, j;
    for(i = 0; i < lin; i++)
        for(j = 0; j < col; j++)
            if(p[i][j] == ' ')
                p[i][j] = (char)(rand() % 26 + 97);
}

void mostraMatriz(char **p, int lin, int col){
    int i, j;
    for(i = 0; i < lin; i++){
        if(col <= 40){
            for(j = 0; j < col; j++){
                putchar(p[i][j]);
                if(j < col - 1)
                    putchar(' ');
            }
            putchar('\n');
        }
        else puts(p[i]);
    }
}

void liberaMatriz(char **p, int lin){
    int i;
    if(p == NULL) return;
    for(i = 0; i < lin; i++){
        free(p[i]);
    }
    free(p);
}

void leiaDimensoes(int *lin, int *col){
    do{
        printf("\nInsira as dimensões da matriz\n");
        printf("(min.: 10 x 10, max: 25 x 75)\n");
        printf("Linhas: ");
        scanf("%d", lin);
        if(*lin < 10 || 25 < *lin) continue;
        printf("\nColunas: ");
        scanf("%d", col);
    } while (*col < 10 || 75 < *col);
}

void leiaPosicao(int lin, int col, int *l, int *c){
    do{
        printf("\nInsira a posicao inicial da palavra\n");
        printf("(min.: {0, 0}, max: {%d, %d})\n", lin-1, col-1);
        printf("Linha: ");
        scanf("%d", l);
        if(*l < 0 || lin <= *l) continue;
        printf("\nColuna: ");
        scanf("%d", c);
    } while (*c < 0 || col <= *c);
}

void leiaDirecao(direcao *dir){
    char c;
    getchar();
    do{
        printf("\nEm qual direcao?\n");
        printf("(V)ertical, (H)orizontal ou (D)iagonal?\n");
        printf("Sua opcao: ");
        scanf("%c", &c);
        c = toupper(c);
    }while(c != 'V' && c != 'H' && c != 'D');
    *dir = (c == 'V') ? vert : (c == 'H') ? horz : diag;
}

int inserePalavra(char **m, int lin, int col, 
char *s, int l, int c, direcao dir){
    int i, tam;
    tam = strlen(s);
    if((dir == diag && (lin - l < tam || col - c < tam)) ||
        (dir == horz && col - c < tam) ||
        (dir == vert && lin - l < tam)){
        printf("\nNao foi possivel inserir a palavra!\n");
        printf("Insira uma palavra de tamanho compativel\n");
        printf("ou altere a posicao inicial da mesma.\n");
        return 0;
    }
    for(i = 0; s[i] != 0; i++){
        if(dir == diag) m[l+i][c+i] = tolower(s[i]);
        if(dir == horz) m[l][c+i] = tolower(s[i]);
        if(dir == vert) m[l+i][c] = tolower(s[i]);
    }
    printf("\nPalavra inserida com sucesso!\n");
    return 1;
}

int validaPalavra(const char *s){
    int i;
    for(i = 0; s[i]; i++)
        if(!isalpha(s[i])){
            printf("\nPalavra invalida!\n");
            return 0;
        }
    return 1;
}

void pedePalavras(char **m, int lin, int col){
    int i, l, c;
    int maisUma;
    char op;
    char s[82];
    direcao dir;
    printf("\nDigite no minimo 5 palavras, sem espacos.\n");
    for(i = 1; i <= 5 || maisUma; i++){
        do{
            do{
                printf("Insira a %da palavra: ", i);
                scanf("%s", s);
            }while(!validaPalavra(s));
            leiaPosicao(lin, col, &l, &c);
            leiaDirecao(&dir);
        }while(!inserePalavra(m, lin, col, s, l, c, dir));
        if(i >= 5){
            printf("\nInserir mais uma palavra? [s/N]: ");
            scanf(" %c", &op);
            printf("THIS IS WRONG: '%c'\n", op);
            maisUma = toupper(op) == 'S';
        }
    }
    printf("\n");
}

int main(){
    int lin, col;
    char **m;
    fflush(stdin);
    leiaDimensoes(&lin, &col);
    m = alocaMatriz(lin, col);
    zeraMatriz(m, lin, col);
    pedePalavras(m, lin, col);
    preencheMatriz(m, lin, col);
    mostraMatriz(m, lin, col);
    liberaMatriz(m, lin);
    return 0;
}
