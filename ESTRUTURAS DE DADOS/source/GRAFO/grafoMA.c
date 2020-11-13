/**
 * @file grafoMA.c
 * @author Henrique Fernandes de Castro Melo (hmelo2509@gmail.com)
 * @brief Arquivo com a implementação de Grafo do tipo Matriz Adjacencia
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
#include "grafoMA.h"
#include "buscaMA.h"
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
erro_t grafoMA_cria(grafoMA_t ** grafo, uint16_t n_vertices, tipoGrafo_t tipo){
    uint16_t i, j;
    uint16_t limite;

    // Verificacao de erro
    if(!grafo || n_vertices == 0)
        return PARAMETRO_INVALIDO;

    // Alocação do grafo em si
    *grafo = malloc(sizeof(grafoMA_t));

    // Verificacao de erro
    if(!(*grafo))
        return ERRO_ALOCACAO;

    // Alocação das linhas do grafo
    (*grafo)->dados = (custo_t **) malloc(sizeof(custo_t *) * n_vertices);

    // Verificacao de erro
    if((*grafo)->dados == NULL){
        free(*grafo);
        return ERRO_ALOCACAO;
    }

    // Alocação das colunas do grafo
    for(i = 0; i < n_vertices; i++){

        // Se o grafo nao e do tipo direcionado, nao e utilizado toda a matriz
        if(tipo == grafoDirecionado)
            limite = n_vertices;
        else
            limite = i + 1;

        // Alocacao das colunas do grafo
        (*grafo)->dados[i] = (custo_t *) malloc(sizeof(custo_t) * limite);
        
        // Verificacao de erro
        if((*grafo)->dados[i] == NULL){
            for(j = 0; j < i; j++){
                free((*grafo)->dados[j]);
            }
            free((*grafo)->dados);
            free(*grafo);
            return ERRO_ALOCACAO;
        }
    }

    // Inicializa o grafo com os dados informados pelo usuario
    (*grafo)->n_arestas = 0;
    (*grafo)->n_vertices = n_vertices;
    (*grafo)->tipo = tipo;

    // Inicializa os dados do grafo com um padrão pré-estabelecido
    for(i = 0; i < n_vertices; i++){

        if(tipo == grafoDirecionado)
            limite = n_vertices;
        else
            limite = i + 1;
        
        for(j=0; j < limite; j++){
            (*grafo)->dados[i][j] = ARESTA_AUSENTE;
        }
        
    }
    return SUCESSO;
}

/**
 * @brief Função que exclui o grafo da memória
 * 
 * @param grafo Apontador para o grafo
 */
void grafoMA_destroi(grafoMA_t ** grafo){
    uint16_t i, limite;

    for(i = 0; i < (*grafo)->n_vertices; i++){

        if((*grafo)->tipo == grafoDirecionado)
            limite = (*grafo)->n_vertices;
        else
            limite = i + 1;

        free((*grafo)->dados[i]);
    }

    free((*grafo)->dados);
    free(*grafo);
}

/**
 * @brief Função auxiliar para ajustar o vertice na matriz, caso necessário
 * 
 * @param grafo Apontador para o grafo
 * @param origem Apontador para o vértice origem
 * @param dest Apontador para o vértice destino 
 */
static void grafoMA_ajustaVertice(grafoMA_t * grafo, vertice_t * origem, vertice_t * dest){
    uint16_t temp;

    // Se o grafo não é direcionado, somente a parte inferior da matriz será utilizada
    if(grafo->tipo == grafoNaoDirecionado){
        if(*origem < *dest){
            temp = *origem;
            *origem = *dest;
            *dest = temp;
        }
    }
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
erro_t grafoMA_verificaAresta(grafoMA_t * grafo, vertice_t origem, vertice_t dest, bool_t * resultado){

    if(origem >= grafo->n_vertices || dest >= grafo->n_vertices)
        return VERTICE_INVALIDO;

    grafoMA_ajustaVertice(grafo, &origem, &dest);
    custo_t custo = grafo->dados[origem][dest];

    if(custo != ARESTA_AUSENTE)
        *resultado = VERDADEIRO;
    else
        *resultado = FALSO;

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
erro_t grafoMA_criaAresta(grafoMA_t * grafo, vertice_t origem, vertice_t dest, custo_t custo){

    // Verifica se já existe aresta entre os dois vértices
    bool_t existe_aresta;
    erro_t error = grafoMA_verificaAresta(grafo, origem, dest, &existe_aresta);
    
    if(error != SUCESSO)
        return error;

    // Se existe, retorna erro
    if(existe_aresta == VERDADEIRO)
        return ARESTA_EXISTENTE;

    // Criação da aresta
    grafoMA_ajustaVertice(grafo, &origem, &dest);
    grafo->dados[origem][dest] = custo;
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
erro_t grafoMA_removeAresta(grafoMA_t * grafo, vertice_t origem, vertice_t dest){

    // Verifica se não existe aresta entre os dois vértices
    bool_t existe_aresta;
    erro_t error = grafoMA_verificaAresta(grafo, origem, dest, &existe_aresta);

    if(error != SUCESSO)
        return error;

    // Se não existe, retorna erro
    if(existe_aresta == FALSO)
        return ARESTA_INEXISTENTE;

    // Remoção da aresta
    grafoMA_ajustaVertice(grafo, &origem, &dest);
    grafo->dados[origem][dest] = ARESTA_AUSENTE;
    grafo->n_arestas = grafo->n_arestas - 1;

    return SUCESSO;
}

/**
 * @brief Função que pega o custo de uma aresta
 * 
 * @param grafo Apontador para o grafo
 * @param origem Vértice de origem da aresta desejada
 * @param dest Vértice de destino da aresta desejada
 * @param custo Apontador do endereço que irá receber o custo
 * @return erro_t Retorna um erro em caso de ocorrer erro
 */
erro_t grafoMA_getCusto(grafoMA_t * grafo, vertice_t origem, vertice_t dest, custo_t * custo){

    // Verifica se não existe aresta entre os dois vértices
    bool_t existe_aresta;
    erro_t error = grafoMA_verificaAresta(grafo, origem, dest, &existe_aresta);

    if(error != SUCESSO)
        return error;

    // Se não existe, retorna erro
    if(existe_aresta == FALSO)
        return ARESTA_INEXISTENTE;

    grafoMA_ajustaVertice(grafo, &origem, &dest);
    *custo = grafo->dados[origem][dest];  

    return SUCESSO;  
}

/**
 * @brief Função que imprime o grafo
 * 
 * @param grafo Apontador para o grafo
 */
void grafoMA_imprime(grafoMA_t * grafo){
    uint16_t i, j;
    uint16_t limite;

    printf("\n----- Impressao de Grafo de Matriz de Adjacências -----\n\n");
    printf("Tipo do Grafo: %s\n", grafo->tipo == grafoDirecionado ? "Direcionado" : "nao Direcionado");
    printf("Quantidade de Vértices: %u\n", grafo->n_vertices);
    printf("Quantidade de Arestas: %u\n\n", grafo->n_arestas);

    for(i = 0; i < grafo->n_vertices; i++){
        if(grafo->tipo == grafoDirecionado)
            limite = grafo->n_vertices;
        else
            limite = i + 1;

        for(j = 0; j < limite; j++){
            if(grafo->dados[i][j] != ARESTA_AUSENTE){
                if(grafo->tipo == grafoDirecionado)
                    printf("%05u > %05u (%u)\n", i, j, (grafo)->dados[i][j]);
                else
                    printf("%05u - %05u (%u)\n", i, j, (grafo)->dados[i][j]);
            }
        }
    }

    printf("\n---- Termino da Impressão ----\n");
}

/**
 * @brief Função auxiliar que imprime a lista de vértices adjacentes a um vértice
 * 
 * @param lista_vertices_adjacentes Apontador para uma lista de vértices adjacentes
 */
static void grafoMA_imprimeListaVertices(listaES_t * lista_vertices_adjacentes){
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
erro_t grafoMA_imprimeAdjacentes(grafoMA_t * grafo){
    listaES_t * lista_vertices_adjacentes;

    uint16_t vertice_atual;
    erro_t error;

    printf("\n----- Impressao de Listas de Adjacência do Grafo -----\n\n");
    printf("Tipo do Grafo: %s\n", grafo->tipo == grafoDirecionado ? "Direcionado" : "nao Direcionado");
    printf("Quantidade de Vértices: %u\n", grafo->n_vertices);
    printf("Quantidade de Arestas: %u\n\n", grafo->n_arestas);

    for(vertice_atual = 0; vertice_atual < grafo->n_vertices; vertice_atual++){
        error = buscaMA_getVerticesAdjacentes(grafo, vertice_atual, &lista_vertices_adjacentes);

        if(error != SUCESSO)
            return error;

        printf("Vertices Adjacentes a %u : ", vertice_atual);
        grafoMA_imprimeListaVertices(lista_vertices_adjacentes);
        listaES_destroi(lista_vertices_adjacentes);
    }

    printf("\n----------------- Termino da Impressão -----------------\n");
    return SUCESSO;
}

/**
 * @brief Função auxiliar que calcula o grau de um vértice
 *  
 * @param grafo Apontador para o grafo
 * @param vertice Vértice desejado
 * @param grau Apontador para o endereço que receberá o grau do vértice
 * @return erro_t Retorna erro em caso de ocorrer erro
 */
static erro_t grafoMA_calculaGrauVertice(grafoMA_t * grafo, vertice_t vertice, uint16_t * grau){
    erro_t error;
    listaES_t * lista_vertices_adjacentes;

    error = buscaMA_getVerticesAdjacentes(grafo, vertice, &lista_vertices_adjacentes);

    if(error != SUCESSO)
        return error;

    *grau = lista_vertices_adjacentes->itens;
    listaES_destroi(lista_vertices_adjacentes);
    
    return SUCESSO;
}

/**
 * @brief Função que imprime o grau de cada vértice
 * 
 * @param grafo Apontador para o grafo
 * @return erro_t Retorna um erro em caso de ocorrer erro
 */
erro_t grafoMA_imprimeGraus(grafoMA_t * grafo){
    uint16_t vertice_atual;
    uint16_t grau;
    erro_t error;

    printf("\n----- Impressao de Graus dos Vértices do Grafo -----\n\n");
    printf("Tipo do Grafo: %s\n", grafo->tipo == grafoDirecionado ? "Direcionado" : "nao Direcionado");
    printf("Quantidade de Vértices: %u\n", grafo->n_vertices);
    printf("Quantidade de Arestas: %u\n\n", grafo->n_arestas);

    for(vertice_atual = 0; vertice_atual < grafo->n_vertices; vertice_atual++){
        error = grafoMA_calculaGrauVertice(grafo, vertice_atual, &grau);

        if(error != SUCESSO)
            return error;

        printf("Vertice %05u Grau: %05u\n", vertice_atual, grau);
    }

    printf("\n----------------- Termino da Impressão -----------------\n");
    return SUCESSO;
}