// -------------------------------------------------------------
// cliente.c
// Autor: Daniela
// implementa funções da estrutura Cliente
// -------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

Cliente criarCliente(char nome[], int tipo, int itens) {
    Cliente novo;
    
    strcpy(novo.nome, nome);
    novo.tipo = tipo;
    novo.itens = itens;
    novo.tempoAtendimento = calcularTempoAtendimento(itens);

    return novo;
}

void liberarCliente(Cliente* c) {
    if (c) {
        free(c);
    }
}

void imprimirCliente(Cliente* c) {
    if (!c) return;

    printf("Nome: %s\n", c->nome);
    printf("Tipo: %s\n", c->tipo == 1 ? "Preferencial" : "Comum");
    printf("Itens: %d\n", c->itens);
    printf("Tempo Estimado: %d segundos\n", c->tempoAtendimento);
}

int calcularTempoAtendimento(int itens) {
    // Exemplo: cada item leva 2 segundos para ser processado + 1 minuto para pagamento
    return itens * 2 + 60;
}

int isPreferencial(int tipo) {
    return tipo == 1;
}
