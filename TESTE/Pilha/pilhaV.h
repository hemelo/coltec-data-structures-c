/**
 * @file pilha.h
 * @author Henrique Fernandes de Castro
 * @brief 
 * @version 0.1
 * @date 2020-08-17
 * 
 */

#pragma once

#ifndef PILHAV_H
#define PILHAV_H

#include <stdint.h>
#include "tipos.h"
#include "dados.h"

/**
 * 
 * @brief Estrutura que representa uma Pilha
 *
 */
struct pilhaV_s{
	void * itens;
    uint16_t nItens;
    uint32_t capacidade;
};
// Tipo que representa a pilha
typedef struct pilhaV_s pilhaV_t;

// Funções exportadas
extern pilhaV_t * pilhaV_criar(uint32_t capacidade);
extern void pilhaV_inicializar(pilhaV_t * pilha, uint32_t capacidade);
extern void pilhaV_excluir(pilhaV_t * pilha);
extern boolean_t pilhaV_estaVazia(pilhaV_t * pilha);
extern erro_t pilhaV_empilha(pilhaV_t * pilha, dados_t dados);
extern erro_t pilhaV_desempilha(pilhaV_t * pilha, dados_t * valorPerdido);
extern boolean_t pilhaV_buscar(pilhaV_t * pilha, dados_t info, uint32_t * posicao);
extern void pilhaV_imprimir(pilhaV_t * pilha);

#endif