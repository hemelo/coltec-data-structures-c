#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include "pilhaES.h"
#include "pilhaV.h"
#include "tipos.h"
#include "erro.h"

#define TAMANHO_VETOR_DADOS 6
#define TAMANHO_VETOR_PILHA 6

// Número de elementos que vão ser empilhados em sequência
#define EMPILHAR            3

// Vetor de Struct Global que contém Dados para serem utilizados nos teste
dados_t dados[TAMANHO_VETOR_DADOS];

void header(){
	printf("+---------------------------------------------------------------------------------+\n");
}

boolean_t testePilhaLista(){
	erro_t erro;
	dados_t info;
	uint32_t posicao;

	header();

	// Criar pilha e inicia-la vazia
	pilha_t * pilha = pilha_criar();

	// Imprime pilha vazia
	//pilha_imprimir(pilha);

	// Empilha Elementos
	for(int i = 0; i < EMPILHAR; i++){
		info = dados[i];
		erro = pilha_empilha(pilha, info);
		if(erro != SUCESSO) { 
			printf("Erro: %u\n", erro);
			return ERRO;
		}
	}

	// Imprime pilha preenchida
	pilha_imprimir(pilha);

	// Desempilha Elemento
	erro = pilha_desempilha(pilha, &info);
	if(erro != SUCESSO){
		printf("Erro: %u\n", erro);
		return ERRO;
	}
	else{
		printf("Foi desempilhado: %f\n\n", info.valor);
	}

	// Empilha mais um elemento
	erro = pilha_empilha(pilha, dados[TAMANHO_VETOR_DADOS - 1]);
	if(erro != SUCESSO){
		printf("Erro: %u\n", erro);
		return ERRO;
	}

	// Imprime pilha após inserções e remoções 
	pilha_imprimir(pilha);

	// Limpar a pilha da memória	
	pilha_excluir(pilha);

	header();
	return SUCESSO; 
}

boolean_t testePilhaVetor(){
	erro_t erro;
	dados_t info;
	uint32_t posicao;

	header();

	// Criar pilha e inicia-la vazia
	pilhaV_t * pilha = pilhaV_criar(TAMANHO_VETOR_PILHA);

	// Imprime pilha vazia
	pilhaV_imprimir(pilha);

	// Empilha Elementos
	for(int i = 0; i < EMPILHAR; i++){
		info = dados[i];
		erro = pilhaV_empilha(pilha, info);
		if(erro != SUCESSO) { 
			printf("Erro: %u\n", erro);
			return ERRO;
		}
	}

	// Imprime pilha preenchida
	pilhaV_imprimir(pilha);

	// Desempilha Elemento
	erro = pilhaV_desempilha(pilha, &info);
	if(erro != SUCESSO){
		printf("Erro: %u\n", erro);
		return ERRO;
	}
	else{
		printf("Foi desempilhado: %f\n\n", info.valor);
	}

	// Empilha mais Elementos
	erro = pilhaV_empilha(pilha, dados[TAMANHO_VETOR_DADOS - 1]);
	if(erro != SUCESSO) { 
		printf("Erro: %u\n", erro);
		return ERRO;
	}

	//testar = pilhaV_buscar(pilha, dados[2], &posicao);

	// Imprime pilha após inserções e remoções 
	pilhaV_imprimir(pilha);

	// Limpar a pilha da memória	
	pilhaV_excluir(pilha);

	header();
	return SUCESSO; 
}

int main(int argc, char **argv){
	// Resultado do teste
	boolean_t resultado;

	// Preenche Vetor com Valores para testar as funções: Empilhar e Buscar
	for(int i = 0; i < TAMANHO_VETOR_DADOS; i++){
		dados[i].valor = i;	
	}

	resultado = testePilhaVetor();
	printf("Teste de Pilha Vetor funcionou? %s\n", resultado ? "ERRO" : "SUCESSO");
	resultado = testePilhaLista();
	printf("Teste de Pilha em Lista funcionou? %s\n", resultado ? "ERRO" : "SUCESSO");
	system("pause");
	return 0;
}


