#ifndef FILA_H
#define FILA_H

#include "cliente.h"

typedef struct NoFila {
    Cliente cliente;
    struct NoFila* proximo;
} NoFila;

typedef struct {
    NoFila* inicio;
    NoFila* fim;
    int tamanho;
} Fila;

void inicializarFila(Fila* f);
int filaVazia(Fila* f);
void enfileirar(Fila* f, Cliente c);
Cliente desenfileirar(Fila* f);
void exibirFila(Fila* f, const char* tipoFila);
void liberarFila(Fila* f);

#endif