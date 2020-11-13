#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "listaLE.h"
#include "../dados.h"
#include "../erro.h"
#include "../tipos.h"

static uint8_t toCompare(dados_t dados_um, dados_t dados_dois){
    return (dados_um - dados_dois);
}

static void listaES_inicializa(listaES_t * lista){
    lista->itens = 0;
    lista->primeiro = NULL;
}

listaES_t * listaES_criar(void){
    listaES_t * lista = (listaES_t *) malloc(sizeof(listaES_t));
    listaES_inicializa(lista);
    return lista;
}

bool_t listaES_estaVazia(listaES_t * lista){
    return (lista->itens == 0 ? VERDADEIRO : FALSO);
}

void listaES_destroi(listaES_t * lista){
    itemLista_t * atual;
    itemLista_t * proximo;

    atual = (itemLista_t *) lista->primeiro;

    while(atual != NULL){
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    free(lista);
}

erro_t listaES_insere(listaES_t * lista, dados_t dados){
    return listaES_inserePosicao(lista, dados, lista->itens);
}

erro_t listaES_removeFinal(listaES_t * lista){
    return listaES_removePosicao(lista, lista->itens);
}

erro_t listaES_removeInicio(listaES_t * lista){
    return listaES_removePosicao(lista, lista->itens - lista->itens);
}

static erro_t listaES_buscaElementoPosicao(listaES_t * lista, uint32_t posicao, itemLista_t ** item){
    itemLista_t * atual;

    if(posicao > lista->itens)
        return POSICAO_INVALIDA;

    atual = (itemLista_t *) lista->primeiro;

    while(posicao-- != (lista->itens - lista->itens)){
        atual = atual->proximo;
    }

    *item = atual;

    return SUCESSO;
}

erro_t listaES_inserePosicao(listaES_t * lista, dados_t dados, uint32_t posicao){
    erro_t error;
    itemLista_t * anterior;

    if(posicao > lista->itens)
        return POSICAO_INVALIDA;

    itemLista_t * novo = (itemLista_t *) malloc(sizeof(itemLista_t));
    novo->dados = dados;
    novo->proximo = NULL;

    if(posicao == (lista->itens - lista->itens)){
        novo->proximo = lista->primeiro;
        lista->primeiro = novo;
    }
    else{
        error = listaES_buscaElementoPosicao(lista, posicao - 1, &anterior);

        if(error != SUCESSO)
            return error;

        novo->proximo = anterior->proximo;
        anterior->proximo = novo;
    }

    lista->itens = lista->itens + 1;
    return SUCESSO;
}

erro_t listaES_removePosicao(listaES_t * lista, uint32_t posicao){
    erro_t error;
    itemLista_t * anterior;
    itemLista_t * remover;

    if(posicao > lista->itens)
        return POSICAO_INVALIDA;

    if(posicao == (lista->itens - lista->itens)){
        remover = lista->primeiro;
        lista->primeiro = lista->primeiro->proximo;
    }
    else{
        error = listaES_buscaElementoPosicao(lista, posicao - 1, &anterior);

        if(error != SUCESSO)
            return error;

        remover = anterior->proximo;
        anterior->proximo = remover->proximo;
    }

    free(remover);
    lista->itens = lista->itens - 1;

    return SUCESSO;
}

erro_t listaES_removeElemento(listaES_t * lista, dados_t dados){
    itemLista_t * anterior = NULL;
    itemLista_t * remover = (itemLista_t * ) lista->primeiro;

    comparaDados_f compare_f = toCompare;

    while(remover != NULL){
        if(compare_f(remover->dados, dados) == 0)
            break;

        remover = remover->proximo;
        anterior = remover;
    }

    if(remover == NULL)
        return ITEM_NAO_ENCONTRADO;

    if(anterior == NULL)
        lista->primeiro = remover->proximo;
    else
        anterior->proximo = remover->proximo;

    free(remover);
    lista->itens = lista->itens - 1;

    return SUCESSO;
}

void listaES_imprime(listaES_t * lista){
    itemLista_t * atual;
    itemLista_t * proximo = lista->primeiro;

    printf("Lista com %u item(s)\n", lista->itens);
    printf("----- Impressao da Lista -----");

    for(uint32_t i = 0; i < lista->itens; i = i + 1){
        atual = proximo;
        proximo = atual->proximo;

        printf("Posicao: %u /  Dado: %u", i, atual->dados);
    }

    printf("------ Fim da Impressao ------");
}

bool_t listaES_buscar(listaES_t * lista, dados_t dado, uint32_t * posicao){
    *posicao = 0;
    itemLista_t * atual = (itemLista_t *) lista->primeiro;

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
