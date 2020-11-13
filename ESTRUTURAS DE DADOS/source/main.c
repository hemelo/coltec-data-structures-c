#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "erro.h"
#include "./HASH/hash.h"
#include "./GRAFO/grafo.h"
#include "./GRAFO/busca.h"
#include "./GRAFO/grafoMA.h"
#include "./GRAFO/grafoLA.h"
#include "./GRAFO/buscaMA.h"

int main(int argc, char ** argv) {
    erro_t erro;

    grafoMA_t * grafo;
    grafoLA_t * grafo_2;

    erro = grafoMA_cria(&grafo, 6, grafoDirecionado);
    erro = grafoMA_criaAresta(grafo, 0, 1, 88);
    erro = grafoMA_criaAresta(grafo, 1, 2, 85);
    erro = grafoMA_criaAresta(grafo, 2, 3, 19);
    erro = grafoMA_criaAresta(grafo, 3, 1, 50);
    erro = grafoMA_criaAresta(grafo, 4, 2, 8);
    erro = grafoMA_criaAresta(grafo, 4, 5, 8);
    grafoMA_imprime(grafo);
    grafoMA_imprimeAdjacentes(grafo);
    grafoMA_imprimeGraus(grafo);
    buscaMA_emLargura(grafo, 0);
    buscaMA_emProfundidade(grafo, 0, simples, ordem);
    buscaMA_emProfundidade(grafo, 0, completa, ordem);

    printf("\n");

    erro = grafoLA_cria(&grafo_2, 6, grafoDirecionado);
    erro = grafoLA_criaAresta(grafo_2, 0, 1, 88);
    erro = grafoLA_criaAresta(grafo_2, 1, 2, 85);
    erro = grafoLA_criaAresta(grafo_2, 2, 3, 19);
    erro = grafoLA_criaAresta(grafo_2, 3, 1, 50);
    erro = grafoLA_criaAresta(grafo_2, 4, 2, 8);
    erro = grafoLA_criaAresta(grafo_2, 4, 5, 8);
    grafoLA_imprime(grafo_2);
    grafoLA_imprimeAdjacentes(grafo_2);
    grafoLA_imprimeGraus(grafo_2);
    
    grafoMA_destroi(&grafo);
    grafoLA_destroi(&grafo_2);
    
    /*
    hashTable_t * tabela;
    erro = hashTable_criar(&tabela, 6, fechado);
    erro = hashTable_insere(tabela, 2);
    erro = hashTable_insere(tabela, 3);
    erro = hashTable_insere(tabela, 1);
    erro = hashTable_insere(tabela, 4);
    erro = hashTable_insere(tabela, 5);
    erro = hashTable_insere(tabela, 6);
    erro = hashTable_insere(tabela, 7);
    erro = hashTable_insere(tabela, 8);
    erro = hashTable_insere(tabela, 9);
    erro = hashTable_insere(tabela, 10);
    erro = hashTable_insere(tabela, 11);
    erro = hashTable_insere(tabela, 12);
    erro = hashTable_remove(tabela, 6);
    printf("%u", erro);
    hashTable_imprime(tabela);
    hashTable_destroi(&tabela);
    */

    printf("Pressione enter para continuar...");
    setbuf(stdin,NULL);
    getchar();

    return SUCESSO;
}