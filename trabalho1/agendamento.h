#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "paciente.h"

typedef struct {
    char cpf[15];
    char sala[10];
    char data[15];
    char hora[8];
} Agendamento;

typedef struct {
    char cpf[15];
    char data[15];
} ChaveAgendamento;

Agendamento* criarAgendamento(char *cpf, char *sala, char *data, char *hora);
void cadastrarAgendamento(ListaCabecalho *lista, char *cpf_paciente);
void listarAgendamentosPorCPF(ListaCabecalho *lista, ListaPacientes *pacientes, char *cpf);
void listarAgendamentosPorSala(ListaCabecalho *lista, ListaPacientes *pacientes, char *sala);
int removerAgendamento(ListaCabecalho *lista, char *cpf, char *data);

#endif
