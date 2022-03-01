//--------------------------------------------------------------------
// Universidade Federal de Sergipe
// Departamento de Matemática
// Aluno João Victor S. R. dos Santos
// Aracaju SE 03/04/2018
// obs.: para compilar: gcc polinomio.c -lm -o polinomio
// Sintaxe: ./poninomio
//--------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "struct.h" 

 void main(int argc, char **argv){
	pol P,Q;
	P = anular_pol(P);
	Q = anular_pol(Q);

//P
//------------------------------
	P.gr = 5;
	for(int i=0;i<=2;i++)
		P.coef[i] = i+1;
	P.coef[3] = 0;
	P.coef[4] = -2;
	P.coef[5] = -1;

imprimir_pol("P",P);
//------------------------------

//Q
//------------------------------
Q.gr = 0;

	Q.gr = 5;
	for(int i=0;i<=2;i++)
		Q.coef[i] = i+3;
	Q.coef[3] = 1;
	Q.coef[4] = 6;
	Q.coef[5] = 7;

imprimir_pol("Q",Q);

//------------------------------

//Soma e Subtração
//------------------------------
pol Soma,Subtracao;
anular_pol(Soma);
anular_pol(Subtracao);

Soma = somar_pols(P,Q);
Subtracao = subtrair_pols(P,Q);

imprimir_pol("(P+Q)",Soma);
imprimir_pol("(P-Q)",Subtracao);
//------------------------------

//Produto
//------------------------------
pol G, H;
	G = anular_pol(G);
	H = anular_pol(H);

G.gr = 4;
G.coef[0] = 9;
G.coef[1] = 2;
G.coef[2] = 3;
G.coef[4] = 2;
imprimir_pol("G",G);

H.gr = 3;
H.coef[0] = -11;
H.coef[1] = -5;
H.coef[2] = 14;
H.coef[3] = 10;
imprimir_pol("H",H);

pol Produto;
	Produto = anular_pol(Produto);
	Produto = produto_pols(G,H);
	imprimir_pol("(G.H)",Produto);
//------------------------------


//Divisão exata ex
//------------------------------
pol M, N;
	M = anular_pol(M);
	N = anular_pol(N);

M.gr = 4;
M.coef[0] = -5;
M.coef[1] = 9;
M.coef[2] = 9;
M.coef[3] = -10;
M.coef[4] = 6;
imprimir_pol("M",M);

N.gr = 2;
N.coef[0] = 5;
N.coef[1] = -4;
N.coef[2] = 2;
imprimir_pol("N",N);

pol_2 Divisao;
	Divisao = divisao_pols(M,N);
	imprimir_pol("(M/N)",Divisao.Quociente);
	imprimir_pol("R",Divisao.Resto);
//------------------------------

//Divisão nao exata ex
//------------------------------
pol U, I;
	U = anular_pol(U);
	I = anular_pol(I);

U.gr = 3;
U.coef[0] = 12;
U.coef[1] = -1;
U.coef[2] = -6;
U.coef[3] = 1;

imprimir_pol("U",U);

I.gr = 1;
I.coef[0] = -2;
I.coef[1] = 1;
imprimir_pol("I",I);

pol_2 Divisao_1;
	Divisao_1 = divisao_pols(U,I);
	imprimir_pol("(U/I)",Divisao_1.Quociente);
	imprimir_pol("R",Divisao_1.Resto);
//------------------------------

//Mod x-1
//------------------------------
pol Mod;
	Mod = anular_pol(Mod);
	Mod = pol_mod(G);
		imprimir_pol("(G_mod(x-1))",Mod);
//------------------------------

}
