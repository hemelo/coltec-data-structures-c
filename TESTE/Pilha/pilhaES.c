#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "pilhaES.h"
#include "tipos.h"
#include "erro.h"

extern pilha_t * pilha_criar(){
	pilha_t * pilha = (pilha_t *) malloc(sizeof(pilha_t));
	pilha_inicializar(pilha);
	return pilha;
}

extern void pilha_inicializar(pilha_t * pilha){
	pilha->nItens = 0;
	pilha->topo = NULL;
}

extern void pilha_excluir(pilha_t * pilha){
	itemPilha_t * anterior;
	itemPilha_t * percorrer = pilha->topo;

	boolean_t vazia = pilha_estaVazia(pilha);
	if(vazia != VERDADEIRO) { 
		do{
			anterior = percorrer;
			percorrer = percorrer->proximoItem;
			free(anterior);
		}while(percorrer->proximoItem != NULL);
	}
	free(pilha);
}

extern boolean_t pilha_estaVazia(pilha_t * pilha){
    return (pilha->nItens == 0 ? VERDADEIRO : FALSO);
}

extern erro_t pilha_empilha(pilha_t * pilha, dados_t conteudo){
	itemPilha_t * novoItem = (itemPilha_t *) malloc(sizeof(itemPilha_t));
	novoItem->dados = conteudo;

	novoItem->proximoItem = pilha->topo;
	pilha->topo = novoItem;

	pilha->nItens++;
	return SUCESSO;
}

extern erro_t pilha_desempilha(pilha_t * pilha, dados_t * valorPerdido){
	itemPilha_t * remover = pilha->topo;

	boolean_t vazia = pilha_estaVazia(pilha);
	if(vazia == VERDADEIRO) { return ERRO_PILHA_VAZIA; }

	pilha->topo = remover->proximoItem;
	memcpy(valorPerdido, &remover->dados, sizeof(dados_t));
	free(remover);

	pilha->nItens--;
	return SUCESSO;
}

extern void pilha_imprimir(pilha_t * pilha){
	printf("Impressao de Pilha em formato de Lista\n");
    itemPilha_t * item = pilha->topo;
    uint32_t pos = 0;
    do{
        dados_t info = item->dados;
        printf("Pos: %d / Valor: %f \n", pos, info.valor);
        item = item->proximoItem;
        pos++;
    }while(item != NULL);
    printf("\n\n");
}
