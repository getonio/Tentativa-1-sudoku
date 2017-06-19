#include <stdio.h>

#include <string.h>

#include <stdlib.h>


int Matriz[9][9];


typedef struct Sudoku

{

 int l;

 int c;

 int *v;

 int aux;

}Sudoku;


void Solucao(int,int);

int Alocar(Sudoku *);

void Desalocar(int *, int (*func)(const int *));

int Montar(Sudoku *);

void Troca(int, int);

int Linha(int,int);

int Coluna(int,int);

int Nove(int,int,int);


int Alocar(Sudoku *Jogo)

{

(Jogo->v) = (int *)calloc(81,sizeof(int));

if(!(Jogo->v))

{

printf("** Erro: Memoria Insuficiente **");

exit(0);

}

}


void Desalocar(int *V, int (*func)(const int *))

{

(*func)(V);

}


int Montar(Sudoku *Jogo)

{

FILE *fp;

char arquivo[50];

int i,j=0,k=0,a,o;

do

{

printf("Digite uma das opcoes:\n\n\t1 - Ler do teclado;\n\n\t2 - Ler de arquivo(formatado semelhante ao jogo apresentado).\n\nOpcao escolhida: ");

scanf("%d",&o);

if((o!=1)&&(o!=2))

{

printf("\n\n********OPCAO INVALIDA*******\n\n");

}

}while((o!=1)&&(o!=2));

printf("\n");

fflush(stdin);

switch(o)

{

case 1:

{

for(i=0;i<81;i++)

{

printf("Linha %d Coluna %d: ", k+1, j+1);

scanf("%d", &a);

(Jogo->v[i])=a;

a=0;

j++;

if(!(j%9))

{

j=0;

k++;

}

}

break;

}

case 2:

{

printf("Digite o nome do arquivo que contem os dados: ");

fflush(stdin);

fgets(arquivo,49,stdin);

if (!(fp = fopen(arquivo,"r")))

{

printf("\n\nErro, nao foi possivel abrir o arquivo\n\n");

exit(0);

}

for(i=0;i<81;i++)

{

fscanf(fp,"\t%d",&a);

(Jogo->v[i])=a;

a=0;

j++;

if(!(j%9))

{

j=0;

}

}

fclose(fp);

break;

}

default:

break;

}

}


void Troca(int l, int c)

{

if(c<8)

{

Solucao(l,c+1);

}

else

{

Solucao(l+1,0);

}

}


void Solucao(int col, int lin)

{

int i;

if(lin>8)

{

printf("\n\n\t*******SOLUCAO*******\n\n\t");

for(lin=0;lin<9;lin++)

{

for(col=0;col<9;col++)

printf("%5d",Matriz[lin][col]);

printf("\n\t");

}

printf("\n\n");

}

if(Matriz[col][lin]!=0)

{

Troca(lin,col);

}

else

{

for(i=0;i<9;i++)

{

if((Linha(lin,i)==1)&&(Coluna(col,i)==1)&&(Nove(lin,col,i)==1))

{

Matriz[lin][col]=(i+1);

Troca(lin,col);

}

}

}

}


int Linha(int l,int aux)

{

int c;

for(c=0;c<9;c++)

{

if(Matriz[l][c]==(aux+1))

{

return 0;

}

return 1;

}

}


int Coluna(int c,int aux)

{

int l;

for(l=0;l<9;l++)

{

if(Matriz[l][c]==(aux+1))

{

return 0;

}

return 1;

}

}


int Nove(int l,int c,int aux)

{

int li,co;

for(li=0;li<3;li++)

{

for(co=0;co<3;co++)

{

if(Matriz[l+li][c+co]==(aux+1))

{

return 0;

}

}

}

return 1;

}


int main()

{

int i, j;

Sudoku S;

(S.l)=9;

(S.c)=9;

int (*p)(const int *);

//*p=free;

printf("\t\t\tSOLUCIONADOR DE SUDOKU\n\n");

printf("A partir de um jogo de SUDOKU constituido por 9 linhas e 9 colunas de forma\ndemonstrada por:\n");

printf("\n\t0\t0\tX\t0\tX\t0\t0\t0\tX");

printf("\n\tX\tX\t0\tX\t0\t0\t0\tX\t0");

printf("\n\t0\t0\tX\t0\t0\tX\tX\tX\t0");

printf("\n\t0\tX\tX\t0\tX\t0\t0\tX\tX");

printf("\n\tX\t0\t0\tX\t0\tX\tX\t0\t0");

printf("\n\t0\tX\t0\t0\tX\t0\tX\tX\t0");

printf("\n\t0\t0\tX\t0\t0\tX\tX\tX\t0");

printf("\n\t0\tX\tX\t0\tX\t0\t0\tX\tX");

printf("\n\tX\t0\t0\tX\t0\tX\tX\t0\t0");

printf("\n\nOnde X representam os numeros apresentados no jogo e 0 os espacos vazios.\n\n");

Alocar(&S);

Montar(&S);

for(i=0;i<9;i++)

{

for(j=0;j<9;j++)

{

Matriz[i][j]=(S.v[i*9+j]);

}

}

Solucao(0,0);

Desalocar(S.v,p);

}
