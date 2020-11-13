#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "listaES.h"
#include "tipos.h"

void ES_teste(){
    Lista * lista = ListaES_criar();
    ES_testeDesordenada(&lista);
    if(lista == NULL) printf("OK CERTO.");
}

void ES_testeDesordenada(Lista ** lista){
    FILE * arquivo = fopen("nomes.txt", "r");
    if(arquivo == NULL){ exit(0); }

    // Seed para geracao de numerosa aleatorios
    srand((unsigned int) time(NULL));

     // Leitura do arquivo e insercao na lista de maneira ORDENADA!
    Dados dados;
    clock_t comeco,fim;

    boolean inseriu;
    uint16_t posicao;

    comeco = clock();
    while(fgets(dados.nome, TAMANHO_PADRAO_STRING, arquivo) != NULL){
        posicao = ES_gerarNumero(*lista);
        listaES_inserePosicao(*lista, dados, posicao);
    }
    fim = clock();
    printf("O processador levou %lf MILISEGUNDOS para inserir %d nomes de forma DESORDENADA em uma LISTA ENCADEADA SIMPLES!", 1000*((double) (fim - comeco)) / CLOCKS_PER_SEC, (*lista)->nItems);

    /* Teste de Remocao
    strcpy(dados.nome, "Mea Yu");
    boolean removeu = listaES_removerItem(lista, dados);
    boolean removeuPosicao = listaES_removerPosicao(lista, 3);
    */

     // Testar Funcionamento
    listaES_imprimirEmArquivo(*lista);
    
    // Fecha Arquivo e Libera a lista
    fclose(arquivo);
    listaES_excluir(*lista);
}

int main(int argc, char ** argv){
    //ES_testeOrdenada();
    ES_teste();
    //ED_testeOrdenada();
    //ED_testeDesordenada();
    //EC_testeOrdenada();
    //EC_testeDesordenada();
    system("pause");
}

