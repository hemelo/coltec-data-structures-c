#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DESCRICAO_TAMANHO_MAXIMO 50

typedef struct ingrediente_s {
	uint16_t codigo;
	char descricao[DESCRICAO_TAMANHO_MAXIMO];
}ingrediente_t;

// Vetor Original

static const ingrediente_t INGREDIENTES[] = {
	{ 8885, "Tomate Sem Toxico"},
	{ 1985, "Queijo Mucarela"},
	{ 1907, "Manjericao"},
	{ 1410, "Farinha de Trigo"},
	{ 1720, "Batata"}
};
	


void bemVindo();
void ** alocaMatriz();
ingrediente_t * alocaVetor();
void preencheMatriz();
void imprimeVetor();
void imprimeMatriz();
void liberaMatriz();
ingrediente_t * ordenaVetor();
void ordenaMatriz();

int main()
{
	void ** matriz = NULL;
	void ** matrizCopia = NULL;
	ingrediente_t * vetorCopia = NULL;

	// bem vindo
	bemVindo();
	
	// Alocação e Preenchimento de matriz Original

	matriz = alocaMatriz(matriz);
	preencheMatriz(matriz, INGREDIENTES);

	// Alocação e Preenchimento de vetor Cópia

	vetorCopia = alocaVetor(vetorCopia);

	// Alocação e Preenchimento de matriz Cópia

	matrizCopia = alocaMatriz(matrizCopia);
	preencheMatriz(matrizCopia, vetorCopia);

	// Ordena Vetor e Matriz Cópia

	vetorCopia = ordenaVetor(vetorCopia);
	ordenaMatriz(matrizCopia);

	// Compara Impressão de Vetor e Matriz originais

	printf("\nVetor Original\n");
	imprimeVetor(INGREDIENTES);
	printf("\nMatriz Original\n");
	imprimeMatriz(matriz);
	
	// Compara Impressão de Vetor e Matriz ordenadas

	printf("\nVetor Ordenado\n");
	imprimeVetor(vetorCopia);
	printf("\nMatriz Ordenada\n");
	imprimeMatriz(matrizCopia);

	// Libera Memória

	liberaMatriz(matriz);
	liberaMatriz(matrizCopia);
	free(vetorCopia);

	return 0;
}

void** alocaMatriz(void **matriz)
{
	// Indireção Múltipla
	matriz = malloc(sizeof(int *) + sizeof(const char *));
	matriz[0] = malloc(NUMERO_INGREDIENTES * sizeof(int));
	matriz[1] = malloc(NUMERO_INGREDIENTES * sizeof(char *));
	return(matriz);
}

void preencheMatriz(void ***matriz, ingrediente_t * dadosIngrediente)
{
	uint16_t i;
	for (i = 0; i < NUMERO_INGREDIENTES; i++) 
	{
		((int*) matriz[0])[i] = dadosIngrediente[i].codigo;
		((const char**) matriz[1])[i] = dadosIngrediente[i].descricao;
	}	
}

void imprimeVetor(ingrediente_t *vetor)
{
	uint16_t i;
	printf("\nCodigo - Ingrediente (Vetor)\n");

	for(i=0; i<NUMERO_INGREDIENTES; i++)
		printf("%d - %s\n", vetor[i].codigo, vetor[i].descricao);
}

void imprimeMatriz(void ***matriz)
{
	uint16_t i;
	printf("\nCodigo - Ingrediente (Matriz)\n");
	
	for(i=0; i<NUMERO_INGREDIENTES; i++)
		printf("%d - %s\n", ((int*) matriz[0])[i], ((const char**) matriz[1])[i]);
}

ingrediente_t * alocaVetor(ingrediente_t * vetorCopia)
{
	vetorCopia = (ingrediente_t *) malloc(sizeof(INGREDIENTES));
 	memcpy(vetorCopia, INGREDIENTES, sizeof(INGREDIENTES));
	return(vetorCopia);
}

ingrediente_t * ordenaVetor(ingrediente_t * vetorOrdenado)
{
	char temp[DESCRICAO_TAMANHO_MAXIMO];
	uint16_t temp2;
	uint16_t i, j;

	vetorOrdenado = (ingrediente_t *) malloc(sizeof(INGREDIENTES));
 	memcpy(vetorOrdenado, INGREDIENTES, sizeof(INGREDIENTES));

	for(j=0; j<NUMERO_INGREDIENTES-1; j++)
	{
		for(i=0; i<NUMERO_INGREDIENTES-1; i++)
		{
			if(strcmp(vetorOrdenado[i].descricao, vetorOrdenado[i+1].descricao) > 0)
			{
				strcpy(temp, vetorOrdenado[i].descricao);
				strcpy(vetorOrdenado[i].descricao, vetorOrdenado[i+1].descricao);
				strcpy(vetorOrdenado[i+1].descricao, temp);
				temp2 = vetorOrdenado[i].codigo;
				vetorOrdenado[i].codigo = vetorOrdenado[i+1].codigo;
				vetorOrdenado[i+1].codigo=temp2;
			}
		}
	}
	return(vetorOrdenado);
}

void ordenaMatriz(void ***matrizOrdenada)
{
	char temp[DESCRICAO_TAMANHO_MAXIMO];
	int temp2;
	uint16_t i, j;

	for(j=0; j<NUMERO_INGREDIENTES-1; j++)
	{
		for(i=0; i<NUMERO_INGREDIENTES-1; i++)
		{
			if(strcmp(((char**) matrizOrdenada[1])[i], ((char**) matrizOrdenada[1])[i+1]) > 0)
			{
				strcpy(temp, ((char**) matrizOrdenada[1])[i]);
				strcpy(((char**) matrizOrdenada[1])[i], ((char**) matrizOrdenada[1])[i+1]);
				strcpy(((char**) matrizOrdenada[1])[i+1], temp);
				temp2 = ((int*) matrizOrdenada[0])[i];
				((int*) matrizOrdenada[0])[i] = ((int*) matrizOrdenada[0])[i+1];
				((int*) matrizOrdenada[0])[i+1] = temp2;
			}
		}
	}
}

void liberaMatriz(void ***matriz)
{
	int i;

	for(i=0; i<2; i++)
		free(matriz[i]);

	free(matriz);
}

void bemVindo(){
	printf(" ___________________________________\n"
		   "|                                   |\n"
		   "|        Exercicio de Revisao       |\n"
		   "|         Henrique Fernandes        |\n"
		   "|___________________________________|\n\n");
}
