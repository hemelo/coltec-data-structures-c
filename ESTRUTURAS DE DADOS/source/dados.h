#pragma once

#include <stdio.h>
#include <stdint.h>
#include "./GRAFO/grafo.h"

#ifndef __DADOS_H__
#define __DADOS_H__

// Tipo que representa dados
typedef vertice_t dados_t;

// Ponteiro para função que compara dois dados do tipo dados_t
typedef uint8_t(* comparaDados_f)(dados_t, dados_t);

#endif // DADOS_H
