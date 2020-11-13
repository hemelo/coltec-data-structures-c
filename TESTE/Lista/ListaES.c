#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "listaES.h"
#include "tipos.h"

uint16_t ES_gerarNumero(Lista * lista);

/* Funções de Criação / Destruição da Lista */

Lista * ListaES_criar(){
    Lista * lista = (Lista *) malloc(sizeof(Lista));
    listaES_inicializar(lista);

    return lista;
}

void listaES_inicializar(Lista * lista){
    lista->nItems = 0;
    lista->primeiroItem = NULL;
}

void listaES_excluir(Lista * lista){
    ItemLista * atual, * proximo;
    atual = lista->primeiroItem;

    while (atual != NULL) {
        proximo = atual->proximoItem;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

/* Funcoes Auxiliares */

boolean listaES_estaVazia(Lista * lista){
    if(lista->nItems == 0) { return VERDADEIRO; }
    return FALSO;
}

boolean listaES_itemPosicao(Lista * lista, uint16_t posicao, ItemLista ** itemProcurado){
    if(listaES_estaVazia(lista)) { return ERRO; }

    ItemLista * atual = lista->primeiroItem;
    
    if(posicao > lista->nItems){ 
        //Procura Ultima Posicao
        while(atual->proximoItem != NULL){
            atual = atual->proximoItem;
        }
    }
    else{
        while(posicao-- != 0){
            atual = atual->proximoItem;
        }
    }

    *itemProcurado = atual;
    return SUCESSO;
}

// Funcoes de Inserção / Remocao

boolean listaES_insereOrdenado(Lista * lista, Dados dados){
    ItemLista * novoItem = (ItemLista *) malloc(sizeof(ItemLista));
    novoItem->dados = dados;

    if(!listaES_estaVazia(lista)){
        ItemLista * anterior = NULL;
        ItemLista * atual = lista->primeiroItem;

        for(int i = 0; i < lista->nItems; i++){
            if(ES_Dados_comparar(dados, atual->dados) <= 0) { break; }

            anterior = atual;
            atual = atual->proximoItem;
        }

        if(anterior != NULL){
            novoItem->proximoItem = atual;
            anterior->proximoItem = novoItem;
        }
        else{
            novoItem->proximoItem = atual;
            lista->primeiroItem = novoItem;
        }
    }
    else{
        lista->primeiroItem = novoItem;
        novoItem->proximoItem = NULL;
    }

    lista->nItems++;
    return SUCESSO;
}

boolean listaES_insereInicio(Lista * lista, Dados dados){
    return listaES_inserePosicao(lista, dados, 0);
}

boolean listaES_insereFinal(Lista * lista, Dados dados){
    return listaES_inserePosicao(lista, dados, lista->nItems);
}

boolean listaES_inserePosicao(Lista * lista, Dados dados, uint16_t posicao){
    ItemLista * novoItem = (ItemLista *) malloc(sizeof(ItemLista));
    novoItem->dados = dados;

    if(posicao == 0){
        novoItem->proximoItem = lista->primeiroItem;
        lista->primeiroItem = novoItem;
    }
    else{
        ItemLista * anterior;
        
        boolean erro = listaES_itemPosicao(lista, posicao - 1, &anterior);
        if(erro != SUCESSO) { return ERRO; }

        novoItem->proximoItem = anterior->proximoItem;
        anterior->proximoItem = novoItem;
    }

    lista->nItems++;
    return SUCESSO;
}

boolean listaES_removerItem(Lista * lista, Dados dados){
    ItemLista * anterior = NULL;
    ItemLista * atual = lista->primeiroItem;

    while(atual != NULL){
        if(ES_Dados_comparar(atual->dados, dados) == 0) break;

        anterior = atual;
        atual = atual->proximoItem;
    }

    if(atual == NULL) { 
        return ERRO; 
    }
    else{
        if(anterior == NULL){
            lista->primeiroItem = atual->proximoItem;
        }
        else{
            anterior->proximoItem = atual->proximoItem;
        }
    }

    free(atual);
    lista->nItems--;
    return SUCESSO;
}

boolean listaES_removerInicio(Lista * lista){
    return listaES_removerPosicao(lista, 0);
}

boolean listaES_removerFinal(Lista * lista){
    return listaES_removerPosicao(lista, lista->nItems);
}

boolean listaES_removerPosicao(Lista * lista, uint16_t posicao){
    ItemLista * anterior;
    ItemLista * remover;

    if(posicao == 0){
        remover = lista->primeiroItem;
        lista->primeiroItem = remover->proximoItem;
    }
    else{
        boolean erro = listaES_itemPosicao(lista, posicao - 1, &anterior);
        if(erro != SUCESSO) { return ERRO; }

        remover = anterior->proximoItem;
        anterior->proximoItem = remover->proximoItem;
    }

    free(remover);
    lista->nItems--;
    return SUCESSO;
}

// Funcoes de Output

void listaES_imprimirEmArquivo(Lista * lista){
    ItemLista * item = lista->primeiroItem;

    FILE * impressao = fopen("impressao.txt", "w");
    if(impressao != NULL){
        for(int i = 0; i < lista->nItems; i++){
            fprintf(impressao, "%s", (item->dados).nome);
            item = item->proximoItem;
        }
    }
    else{
        printf("Ocorreu um erro na manipulação de Arquivos!");
    }
}

void listaES_imprimir(Lista * lista){
    ItemLista * item = lista->primeiroItem;
    do{
        Dados info = item->dados;
        printf("%s", info.nome);
        item = item->proximoItem;
    }while(item->proximoItem != NULL);
}

/* Auxiliares */

uint16_t ES_gerarNumero(Lista * lista){
    if(!listaES_estaVazia(lista)) { return rand() % lista->nItems; }
    else { return 0; }
}

int16_t ES_Dados_comparar(Dados info1, Dados info2){
    for(int i = 0; info1.nome[i]; i++){
        info1.nome[i] = tolower(info1.nome[i]);
    }

    for(int i = 0; info2.nome[i]; i++){
        info2.nome[i] = tolower(info2.nome[i]);
    }
    return strncmp(info1.nome, info2.nome, 4);
}