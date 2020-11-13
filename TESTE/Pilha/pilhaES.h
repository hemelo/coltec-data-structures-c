/**
 * @file pilha.h
 * @author Henrique Fernandes de Castro
 * @brief 
 * @version 0.1
 * @date 2020-08-17
 * 
 */

#pragma once

#ifndef PILHAES_H
#define PILHAES_H

#include <stdint.h>
#include "tipos.h"
#include "dados.h"

/**
 * @brief Estrutura que representa um item da pilha
 * @param proximoItem Contém o endereço do próximo item da pilha
 * @param dadosItem Contém os dados do item
 */
struct itemPilha_s{
    struct itemPilha_s * proximoItem;
    dados_t dados;
};
// Tipo que representa a estrutura de um item da pilha
typedef struct itemPilha_s itemPilha_t;

/**
 * 
 * @brief Estrutura que representa uma Pilha
 * @param nItems Quantidade de itens da pilha
 * @param topo Contém o endereço de memória do topo da pilha
 */
struct pilha_s{
    uint16_t nItens;
    itemPilha_t * topo;
};
// Tipo que representa a pilha
typedef struct pilha_s pilha_t;

// Funções exportadas
extern pilha_t * pilha_criar();
extern void pilha_inicializar(pilha_t * pilha);
extern void pilha_excluir(pilha_t * pilha);
extern boolean_t pilha_estaVazia(pilha_t * pilha);
extern erro_t pilha_empilha(pilha_t * pilha, dados_t dados);
extern erro_t pilha_desempilha(pilha_t * pilha, dados_t * valorPerdido);
//itemPilha_t * pilha_buscar(pilha_t * pilha, uint32_t * posicao);
extern void pilha_imprimir(pilha_t * pilha);

#endif