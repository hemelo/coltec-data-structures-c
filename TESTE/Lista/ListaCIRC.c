#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "listaCIRC.h"
#include "tipos.h"

uint16_t CIRC_gerarNumero(Lista * lista);

/* Funções de Criação / Destruição da Lista */

Lista * ListaC_criar(){
    Lista * lista = (Lista *) malloc(sizeof(Lista));
    listaC_inicializar(lista);

    return lista;
}

void listaC_inicializar(Lista * lista){
    lista->nItems = 0;
    lista->primeiroItem = NULL;
}

void listaC_excluir(Lista * lista){
    ItemLista * atual, * proximo;
    atual = lista->primeiroItem;

    while (lista->nItems-- != 0) {
        proximo = atual->proximoItem;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

/* Funcoes Auxiliares */

boolean listaC_estaVazia(Lista * lista){
    if(lista->nItems == 0) { return VERDADEIRO; }
    return FALSO;
}

boolean listaC_itemPosicao(Lista * lista, uint16_t posicao, ItemLista ** itemProcurado){
    if(listaC_estaVazia(lista)) { return ERRO; }

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

boolean listaC_insereOrdenado(Lista * lista, Dados dados){
    ItemLista * novoItem = (ItemLista *) malloc(sizeof(ItemLista));
    novoItem->dados = dados;

    if(!listaC_estaVazia(lista)){
        ItemLista * anterior = NULL;
        ItemLista * atual = lista->primeiroItem;

        for(int i = 0; i < lista->nItems; i++){
            if(CIRC_Dados_comparar(dados, atual->dados) <= 0) { break; }

            anterior = atual;
            atual = atual->proximoItem;
        }

        if(anterior != NULL){
            novoItem->proximoItem = atual;
            anterior->proximoItem = novoItem;
        }
        else{
            
            ItemLista * percorrer;
            boolean erro = listaC_itemPosicao(lista, lista->nItems - 1, &percorrer);
            if(erro != SUCESSO) { return ERRO; }

            percorrer->proximoItem = novoItem;
            novoItem->proximoItem = atual;
            lista->primeiroItem = novoItem;
        }
    }
    else{
        lista->primeiroItem = novoItem;
        novoItem->proximoItem = novoItem;
    }

    lista->nItems++;
    return SUCESSO;
}

boolean listaC_insereInicio(Lista * lista, Dados dados){
    return listaC_inserePosicao(lista, dados, 0);
}

boolean listaC_insereFinal(Lista * lista, Dados dados){
    return listaC_inserePosicao(lista, dados, lista->nItems);
}

boolean listaC_inserePosicao(Lista * lista, Dados dados, uint16_t posicao){
    ItemLista * novoItem = (ItemLista *) malloc(sizeof(ItemLista));
    novoItem->dados = dados;

    if(posicao == 0){
        if(lista->nItems > 0){
            ItemLista * percorrer;
            boolean erro = listaC_itemPosicao(lista, lista->nItems - 1, &percorrer);
            if(erro != SUCESSO) { return ERRO; }
            percorrer->proximoItem = novoItem;
        }
        novoItem->proximoItem = lista->primeiroItem;
        lista->primeiroItem = novoItem;
    }
    else{
        ItemLista * anterior;
        
        boolean erro = listaC_itemPosicao(lista, posicao - 1, &anterior);
        if(erro != SUCESSO) { return ERRO; }

        novoItem->proximoItem = anterior->proximoItem;
        anterior->proximoItem = novoItem;
    }

    lista->nItems++;
    return SUCESSO;
}

boolean listaC_removerItem(Lista * lista, Dados dados){
    ItemLista * anterior = NULL;
    ItemLista * atual = lista->primeiroItem;

    while(atual != NULL){
        if(CIRC_Dados_comparar(atual->dados, dados) == 0) break;

        anterior = atual;
        atual = atual->proximoItem;
    }

    if(atual == NULL) { 
        return ERRO; 
    }
    else{
        if(anterior == NULL){
            ItemLista * percorrer;
            boolean erro = listaC_itemPosicao(lista, lista->nItems - 1, &percorrer);
            if(erro != SUCESSO) { return ERRO; }

            percorrer->proximoItem = atual->proximoItem;
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

boolean listaC_removerInicio(Lista * lista){
    return listaC_removerPosicao(lista, 0);
}

boolean listaC_removerFinal(Lista * lista){
    return listaC_removerPosicao(lista, lista->nItems);
}

boolean listaC_removerPosicao(Lista * lista, uint16_t posicao){
    ItemLista * anterior;
    ItemLista * remover;

    if(posicao == 0){
        ItemLista * percorrer;
        boolean erro = listaC_itemPosicao(lista, lista->nItems - 1, &percorrer);
        if(erro != SUCESSO) { return ERRO; }

        remover = lista->primeiroItem;
        percorrer->proximoItem = remover->proximoItem;
        lista->primeiroItem = remover->proximoItem;
    }
    else{
        boolean erro = listaC_itemPosicao(lista, posicao - 1, &anterior);
        if(erro != SUCESSO) { return ERRO; }

        remover = anterior->proximoItem;
        anterior->proximoItem = remover->proximoItem;
    }

    free(remover);
    lista->nItems--;
    return SUCESSO;
}

// Funcoes de Output

void listaC_imprimirEmArquivo(Lista * lista){
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

void listaC_imprimir(Lista * lista){
    ItemLista * item = lista->primeiroItem;
    for(int i = 0; i < lista->nItems; i++){
        Dados info = item->dados;
        printf("%s", info.nome);
        item = item->proximoItem;
    }
}

/* Auxiliares */

uint16_t CIRC_gerarNumero(Lista * lista){
    if(!listaC_estaVazia(lista)) { return rand() % lista->nItems; }
    else { return 0; }
}

int16_t CIRC_Dados_comparar(Dados info1, Dados info2){
    for(int i = 0; info1.nome[i]; i++){
        info1.nome[i] = tolower(info1.nome[i]);
    }

    for(int i = 0; info2.nome[i]; i++){
        info2.nome[i] = tolower(info2.nome[i]);
    }
    return strncmp(info1.nome, info2.nome, 4);
}