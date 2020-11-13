/**
 * @file busca.h
 * @author Henrique Fernandes de Castro Melo (hmelo2509@gmail.com)
 * @brief Arquivo com as definicoes de Busca em Grafo de tipo generico
 * @version 0.1
 * @date 2020-11-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */


#pragma once

#include <stdio.h>
#include <stdint.h>
#include "../tipos.h"
#include "grafo.h"

#ifndef __BUSCA_h__
#define __BUSCA_h__

#define ERRO_BUSCA_OFFSET  (-32)
#define PREDECESSOR_DESCONHECIDO (ERRO_BUSCA_OFFSET + 0)
#define PREDECESSOR_SOURCE (ERRO_BUSCA_OFFSET + 1)
#define ARVORE_DESCONHECIDA (ERRO_BUSCA_OFFSET + 2)

// Tipo que representa uma marcação do vértice
typedef enum marcaVertice_e{
    // Não visitado
    branco,
    // Visitado, porém não encontrado adjacentes ainda
    cinza,
    // Visitado e encontrado adjacentes
    preto
}marcaVertice_t;

// Tipo que representa o tipo da busca a ser realizada
typedef enum tipoBusca_e{
    emLargura,
    emProfundidade
}tipoBusca_t;

// Tipo que representa um tipo de prioridade na busca em profundidade
typedef enum tipoPrioridade_e{
    ordem,
    custo
}tipoPrioridade_t;

// Tipo que representa um tipo de busca em prioridade
typedef enum tipoProfundidade_e{
    simples,
    completa
}tipoProfundidade_t;

// Tipo que representa os dados de um vértice durante a busca
typedef struct dadoVertice_e{
    
    // Apontador para o vetor de Timestamps do vértice atual
    uint32_t * timestamps;

    // Número da árvore a qual o vértice atual pertence 
    int32_t arvore;

    // Vértice que antecede o vértice atual
    vertice_t predecessor;

    // Marcação do vértice atual
    marcaVertice_t marca; 
    
}dadoVertice_t;

#endif