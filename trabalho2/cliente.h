// -------------------------------------------------------------
// cliente.h
// Autor: Daniela
// estrutura Cliente e funções 
// -------------------------------------------------------------

#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct Cliente {
    char nome[50];
    int tipo;             // 0 = comum, 1 = preferencial
    int itens;
    int tempoAtendimento; // calculado depois
} Cliente;

// Cria um cliente dinamicamente
Cliente criarCliente(char nome[], int tipo, int itens);

// Libera memória do cliente
void liberarCliente(Cliente* c);

// Exibe dados do cliente
void imprimirCliente(Cliente* c);

// função para calcular tempo de atendimento - auxiliar
int calcularTempoAtendimento(int itens);

// função para verificar se é preferencial - auxiliar
int isPreferencial(int tipo);

#endif
