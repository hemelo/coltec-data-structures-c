/**
 * @file buscaMA.h
 * @author Henrique Fernandes de Castro Melo (hmelo2509@gmail.com)
 * @brief Arquivo com as definicoes de Busca em Grafo do tipo Matriz Adjacencia
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
#include "busca.h"
#include "../tipos.h"
#include "../LISTA/listaLE.h"

#ifndef __BUSCAMA_h__
#define __BUSCAMA_h__

typedef erro_t(* buscaProfundidade_f)(grafoMA_t *, vertice_t);

erro_t buscaMA_getVerticesAdjacentes(grafoMA_t * grafo, vertice_t vertice_de_busca, listaES_t ** lista_vertices_adjacentes);
erro_t buscaMA_emLargura(grafoMA_t * grafo, vertice_t vertice_source);
erro_t buscaMA_emProfundidade(grafoMA_t * grafo, vertice_t vertice_source, tipoProfundidade_t tipo, tipoPrioridade_t prioridade);

#endif