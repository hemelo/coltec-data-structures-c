#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "listaED.h"
#include "tipos.h"

uint16_t ED_gerarNumero(Lista * lista);

/* Funções de Criação / Destruição da Lista */

Lista * ListaED_criar(){
    Lista * lista = (Lista *) malloc(sizeof(Lista));
    listaED_inicializar(lista);

    return lista;
}

void listaED_inicializar(Lista * lista){
    lista->nItems = 0;
    lista->primeiroItem = NULL;
}

void listaED_excluir(Lista * lista){
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

boolean listaED_estaVazia(Lista * lista){
    if(lista->nItems == 0) { return VERDADEIRO; }
    return FALSO;
}

boolean listaED_itemPosicao(Lista * lista, uint16_t posicao, ItemLista ** itemProcurado){
    if(listaED_estaVazia(lista)) { return ERRO; }

    ItemLista * atual = lista->primeiroItem;
    
    if(posicao > lista->nItems){ 
        //Procura Ultima Posicao
        while(atual->proximoItem != NULL){
            atual->anteriorItem = atual;
            atual = atual->proximoItem;
        }
    }
    else{
        while(posicao-- != 0){
            atual->anteriorItem = atual;
            atual = atual->proximoItem;
        }
    }

    *itemProcurado = atual;
    return SUCESSO;
}

// Funcoes de Inserção / Remocao

boolean listaED_insereOrdenado(Lista * lista, Dados dados){
    ItemLista * novoItem = (ItemLista *) malloc(sizeof(ItemLista));
    novoItem->dados = dados;
    novoItem->proximoItem = NULL;
    novoItem->anteriorItem = NULL;

    if(!listaED_estaVazia(lista)){
        ItemLista * anterior = NULL;
        ItemLista * atual = lista->primeiroItem;

        while(atual->proximoItem != NULL){
            if(ED_Dados_comparar(dados, atual->dados) < 0) { break; }

            anterior = atual;
            atual = atual->proximoItem;
        }

        if(anterior != NULL){
            novoItem->anteriorItem = anterior;
            anterior->proximoItem = novoItem;
            novoItem->proximoItem = atual;
            atual->anteriorItem = novoItem;
        }
        else{
            novoItem->proximoItem = atual;
            atual->anteriorItem = novoItem;
            lista->primeiroItem = novoItem;
        }
    }
    else{
        lista->primeiroItem = novoItem;
    }

    lista->nItems++;
    return SUCESSO;
}

boolean listaED_insereInicio(Lista * lista, Dados dados){
    return listaED_inserePosicao(lista, dados, 0);
}

boolean listaED_insereFinal(Lista * lista, Dados dados){
    return listaED_inserePosicao(lista, dados, lista->nItems);
}

boolean listaED_inserePosicao(Lista * lista, Dados dados, uint16_t posicao){
    ItemLista * novoItem = (ItemLista *) malloc(sizeof(ItemLista));
    novoItem->dados = dados;

    if(posicao == 0){
        novoItem->proximoItem = lista->primeiroItem;
        novoItem->anteriorItem = NULL;
        lista->primeiroItem = novoItem;
    }
    else{
        ItemLista * anterior;

        boolean erro = listaED_itemPosicao(lista, posicao - 1, &anterior);
        if(erro != SUCESSO) { return ERRO; }

        novoItem->proximoItem = anterior->proximoItem;
        anterior->proximoItem->anteriorItem = novoItem;
        anterior->proximoItem = novoItem;
        novoItem->anteriorItem = anterior;
    }

    lista->nItems++;
    return SUCESSO;
}

boolean listaED_removerItem(Lista * lista, Dados dados){
    ItemLista * atual = lista->primeiroItem;

    while(atual != NULL){
        if(ED_Dados_comparar(atual->dados, dados) == 0) break;

        atual->anteriorItem = atual;
        atual = atual->proximoItem;
    }

    if(atual == NULL) { 
        return ERRO; 
    }
    else{
        if(atual->anteriorItem == NULL){
            lista->primeiroItem = atual->proximoItem;
            (lista->primeiroItem)->anteriorItem = NULL;
        }
        else{
            (atual->anteriorItem)->proximoItem = atual->proximoItem;
        }
    }

    free(atual);
    lista->nItems--;
    return SUCESSO;
}

boolean listaED_removerInicio(Lista * lista){
    return listaED_removerPosicao(lista, 0);
}

boolean listaED_removerFinal(Lista * lista){
    return listaED_removerPosicao(lista, lista->nItems);
}

boolean listaED_removerPosicao(Lista * lista, uint16_t posicao){
    ItemLista * remover;

    if(posicao == 0){
        remover = lista->primeiroItem;
        lista->primeiroItem = remover->proximoItem;
        remover->anteriorItem = NULL;
    }
    else{
        boolean erro = listaED_itemPosicao(lista, posicao - 1, &remover);
        if(erro != SUCESSO) { return ERRO; }

        remover->anteriorItem = remover;
        remover = remover->proximoItem;
        (remover->anteriorItem)->proximoItem = remover->proximoItem;
    }

    free(remover);
    lista->nItems--;
    return SUCESSO;
}

// Funcoes de Output

void listaED_imprimirEmArquivo(Lista * lista){
    ItemLista * item = lista->primeiroItem;

    FILE * impressao = fopen("impressao.txt", "w");
    if(impressao != NULL){
        for(int i = 0; i < lista->nItems; i++){
            fprintf(impressao, "%s", (item->dados).nome);
            item->anteriorItem = item;
            item = item->proximoItem;
        }
    }
    else{
        printf("Ocorreu um erro na manipulação de Arquivos!");
    }
}

void listaED_imprimir(Lista * lista){
    ItemLista * item = lista->primeiroItem;
    do{
        Dados info = item->dados;
        printf("%s", info.nome);
        item->anteriorItem = item;
        item = item->proximoItem;
    }while(item->proximoItem != NULL);
}

/* Auxiliares */

uint16_t ED_gerarNumero(Lista * lista){
    if(!listaED_estaVazia(lista)) { return rand() % lista->nItems; }
    else { return 0; }
}

int16_t ED_Dados_comparar(Dados info1, Dados info2){
    for(int i = 0; info1.nome[i]; i++){
        info1.nome[i] = tolower(info1.nome[i]);
    }

    for(int i = 0; info2.nome[i]; i++){
        info2.nome[i] = tolower(info2.nome[i]);
    }
    return strncmp(info1.nome, info2.nome, 4);
}