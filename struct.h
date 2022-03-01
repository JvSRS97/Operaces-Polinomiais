//---------------------------------------------------------------------------------------------------------------
// Universidade Federal de Sergipe
// Departamento de Matemática
// Aluno João Victor S. R. dos Santos
// Biblioteta para o curso de Introdução à Computação Gráfica
// Para ler, alocar e gravar imagens ppm e pgm
// Prof Evilson Vieira com edição de João Victor S.R. dos Santos
// Aracaju SE 03/04/2018
//----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define abs(a) (((a)<0) ? -(a) : (a))

//Parte 1
//----------------------------------------------------------------------------
typedef struct {
  int  l, h;                               // altura x largura
  unsigned char type, cmax, **r, **g, **b; // tipo, cor maxima, ponteiros para os canais de cor rgb (use g para gray:cinza)
  } imagem;

void alocar_imagem(imagem *foto, unsigned char type, int largura, int altura, unsigned char cmax)
{
  int i,j;
  foto->type = type;
  foto->l = largura;
  foto->h = altura;
  foto->cmax = cmax;
  foto->g = malloc(sizeof(char*) * foto->l);
  for (i=0; i < foto->l; i++)  foto->g[i] = malloc(sizeof(char) * foto->h); //verde ou cinza
  if ((foto->type == 3)||(foto->type == 6))
  {
    foto->r = malloc(sizeof(char*) * foto->l);
    for (i=0; i < foto->l; i++)  foto->r[i] = malloc(sizeof(char) * foto->h); //vermelho
    foto->b = malloc(sizeof(char*) * foto->l);
    for (i=0; i < foto->l; i++)  foto->b[i] = malloc(sizeof(char) * foto->h); //azul
  }
}

void ler_imagem(char *arquivo, imagem *foto)
{
  int i,j;
  FILE *fp;
  unsigned char caractere;
  fp = fopen(arquivo, "r");
  while ((caractere=getc(fp))=='#')
    while((caractere=getc(fp))!='\n');
  ungetc(caractere,fp);
  fscanf(fp, "P%hhu\n", &foto->type);
  while ((caractere=getc(fp))=='#')
    while((caractere=getc(fp))!='\n');
  ungetc(caractere,fp);
  fscanf(fp, "%u %u %hhu\n", &(foto->l), &(foto->h), &(foto->cmax));
  foto->g = malloc(sizeof(char*) * foto->l);
  for (i=0; i < foto->l; i++)  foto->g[i] = malloc(sizeof(char) * foto->h); //verde ou cinza
  if ((foto->type == 3)||(foto->type == 6))
  {
    foto->r = malloc(sizeof(char*) * foto->l);
    for (i=0; i < foto->l; i++)  foto->r[i] = malloc(sizeof(char) * foto->h); //vermelho
    foto->b = malloc(sizeof(char*) * foto->l);
    for (i=0; i < foto->l; i++)  foto->b[i] = malloc(sizeof(char) * foto->h); //azul
  }
  switch(foto->type)
  {
    case(2):
      for (j=0; j < foto->h ; j++)
        for (i=0; i < foto->l; i++)
          fscanf(fp, "%hhu ", &(foto->g[j][i]));
    break;
    case(3):
      for (j=0; j < foto->h ; j++)
        for (i=0; i < foto->l; i++)
          fscanf(fp, "%hhu %hhu %hhu ", &(foto->r[i][j]), &(foto->g[i][j]),&(foto->b[i][j]));
    break;

    case(5):
      for (j=0; j < foto->h ; j++)
        for (i=0; i < foto->l; i++)
          fscanf(fp, "%c", &(foto->g[i][j]));
    break;
    case(6):
      for (j=0; j < foto->h ; j++)
        for (i=0; i < foto->l; i++)
          fscanf(fp, "%c%c%c", &(foto->r[i][j]), &(foto->g[i][j]),&(foto->b[i][j]));
    break;
    default:
      printf("Formato inválido!");
      fclose(fp);
      exit(0);
  }
  fclose(fp);
}

void salvar_imagem(imagem *foto, char *arquivo)
{
  int i,j;
  FILE *fp;
  unsigned char type=foto->type;
  if(type==2) type=5;      // salva só binário
  else if(type==3) type=6; // salva só binário
  fp = fopen(arquivo, "w");
  fprintf(fp, "P%hhu\n", type);
  fprintf(fp, "# Criado no curso de Introdução à Computação Gráfica\n");
  fprintf(fp, "# Departamento de Matemática - UFS\n");
  fprintf(fp, "# Joao Victor S. R. dos Santos\n");
  fprintf(fp, "%u %u %hhu\n", foto->l, foto->h, foto->cmax);
  switch(type)
  {
    case(5):
      for (j=0; j < foto->h ; j++)
        for (i=0; i < foto->l; i++)
          fprintf(fp, "%c", foto->g[i][j]);
    break;
    case(6):
      for (j=0; j < foto->h ; j++)
        for (i=0; i < foto->l; i++)
          fprintf(fp, "%c%c%c", foto->r[i][j], foto->g[i][j],foto->b[i][j]);
    break;
    default:
      printf(" Formato inválido!");
      fclose(fp);
      exit(0);
  }
  fclose(fp);
	 printf("\n Imagem gerada com sucesso!\n");
}

void free_imagem(imagem foto)
{
  int i;
  for (i=0; i < foto.l; i++)  free(foto.g[i]);
  if ((foto.type == 3)||(foto.type == 6))
    for (i=0; i < foto.l; i++)
    {
      free(foto.r[i]);
      free(foto.b[i]);
    }
}

int min(int a, int b)
{
  return (a<b)?a:b;
}

int max(int a, int b)
{
  return (a<b)?b:a;
}


//Parte 2
//----------------------------------------------------------------------------------------------------------
typedef struct {//estrutura ponto
  int x,y,ordem,fecho; //a ordem de um ponto é um numero que representa somente este ponto. Ela é definida na hora de leitura dos pontos. Com ela é possivel identificar cada ponto de acordo com a ordem de leitura. 
//fecho=1 significa que o ponto está no fecho. Isto será trabalhado na parte 4
  } ponto;

//Definindo função para zerar um ponto,ou seja "deletar um ponto"
//---------------------------------------------------------------------------
	ponto zerar_ponto(ponto A){
		A.x = 0;
		A.y = 0;
		A.ordem = 0; //se a ordem é 0 o ponto não existe mais
		A.fecho = 0; //não está no fecho
	return A;
	}
//---------------------------------------------------------------------------

//Definindo função para imprimir um ponto
//---------------------------------------------------------------------------
	void imprimir_ponto(ponto A){
		if(A.ordem < 10)
			printf(" Ponto 0%d: (%d,%d)", A.ordem, A.x, A.y);
		else
			printf(" Ponto %d: (%d,%d)", A.ordem, A.x, A.y);
	}
//---------------------------------------------------------------------------

ponto Ponto_med(ponto A, ponto B) // o resultado será (A+B)/2 com valores arredondados para baixo
{
  ponto M;
  M.x = (A.x+B.x+1)/2; 
  M.y = (A.y+B.y+1)/2;
  return M;
}

typedef struct {//estrutura cor
  int r,g,b;
  } cor;


//Definindo a função para marcar um ponto na imagem com uma determinada cor
//-------------------------------------------------------------------------------------
	void marcar(ponto A, imagem img, cor cor){
 	img.r[A.x][A.y] = cor.r;
	img.g[A.x][A.y] = cor.g;
	img.b[A.x][A.y] = cor.g;
 }
//-------------------------------------------------------------------------------------


int ok_r(ponto A, ponto B)
{
  if (abs(A.x-B.x)>1) return 1;
  else if (abs(A.y-B.y)>1) return 1;
  else return 0;
}

int ok_b(ponto A, ponto B){
	if (ok_r(A,B)) 		 return 1;
	else return 0;
}

//Definindo função de bezier de grau 1 para ligar dois pontos
//-----------------------------------------------------------------	
	void ligar_pontos(ponto A, ponto B, imagem img, cor cor)
	{
 	 ponto Med;
   if (ok_b(A,B))
  	{  
   	 	Med = Ponto_med(A,B);    
  
   		marcar(Med, img, cor);
   	 	ligar_pontos(A, Med, img, cor);
   	 	ligar_pontos(Med, B, img, cor);
  	}
  else
  	{
  	  marcar(A, img, cor);
  	  marcar(B, img, cor);
  	}
	}
//------------------------------------------------------------------	

//Definindo função para calcular a distancia entre dois pontos
//-----------------------------------------------------------------	
 float dist_2p(ponto A, ponto B){
		float dist2p = 1;
		dist2p = sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));		
		return dist2p;
	}
//-----------------------------------------------------------------	

//Definindo função para calcular a distancia A->P->B
//-----------------------------------------------------------------	
 float dist_3p(ponto A, ponto B, ponto P){
		float dist3p = 1;
		dist3p = dist_2p(A,P) + dist_2p(P,B);	
		return dist3p;
	}	
//-----------------------------------------------------------------	

//Definindo função para encontrar o minimo de dois numeros
//-----------------------------------------------------------------	
	float minimo(float a, float b){
		float minimo=0;
		if(a>b)
			minimo=b;
		else
			minimo=a;
		return minimo;
	} 	
//-----------------------------------------------------------------

//Definindo função para encontrar o maximo de dois numeros
//-----------------------------------------------------------------	
	float maximo(float a, float b){
		float maximo=0;
		if(a>b)
			maximo=a;
		else
			maximo=b;
		return maximo;
	} 	
//-----------------------------------------------------------------


//Definindo função para encontrar o ponto o qual possui o menor valor para a coordenada x 
//----------------------------------------------------------------------------------------------
	ponto min_x(ponto A, ponto B){
		ponto Min;
		if(minimo(A.x,B.x)==A.x){
			Min.x = A.x;
			Min.y = A.y;
			Min.ordem = A.ordem;		
		}
		else{
			Min.x = B.x;
			Min.y = B.y;
			Min.ordem = B.ordem;
		}
	return Min;			
	}
//----------------------------------------------------------------------------------------------


//Definindo função para encontrar o ponto o qual possui o maior valor para a coordenada x 
//----------------------------------------------------------------------------------------------
	ponto max_x(ponto A, ponto B){
		ponto Max;
		if(maximo(A.x,B.x)==A.x){
			Max.x = A.x;
			Max.y = A.y;
			Max.ordem = A.ordem;		
		}
		else{
			Max.x = B.x;
			Max.y = B.y;
			Max.ordem = B.ordem;
		}
	return Max;			
	}
//----------------------------------------------------------------------------------------------

//Definindo função para encontrar o ponto o qual possui o menor valor para a coordenada y 
//----------------------------------------------------------------------------------------------
	ponto min_y(ponto A, ponto B){
		ponto Min;
		if(minimo(A.y,B.y)==A.y){
			Min.x = A.x;
			Min.y = A.y;
			Min.ordem = A.ordem;		
		}
		else{
			Min.x = B.x;
			Min.y = B.y;
			Min.ordem = B.ordem;
		}
	return Min;			
	}
//----------------------------------------------------------------------------------------------


//Definindo função para encontrar o ponto o qual possui o maior valor para a coordenada y
//----------------------------------------------------------------------------------------------
	ponto max_y(ponto A, ponto B){
		ponto Max;
		if(maximo(A.y,B.y)==A.y){
			Max.x = A.x;
			Max.y = A.y;
			Max.ordem = A.ordem;		
		}
		else{
			Max.x = B.x;
			Max.y = B.y;
			Max.ordem = B.ordem;
		}
	return Max;			
	}
//----------------------------------------------------------------------------------------------

//Definindo função para calcular a norma de um vetor
//-----------------------------------------------------------------	
	float norma(ponto A){
		float norma = 1;
		norma = sqrt((A.x*A.x)+(A.y*A.y));
		return norma;	
	}
//-----------------------------------------------------------------	

//Definindo função para calcular o produto interno de dois vetores
//-----------------------------------------------------------------	
	int prod_interno(ponto A, ponto B){
		int prod_int = 1;
		prod_int = A.x*B.x + A.y*B.y;
		return prod_int;	
	}
//-----------------------------------------------------------------------	

//Definindo função para calcular o angulo entre dois vetores em graus
//-----------------------------------------------------------------------	
	float theta(ponto A, ponto B){
		float theta = 1;
		theta = (acos ((prod_interno(A,B))/(norma(A)*norma(B))))*180/3.141592;
		return theta;	
	}
//-----------------------------------------------------------------------	

//Definindo função para testar se um ponto é diferente de outro
//-----------------------------------------------------------------------	
	int teste_dif_pontos(ponto A, ponto B){
		int result = 0;
		if (A.x != B.x)
			result = 1;//são diferentes
		else
			if(A.y != B.y)//economizar um pouquinho de tempo
				result = 1;//são diferentes
			else
				result = 0;
		return result;
	}
//-----------------------------------------------------------------------	

//Definindo função para criar o vetor AB
//-----------------------------------------------------------------------------------------
	ponto criar_vetor(ponto A, ponto B){
		ponto Vetor;
		Vetor.x = B.x - A.x;
		Vetor.y = B.y - A.y;
		Vetor.ordem = -1;//para dizer identificar como vetor, caso seja necessário
		return Vetor;
	}
//-----------------------------------------------------------------------------------------

//Definindo função para calcular o coeficiente do K do produto vetorial (i,j,k)
//-----------------------------------------------------------------------------------------
	int calcular_k(ponto A, ponto B){
		int k=0;
		k = (A.x * B.y)-(B.x * A.y);
		return k;
	}
//-----------------------------------------------------------------------------------------

//Definindo função sinal                                            
//-----------------------------------------------------------------------------------------
	int sinal(float a, float b){
		int result = 0;
		if((a>0 && b>0) || (a<0 && b<0))
			result = 1; //sinais iguais
		return result;	
	}
//-----------------------------------------------------------------------------------------

//Definindo função para verificar se um dado ponto P está acima ou abaixo de um dado segmento AB ou BA
//-----------------------------------------------------------------------------------------------------
	int verificar_local(ponto A, ponto B, ponto P){
		int result = 1;//acima
		//identificar qual dos pontos (A ou B) que está mais a esquerda para fazer dele a origem dos vetores
		if(teste_dif_pontos(min_x(A,B),A) == 0){//Se o ponto mais a esquerda for o ponto A
			ponto AB = criar_vetor(A,B);
			ponto AP = criar_vetor(A,P);

			ponto acima_B;
			acima_B.x = B.x ;
			acima_B.y = B.y - 20;

			ponto C = criar_vetor(A,acima_B);	
			if(sinal(calcular_k(AB,AP),calcular_k(AB,C))==1)//sinais iguais
				result = 0 ;//abaixo
		} 
		else{//Se o ponto mais a esquerda for o ponto B
			ponto BA = criar_vetor(B,A);
			ponto BP = criar_vetor(B,P);
			
			ponto acima_A;
			acima_A.x = A.x;
			acima_A.y = A.y - 20;

			ponto C = criar_vetor(B,acima_A);	
			if(sinal(calcular_k(BA,BP),calcular_k(BA,C))==1)//sinais iguais
				result = 0;//abaixo
		}
		return result;
	}
//-----------------------------------------------------------------------------------------------------

//Parte 3
//-----------------------------------------------------------------------------------------------------

typedef struct {//estrutura conjunto
  ponto ponto[1005];
	int tam;//quantidade de pontos do conjunto 
  } conjunto;

//Definindo função para adicionar o ponto P ao conjunto A
//---------------------------------------------------------------------------	
	conjunto adicionar_ponto(ponto P, conjunto A){
		A.tam += 1;
		A.ponto[A.tam] = P;	
		return A;
	}
//---------------------------------------------------------------------------


//Definindo função para testar se o ponto P pertence ao conjunto A
//---------------------------------------------------------------------------
	ponto teste_pertence(ponto P, conjunto A){
		ponto result; // result.x = 1 significa que o ponto pertence ao conjunto A e result.y = A.ponto[i].ordem		
		result = zerar_ponto(result);
		int i;
		for(i=1;i<=A.tam;i++){
			if(teste_dif_pontos(P,A.ponto[i])==0){//se os pontos P e A.ponto[i] são iguais, P pertence ao conjunto A
				result.x = 1;
				result.y = A.ponto[i].ordem;
				break;
			}
		}
		return result;
	}
//---------------------------------------------------------------------------

//Definindo função para remover um ponto P do conjunto A
//---------------------------------------------------------------------------	
	conjunto remover_ponto(ponto P, conjunto A){
		int i,n=0;
		ponto Bckp;
			for(i=1;i<=A.tam;i++){
				if(teste_dif_pontos(P,A.ponto[i])==0){//se os pontos P e A.ponto[i] são iguais, A.ponto[i] é o ponto a ser removido 
					if(i==A.tam)
						A.ponto[i] = zerar_ponto(A.ponto[i]);
					else					
						for(n=i;n<A.tam;n++){
							Bckp = A.ponto[n+1];//o ponto backup é o proximo ponto
							A.ponto[n] = Bckp;
						}
					A.tam -= 1;
				}
			}
		return A;
	}
//---------------------------------------------------------------------------

//Definindo função para unir dois conjuntos
//---------------------------------------------------------------------------
	conjunto unir_conjuntos(conjunto A, conjunto B){
		int i,j;	
		conjunto C;
			C = A;
			C.tam += B.tam;	
				for(i=A.tam+1,j=1;i<=C.tam;i++,j++)
					C.ponto[i] = B.ponto[j];
		return C;
	}
//---------------------------------------------------------------------------

//Definindo função para retirar o conjunto A do conjunto B
//---------------------------------------------------------------------------
	conjunto remover_conjunto(conjunto A, conjunto B){
		int i;
			for(i=1;i<=A.tam;i++)
				B = remover_ponto(A.ponto[i],B);
		return B;
	}
//---------------------------------------------------------------------------

//Definindo função para imprimir um conjunto
//---------------------------------------------------------------------------
	void imprimir_conjunto(char nome_do_conjunto[], conjunto A){
		if(A.tam==0)
			printf("\n\n O conjunto %s é um conjunto vazio!\n",nome_do_conjunto);
		else{
			printf("\n\n Conjunto %s (%d elementos):",nome_do_conjunto,A.tam);
			for(int i=1;i<=A.tam;i++){
				printf("\n");
					imprimir_ponto(A.ponto[i]);
	 		}	
		}
	}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------

//Parte 4
//---------------------------------------------------------------------------------------------------------------
typedef struct {//estrutura de matriz nxm
  int entrada[20][20];
  int n, m; //n = numero de linhas e m = numero de colunas
  } matriz;


//Função para zerar uma matriz (é preciso definir a ordem da matriz antes de chamar esta função)
//---------------------------------------------------------------------------
 matriz zerar_matriz(matriz A){
	int i,j;
	for(i=0;i<A.n;i++) 
		for(j=0;j<A.m;j++)
			A.entrada[i][j]=0;
	return A;	
}
//---------------------------------------------------------------------------

//Função para imprimir uma matriz
//---------------------------------------------------------------------------
 void imprimir_matriz(char nome_da_matriz[],matriz A){
	if(A.n <= 0 || A.m <= 0)
		printf("\n A matriz %s é uma matriz nula!\n",nome_da_matriz);
	else{
		int i,j;
		printf("\n Matriz %s (de ordem %dx%d):\n ",nome_da_matriz,A.n,A.m);
		for(i=0;i<A.n;i++) 
			for(j=0;j<A.m;j++){
				if(A.entrada[i][j]<10 && A.entrada[i][j]>=0)
					printf(" %d ", A.entrada[i][j]);
				else 
					printf("%d ", A.entrada[i][j]);
				if(j==A.m-1)
					printf("\n ");
			}
		printf("\n");
	}
}
//---------------------------------------------------------------------------

//Função para somar duas matrizes de mesma ordem
//---------------------------------------------------------------------------
matriz somar_matrizes(matriz A, matriz B){
	matriz C;
	if(A.n != B.n || A.m != B.m)
		printf("\n As matrizes não possuem mesma ordem para poder realizar a soma das mesmas!\n");
	else{
		int i,j;
		C = A;
		for(i=0;i<C.n;i++) 
			for(j=0;j<C.m;j++){
				C.entrada[i][j] += B.entrada[i][j];
			}
	}
return C;
}
//---------------------------------------------------------------------------

//Função para subtrair uma matriz B de uma matriz A (também deve ter a mesma ordem)
//---------------------------------------------------------------------------
matriz subtrair_matrizes(matriz A, matriz B){
matriz C;
	if(A.n != B.n || A.m != B.m)
		printf("\n As matrizes não possuem mesma ordem para poder realizar a subtração das mesmas!\n");

	else{
		int i,j;
		C = A;
		for(i=0;i<C.n;i++) 
			for(j=0;j<C.m;j++){
				C.entrada[i][j] -= B.entrada[i][j];
			}
	}
return C;
}
//---------------------------------------------------------------------------

//Função para multiplicar uma matriz por um escalar
//---------------------------------------------------------------------------
matriz x_matriz(int x, matriz A){
	int i,j;
	matriz C = A;
	for(i=0;i<C.n;i++) 
			for(j=0;j<C.m;j++){
				C.entrada[i][j] *= x; 
			}
return C;
}
//---------------------------------------------------------------------------

//Função para fazer o produto de duas matrizes
//---------------------------------------------------------------------------
matriz prod_matrizes(matriz A, matriz B){
	if(A.m != B.n)
		printf("\n Não é possível realizar o produto das matrizes!\n");

	else{
		int i,j,r;
		matriz C;
		C.n = A.n;
		C.m = B.m;
		C = zerar_matriz(C);

		for(i=0;i<C.n;i++) 
			for(j=0;j<C.m;j++)
				for(r=0;r<A.m;r++)
					C.entrada[i][j] += A.entrada[i][r]*B.entrada[r][j];
	return C;
	}
}
//---------------------------------------------------------------------------

//Função para criar uma matriz identidade de ordem n
//---------------------------------------------------------------------------
matriz criar_id_n(int n){
	int i,j;
	matriz I;
	I.n=n;
	I.m=n;
	I = zerar_matriz(I);
	
	for(i=0;i<I.n;i++) 
			for(j=0;j<I.m;j++)				
				if(i==j)
					I.entrada[i][j] = 1;				
	return I;
}
//---------------------------------------------------------------------------

//Função para calcular a transposta de uma matriz
//---------------------------------------------------------------------------
matriz transpose(matriz A){
	int i,j;
	matriz A_t;
	A_t.n = A.m;
	A_t.m = A.n;
	for(i=0;i<A_t.n;i++) 
			for(j=0;j<A_t.m;j++){
				A_t.entrada[i][j] = A.entrada[j][i];
			}
return A_t;
}
//---------------------------------------------------------------------------

//Função para trocar duas linhas de uma matriz
//---------------------------------------------------------------------------
matriz trocar_linhas(int l_i,int l_j,matriz A){
	matriz C;
	int i,j;
	i = l_i-1;
	j = l_j-1;

	if(A.n < l_i || A.n < l_j)
		printf("\n A matriz não possui estas linhas!\n");

  	else{
		int k;
		C = A;
		for(k=0;k<C.m;k++){ 
			C.entrada[i][k] = A.entrada[j][k];
			C.entrada[j][k] = A.entrada[i][k];
		}
	}
return C;
}
//---------------------------------------------------------------------------


//Função para trocar duas colunas de uma matriz
//---------------------------------------------------------------------------
matriz trocar_colunas(int c_i,int c_j,matriz A){
	matriz C;
	int i,j;
	i = c_i-1;
	j = c_j-1;

	if(A.m < c_i || A.m < c_j)
		printf("\n A matriz não possui estas colunas!\n");
	else{
		int k;
		C = A;
		for(k=0;k<C.n;k++){ 
			C.entrada[k][i] = A.entrada[k][j];
			C.entrada[k][j] = A.entrada[k][i];
		}
	}
return C;
}
//---------------------------------------------------------------------------

//Função para eliminar uma linha e uma coluna de uma matriz
//---------------------------------------------------------------------------
matriz remov_linha_coluna(int l,int c, matriz A){
	matriz C;
	if(A.n < l || A.m < c)
		printf("\n A matriz não possui esta linha ou coluna!\n");
	else{
		int g,h;
		C = A;

		for(h=0;h<C.m;h++)//zerando a linha a ser removida
					C.entrada[l-1][h] = 0;
		for(h=0;h<C.n;h++)//zerando a coluna a ser removida
					C.entrada[h][c-1] = 0;
		
		if(l == C.n && c == C.m){//a linha e coluna a serem removidas são as últimas da matriz
				//printf("\n Caso 1: a linha e coluna a serem removidas são as últimas da matriz.\n");
				C.n -= 1;	
				C.m -= 1;	
		}
		else{
			if(l != C.n && c != C.m){//a linha e a coluna a serem removidas não são as últimas da matriz
				//printf("\n Caso 2: a linha e a coluna a serem removidas não são as últimas da matriz.\n");
				for(g=l;g<=C.n-1;g++)//trocar as linhas até que a linha que se deseja remover seja a última
					C = trocar_linhas(g,g+1,C); 
				for(h=c;h<=C.m-1;h++)
					C = trocar_colunas(h,h+1,C);//trocar as colunas até que a coluna que se deseja remover seja a última			
				C.n -= 1;	
				C.m -= 1;
			}
			else
				if(l == C.n){//a linha a ser removida é a última linha (basta trocar as colunas)
					//printf("\n Caso 3: a linha a ser removida é a última linha.\n");
					for(h=c;h<=C.m-1;h++)
						C = trocar_colunas(h,h+1,C);//trocar as colunas até que a coluna que se deseja remover seja a última
					C.n -= 1;	
					C.m -= 1;	
				}
				else{ //a coluna a ser removida é a última coluna (basta trocar as linhas) 
					//printf("\n Caso 4: a coluna a ser removida é a última coluna.\n");
					for(g=l;g<=C.n-1;g++)//trocar as linhas até que a linha que se deseja remover seja a última
						C = trocar_linhas(g,g+1,C); 				
					C.n -= 1;	
					C.m -= 1;
				}
		}
	}
return C;
}
//---------------------------------------------------------------------------

//Função para calcular o Traço de uma matriz
//---------------------------------------------------------------------------
int tr(matriz A){
		int tr = 0;
		if(A.n != A.m)
			printf("\n A matriz não é uma  matriz quadrada!\n");
		else{
			int i,j;
				for(i=0;i<A.n;i++)
					for(j=0;j<A.m;j++){
						if(i == j)
							tr += A.entrada[i][j];
					}
		}	
		return tr;
}
//---------------------------------------------------------------------------

//Função para calcular (-1)^(i+j)
//---------------------------------------------------------------------------
int sinal_do_cofator(int i, int j){
	if((i+j)%2 != 0)//i+j é ímpar
		return -1;
	else//i+j é par
		return 1;
}
//---------------------------------------------------------------------------


//Função para calcular o determinante de uma matriz
//---------------------------------------------------------------------------
int det(matriz A){
	int determinante = 0;
	if(A.n != A.m)
		printf("\n A matriz não é uma  matriz quadrada!\n");
	else{
			int i,j;
			matriz A_remov;			
		if(A.n == 1)
			determinante = A.entrada[0][0];
		else{
				if(A.n == 2)
					determinante = A.entrada[0][0]*A.entrada[1][1] - A.entrada[0][1]*A.entrada[1][0];
				else
						for(i=0;i<A.n;i++){//Laplace para a coluna 1
								A_remov = remov_linha_coluna(i+1,1,A);
								determinante += A.entrada[i][0]*sinal_do_cofator(i+1,1)*det(A_remov);  
							}
		}
	}
return determinante;
}
//---------------------------------------------------------------------------

//Função para calcular a matriz dos cofatores de uma matriz
//---------------------------------------------------------------------------
matriz matriz_cofatores(matriz A){
	matriz C;
	if(A.n != A.m)
		printf("\n A matriz não é uma  matriz quadrada!\n");
	else{
		int i,j;
		matriz A_remov;
		C.n = A.n;
		C.m = A.m;
		for(i=0;i<C.n;i++)
					for(j=0;j<C.m;j++){
						A_remov = remov_linha_coluna(i+1,j+1,A);
						C.entrada[i][j] = sinal_do_cofator(i+1,j+1)*det(A_remov);
					}
	}
return C;
}
//---------------------------------------------------------------------------

//Função para calcular a adjunta de uma matriz
//---------------------------------------------------------------------------
matriz adj(matriz A){
	matriz C;
	if(A.n != A.m)
		printf("\n A matriz não é uma  matriz quadrada!\n");
	else{
			int det_A;
			det_A = det(A);
			if(det_A == 0)
				printf("\n O determinante da matriz é 0. Logo, a matriz não é inversível!\n");
			else
				C = transpose(matriz_cofatores(A)); //como a matriz é inteira, lembrar de chamar 1/det(A) na hora q for imprimir a matriz
	}
return C;
}
//---------------------------------------------------------------------------

//Definindo função somatório do valor x de i a n
//---------------------------------------------------------------------------
float sum(float x,int i,int n){
	float sum =0,r;	
	for(r=i;r<=n;r++)		
		sum += x;
return sum;
}
//---------------------------------------------------------------------------

typedef struct {//estrutura de matriz nxm com entradas reais
  float entrada[20][20];
  int n, m; //n = numero de linhas e m = numero de colunas
  } matriz_real;


//Função para imprimir uma matriz real
//---------------------------------------------------------------------------
 void imprimir_matriz_real(char nome_da_matriz[],matriz_real A){
	if(A.n <= 0 || A.m <= 0)
		printf("\n A matriz %s é uma matriz nula!\n",nome_da_matriz);
	else{
		int i,j;
		printf("\n Matriz %s (de ordem %dx%d):\n ",nome_da_matriz,A.n,A.m);
		for(i=0;i<A.n;i++) 
			for(j=0;j<A.m;j++){
				if(A.entrada[i][j]<10 && A.entrada[i][j]>=0)
					printf(" %.2f ", A.entrada[i][j]);
				else 
					printf("%.2f ", A.entrada[i][j]);
				if(j==A.m-1)
					printf("\n ");
			}
		printf("\n");
	}
}
//---------------------------------------------------------------------------

//Função para converter uma matriz inteira em uma matriz real
//---------------------------------------------------------------------------
matriz_real convert_matriz(matriz A){
	matriz_real C;
	if(A.n <= 0 || A.m <= 0)
		printf("\n A matriz é uma matriz nula!\n");
	else{
		int i,j;
		C.n = A.n;
		C.m = A.m;
		for(i=0;i<C.n;i++)
			for(j=0;j<C.m;j++)
				C.entrada[i][j]	= A.entrada[i][j];
	}
return C;
}
//---------------------------------------------------------------------------

//Função para somar a uma linha i o múltiplo de uma linha j
//---------------------------------------------------------------------------
matriz_real Li_xLj(int i, int j, float x,matriz_real A){
	matriz_real C;
	int g;
	C = A;
	for(g=0;g<A.m;g++)
			C.entrada[i][g] += x*A.entrada[j][g];
return C;
}
//---------------------------------------------------------------------------

//Função para encontrar a decomposição LU de uma matriz A (A=LU) se ela não for singular
//-----------------------------------------------------------------------------------------------
void decomp_LU(char nome_da_matriz[],matriz A){
		if(det(A) == 0)
			printf("\n A matriz %s é uma matriz singular (det = 0).\n",nome_da_matriz);
		else{
			matriz_real L,U;
			int i,j; 
			L = convert_matriz(criar_id_n(A.m)); //L inicialmente é a matriz identidade
			U = convert_matriz(A); //U inicialmente é a matriz A

			for(j=0;j<U.m-1;j++){
				for(i=j+1;i<U.n;i++){
						//imprimir_matriz_real("U",U);
						L.entrada[i][j] = U.entrada[i][j]/U.entrada[j][j];	
						//printf("\n L.entrada[%d][%d] = %.1f",i,j,L.entrada[i][j]);
						U = Li_xLj(i,j,-L.entrada[i][j],U);
				}
			}	
			printf("\n Decomposição LU \n %s = LU, onde\n",nome_da_matriz);
			imprimir_matriz(nome_da_matriz,A);
			imprimir_matriz_real("L",L);
			printf(" e\n");
			imprimir_matriz_real("U",U);
		}
}
//-----------------------------------------------------------------------------------------------

//Parte 5
//---------------------------------------------------------------------------------------------------------------
typedef struct {//estrutura de polinomios de até grau 4 para produto e de até grau 8 para soma.
  int coef[9];
  int gr;
  } pol;

//Anulando um polinômio
//---------------------------------------------------------------------------
//Depois de declarar um polinômio, antes de declarar seu grau e seus coeficientes, é necessário anular ele para que não haja erros.
pol anular_pol(pol P){
	P.gr = 0;
	for(int i=0;i<9;i++)
		P.coef[i] = 0;
return P;
}
//---------------------------------------------------------------------------

//Impressão de um polinômio
//---------------------------------------------------------------------------
void imprimir_pol(char nome_do_polinomio[], pol P){

	printf("\n %s(x) = ",nome_do_polinomio);
	for(int i=P.gr;i>=0;i--){
		if(P.coef[i]==0){
				if(P.coef[i-1]>0)	
					printf(" +");		
			}

		else{
			if(i>0 && P.coef[i]!=0){
					if(P.coef[i-1]>0)
						if(i!=1)	
							printf(" %d.x^%d +",P.coef[i],i);
						else							
							printf(" %d.x +",P.coef[i]);
					
					else
							if(i!=1)
								printf(" %d.x^%d",P.coef[i],i);
							else
								printf(" %d.x",P.coef[i]);					
				}
			else
					if(P.coef[i]!=0)
						printf(" %d \n",P.coef[i]);	
		}
	}
		if(P.coef[0]==0)
			printf("\n");
}
//---------------------------------------------------------------------------

//Adição entre dois polinômios
//---------------------------------------------------------------------------
pol somar_pols(pol P, pol Q){
	pol S;
	S = anular_pol(S);
	S.gr=maximo(P.gr,Q.gr);
	for(int i=0;i<=S.gr;i++)
		S.coef[i] = P.coef[i] + Q.coef[i];
return S;
}
//---------------------------------------------------------------------------

//Subtração entre dois polinômios
//---------------------------------------------------------------------------
pol subtrair_pols(pol P, pol Q){
	pol S;
	S = anular_pol(S);
		if((P.gr == Q.gr) && (P.coef[P.gr] == Q.coef[Q.gr]))
			S.gr = P.gr - 1;
		else
			S.gr = maximo(P.gr,Q.gr);

	for(int i=0;i<=S.gr;i++)
		S.coef[i] = P.coef[i] - Q.coef[i];

return S;
}
//---------------------------------------------------------------------------

//Produto de dois polinômios
//---------------------------------------------------------------------------
pol produto_pols(pol P, pol Q){
	int i,j,k;	
	pol S;
	S = anular_pol(S);
	S.gr=P.gr+Q.gr;
	
for(k=0;k<=S.gr;k++)
	for(i=0;i<=P.gr;i++){
		for(j=0;j<=Q.gr;j++){
			if((i+j) == k){
					S.coef[k] += P.coef[i]*Q.coef[j]; 
			}
	}
}
return S;
}
//---------------------------------------------------------------------------

typedef struct {//estrutura que contem dois polinômios. Para ser trabalhado com divisão de polinômios. A ideia é retornar o quociente e o resto.
  pol Quociente;
	pol Resto;
  } pol_2;

//Divisão de dois polinômios
//---------------------------------------------------------------------------
pol_2 divisao_pols(pol P, pol Q){
	pol_2 Resultado;
pol P_1, S, R, Aux, Aux_1;
	int entrada = 1;
	
	P_1 = anular_pol(P_1);
	P_1 = P;	
	
	S = anular_pol(S);
	R = anular_pol(R);
	Aux = anular_pol(Aux);

	S.gr = P_1.gr - Q.gr;

	while(entrada != 0){
		entrada = P_1.gr - Q.gr;
		S.coef[entrada] = P_1.coef[P_1.gr]/Q.coef[Q.gr];
			
		Aux_1 = anular_pol(Aux_1);	
		Aux_1.gr = entrada;
		Aux_1.coef[entrada] = S.coef[entrada]; 		

		Aux = produto_pols(Aux_1,Q); 
	
		P_1 = subtrair_pols(P_1,Aux);
	}
	//P_1 agora é o resto. Ou seja, P = S.Q + P_1
	Resultado.Quociente = S;
	Resultado.Resto = P_1;	

return Resultado;
}
//---------------------------------------------------------------------------

//Polinômio Módulo (x-1)
//---------------------------------------------------------------------------
pol pol_mod(pol P){
	pol Q;
	pol_2 Resultado;

	Q = anular_pol(Q);
	Q.gr = 1;

	Q.coef[0] = -1;
	Q.coef[1] = 1;
	
	Resultado = divisao_pols(P,Q);

	return Resultado.Resto;
	



}

//---------------------------------------------------------------------------
