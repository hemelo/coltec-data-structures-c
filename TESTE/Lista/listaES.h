/**
 * @file lista.h
 * @author Henrique Fernandes de Castro
 * @brief 
 * @version 0.1
 * @date 2020-07-13
 * 
 */

#pragma once

#ifndef LISTAES_H
#define LISTAES_H

#include <stdint.h>
#include "tipos.h"
#include "dados.h"

/**
 * @brief Estrutura que representa um item da lista
 * @param proximoItem Contém o endereço do próximo item da lista
 * @param dadosItem Contém os dados do item
 */
struct itemLista{
    struct itemLista * proximoItem;
    Dados dados;
};
// Tipo que representa a estrutura de um item da lista
typedef struct itemLista ItemLista;

/**
 * 
 * @brief Estrutura que representa uma Lista
 * @param nItems Quantidade de itens da lista
 * @param primeiroItem Contém o endereço de memória do primeiro item
 */
struct lista{
    uint16_t nItems;
    ItemLista * primeiroItem;
};
// Tipo que representa a lista
typedef struct lista Lista;

// Funções exportadas
Lista * ListaES_criar();
void listaES_inicializar(Lista * lista);
void listaES_excluir(Lista * lista);
boolean listaES_itemPosicao(Lista * lista, uint16_t posicao, ItemLista ** itemProcurado);
boolean listaES_estaVazia(Lista * lista);
boolean listaES_insereInicio(Lista * lista, Dados dados);
boolean listaES_insereFinal(Lista * lista, Dados dados);
boolean listaES_inserePosicao(Lista * lista, Dados dados, uint16_t posicao);
boolean listaES_insereOrdenado(Lista * lista, Dados dados);
boolean listaES_removerItem(Lista * lista, Dados dados);
boolean listaES_removerPosicao(Lista * lista, uint16_t posicao);
boolean listaES_removerInicio(Lista * lista);
boolean listaES_removerFinal(Lista * lista);
void listaES_imprimirEmArquivo(Lista * lista);
void listaES_imprimir(Lista * lista);


#endif