#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void inicializarFila(Fila* f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
}

int filaVazia(Fila* f) {
    return (f->inicio == NULL);
}

void enfileirar(Fila* f, Cliente c) {
    NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
    if (novo == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }
    
    novo->cliente = c;
    novo->proximo = NULL;
    
    if (filaVazia(f)) {
        f->inicio = novo;
    } else {
        f->fim->proximo = novo;
    }
    
    f->fim = novo;
    f->tamanho++;
}

Cliente desenfileirar(Fila* f) {
    Cliente clienteVazio = {"", 0, 0}; 
    
    if (filaVazia(f)) {
        printf("A fila está vazia.\n");
        return clienteVazio;
    }
    
    NoFila* temp = f->inicio;
    Cliente c = temp->cliente;
    
    f->inicio = f->inicio->proximo;
    
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    
    free(temp);
    f->tamanho--;
    return c;
}

void exibirFila(Fila* f, const char* tipoFila) {
    if (filaVazia(f)) {
        printf("Fila %s vazia.\n", tipoFila);
        return;
    }
    
    printf("Fila %s (%d clientes):\n", tipoFila, f->tamanho);
    printf("----------------------------------------\n");
    
    NoFila* atual = f->inicio;
    int posicao = 1;
    
    while (atual != NULL) {
        printf("%d. %s - %d itens\n", 
               posicao, 
               atual->cliente.nome, 
               atual->cliente.itens);
        atual = atual->proximo;
        posicao++;
    }
    printf("----------------------------------------\n");
}

void liberarFila(Fila* f) {
    while (!filaVazia(f)) {
        desenfileirar(f);
    }
}