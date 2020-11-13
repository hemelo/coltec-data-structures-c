#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "pilha.h"
#include "pilhaLE.h"
#include "../erro.h"
#include "../dados.h"
#include "../tipos.h"

static uint8_t toCompare(dados_t dados_um, dados_t dados_dois){
    return (dados_um - dados_dois);
}

static void pilhaLE_inicializa(pilhaLE_t * pilha){
    pilha->itens = 0;
    pilha->topo = NULL;
}

pilhaLE_t * pilhaLE_criar(void){
    pilhaLE_t * pilha = (pilhaLE_t *) malloc(sizeof(pilhaLE_t));
    pilhaLE_inicializa(pilha);
    return pilha;
}

bool_t pilhaLE_estaVazia(pilhaLE_t * pilha) {
    return (pilha->itens == 0 ? VERDADEIRO : FALSO);
}

void pilhaLE_destroi(pilhaLE_t * pilha) {
    itemPilha_t * atual = (itemPilha_t *)pilha->topo;
    itemPilha_t * proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    free(pilha);
}

erro_t pilhaLE_empilha(pilhaLE_t * pilha, dados_t dados) {
    itemPilha_t * novo = (itemPilha_t *) malloc(sizeof(itemPilha_t));
    novo->dados = dados;
    novo->proximo = (itemPilha_t *) pilha->topo;
    pilha->topo = novo;
    pilha->itens = pilha->itens + 1;
    return SUCESSO;
}

erro_t pilhaLE_desempilha(pilhaLE_t * pilha, dados_t * dados) {
    itemPilha_t * remover = (itemPilha_t *) pilha->topo;

    if(remover == NULL)
        return ESTRUTURA_VAZIA;

    pilha->topo = pilha->topo->proximo;

    memcpy(dados, &remover->dados, sizeof(dados_t));
    free(remover);

    return SUCESSO;
}

erro_t pilhaLE_topo(pilhaLE_t * pilha, dados_t * topo){
     if (pilha->topo == NULL)
        return ESTRUTURA_VAZIA;

     memcpy(topo, &pilha->topo->dados,sizeof(dados_t));

     return SUCESSO;
}

bool_t pilhaLE_busca(pilhaLE_t * pilha, dados_t dados, uint32_t * posicao){
    *posicao = 0;
    itemPilha_t * atual = (itemPilha_t *) pilha->topo;

    comparaDados_f compare_f = toCompare;

    while(atual != NULL){
        if(compare_f(atual->dados, dados) == 0)
            break;

        atual = atual->proximo;
        (*posicao) = (*posicao) + 1;
    }

    if(atual == NULL)
        return FALSO;

    return VERDADEIRO;
}

void pilhaLE_imprime(pilhaLE_t * pilha){
    itemPilha_t * atual;
    itemPilha_t * proximo = pilha->topo;

    printf("Pilha com %u item(s)\n", pilha->itens);
    printf("----- Impressao da Pilha -----");

    for(uint32_t i = 0; i < pilha->itens; i = i + 1){
        atual = proximo;
        proximo = atual->proximo;

        printf("Posicao: %u /  Dado: %u", i, atual->dados);
    }

    printf("------ Fim da Impressao ------");
}
