/**
 * @file filaDE.h
 * @author Henrique Fernandes de Castro
 * @brief 
 * @version 0.1
 * @date 2020-08-25
 * 
 */

#pragma once

#ifndef FILADE_H
#define FILADE_H

#include <stdint.h>
#include "tipos.h"
#include "erro.h"
#include "dados.h"

/**
 * 
 * @brief Estrutura que representa uma Fila
 * 
 */
struct filaDE_s{
	void * vetor;
    uint32_t nItens;
    uint16_t inicio;
    uint16_t ultimo;
    uint32_t capacidade;
};
// Tipo que representa a fila
typedef struct filaDE_s filaDE_t;

// Funções exportadas
filaDE_t * filaDE_criar(uint32_t capacidade);
void filaDE_inicializar(filaDE_t * fila, uint32_t capacidade);
void filaDE_excluir(filaDE_t * fila);
uint32_t filaDE_posicaoAbsoluta(filaDE_t * fila, uint32_t indice);
uint32_t filaDE_proximaPosicao(filaDE_t * fila, uint32_t indice);
uint32_t filaDE_posicaoAnterior(filaDE_t * fila, uint32_t indice);
boolean_t filaDE_estaVazia(filaDE_t * fila);
erro_t filaDE_insereInicio(filaDE_t * fila, dados_t dados);
erro_t filaDE_insereFinal(filaDE_t * fila, dados_t dados);
erro_t filaDE_removeInicio(filaDE_t * fila, dados_t * valorPerdido);
erro_t filaDE_removeFinal(filaDE_t * fila, dados_t * valorPerdido);
//itemFila_t * fila_buscar(filaDE_t * fila);
void filaDE_imprimir(filaDE_t * fila);

#endif