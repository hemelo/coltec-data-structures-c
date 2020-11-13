#pragma once

#include <stdio.h>

#ifndef __ERROS_H__
#define __ERROS_H__

#define SUCESSO (0)
#define ERRO_OFFSET (1)
#define PARAMETRO_INVALIDO (ERRO_OFFSET + 0)
#define ERRO_ALOCACAO (ERRO_OFFSET + 1)

// Tipo que representa um erro
typedef unsigned char erro_t;

#endif // ERROS_H

