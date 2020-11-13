#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "filaLE.h"
#include "tipos.h"
#include "erro.h"

filaLE_t * filaLE_criar(){
	filaLE_t * fila = (filaLE_t *) malloc(sizeof(filaLE_t));
	filaLE_inicializar(fila);
	return fila;
}

void filaLE_inicializar(filaLE_t * fila){
	fila->nItens = 0;
	fila->inicio = NULL;
	fila->fim = NULL;
}

void filaLE_excluir(filaLE_t * fila){
	itemFila_t * refAnterior;
	itemFila_t * ref = fila->inicio;

	while(ref != NULL){
		refAnterior = ref;
		ref = ref->proximoItem;

		free(refAnterior);
	}
	free(fila);
}

boolean_t filaLE_estaVazia(filaLE_t * fila){
	return fila->nItens == 0 ? VERDADEIRO : FALSO;
}

erro_t filaLE_insere(filaLE_t * fila, dados_t dados){
	itemFila_t * novoItem = (itemFila_t *) malloc(sizeof(itemFila_t));
	novoItem->dados = dados;
	novoItem->proximoItem = NULL;


	if(filaLE_estaVazia(fila) == VERDADEIRO){
		fila->inicio = novoItem;
	}
	else{
		fila->fim->proximoItem = novoItem;
	}

	fila->nItens++;
	fila->fim = novoItem;
	return SUCESSO;
}

erro_t filaLE_remove(filaLE_t * fila, dados_t * valorPerdido){
	itemFila_t * remover;

	if(filaLE_estaVazia(fila) == VERDADEIRO) return ERRO_FILA_VAZIA;

	remover = fila->inicio;
	fila->inicio = remover->proximoItem;

	if(fila->inicio == NULL)
		fila->fim = NULL;

	*valorPerdido = remover->dados;
	free(remover);
	fila->nItens--;
	return SUCESSO;
}

itemFila_t * filaLE_buscar(filaLE_t * fila){

}

void filaLE_imprimir(filaLE_t * fila){
	itemFila_t * percorre = fila->inicio;
	uint32_t pos;

	for(pos = 0; pos < fila->nItens; pos++){
    	printf("Pos: %u / Valor: %f\n", pos, (percorre->dados).valor);
    	percorre = percorre->proximoItem;
    }
}