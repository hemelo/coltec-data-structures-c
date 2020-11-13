#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "erro.h"
#include "filaV.h"
#include "tipos.h"

/* Fila */
filaV_t * filaV_criar(uint32_t capacidade){
	filaV_t * fila = (filaV_t *) malloc(sizeof(filaV_t));
	filaV_inicializar(fila, capacidade);
	return fila;
}

void filaV_inicializar(filaV_t * fila, uint32_t capacidade){
	fila->vetor = (dados_t *) malloc(capacidade * sizeof(dados_t));
	fila->nItens = 0;
	fila->inicio = 0;
	fila->ultimo = 0;
	fila->capacidade = capacidade;
}

void filaV_excluir(filaV_t * fila){
	free(fila->vetor);
	free(fila);
}

boolean_t filaV_estaVazia(filaV_t * fila){
	return fila->nItens == 0 ? VERDADEIRO : FALSO;
}

uint32_t filaV_posicaoAbsoluta(filaV_t * fila, uint32_t indice){
	return (fila->inicio + indice) % fila->capacidade;
}

uint32_t filaV_proximaPosicao(filaV_t * fila, uint32_t indice){
	return (indice + 1) % fila->capacidade;
} 

erro_t filaV_insere(filaV_t * fila, dados_t dados){
	if(fila->nItens == fila->capacidade) return ERRO_FILA_CHEIA;
	dados_t * itens = fila->vetor;
	itens[fila->ultimo] = dados;
	fila->ultimo = filaV_proximaPosicao(fila, fila->ultimo);
	fila->nItens++;
	return SUCESSO;
}

erro_t filaV_remove(filaV_t * fila, dados_t * valorPerdido){
	if(filaV_estaVazia(fila) == VERDADEIRO) return ERRO_FILA_VAZIA;
	dados_t * itens = fila->vetor;

	*valorPerdido = itens[fila->inicio];
	memcpy(valorPerdido, &itens[fila->inicio], sizeof(dados_t));

	fila->inicio = filaV_proximaPosicao(fila, fila->inicio);
	fila->nItens--;
	return SUCESSO;
}

void filaV_imprimir(filaV_t * fila){
	dados_t * itens = fila->vetor;
	for(int i = 0; i < fila->nItens; i++){
		printf("Pos: %u | Dados: %f\n", i, itens[filaV_posicaoAbsoluta(fila, i)].valor);
	}
}