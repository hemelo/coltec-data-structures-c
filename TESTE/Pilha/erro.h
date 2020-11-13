#pragma once

#ifndef ERRO_H_
#define ERRO_H_

#include <stdint.h>

/* Inclusões */

/* Constantes */

#define SUCESSO (0)
#define ERRO (!SUCESSO)

/// Valor inicial a partir dos quais os erros de lista aparecem
#define PILHA_ERROS_OFFSET                (144) // [0x90:0x9F] / [144-159]

/* Erros */
#define ERRO_PILHA_VAZIA                  (PILHA_ERROS_OFFSET + 0)
#define ERRO_PILHA_ITEM_NAO_ENCONTRADO    (PILHA_ERROS_OFFSET + 1)
#define ERRO_PILHA_CHEIA                  (PILHA_ERROS_OFFSET + 2)
#define ERRO_ARQUIVO 					  (PILHA_ERROS_OFFSET + 3)
/// Tipo Erro
typedef unsigned char erro_t;

#endif