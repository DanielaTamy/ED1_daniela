// ===============================================
// agendamento.h
// Módulo de controle de agendamentos
// ===============================================

#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"
#include "lista.h"

// Estrutura de agendamento
typedef struct {
    char cpf[15];
    char sala[10];
    char data[11];
    char hora[6];
    int status;
} Agendamento;

// Estrutura de chave auxiliar para busca/remoção
typedef struct {
    char cpf[15];
    char data[11];
} ChaveAgendamento;

// Estrutura de historico (MODIFICADA)
typedef struct Historico {
    int total_agendamentos;
    int agendamentos_ativos;
    int agendamentos_cancelados;
    ListaCabecalho registros;
} Historico;

// Funções principais
Agendamento* criarAgendamento(char *cpf, char *sala, char *data, char *hora);
void cadastrarAgendamento(ListaCabecalho *lista, Historico *historico, char *cpf_paciente);
void listarAgendamentosPorCPF(ListaCabecalho *lista, ListaPacientes *pacientes, char *cpf);
void listarAgendamentosPorSala(ListaCabecalho *lista, ListaPacientes *pacientes, char *sala);
int removerAgendamento(ListaCabecalho *lista, Historico *historico, char *cpf, char *data);
void mostrarAgendamento(void *dados);

// Funções historico
Historico* criarHistorico();
void adicionarHistorico(Historico *historico, Agendamento *agendamento);
void exibirHistorico(Historico *historico);
void exibirEstatisticasHistorico(Historico *historico);
void liberarHistorico(Historico *historico); // Função para liberar a memória do histórico

#endif