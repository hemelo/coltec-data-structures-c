/**
 * @file lista.h
 * @author Henrique Fernandes de Castro
 * @brief 
 * @version 0.1
 * @date 2020-07-13
 * 
 */

#pragma once

#ifndef LISTACIRC_H
#define LISTACIRC_H

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
Lista * ListaC_criar();
void listaC_inicializar(Lista * lista);
void listaC_excluir(Lista * lista);
boolean listaC_itemPosicao(Lista * lista, uint16_t posicao, ItemLista ** itemProcurado);
boolean listaC_estaVazia(Lista * lista);
boolean listaC_insereInicio(Lista * lista, Dados dados);
boolean listaC_insereFinal(Lista * lista, Dados dados);
boolean listaC_inserePosicao(Lista * lista, Dados dados, uint16_t posicao);
boolean listaC_insereOrdenado(Lista * lista, Dados dados);
boolean listaC_removerItem(Lista * lista, Dados dados);
boolean listaC_removerPosicao(Lista * lista, uint16_t posicao);
boolean listaC_removerInicio(Lista * lista);
boolean listaC_removerFinal(Lista * lista);
void listaC_imprimirEmArquivo(Lista * lista);
void listaC_imprimir(Lista * lista);


#endif