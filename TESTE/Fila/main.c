#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "filaLE.h"
#include "filaV.h"
#include "filaDE.h"
#include "tipos.h"
#include "erro.h"

#define TAMANHO_VETOR_DADOS 6
#define TAMANHO_VETOR_FILA 6

// Número de elementos que vão ser enfileirados em sequência
#define ENFILEIRAR 4

// Vetor de Struct Global que contém Dados para serem utilizados nos teste
dados_t dados[TAMANHO_VETOR_DADOS];

void header(){
	printf("+---------------------------------------------------------------------------------+\n");
}

boolean_t testeFilaLista(){
	erro_t erro;
	dados_t info;
	uint32_t posicao;

	header();

	// Criar fila e inicia-la vazia
	filaLE_t * fila = filaLE_criar();

	// Imprime fila vazia
	filaLE_imprimir(fila);

	// Enfileira Elementos
	for(int i = 0; i < ENFILEIRAR; i++){
		info = dados[i];
		erro = filaLE_insere(fila, info);
		if(erro != SUCESSO) { 
			printf("Erro: %u\n", erro);
			return ERRO;
		}
	}

	// Imprime Fila preenchida
	filaLE_imprimir(fila);

	// Tirar Elemento da Fila
	erro = filaLE_remove(fila, &info);
	if(erro != SUCESSO){
		printf("Erro: %u\n", erro);
		return ERRO;
	}
	else{
		printf("Foi removido: %f\n\n", info.valor);
	}

	// Adicionar Elemento da Fila
	erro = filaLE_insere(fila, dados[TAMANHO_VETOR_DADOS - 1]);
	if(erro != SUCESSO){
		printf("Erro: %u\n", erro);
		return ERRO;
	}

	// Imprime fila após inserções e remoções 
	filaLE_imprimir(fila);

	// Limpar a fila da memória	
	filaLE_excluir(fila);

	header();
	return SUCESSO; 
}

boolean_t testeFilaVetor(){
	erro_t erro;
	dados_t info;
	uint32_t posicao;

	header();

	// Criar fila e inicia-la vazia
	filaV_t * fila = filaV_criar(TAMANHO_VETOR_FILA);

	// Imprime fila vazia
	filaV_imprimir(fila);

	// Enfileira Elementos
	for(int i = 0; i < ENFILEIRAR; i++){
		info = dados[i];
		erro = filaV_insere(fila, info);
		if(erro != SUCESSO) { 
			printf("Erro: %u\n", erro);
			return ERRO;
		}
	}

	// Imprime fila preenchida
	filaV_imprimir(fila);

    // Tirar Elemento da Fila
	erro = filaV_remove(fila, &info);
	if(erro != SUCESSO){
		printf("Erro: %u\n", erro);
		return ERRO;
	}
	else{
		printf("Foi desenfileirado: %f\n\n", info.valor);
	}

	// Enfileira mais Elementos
	erro = filaV_insere(fila, dados[TAMANHO_VETOR_DADOS - 1]);
	if(erro != SUCESSO){ 
		printf("Erro: %u\n", erro);
		return ERRO;
	}

	//testar = filaV_buscar(pilha, dados[2], &posicao);

	// Imprime fila após inserções e remoções 
	filaV_imprimir(fila);

	// Limpar a fila da memória	
	filaV_excluir(fila);

	header();
	return SUCESSO; 
}

boolean_t testeFilaDupla(){
	erro_t erro;
	dados_t info;
	uint32_t posicao;

	header();

	// Criar fila e inicia-la vazia
	filaDE_t * fila = filaDE_criar(TAMANHO_VETOR_FILA);

	// Imprime fila vazia
	filaDE_imprimir(fila);

	// Enfileira Elementos
	for(int i = 0; i < ENFILEIRAR; i++){
		info = dados[i];
		erro = filaDE_insereInicio(fila, info);
		if(erro != SUCESSO) { 
			printf("Erro: %u\n", erro);
			return ERRO;
		}
	}

	// Imprime fila preenchida
	filaDE_imprimir(fila);

    // Tirar Elemento da Fila
	erro = filaDE_removeInicio(fila, &info);
	if(erro != SUCESSO){
		printf("Erro: %u\n", erro);
		return ERRO;
	}
	else{
		printf("Foi desenfileirado: %f\n\n", info.valor);
	}

	// Enfileira mais Elementos
	erro = filaDE_insereFinal(fila, dados[TAMANHO_VETOR_DADOS - 1]);
	if(erro != SUCESSO){ 
		printf("Erro: %u\n", erro);
		return ERRO;
	}

	//testar = filaDE_buscar(pilha, dados[2], &posicao);

	// Imprime fila após inserções e remoções 
	filaDE_imprimir(fila);

	// Limpar a fila da memória	
	filaDE_excluir(fila);

	header();
	return SUCESSO; 
}

// Função que o Grande Ivo Nascimento me emprestou

void pressioneEnterParaContinuar(){
    printf("Pressione ENTER para continuar");
    setbuf(stdin, NULL);
    getchar();
}

int main(int argc, char **argv){
	// Resultado do teste
	boolean_t resultado;

	// Preenche Vetor com Valores para testar as funções: Empilhar e Buscar
	for(int i = 0; i < TAMANHO_VETOR_DADOS; i++){
		dados[i].valor = i;	
	}

	resultado = testeFilaVetor();
	printf("Teste de Fila Vetor funcionou? %s\n", resultado ? "ERRO" : "SUCESSO");
	resultado = testeFilaLista();
	printf("Teste de Fila em Lista funcionou? %s\n", resultado ? "ERRO" : "SUCESSO");
	resultado = testeFilaDupla();
	printf("Teste de Fila em Vetor Duplamente Encadeado funcionou? %s\n", resultado ? "ERRO" : "SUCESSO");
	pressioneEnterParaContinuar();
	return 0;
}