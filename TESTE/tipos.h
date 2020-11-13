/**
 * @file tipos.h
 * @author Henrique Fernandes de Castro Melo
 * @brief 
 * @version 0.1
 * @date 2020-11-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#ifndef TIPOS_H
#define TIPOS_H

#include <stdio.h>
#include <stdint.h>

static const ingrediente_t INGREDIENTES[] = {
	{ 8885, "Tomate Sem Toxico"},
	{ 1985, "Queijo Mucarela"},
	{ 1907, "Manjericao"},
	{ 1410, "Farinha de Trigo"},
	{ 1720, "Batata"}
};

#define NUMERO_INGREDIENTES (sizeof(INGREDIENTES)/sizeof(ingrediente_t))

struct ingrediente_s{
	uint16_t codigo;
	char * descricao;
};

typedef struct ingrediente_s ingrediente_t;

#endif