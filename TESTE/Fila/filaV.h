/**
 * @file filaV.h
 * @author Henrique Fernandes de Castro
 * @brief 
 * @version 0.1
 * @date 2020-08-25
 * 
 */

#pragma once

#ifndef FILAV_H
#define FILAV_H

#include <stdint.h>
#include "tipos.h"
#include "erro.h"
#include "dados.h"

/**
 * 
 * @brief Estrutura que representa uma Fila
 * 
 */
struct filaV_s{
	void * vetor;
    uint32_t nItens;
    uint16_t inicio;
    uint16_t ultimo;
    uint32_t capacidade;
};
// Tipo que representa a fila
typedef struct filaV_s filaV_t;

// Funções exportadas
filaV_t * filaV_criar(uint32_t capacidade);
void filaV_inicializar(filaV_t * fila, uint32_t capacidade);
void filaV_excluir(filaV_t * fila);
uint32_t filaV_posicaoAbsoluta(filaV_t * fila, uint32_t indice);
uint32_t filaV_proximaPosicao(filaV_t * fila, uint32_t indice);
boolean_t filaV_estaVazia(filaV_t * fila);
erro_t filaV_insere(filaV_t * fila, dados_t dados);
erro_t filaV_remove(filaV_t * fila, dados_t * valorPerdido);
//itemFila_t * fila_buscar(filaV_t * fila);
void filaV_imprimir(filaV_t * fila);

#endif