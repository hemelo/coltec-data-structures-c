/**
 * @file filaLE.h
 * @author Henrique Fernandes de Castro
 * @brief 
 * @version 0.1
 * @date 2020-08-25
 * 
 */

#pragma once

#ifndef FILALE_H
#define FILALE_H

#include <stdint.h>
#include "tipos.h"
#include "erro.h"
#include "dados.h"

/**
 * @brief Estrutura que representa um item da lista
 * @param proximoItem Contém o endereço do próximo item da lista
 * @param dadosItem Contém os dados do item
 */
struct itemLista_s{
    struct itemLista_s * proximoItem;
    dados_t dados;
};
// Tipo que representa a estrutura de um item da fila
typedef struct itemLista_s itemFila_t;

/**
 * 
 * @brief Estrutura que representa uma Fila
 * @param nItems Quantidade de itens da Fila
 * @param inicio Contém o endereço de memória do primeiro item
 * @param fim Contém o endereço de memória do ultimo item
 */
struct fila_s{
    uint16_t nItens;
    itemFila_t * inicio;
    itemFila_t * fim;
};
// Tipo que representa a fila
typedef struct fila_s filaLE_t;

// Funções exportadas
filaLE_t * filaLE_criar();
void filaLE_inicializar(filaLE_t * fila);
void filaLE_excluir(filaLE_t * fila);
boolean_t filaLE_estaVazia(filaLE_t * fila);
erro_t filaLE_insere(filaLE_t * fila, dados_t dados);
erro_t filaLE_remove(filaLE_t * fila, dados_t * valorPerdido);
//itemFila_t * fila_buscar(filaLE_t * fila);
void filaLE_imprimir(filaLE_t * fila);

#endif