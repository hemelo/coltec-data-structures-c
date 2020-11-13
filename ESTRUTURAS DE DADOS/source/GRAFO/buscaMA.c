/**
 * @file buscaMA.c
 * @author Henrique Fernandes de Castro Melo (hmelo2509@gmail.com)
 * @brief Arquivo com as implementacoes de Busca em Grafo do tipo Matriz Adjacencia
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
#include "busca.h"
#include "buscaMA.h"
#include "grafoMA.h"
#include "../tipos.h"
#include "../erro.h"
#include "../LISTA/listaLE.h"
#include "../FILA/filaLE.h"
#include "../PILHA/pilhaLE.h"

/**
 * @brief Função auxiliar que inicializa o vetor de Struct que contém os dados da Busca em Grafo
 * 
 * @param grafo Apontador para o grafo
 * @param tipo  Tipo de Busca
 * @return dadoVertice_t* Vetor com os dados de todos os vértices
 */
static dadoVertice_t * buscaMA_inicializaVetorDadosAuxiliares(grafoMA_t * grafo, tipoBusca_t tipo){

    // Aloca o vetor com a quantidade de vértices do grafo
    dadoVertice_t * dados_busca = (dadoVertice_t *) malloc(grafo->n_vertices * sizeof(dadoVertice_t));

    // Inicializa o vetor com dados pré-estabelecidos
    for(int i = 0; i < grafo->n_vertices; i++){
        
        // Se o tipo for em profundidade, é alocado um vetor para salvar dois timestamps
        if(tipo == emProfundidade)
            dados_busca[i].timestamps = (uint32_t *) calloc(2, sizeof(uint32_t));

        // Dados padrões pra cada vértice
        dados_busca[i].predecessor = PREDECESSOR_DESCONHECIDO;
        dados_busca[i].arvore = ARVORE_DESCONHECIDA;
        dados_busca[i].marca = branco;
    }

    return dados_busca;
}

/**
 * @brief Função auxiliar que busca vértices adjacentes a um vértice
 * 
 * @param grafo Apontador para o grafo
 * @param vertice_de_busca Vértice referência 
 * @param lista_vertices_adjacentes Apontador para o local que receberá a lista com os vértices adjacentes a um vértice
 * @return erro_t Retorna um erro em caso de ocorrer erro 
 */
erro_t buscaMA_getVerticesAdjacentes(grafoMA_t * grafo, vertice_t vertice_de_busca, listaES_t ** lista_vertices_adjacentes){
    uint16_t i; 
    erro_t error;
    bool_t resultado;

    *lista_vertices_adjacentes = listaES_criar();
     
    if(lista_vertices_adjacentes == NULL)
        return PARAMETRO_INVALIDO;

    if(vertice_de_busca >= grafo->n_vertices)
        return VERTICE_INVALIDO;

    for(i = 0; i < grafo->n_vertices; i++){
        error = grafoMA_verificaAresta(grafo, vertice_de_busca, i, &resultado);

        if(error != SUCESSO)
            return error;

        if(resultado == VERDADEIRO){
            listaES_insere(*lista_vertices_adjacentes, i);
        }
    }

    return SUCESSO;
}

/**
 * @brief Função auxiliar que imprime o resultado da busca em largura
 * 
 * @param grafo Apontador para o grafo
 * @param dados_busca Apontador para os dados dos vértices
 * @param vertice_source Vértice no qual a busca começou
 */
static void buscaMA_imprimirBuscaLargura(grafoMA_t * grafo, dadoVertice_t * dados_busca, vertice_t vertice_source){
    uint16_t i;
    vertice_t predecessor;

    printf("\n----- Impressao de Busca por Largura -----\n\n");
    printf("Fonte de Busca: %u\n\n", vertice_source);

    for(i = 0; i < grafo->n_vertices; i++){
        printf("Vértice: %05u ", i);

        predecessor = dados_busca[i].predecessor;
        if(predecessor != PREDECESSOR_DESCONHECIDO && predecessor != PREDECESSOR_SOURCE)
            printf("Predecessor: %05u \n", predecessor);
        else
            printf("Predecessor: %s \n", predecessor == PREDECESSOR_DESCONHECIDO ? "DESC." : "FONTE");

        //printf("Distância da Fonte: %05u\n", 0);
    }
    printf("\n------------ Fim da Impressao ------------\n");
}

/**
 * @brief Função auxiliar que imprime o resultado da busca em profundidade
 * 
 * @param grafo Apontador para o grafo
 * @param dados_busca Apontador para o vetor de dados dos vértices
 * @param vertice_source Vértice no qual a busca começou
 * @param profundidade Tipo de busca em profundidade
 */
static void buscaMA_imprimirBuscaProfundidade(grafoMA_t * grafo, dadoVertice_t * dados_busca, vertice_t vertice_source, tipoProfundidade_t profundidade){
    uint16_t i;
    vertice_t predecessor;
    int32_t arvore;

    if(profundidade == completa)
        printf("\n----- Impressao de Busca por Profundidade Completa -----\n\n");
    else
        printf("\n----- Impressao de Busca por Profundidade Simples -----\n\n");

    printf("Fonte de Busca: %u\n\n", vertice_source);

    for(i = 0; i < grafo->n_vertices; i++){
        printf("Vértice: %05u ", i);

        predecessor = dados_busca[i].predecessor;
        if(predecessor != PREDECESSOR_DESCONHECIDO && predecessor != PREDECESSOR_SOURCE)
            printf("Predecessor: %05u ", predecessor);
        else
            printf("Predecessor: %s ", predecessor == PREDECESSOR_DESCONHECIDO ? "DESC." : "FONTE");

        //printf("Distância da Fonte: %05u ", 0);

        printf("Timestamps: %05u %05u ", dados_busca[i].timestamps[0], dados_busca[i].timestamps[1]);

        arvore = dados_busca[i].arvore;
        if(arvore != ARVORE_DESCONHECIDA)
            printf("Arvore: %05u \n", arvore);
        else
            printf("Arvore: %s \n", "DESC.");

    }
    
    printf("\n---------------------- Fim da Impressao ----------------------\n");
}

/**
 * @brief Função que faz a busca em largura do grafo
 * 
 * @param grafo Apontador para o grafo
 * @param vertice_source Fonte de início para busca
 * @return erro_t Retorna um erro em caso de ocorrer erro
 */
erro_t buscaMA_emLargura(grafoMA_t * grafo, vertice_t vertice_source){
    uint16_t i;
    uint32_t temp;
    erro_t error;
    vertice_t vertice_de_busca;
    filaES_t * queue;
    listaES_t * lista_vertices_adjacentes;
    itemLista_t * adjacente; 
    dadoVertice_t * dados_busca;

    if(vertice_source >= grafo->n_vertices)
        return VERTICE_INVALIDO;

    // Inicializa vetor de dados dos vértices
    dados_busca = buscaMA_inicializaVetorDadosAuxiliares(grafo, emLargura);

    // Insere os dados referentes ao vértice fonte
    dados_busca[vertice_source].predecessor = PREDECESSOR_SOURCE;
    dados_busca[vertice_source].marca = cinza;
    
    // Cria a queue de vértices e insere o vértice fonte
    queue = filaES_criar(); 
    filaES_insere(queue, vertice_source);

    // Enquanto ter itens na fila, a busca continua
    while(queue->itens != 0){

        // Remove o primeiro da fila e o seleciona para buscar vértices adjacentes a ele 
        error = filaES_remove(queue, &vertice_de_busca);

        if(error != SUCESSO)
            return error;
       
        // Busca os adjacentes ao vértice de busca
        error = buscaMA_getVerticesAdjacentes(grafo, vertice_de_busca, &lista_vertices_adjacentes);
        
        if(error != SUCESSO)
            return error;
       
        // Vértice removido da queue é marcado como visitado e encontrado adjacentes
        dados_busca[vertice_de_busca].marca = preto;

        // Seleciona o primeiro adjacente encontrado com base em Ordem
        adjacente = lista_vertices_adjacentes->primeiro;

        // Insere na fila todos os adjacentes que ainda não haviam sido encontrados (que não estão na fila)
        while(adjacente != NULL){
            if(filaES_buscar(queue, adjacente->dados, &temp) == FALSO && dados_busca[adjacente->dados].marca == branco){
                filaES_insere(queue, adjacente->dados);

                // Atualiza os dados dos vértices válidos e os marca como visitados
                dados_busca[adjacente->dados].marca = cinza;
                dados_busca[adjacente->dados].predecessor = vertice_de_busca;
                dados_busca[adjacente->dados].arvore = 1;
            }
            adjacente = adjacente->proximo;
        }

        // Limpa a lista
        listaES_destroi(lista_vertices_adjacentes);
    }

    buscaMA_imprimirBuscaLargura(grafo, dados_busca, vertice_source);

    free(dados_busca);
    filaES_destroi(queue);

    return SUCESSO;
}

/**
 * @brief Função auxiliar e recursiva para a busca em profundidade
 * 
 * @param grafo Apontador para o grafo
 * @param vertice_source Fonte de início para busca
 * @param dados_busca Apontador para o vetor de dados dos vértices
 * @param posicao Apontador para o timestamp atual
 * @param arvore Arvore formada pela busca em profundidade atual
 * @return dadoVertice_t* Retorna dados dos vértices
 */
static dadoVertice_t * buscaMA_auxEmProfundidade(grafoMA_t * grafo, vertice_t vertice_source, dadoVertice_t * dados_busca, uint32_t * posicao, uint32_t arvore){
    uint16_t i;
    erro_t error;
    itemLista_t * adjacente; 
    listaES_t * lista_vertices_adjacentes;
    
    lista_vertices_adjacentes = listaES_criar();
    error = buscaMA_getVerticesAdjacentes(grafo, vertice_source, &lista_vertices_adjacentes);

    if(error != SUCESSO)
        return NULL;

    adjacente = lista_vertices_adjacentes->primeiro;

    while(adjacente != NULL){
        if(dados_busca[adjacente->dados].marca == branco){
            dados_busca[adjacente->dados].predecessor = vertice_source;
            dados_busca[adjacente->dados].marca = cinza;
            dados_busca[adjacente->dados].timestamps[0] = ++(*posicao);
            dados_busca[adjacente->dados].arvore = arvore;

            dados_busca = buscaMA_auxEmProfundidade(grafo, adjacente->dados, dados_busca, posicao, arvore);
        }

        adjacente = adjacente->proximo;
    }
    
    dados_busca[vertice_source].marca = preto;
    dados_busca[vertice_source].timestamps[1] = ++(*posicao);

    listaES_destroi(lista_vertices_adjacentes);

    return dados_busca;
}

static erro_t buscaMA_profundidadeSimples(grafoMA_t * grafo, vertice_t vertice_source){
    dadoVertice_t * dados_busca;
    uint32_t posicao = 0;

    if(vertice_source >= grafo->n_vertices)
        return VERTICE_INVALIDO;

    dados_busca = buscaMA_inicializaVetorDadosAuxiliares(grafo, emProfundidade);
    dados_busca[vertice_source].predecessor = PREDECESSOR_SOURCE;
    dados_busca[vertice_source].marca = cinza;
    dados_busca[vertice_source].arvore = 1;

    dados_busca = buscaMA_auxEmProfundidade(grafo, vertice_source, dados_busca, &posicao, 1);
    buscaMA_imprimirBuscaProfundidade(grafo, dados_busca, vertice_source, simples);
}

static erro_t buscaMA_profundidadeCompleta(grafoMA_t * grafo, vertice_t vertice_source){
    dadoVertice_t * dados_busca;
    uint32_t i;
    uint32_t arvore = 1;
    uint32_t posicao = 0;
    vertice_t vertice_busca = vertice_source;
    
    if(vertice_source >= grafo->n_vertices)
        return VERTICE_INVALIDO;

    dados_busca = buscaMA_inicializaVetorDadosAuxiliares(grafo, emProfundidade);
    dados_busca[vertice_source].predecessor = PREDECESSOR_SOURCE;
    dados_busca[vertice_source].marca = cinza;
    dados_busca[vertice_source].arvore = 1;

    do{
        dados_busca = buscaMA_auxEmProfundidade(grafo, vertice_busca, dados_busca, &posicao, arvore);

        for(i = 0; i < grafo->n_vertices; i++){
            if(dados_busca[i].marca == branco){
                vertice_busca = i;
                dados_busca[vertice_busca].marca = cinza;
                dados_busca[vertice_busca].arvore = ++arvore;
                dados_busca[vertice_busca].predecessor = PREDECESSOR_DESCONHECIDO;
                dados_busca[vertice_busca].timestamps[0] = ++posicao;
                dados_busca[vertice_busca].timestamps[1] = ++posicao;
                break; 
            }else{
                vertice_busca = VERTICE_INVALIDO;
            }
        }
    }while(vertice_busca != VERTICE_INVALIDO);
    
    buscaMA_imprimirBuscaProfundidade(grafo, dados_busca, vertice_source, completa);
}

/**
 * @brief Função auxiliar para selecionar o tipo de busca em profundidade a ser feito, com base na escolha do usuário
 * 
 * @param grafo  Apontador para o grafo
 * @param vertice_source Vértice referência para a busca em profundidade
 * @param tipo Tipo de busca em profundidade a ser realizada 
 * @param prioridade Prioridade na busca
 * @return erro_t Retorna um erro em caso de ocorrer erro
 */
erro_t buscaMA_emProfundidade(grafoMA_t * grafo, vertice_t vertice_source, tipoProfundidade_t tipo, tipoPrioridade_t prioridade){
    buscaProfundidade_f funcao;

    // Seleciona a função de busca em profundidade com base nas escolhas do usuário
    switch(tipo){
        case simples: 
            switch(prioridade){
                case custo:
                // falta implementacao
                break;
                case ordem:
                funcao = buscaMA_profundidadeSimples;
                break;
            }
            break;
        case completa:
            switch(prioridade){
                case custo:
                // falta implementação
                case ordem:
                funcao = buscaMA_profundidadeCompleta;
                break;
            }
            break;
        default:
        funcao = buscaMA_profundidadeSimples;
    }

    //Executa a busca em profundidade
    funcao(grafo, vertice_source);
}