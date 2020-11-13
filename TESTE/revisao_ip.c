/**
 * @file revisao_ip.c
 * @author Henrique Fernandes de Castro Melo
 * @brief 
 * @version 0.2
 * @date 2020-11-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "tipos.h"



int main(int argc, char * argv[]){
    void ** matriz;

}

void ** alocaMatriz(void ** matriz)
{
    // Aloca as Duas Colunas
	matriz = malloc(sizeof(uint16_t *) + sizeof(const char *));

    // Aloca as Linhas da Primeira Coluna
	matriz[0] = malloc(NUMERO_INGREDIENTES * sizeof(int));

    // Aloca as Linhas da Segunda Coluna
	matriz[1] = malloc(NUMERO_INGREDIENTES * sizeof(char *));
	return(matriz);
}

void bemVindo(){
	printf(" __________________________________\n");
	printf("|                                   |\n");
	printf("|        Exercicio de Revisao      |\n");
	printf("|         Henrique Fernandes       |\n");
	printf("|__________________________________|\n\n");
}