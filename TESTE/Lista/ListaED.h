/**
 * @file lista.h
 * @author Henrique Fernandes de Castro
 * @brief 
 * @version 0.1
 * @date 2020-07-13
 * 
 */

#pragma once

#ifndef LISTAED_H
#define LISTAED_H

#include <stdint.h>
#include "tipos.h"
#include "dados.h"

/**
 * @brief Estrutura que representa um item da lista
 * @param proximoItem Contém o endereço do próximo item da lista
 * @param dadosItem Contém os dados do item
 */
struct itemLista{
	struct itemLista * anteriorItem;
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
Lista * ListaED_criar();
void listaED_inicializar(Lista * lista);
void listaED_excluir(Lista * lista);
boolean listaED_itemPosicao(Lista * lista, uint16_t posicao, ItemLista ** itemProcurado);
boolean listaED_estaVazia(Lista * lista);
boolean listaED_insereInicio(Lista * lista, Dados dados);
boolean listaED_insereFinal(Lista * lista, Dados dados);
boolean listaED_inserePosicao(Lista * lista, Dados dados, uint16_t posicao);
boolean listaED_insereOrdenado(Lista * lista, Dados dados);
boolean listaED_removerItem(Lista * lista, Dados dados);
boolean listaED_removerPosicao(Lista * lista, uint16_t posicao);
boolean listaED_removerInicio(Lista * lista);
boolean listaED_removerFinal(Lista * lista);
void listaED_imprimirEmArquivo(Lista * lista);
void listaED_imprimir(Lista * lista);

#endif