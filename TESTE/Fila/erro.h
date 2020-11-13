#pragma once

#ifndef ERRO_H_
#define ERRO_H_

#include <stdint.h>

/* Inclusões */

/* Constantes */

#define SUCESSO (0)
#define ERRO (!SUCESSO)

/// Valor inicial a partir dos quais os erros de lista aparecem
#define FILA_ERROS_OFFSET                (144) // [0x90:0x9F] / [144-159]

/* Erros */
#define ERRO_FILA_VAZIA               (FILA_ERROS_OFFSET + 0)
#define ERRO_FILA_CHEIA               (FILA_ERROS_OFFSET + 1)

/// Tipo Erro
typedef unsigned char erro_t;

#endif