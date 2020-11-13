#pragma once

#include <stdio.h>
#include <stdint.h>
#include "../dados.h"
#include "../tipos.h"

#ifndef __LISTALE_H__
#define __LISTALE_H__

typedef struct itemLista_s{
    dados_t dados;
    struct itemLista_s * proximo;
}itemLista_t;

typedef struct listaES_s{
    uint16_t itens;
    struct itemLista_s * primeiro;
}listaES_t;

listaES_t * listaES_criar(void);
void listaES_destroi(listaES_t * lista);
void listaES_imprime(listaES_t * lista);
bool_t listaES_estaVazia(listaES_t * lista);
erro_t listaES_insere(listaES_t * lista, dados_t dados);
erro_t listaES_inserePosicao(listaES_t * lista, dados_t dados, uint32_t posicao);
erro_t listaES_removeElemento(listaES_t * lista, dados_t dados);
erro_t listaES_removeInicio(listaES_t * lista);
erro_t listaES_removeFinal(listaES_t * lista);
erro_t listaES_removePosicao(listaES_t * lista, uint32_t posicao);
erro_t listaES_buscar(listaES_t * lista, dados_t dado, uint32_t * posicao);

#endif // LISTA_H
