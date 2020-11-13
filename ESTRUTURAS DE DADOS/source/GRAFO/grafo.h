/**
 * @file busca.h
 * @author Henrique Fernandes de Castro Melo (hmelo2509@gmail.com)
 * @brief Arquivo com as definicoes de Grafo de tipo generico
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

#ifndef __GRAFO_h__
#define __GRAFO_h__

#define ERRO_GRAFOS_OFFSET  (64)
#define VERTICE_INVALIDO    (ERRO_GRAFOS_OFFSET + 0)
#define ARESTA_AUSENTE      (ERRO_GRAFOS_OFFSET + 1)
#define ARESTA_EXISTENTE    (ERRO_GRAFOS_OFFSET + 2)
#define CUSTO_INFINITO      (ERRO_GRAFOS_OFFSET + 3)
#define ARESTA_INEXISTENTE  (ERRO_GRAFOS_OFFSET + 4)

// Enumeração que representa o tipo do grafo
typedef enum tipoGrafo_e{
    grafoNaoDirecionado,
    grafoDirecionado
}tipoGrafo_t;

// Tipo que representa o custo de uma aresta de um grafo
typedef int32_t custo_t;

// Tipo que representa vértice de grafo
typedef uint32_t vertice_t;

#endif // GRAFO_H
