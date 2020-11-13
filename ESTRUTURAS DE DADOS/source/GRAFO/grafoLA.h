/**
 * @file grafoLA.h
 * @author Henrique Fernandes de Castro Melo (hmelo2509@gmail.com)
 * @brief Arquivo com as definicoes de Grafo do tipo Lista de Adjacência
 * @version 0.1
 * @date 2020-11-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include <stdint.h>
#include "grafo.h"
#include "../LISTA/listaLE.h"
#include "../tipos.h"

#ifndef __GRAFOLA_h__
#define __GRAFOLA_h__

// Tipo que representa um grafo de Matriz de Adjacências
typedef struct grafoLA_s{
    // Vetor para alocar as listas de adjacência do grafo
    listaES_t ** listas;

    // Número de vértices do grafo
    uint16_t n_vertices;

    // Número de arestas do grafo
    uint32_t n_arestas;

    // Tipo do Grafo
    tipoGrafo_t tipo;
}grafoLA_t;

erro_t grafoLA_cria(grafoLA_t ** grafo, uint16_t n_vertices, tipoGrafo_t tipo);
void grafoLA_destroi(grafoLA_t ** grafo);
erro_t grafoLA_verificaAresta(grafoLA_t * grafo, vertice_t origem, vertice_t dest, bool_t * resultado);
erro_t grafoLA_criaAresta(grafoLA_t * grafo, vertice_t origem, vertice_t dest, custo_t custo);
erro_t grafoLA_removeAresta(grafoLA_t * grafo, vertice_t origem, vertice_t dest);
void grafoLA_imprime(grafoLA_t * grafo);
erro_t grafoLA_imprimeAdjacentes(grafoLA_t * grafo);
erro_t grafoLA_imprimeGraus(grafoLA_t * grafo);

#endif // GRAFOLA_H
