#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "filaLE.h"
#include "../erro.h"
#include "../dados.h"
#include "../tipos.h"

static uint8_t toCompare(dados_t dados_um, dados_t dados_dois){
    return (dados_um - dados_dois);
}

static void filaES_inicializa(filaES_t * fila){
    fila->itens = 0;
    fila->inicio = NULL;
    fila->fim = NULL;
}

filaES_t * filaES_criar(void){
    filaES_t * fila = (filaES_t *) malloc(sizeof(filaES_t));
    filaES_inicializa(fila);
    return fila;
}

bool_t filaES_estaVazia(filaES_t * fila){
    return (fila->itens == 0 ? VERDADEIRO : FALSO);
}

void filaES_destroi(filaES_t * fila){
    itemFila_t * anterior;
    itemFila_t * atual = (itemFila_t *) fila->inicio;

    while(atual != NULL){
        anterior = atual;
        atual = atual->proximo;
        free(anterior);
    }
    free(fila);
}

erro_t filaES_insere(filaES_t * fila, dados_t dados){
	itemFila_t * novo = (itemFila_t *) malloc(sizeof(itemFila_t));

    if(novo == NULL)
        return ERRO_ALOCACAO;

	novo->dados = dados;
	novo->proximo = NULL;

	if(filaES_estaVazia(fila) == VERDADEIRO){
		fila->inicio = novo;
	}
	else{
		fila->fim->proximo = novo;
	}

	fila->fim = novo;
    fila->itens = fila->itens + 1;

	return SUCESSO;
}

erro_t filaES_remove(filaES_t * fila, dados_t * dados){
	itemFila_t * remover;

	if(filaES_estaVazia(fila) == VERDADEIRO) 
        return ESTRUTURA_VAZIA;

	remover = fila->inicio;
	fila->inicio = remover->proximo;

	if(fila->inicio == NULL)
		fila->fim = NULL;

	*dados = remover->dados;
	free(remover);

	fila->itens = fila->itens - 1;

	return SUCESSO;
}

bool_t filaES_buscar(filaES_t * fila, dados_t dado, uint32_t * posicao){
    *posicao = 0;
    itemFila_t * atual = (itemFila_t *) fila->inicio;

    comparaDados_f compare_f = toCompare;

    while(atual != NULL){
        if(compare_f(atual->dados, dado) == 0)
            break;

        atual = atual->proximo;
        (*posicao) = (*posicao) + 1;
    }

    if(atual == NULL)
        return FALSO;

    return VERDADEIRO;
}

void filaES_imprime(filaES_t * fila){
    itemFila_t * atual;
    itemFila_t * proximo = fila->inicio;

    printf("Fila com %u item(s)\n", fila->itens);
    printf("----- Impressao da Fila -----");

    for(uint32_t i = 0; i < fila->itens; i = i + 1){
        atual = proximo;
        proximo = atual->proximo;

        printf("Posicao: %u /  Dado: %u", i, atual->dados);
    }

    printf("------ Fim da Impressao ------");
}