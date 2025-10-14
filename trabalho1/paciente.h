#ifndef PACIENTE_H
#define PACIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

// estrutura para paciente universitário
typedef struct { 
    char nome[100];
    char cpf[20];   //possibilita caracteres a mais para que não haja possibilidade de erro
    char grr[15];   // mesma coisa 
    char curso[50];
} Paciente;

// estrutura para a lista de pacientes -> lista.h
typedef Lista ListaPacientes;

// funções importantes da lsta 
ListaPacientes* criarListaPacientes();
void liberarListaPacientes(ListaPacientes *lista);
void cadastrarPaciente(ListaPacientes *lista, char nome[], char cpf[], char grr[], char curso[]);
Paciente* buscarPacientePorCPF(ListaPacientes *lista, char cpf[]);
void exibirPacientes(ListaPacientes *lista);
int removerPacientePorCPF(ListaPacientes *lista, char cpf[]);

#endif
