#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agendamento.h"
#include "paciente.h"
#include "lista.h"

void limparBuffer() //função criada para limpar o biffer do teclado, para que nn apareça caracteres indesejados
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) //ignora os caracteres ate o fim da linha
        ;
}

void menuPrincipal()
{
    printf("\nCLINICA UNIVERSITARIA\n");
    printf("1. Gerenciar Pacientes\n");
    printf("2. Gerenciar Agendamentos\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

void menuPacientes()
{
    printf("\nMENU DE PACIENTES\n");
    printf("1. Cadastrar paciente\n");
    printf("2. Buscar paciente por CPF\n");
    printf("3. Remover paciente\n");
    printf("4. Exibir todos os pacientes\n");
    printf("0. Voltar\n");
    printf("Escolha uma opcao: ");
}

void menuAgendamentos()
{
    printf("\nMENU DE AGENDAMENTOS\n");
    printf("1. Cadastrar agendamento\n");
    printf("2. Listar por CPF\n");
    printf("3. Listar por sala\n");
    printf("4. Remover agendamento\n");
    printf("5. Mostrar todos os agendamentos\n");
    printf("6. Exibir Historico\n");
    printf("0. Voltar\n");
    printf("Escolha uma opcao: ");
}

int main() {
    ListaPacientes *listaPacientes = criarListaPacientes();
    ListaCabecalho listaAgendamentos;
    inicializarListaCabecalho(&listaAgendamentos);
    Historico *historico = criarHistorico();

    int opcaoPrincipal = -1, opcaoSub = -1;
    char entrada[20]; // buffer para ler a entrada do teclado
    char nome[100], cpf[20], grr[15], curso[50];
    char sala[15], data[12];

    do {
        menuPrincipal();
        if (fgets(entrada, sizeof(entrada), stdin) == NULL)
            continue;
        sscanf(entrada, "%d", &opcaoPrincipal);
        switch (opcaoPrincipal)
        {
        case 1: // para gerenciar pacientes
            do {
                menuPacientes();
                if (fgets(entrada, sizeof(entrada), stdin) == NULL)
                    continue;
                sscanf(entrada, "%d", &opcaoSub);
                switch (opcaoSub)
                {
                case 1:
                    printf("\nCADASTRO DE PACIENTE\n");
                    printf("Nome: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    printf("Cpf: ");
                    fgets(cpf, sizeof(cpf), stdin);
                    cpf[strcspn(cpf, "\n")] = 0;
                    printf("Grr: ");
                    fgets(grr, sizeof(grr), stdin);
                    grr[strcspn(grr, "\n")] = 0;
                    printf("Curso: ");
                    fgets(curso, sizeof(curso), stdin);
                    curso[strcspn(curso, "\n")] = 0;
                    cadastrarPaciente(listaPacientes, nome, cpf, grr, curso);
                    break;
                case 2: {
                    printf("Digite o CPF para buscar: ");
                    fgets(cpf, sizeof(cpf), stdin);
                    cpf[strcspn(cpf, "\n")] = 0;
                    Paciente *p = buscarPacientePorCPF(listaPacientes, cpf);
                    if (p)
                        printf("Foi encontrado: %s | Cpf: %s | Grr: %s | Curso: %s\n", p->nome, p->cpf, p->grr, p->curso);
                    else
                        printf("Paciente nao encontrado\n");
                    break;
                }
                case 3:
                    printf("Cpf do paciente que deseja remover: ");
                    fgets(cpf, sizeof(cpf), stdin);
                    cpf[strcspn(cpf, "\n")] = 0;
                    if (removerPacientePorCPF(listaPacientes, cpf))
                        printf("Paciente removido com sucesso\n");
                    else
                        printf("Paciente nao encontrado\n");
                    break;
                case 4:
                    exibirPacientes(listaPacientes);
                    break;
                }
            } while (opcaoSub != 0);
            break;
        case 2: // para gerenciar agendamentos
            do {
                menuAgendamentos();
                if (fgets(entrada, sizeof(entrada), stdin) == NULL)
                    continue;
                sscanf(entrada, "%d", &opcaoSub);
                switch (opcaoSub)
                {
                case 1:
                {
                    printf("\nAGENDAMENTO NOVO\n");
                    printf("Cpf do paciente: ");
                    fgets(cpf, sizeof(cpf), stdin);
                    cpf[strcspn(cpf, "\n")] = 0;
                    Paciente *p = buscarPacientePorCPF(listaPacientes, cpf);
                    if (p == NULL)
                    {
                        printf("Paciente nao encontrado, cadastre antes.\n");
                        break;
                    }
                    cadastrarAgendamento(&listaAgendamentos, historico, cpf);
                    break;
                }
                case 2:
                { // Listar por CPF
                    printf("Cpf para buscar: ");
                    fgets(cpf, sizeof(cpf), stdin);
                    cpf[strcspn(cpf, "\n")] = 0;
                    listarAgendamentosPorCPF(&listaAgendamentos, listaPacientes, cpf);
                    break;
                }
                case 3:
                {
                    printf("Sala para buscar: ");
                    fgets(sala, sizeof(sala), stdin);
                    sala[strcspn(sala, "\n")] = 0;
                    listarAgendamentosPorSala(&listaAgendamentos, listaPacientes, sala);
                    break;
                }
                case 4:
                    printf("Cpf: ");
                    fgets(cpf, sizeof(cpf), stdin);
                    cpf[strcspn(cpf, "\n")] = 0;
                    printf("Data (DD/MM/AAAA): ");
                    fgets(data, sizeof(data), stdin);
                    data[strcspn(data, "\n")] = 0;

                    if (removerAgendamento(&listaAgendamentos, historico, cpf, data))
                        printf("Agendamento removido com sucesso!\n");
                    else
                        printf("Agendamento nao encontrado.\n");
                    break;
                case 5:
                    printf("\nLISTA DE TODOS OS AGENDAMENTOS:\n");
                    percorrerListaCabecalho(&listaAgendamentos, mostrarAgendamento);
                    break;
                case 6:
                    exibirHistorico(historico);
                    exibirEstatisticasHistorico(historico);
                    break;
                }
            } while (opcaoSub != 0);
            break;
        }

    } while (opcaoPrincipal != 0);

    printf("\nSaindo\n");
    liberarListaPacientes(listaPacientes);
    liberarListaCabecalho(&listaAgendamentos, free);
    liberarHistorico(historico);

    return 0;
}