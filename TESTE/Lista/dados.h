/**
 * @file dados.h
 * @author Henrique Fernandes de Castro
 * @brief 
 * @version 0.1
 * @date 2020-07-13
 * 
 */

#pragma once

#ifndef DADOS_H
#define DADOS_H

#include <stdint.h>
#include "tipos.h"

/**
 * @brief Estrutura que contém os dados de uma pessoa
 *
 */
struct Dados{
    char nome[TAMANHO_PADRAO_STRING];
};
// Tipo que representa a estrutura Dados
typedef struct Dados Dados;

// Funcoes exportadas
int16_t ES_Dados_comparar(Dados info1, Dados info2);

#endif