#pragma once

#include <stdio.h>
#include <stdint.h>
#include "../dados.h"
#include "../tipos.h"

#ifndef __FILALE_H__
#define __FILALE_H__

typedef struct itemFila_s{
    dados_t dados;
    struct itemFila_s *proximo;
}itemFila_t;

typedef struct filaES_s{
    uint16_t itens;
    struct itemFila_s * inicio;
    struct itemFila_s * fim;
}filaES_t;

filaES_t * filaES_criar(void);
void filaES_destroi(filaES_t * fila);
void filaES_imprime(filaES_t * fila);
bool_t filaES_estaVazia(filaES_t * fila);
erro_t filaES_insere(filaES_t * fila, dados_t dados);
erro_t filaES_remove(filaES_t * fila, dados_t * dados);
bool_t filaES_buscar(filaES_t * fila, dados_t dado, uint32_t * posicao);

#endif // FILA_H
