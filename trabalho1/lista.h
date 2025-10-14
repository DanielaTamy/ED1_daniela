// ===============================================
// lista.h
// Módulo para declarar a estrutura e as funções
// ===============================================

#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura de nó genérico (pode guardar qualquer tipo de dado)
typedef struct No {
    void *dados;           // ponteiro genérico: pode ser Paciente, Agendamento, etc.
    struct No *proximo;
} No;

// Estrutura de lista simples (sem cabeçalho)
typedef struct {
    No *inicio;
    int tamanho;
} Lista;

// Estrutura de lista com cabeçalho (para histórico/agendamentos)
typedef struct {
    No *cabeca;   // nó sentinela
    int tamanho;
} ListaCabecalho;

// Funções básicas para lista simples
void inicializarLista(Lista *lista);
void inserirNoFim(Lista *lista, void *dados);
void *buscarElemento(Lista *lista, int (*criterio)(void*, void*), void *chave);
int removerElemento(Lista *lista, int (*criterio)(void*, void*), void *chave, void (*liberarDados)(void*));
void liberarLista(Lista *lista, void (*liberarDados)(void*));
void percorrerLista(Lista *lista, void (*mostrar)(void*));


// Funções para lista com cabeçalho
void inicializarListaCabecalho(ListaCabecalho *lista);
void inserirNoFimCabecalho(ListaCabecalho *lista, void *dados);
void percorrerListaCabecalho(ListaCabecalho *lista, void (*mostrar)(void*));
void liberarListaCabecalho(ListaCabecalho *lista, void (*liberarDados)(void*));


#endif
