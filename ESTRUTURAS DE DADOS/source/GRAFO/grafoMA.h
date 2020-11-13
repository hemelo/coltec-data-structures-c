/**
 * @file grafoMA.h
 * @author Henrique Fernandes de Castro Melo (hmelo2509@gmail.com)
 * @brief Arquivo com as definicoes de Grafo do tipo Matriz Adjacencia
 * @version 0.1
 * @date 2020-11-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include <stdint.h>
#include "grafo.h"
#include "grafoMA.h"
#include "../tipos.h"

#ifndef __GRAFOMA_h__
#define __GRAFOMA_h__

// Tipo que representa um grafo de Matriz de Adjacências
typedef struct grafoMA_s{
    // Matriz de Adjacências do grafo
    custo_t ** dados;

    // Número de vértices do grafo
    uint16_t n_vertices;

    // Número de arestas do grafo
    uint32_t n_arestas;

    // Tipo do Grafo
    tipoGrafo_t tipo;
}grafoMA_t;


erro_t grafoMA_cria(grafoMA_t ** grafo, uint16_t n_vertices, tipoGrafo_t tipo);
void grafoMA_destroi(grafoMA_t ** grafo);
erro_t grafoMA_verificaAresta(grafoMA_t * grafo, vertice_t origem, vertice_t dest, bool_t * resultado);
erro_t grafoMA_criaAresta(grafoMA_t * grafo, vertice_t origem, vertice_t dest, custo_t custo);
erro_t grafoMA_removeAresta(grafoMA_t * grafo, vertice_t origem, vertice_t dest);
erro_t grafoMA_getCusto(grafoMA_t * grafo, vertice_t origem, vertice_t dest, custo_t * custo);
void grafoMA_imprime(grafoMA_t * grafo);
erro_t grafoMA_imprimeAdjacentes(grafoMA_t * grafo);
erro_t grafoMA_imprimeGraus(grafoMA_t * grafo);

#endif // GRAFOMA_H
