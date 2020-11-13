/**
 * @file dados.h
 * @author Henrique Fernandes de Castro
 * @brief 
 * @version 0.1
 * @date 2020-08-17
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
struct dados_s{
    float valor;
};
// Tipo que representa a estrutura Dados
typedef struct dados_s dados_t;

#endif