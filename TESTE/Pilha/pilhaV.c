#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "pilhaV.h"
#include "tipos.h"
#include "erro.h"

extern pilhaV_t * pilhaV_criar(uint32_t capacidade){
	pilhaV_t * pilha = (pilhaV_t *) malloc(sizeof(pilhaV_t));
	pilhaV_inicializar(pilha, capacidade);
	return pilha;
}

extern void pilhaV_inicializar(pilhaV_t * pilha, uint32_t capacidade){
	pilha->nItens = 0;
	pilha->capacidade = capacidade;
	pilha->itens = malloc(capacidade * sizeof(dados_t));
}

extern void pilhaV_excluir(pilhaV_t * pilha){
	free(pilha->itens);
	free(pilha);
}

extern boolean_t pilhaV_estaVazia(pilhaV_t * pilha){
    return (pilha->nItens == 0 ? VERDADEIRO : FALSO);
}

extern erro_t pilhaV_empilha(pilhaV_t * pilha, dados_t dados){
	dados_t * itens = pilha->itens;

	if(pilha->nItens >= pilha->capacidade) return ERRO_PILHA_CHEIA;

	itens[pilha->nItens++] = dados;

	return SUCESSO;
}

extern erro_t pilhaV_desempilha(pilhaV_t * pilha, dados_t * info){
	dados_t * itens = pilha->itens;

	if(pilhaV_estaVazia(pilha) == VERDADEIRO) return ERRO_PILHA_VAZIA;

	--pilha->nItens;
	memcpy(info, itens + pilha->nItens, sizeof(dados_t));
	return SUCESSO;
}

extern erro_t pilhaV_topo(pilhaV_t * pilha, dados_t * info){
	dados_t * itens = pilha->itens;

	if(pilhaV_estaVazia(pilha) == VERDADEIRO) return ERRO_PILHA_VAZIA;

	memcpy(info, itens + (pilha->nItens - 1), sizeof(dados_t));
}

extern boolean_t pilhaV_buscar(pilhaV_t * pilha, dados_t info, uint32_t * posicao){
	uint32_t pos;
	boolean_t achou;
	dados_t * itens = pilha->itens;

	for(pos = pilha->nItens - 1; pos < pilha->nItens; pos--){
		achou = (itens[pos].valor == info.valor);
		if(achou == VERDADEIRO) break;
	}

	if(achou != VERDADEIRO) return ERRO_PILHA_ITEM_NAO_ENCONTRADO;

	*posicao = pilha->nItens - pos - 1;
	return SUCESSO;
}

extern void pilhaV_imprimir(pilhaV_t * pilha){
    dados_t * itens = pilha->itens;
    uint32_t pos;

    printf("Impressao de Pilha em formato de Vetor\n");

    for(pos = pilha->nItens - 1; pos < pilha->nItens; pos--){
    	printf("Pos: %u / Valor: %f\n", pilha->nItens - pos - 1, itens[pos].valor);
    }
    printf("\n\n");
}