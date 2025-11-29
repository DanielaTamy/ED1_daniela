#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"
#include "lista.h"
#include "paciente.h"

typedef struct {
    char cpf[15];
    char sala[10];
    char data[11];
    char hora[6];
} Agendamento;

typedef struct {
    char cpf[15];
    char data[15];
} ChaveAgendamento;

// Estrutura de historico (MODIFICADA)
typedef struct Historico {
    int total_agendamentos;
    int agendamentos_ativos;
    int agendamentos_cancelados;
    ListaCabecalho registros;
} Historico;

Agendamento* criarAgendamento(char *cpf, char *sala, char *data, char *hora);
void cadastrarAgendamento(ListaCabecalho *lista);
void listarAgendamentosPorCPF(ListaCabecalho *lista, char *cpf);
void listarAgendamentosPorSala(ListaCabecalho *lista, char *sala);
int removerAgendamento(ListaCabecalho *lista, char *cpf, char *data);
void exibirHistorico(ListaCabecalho *lista);

// Funções auxiliares
int compararAgendamento(void *dados, void *chave);
void mostrarAgendamento(void *dados);

#endif
