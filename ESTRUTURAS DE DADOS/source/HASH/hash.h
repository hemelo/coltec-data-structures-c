/**
 * @file hash.h
 * @author Henrique Fernandes de Castro Melo (hmelo2509@gmail.com)
 * @brief Arquivo com as definicoes de Hash de tipo generico
 * @version 0.1
 * @date 2020-11-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include <stdio.h>
#include <stdint.h>
#include "../dados.h"
#include "../tipos.h"

#ifndef __HASH_h__
#define __HASH_h__

#define COEFICIENTE_REHASH_1 (2)
#define COEFICIENTE_REHASH_2 (3)

#define ERRO_HASH_OFFSET (128)
#define ERRO_NAO_ENCONTRADO (ERRO_HASH_OFFSET + 0)
#define ERRO_TABELA_CHEIA (ERRO_HASH_OFFSET + 1)

// Tipo que representa um tipo de tabela hash
typedef enum hashTipo_s{
    fechado,
    aberto
}hashTipo_t;

// Tipo que representa uma tabela hash simples
typedef struct hashTable_s{
    void ** data;
    hashTipo_t tipo;
    uint32_t tamanho;
    uint32_t n_colunas;
}hashTable_t;

erro_t hashTable_criar(hashTable_t ** nova_tabela, uint32_t tamanho_tabela, hashTipo_t tipo_tabela);
erro_t hashTable_destroi(hashTable_t ** tabela);
erro_t hashTable_insere(hashTable_t * tabela, dados_t data);
erro_t hashTable_remove(hashTable_t * tabela, dados_t data);
erro_t hashTable_imprime(hashTable_t * tabela);
erro_t hashTable_busca(hashTable_t * tabela, dados_t data, bool_t * resultado, uint32_t * pos);

#endif // hash.h