#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "erro.h"
#include "filaDE.h"
#include "tipos.h"

/* Fila */
filaDE_t * filaDE_criar(uint32_t capacidade){
	filaDE_t * fila = (filaDE_t *) malloc(sizeof(filaDE_t));
	filaDE_inicializar(fila, capacidade);
	return fila;
}

void filaDE_inicializar(filaDE_t * fila, uint32_t capacidade){
	fila->vetor = (dados_t *) malloc(capacidade * sizeof(dados_t));
	fila->nItens = 0;
	fila->inicio = 0;
	fila->ultimo = 0;
	fila->capacidade = capacidade;
}

void filaDE_excluir(filaDE_t * fila){
	free(fila->vetor);
	free(fila);
}

boolean_t filaDE_estaVazia(filaDE_t * fila){
	return fila->nItens == 0 ? VERDADEIRO : FALSO;
}

uint32_t filaDE_posicaoAbsoluta(filaDE_t * fila, uint32_t indice){
	return (fila->inicio + indice) % fila->capacidade;
}

uint32_t filaDE_proximaPosicao(filaDE_t * fila, uint32_t indice){
	return (indice + 1) % fila->capacidade;
} 

uint32_t filaDE_posicaoAnterior(filaDE_t * fila, uint32_t indice){
	if(indice == 0) return fila->capacidade - 1;
	else return indice -1;
}

erro_t filaDE_insereFinal(filaDE_t * fila, dados_t dados){
	if(fila->nItens == fila->capacidade) return ERRO_FILA_CHEIA;
	dados_t * itens = fila->vetor;
	itens[fila->ultimo] = dados;
	fila->ultimo = filaDE_proximaPosicao(fila, fila->ultimo);
	fila->nItens++;
	return SUCESSO;
}

erro_t filaDE_insereInicio(filaDE_t * fila, dados_t dados){
	if(fila->nItens == fila->capacidade) return ERRO_FILA_CHEIA;
	dados_t * itens = fila->vetor;

	fila->inicio = filaDE_posicaoAnterior(fila, fila->inicio);
	itens[fila->inicio] = dados;
	fila->nItens++;
	return SUCESSO;
}

erro_t filaDE_removeInicio(filaDE_t * fila, dados_t * valorPerdido){
	if(filaDE_estaVazia(fila) == VERDADEIRO) return ERRO_FILA_VAZIA;
	dados_t * itens = fila->vetor;

	*valorPerdido = itens[fila->inicio];
	memcpy(valorPerdido, &itens[fila->inicio], sizeof(dados_t));

	fila->inicio = filaDE_proximaPosicao(fila, fila->inicio);
	fila->nItens--;
	return SUCESSO;
}

erro_t filaDE_removeFinal(filaDE_t * fila, dados_t * valorPerdido){
	dados_t * itens = fila->vetor;
	fila->ultimo = filaDE_posicaoAnterior(fila, fila->ultimo);
	*valorPerdido = itens[fila->ultimo];
	memcpy(valorPerdido, &itens[fila->ultimo], sizeof(dados_t));
	fila->nItens--;
	return SUCESSO;
}

void filaDE_imprimir(filaDE_t * fila){
	dados_t * itens = fila->vetor;
	for(int i = 0; i < fila->nItens; i++){
		printf("Pos: %u | Dados: %f\n", i, itens[filaDE_posicaoAbsoluta(fila, i)].valor);
	}
}