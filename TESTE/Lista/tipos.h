/**
 * @file tipos.h
 * @author Henrique Fernandes de Castro
 * @brief 
 * @version 0.1
 * @date 2020-07-13
 * 
 */

#pragma once

#ifndef TIPOS_H
#define TIPOS_H

#define TAMANHO_PADRAO_STRING 25
#define VERDADEIRO 1
#define FALSO (!VERDADEIRO)
#define SUCESSO (0)
#define ERRO (!SUCESSO)

// Tipo que representa booleana
typedef unsigned char boolean;

// Tipo que representa uma string
typedef char * string;
#endif 
