/**
 * @file grafoLA.c
 * @author Henrique Fernandes de Castro Melo (hmelo2509@gmail.com)
 * @brief Arquivo com a implementação de Grafo do tipo Lista de Adjacencia
 * @version 0.1
 * @date 2020-11-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "grafoLA.h"
#include "../tipos.h"
#include "../erro.h"
#include "../LISTA/listaLE.h"

/**
 * @brief Função que cria e inicializa o grafo
 * 
 * @param grafo Apontador para o local que receberá o grafo já inicializado
 * @param n_vertices Número de vértices do grafo
 * @param tipo Tipo do grafo
 * @return erro_t Retorna um erro em caso de ocorrer erro
 */
erro_t grafoLA_cria(grafoLA_t ** grafo, uint16_t n_vertices, tipoGrafo_t tipo){
    uint16_t i, j;

    // Verificacao de erro
    if(!grafo || n_vertices == 0)
        return PARAMETRO_INVALIDO;

    // Alocação do grafo em si
    *grafo = malloc(sizeof(grafoLA_t));

    // Verificacao de erro
    if(!(*grafo))
        return ERRO_ALOCACAO;

    // Alocação das listas de adj do grafo
    (*grafo)->listas = (listaES_t **) malloc(sizeof(listaES_t *) * n_vertices);

    // Verificacao de erro
    if((*grafo)->listas == NULL){
        free(*grafo);
        return ERRO_ALOCACAO;
    }

     // Inicializa o grafo com os dados informados pelo usuario
    (*grafo)->n_arestas = 0;
    (*grafo)->n_vertices = n_vertices;
    (*grafo)->tipo = tipo;

    // Aloca e Inicializa as listas
    for(i = 0; i < n_vertices; i++){

        (*grafo)->listas[i] = listaES_criar();

        // Verificacao de Erro
        if((*grafo)->listas[i] == NULL){
            for(j = 0; j < n_vertices; j++){
                listaES_destroi((*grafo)->listas[j]);
            }

            free(*grafo);
            return ERRO_ALOCACAO;
        }
    }
}

/**
 * @brief Função que exclui o grafo da memória
 * 
 * @param grafo Apontador para o grafo
 */
void grafoLA_destroi(grafoLA_t ** grafo){
    uint16_t i;

    for(i = 0; i < (*grafo)->n_vertices; i++){
        listaES_destroi((*grafo)->listas[i]);
    }
    
    free(*grafo);
}

/**
 * @brief Função pra verificar se existe uma aresta entre dois vértices do grafo
 * 
 * @param grafo Apontador para o grafo
 * @param origem  Vértice de origem da aresta
 * @param dest Vértice de destino da aresta
 * @param resultado Booleano que diz se existe aresta ou nao
 * @return erro_t Retorna um erro em caso de ocorrer erro
 */
erro_t grafoLA_verificaAresta(grafoLA_t * grafo, vertice_t origem, vertice_t dest, bool_t * resultado){
    uint16_t temp;

    if(origem >= grafo->n_vertices || dest >= grafo->n_vertices)
        return VERTICE_INVALIDO;

    *resultado = listaES_buscar(grafo->listas[origem], dest, &temp);

    return SUCESSO;
}

/**
 * @brief Função que cria aresta entre dois vértices
 * 
 * @param grafo Apontador para o grafo
 * @param origem Origem da aresta 
 * @param dest Destino da aresta
 * @param custo Custo da aresta
 * @return erro_t Retorna erro em caso de ocorrer erro
 */
erro_t grafoLA_criaAresta(grafoLA_t * grafo, vertice_t origem, vertice_t dest, custo_t custo){

    // Verifica se já existe aresta entre os dois vértices
    bool_t existe_aresta;
    erro_t error = grafoLA_verificaAresta(grafo, origem, dest, &existe_aresta);
    
    if(error != SUCESSO)
        return error;

    // Se existe, retorna erro
    if(existe_aresta == VERDADEIRO)
        return ARESTA_EXISTENTE;

    // Criação da aresta
    listaES_insere(grafo->listas[origem], dest);

    if(grafo->tipo == grafoNaoDirecionado)
        listaES_insere(grafo->listas[dest], origem);

    grafo->n_arestas = grafo->n_arestas + 1;

    return SUCESSO;
}

/**
 * @brief Função que remove uma aresta entre dois vértices
 * 
 * @param grafo Apontador para o grafo
 * @param origem Vértice de origem da aresta a ser deletada
 * @param dest Vértice de destino da aresta a ser deletada
 * @return erro_t Retorna um erro em caso de ocorrer erro
 */
erro_t grafoLA_removeAresta(grafoLA_t * grafo, vertice_t origem, vertice_t dest){

    // Verifica se não existe aresta entre os dois vértices
    bool_t existe_aresta;
    erro_t error = grafoLA_verificaAresta(grafo, origem, dest, &existe_aresta);

    if(error != SUCESSO)
        return error;

    // Se não existe, retorna erro
    if(existe_aresta == FALSO)
        return ARESTA_INEXISTENTE;

    // Remoção da aresta
    listaES_removeElemento(grafo->listas[origem], dest);

    if(grafo->tipo == grafoNaoDirecionado)
        listaES_removeElemento(grafo->listas[dest], origem);

    grafo->n_arestas = grafo->n_arestas - 1;

    return SUCESSO;
}

/**
 * @brief Função auxiliar de impressao do grafo
 * 
 * @param grafo Apontador para o grafo
 */
static void grafoLA_imprimeNaoDirecionado(grafoLA_t * grafo){

}

/**
 * @brief Função auxiliar de impressao do grafo
 * 
 * @param grafo Apontador para o grafo
 */
static void grafoLA_imprimeDirecionado(grafoLA_t * grafo){
    uint16_t i;
    itemLista_t * item;

    for(i = 0; i < grafo->n_vertices; i++){
        item = grafo->listas[i]->primeiro;
        while(item != NULL){
            printf("%05u - %05u\n", i, item->dados);
            item = item->proximo;
        }
    }
}

/**
 * @brief Função que imprime o grafo
 * 
 * @param grafo Apontador para o grafo
 */
void grafoLA_imprime(grafoLA_t * grafo){
    printf("\n----- Impressao de Grafo de Listas de Adjacências -----\n\n");
    printf("Tipo do Grafo: %s\n", grafo->tipo == grafoDirecionado ? "Direcionado" : "nao Direcionado");
    printf("Quantidade de Vértices: %u\n", grafo->n_vertices);
    printf("Quantidade de Arestas: %u\n\n", grafo->n_arestas);
    
    if(grafo->tipo == grafoNaoDirecionado)
        grafoLA_imprimeNaoDirecionado(grafo);
    else
        grafoLA_imprimeDirecionado(grafo);

    printf("\n---- Termino da Impressão ----\n");
}

/**
 * @brief Função que imprime o grau de cada vértice
 * 
 * @param grafo Apontador para o grafo
 * @return erro_t Retorna um erro em caso de ocorrer erro
 */
erro_t grafoLA_imprimeGraus(grafoLA_t * grafo){
    uint16_t vertice_atual;
    erro_t error;

    printf("\n----- Impressao de Graus dos Vértices do Grafo -----\n\n");
    printf("Tipo do Grafo: %s\n", grafo->tipo == grafoDirecionado ? "Direcionado" : "nao Direcionado");
    printf("Quantidade de Vértices: %u\n", grafo->n_vertices);
    printf("Quantidade de Arestas: %u\n\n", grafo->n_arestas);

    for(vertice_atual = 0; vertice_atual < grafo->n_vertices; vertice_atual++){
        printf("Vertice %05u Grau: %05u\n", vertice_atual, grafo->listas[vertice_atual]->itens);
    }

    printf("\n----------------- Termino da Impressão -----------------\n");
    return SUCESSO;
}

/**
 * @brief Função auxiliar que imprime a lista de vértices adjacentes a um vértice
 * 
 * @param lista_vertices_adjacentes Apontador para uma lista de vértices adjacentes
 */
static void grafoLA_imprimeListaVertices(listaES_t * lista_vertices_adjacentes){
    itemLista_t * atual;
    itemLista_t * proximo = lista_vertices_adjacentes->primeiro;

    for(uint32_t i = 0; i < lista_vertices_adjacentes->itens; i = i + 1){
        atual = proximo;
        proximo = atual->proximo;

        printf("%u ", atual->dados);
    }

    printf("\n");
}

/**
 * @brief Função que imprime todas as listas de vértices adjacentes a todos os vértices
 * 
 * @param grafo Apontador para o grafo
 * @return erro_t Retorna um erro em caso de ocorrer erro
 */
erro_t grafoLA_imprimeAdjacentes(grafoLA_t * grafo){
    uint16_t vertice_atual;
    erro_t error;

    printf("\n----- Impressao de Listas de Adjacência do Grafo -----\n\n");
    printf("Tipo do Grafo: %s\n", grafo->tipo == grafoDirecionado ? "Direcionado" : "nao Direcionado");
    printf("Quantidade de Vértices: %u\n", grafo->n_vertices);
    printf("Quantidade de Arestas: %u\n\n", grafo->n_arestas);

    for(vertice_atual = 0; vertice_atual < grafo->n_vertices; vertice_atual++){
        printf("Vertices Adjacentes a %u : ", vertice_atual);
        grafoLA_imprimeListaVertices(grafo->listas[vertice_atual]);
    }

    printf("\n----------------- Termino da Impressão -----------------\n");
    return SUCESSO;
}