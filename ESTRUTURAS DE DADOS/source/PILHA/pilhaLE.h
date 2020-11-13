#pragma once

#include <stdio.h>
#include <stdint.h>
#include "../dados.h"
#include "../tipos.h"

#ifndef __PILHALE_H__
#define __PILHALE_H__

typedef struct itemPilha_s{
    dados_t dados;
    struct itemPilha_s * proximo;
}itemPilha_t;

typedef struct pilhaLE_s{
    uint16_t itens;
    struct itemPilha_s * topo;
}pilhaLE_t;

pilhaLE_t * pilhaLE_cria(void);
void pilhaLE_destroi(pilhaLE_t * pilha);
void pilhaLE_imprime(pilhaLE_t * pilha);
bool_t pilhaLE_estaVazia(pilhaLE_t * pilha);
erro_t pilhaLE_empilha(pilhaLE_t * pilha, dados_t dados);
erro_t pilhaLE_desempilha(pilhaLE_t * pilha, dados_t * dados);
erro_t pilhaLE_topo(pilhaLE_t * pilha, dados_t * topo);
erro_t pilhaLE_busca(pilhaLE_t * pilha, dados_t dados, uint32_t * posicao);

#endif // PILHA_H
