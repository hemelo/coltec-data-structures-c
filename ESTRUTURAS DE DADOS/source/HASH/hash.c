/**
 * @file hash.c
 * @author Henrique Fernandes de Castro Melo (hmelo2509@gmail.com)
 * @brief Arquivo com asa implementacoes de Hash de tipo generico
 * @version 0.1
 * @date 2020-11-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "hash.h"
#include "../tipos.h"
#include "../erro.h"
#include "../LISTA/listaLE.h"

/**
 * @brief Função hash
 * 
 * @param tabela Apontador para a tabela
 * @param key Chave para gerar hash
 * @return uint32_t Valor gerado pela funcao hash
 */
 static uint32_t hashing(hashTable_t * tabela, dados_t key){
     return ((uint32_t) key % (tabela->tamanho));
 }

/**
 * @brief Função que cria a tabela hash
 * 
 * @param nova_tabela Apontador para o endereço que receberá a tabela hash
 * @param tamanho_tabela Tamanho da tabela hash
 * @param tipo_tabela Tipo de tabela hash
 * @return erro_t Retorna um erro em caso de ocorrer erro
 */
erro_t hashTable_criar(hashTable_t ** nova_tabela, uint32_t tamanho_tabela, hashTipo_t tipo_tabela){
    uint16_t i; 

    // Alocacao da tabela na memória
    *nova_tabela = (hashTable_t *) malloc(sizeof(hashTable_t));

    // Verifica erro
    if(!nova_tabela)
        return ERRO_ALOCACAO;

    // Inicializa a tabela hash
    (*nova_tabela)->n_colunas = 0;
    (*nova_tabela)->tamanho = tamanho_tabela;
    (*nova_tabela)->tipo = tipo_tabela;

    // Aloca o tipo de dado que vai ser armazenado de acordo com o fechamento da tabela hash
    if(tipo_tabela == aberto)
        (*nova_tabela)->data = (listaES_t **) malloc(sizeof(listaES_t *) * tamanho_tabela);
    else
        (*nova_tabela)->data = (dados_t **) malloc(sizeof(dados_t *) * tamanho_tabela);

    for(i = 0; i < tamanho_tabela; i++){
        (*nova_tabela)->data[i] = NULL;
    }
        
    return SUCESSO;
}

/**
 * @brief Função para liberar a tabela da memória
 * 
 * @param tabela Apontador para o endereço da tabela
 * @return erro_t Retorna um erro caso ocorra erro
 */
erro_t hashTable_destroi(hashTable_t ** tabela){
     uint16_t i;

    for(i = 0; i < (*tabela)->tamanho; i++){
        if((*tabela)->tipo == aberto)
            listaES_destroi((*tabela)->data[i]);
        else
            free((*tabela)->data[i]);
    }
    
    free(*tabela);
}

/**
 * @brief Função auxiliar para inserção de dados na tabela hash
 * 
 * @param tabela Apontador para a tabela
 * @param hash Recebe o hash
 * @param n_tentativas Apontador para o endereço do numero de tentativas
 * @return uint32_t Novo hash
 */
static uint32_t hashTable_rehashing(hashTable_t * tabela, uint32_t hash, uint32_t n_tentativas){
    return ((hash + (COEFICIENTE_REHASH_1 * n_tentativas * n_tentativas) + (COEFICIENTE_REHASH_2) * n_tentativas * n_tentativas) % ((uint32_t) tabela->tamanho));
}

/**
 * @brief Função de inserção de dados na tabela hash
 * 
 * @param tabela Apontador para a tabela
 * @param data Dados a serem inseridos
 * @return erro_t Retorna erro em caso de ocorrer erro
 */
erro_t hashTable_insere(hashTable_t * tabela, dados_t data){
    uint32_t hash = hashing(tabela, data);
    bool_t error;

    if(!tabela)
        return ERRO_ALOCACAO;
    
    if(tabela->tipo == aberto){
        listaES_t * l = (listaES_t *) tabela->data[hash];

        if(l == NULL)
            l = (listaES_t *) listaES_criar();

        if(l == NULL)
            return ERRO_ALOCACAO;

        error = listaES_insere(l, data);
    
        if(error != SUCESSO)
            return error;

        tabela->data[hash] = l;
    }
    else{
        dados_t * d = (dados_t *) tabela->data[hash];
        
        if(d == NULL){
            d = (dados_t *) malloc (sizeof(dados_t));

            if(d == NULL)
                return ERRO_ALOCACAO;

            d = data;
            tabela->data[hash] = d;
        }
        else{
            uint32_t rehash;

            if(tabela->n_colunas == tabela->tamanho)
                return ERRO_TABELA_CHEIA;
                
            for(uint32_t i = 0; i < tabela->tamanho; i++){
                rehash = hashTable_rehashing(tabela, hash, i);
                d = tabela->data[rehash];

                if(d == NULL)
                    break;
            }

            d = data;
            tabela->data[rehash] = d;

            if(error != SUCESSO)
                return error;
        }
    }

    tabela->n_colunas++;

    return SUCESSO;
}

/**
 * @brief Função de remoção de dados da tabela hash
 * 
 * @param tabela Apontador para a tabela
 * @param data Dado a ser removido
 * @return erro_t Retorna erro em caso de ocorrer erro
 */
erro_t hashTable_remove(hashTable_t * tabela, dados_t data){
    uint16_t hash = hashing(tabela, data);
    uint32_t pos;
    bool_t res;
    erro_t error;

    if(!tabela)
        return ERRO_ALOCACAO;

    if(tabela->tipo == aberto){
        listaES_t * l = (listaES_t *) tabela->data[hash];
        error = listaES_removeElemento(l, data);
        
        if(error != SUCESSO)
            return error;

        if(listaES_estaVazia(l) == VERDADEIRO){
            listaES_destroi(l);
            tabela->data[hash] = NULL;
        }
        else{
            tabela->data[hash] = l;
        }
    }
    else{
        error = hashTable_busca(tabela, data, &res, &pos);
        
        if(error != SUCESSO)
            return error;

        if(res == FALSO)
            return ERRO_NAO_ENCONTRADO;

        free((dados_t *) tabela->data[pos]);
        tabela->data[pos] = NULL;
    }

    tabela->n_colunas--;

    return SUCESSO;
}

/**
 * @brief Função de busca de dados na tabela
 * 
 * @param tabela Apontador para a tabela
 * @param data Dado que está sendo buscado
 * @param resultado Resultado da busca
 * @param pos Apontador para a posicao do dado caso encontrado
 * @return erro_t Retorna erro em caso de ocorrer erro
 */
erro_t hashTable_busca(hashTable_t * tabela, dados_t data, bool_t * resultado, uint32_t * pos){
    uint16_t hash = hashing(tabela, data);
    erro_t error;
    bool_t p;

    *pos = hash;

    if(!tabela)
        return ERRO_ALOCACAO;

    if(tabela->tipo == aberto){
        listaES_t * l = (listaES_t *) tabela->data[hash];

        if(l != NULL){
            *resultado = listaES_buscar(l, data, &p);
        }
        else{
            *resultado = FALSO;
        }
    }
    else{
        dados_t * d = (dados_t *) tabela->data[hash];
        uint32_t rehash;

        if(d != NULL && d == data){
            *resultado = VERDADEIRO;
        }
        else{
            *resultado = FALSO;

            for(uint32_t i = 0; i < tabela->tamanho; i++){
                rehash = hashTable_rehashing(tabela, hash, i);
                d = (dados_t *) tabela->data[rehash];
                
                if(d != NULL && d == data){
                    *resultado = VERDADEIRO;
                    *pos = rehash;
                    break;
                }
            }
        }
    }

    return SUCESSO;
}

/**
 * @brief Função auxiliar para impressão de tabela hash aberto
 * 
 * @param tabela Apontador para a tabela
 */
static void hashTable_imprimeAberto(hashTable_t * tabela){
    itemLista_t * atual;
    itemLista_t * proximo;

    printf("------ Impressao de Hash ------\n\n");
   
    for(uint32_t i = 0; i < tabela->tamanho; i++){
        listaES_t * lista = (listaES_t *) tabela->data[i];

        if(lista == NULL)
            continue;
        
        printf("Hash: %u / Dado: ", i);

        proximo = lista->primeiro;

        while(proximo != NULL){
            atual = proximo;
            proximo = atual->proximo;

            printf("%u ", atual->dados);
        }
        printf("\n");
    }

    printf("\n------ Fim da Impressao ------");
}

/**
 * @brief Função auxiliar para impressão de tabela hash fechada
 * 
 * @param tabela Apontador para a tabela
 */
static void hashTable_imprimeSeparado(hashTable_t * tabela){
    printf("------ Impressao de Hash ------\n\n");
   
    for(uint32_t i = 0; i < tabela->tamanho; i++){
        dados_t * dado = (dados_t *) tabela->data[i];

        if(dado == NULL)
            continue;
        
        printf("Hash: %u / Dado: %u\n", i , dado);
    }

    printf("\n------ Fim da Impressao ------");
}

/**
 * @brief Função de impressão de tabela
 * 
 * @param tabela Apontador para a tabela hash
 * @return erro_t Retorna um erro em caso de erro
 */
erro_t hashTable_imprime(hashTable_t * tabela){
    if(tabela->tipo == aberto)
        hashTable_imprimeAberto(tabela);
    else
        hashTable_imprimeSeparado(tabela);
}
