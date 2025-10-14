#include "agendamento.h"
#include "paciente.h"

Agendamento* criarAgendamento(char *cpf, char *sala, char *data, char *hora) {
    Agendamento *novo = (Agendamento*) malloc(sizeof(Agendamento));
    if (!novo) {
        printf("Erro ao alocar memoria\n");
        return NULL;
    }
    strcpy(novo->cpf, cpf);
    strcpy(novo->sala, sala);
    strcpy(novo->data, data);
    strcpy(novo->hora, hora);
    return novo;
}

void cadastrarAgendamento(ListaCabecalho *lista, char *cpf_paciente) {
    char cpf[15], sala[10], data[15], hora[8];

   /* printf("CPF do paciente: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0; */

    printf("Sala: ");
    fgets(sala, sizeof(sala), stdin);
    sala[strcspn(sala, "\n")] = 0;

    printf("Data (DD/MM/AAAA): ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = 0;

    printf("Hora (HH:MM): ");
    fgets(hora, sizeof(hora), stdin);
    hora[strcspn(hora, "\n")] = 0;

    Agendamento *novo = criarAgendamento(cpf_paciente, sala, data, hora);
    if (novo == NULL) return;
    inserirNoFimCabecalho(lista, novo);
    printf("Agendamento cadastrado\n");
}

void listarAgendamentosPorCPF(ListaCabecalho *lista, ListaPacientes *pacientes, char *cpf) {
    No *aux = lista->cabeca->proximo;
    int encontrados = 0;
    Paciente *p = buscarPacientePorCPF(pacientes, cpf);

    printf("\n--- AGENDAMENTOS DO CPF %s ---\n", cpf);
    if (p != NULL)
        printf("Paciente: %s (%s - %s)\n", p->nome, p->grr, p->curso);

    while (aux != NULL) {
        Agendamento *a = (Agendamento*) aux->dados;
        if (strcmp(a->cpf, cpf) == 0) {
            printf("Data: %s | Hora: %s | Sala: %s\n", a->data, a->hora, a->sala);
            encontrados++;
        }
        aux = aux->proximo;
    }

    if (!encontrados)
        printf("Nenhum agendamento encontrado.\n");
}

void listarAgendamentosPorSala(ListaCabecalho *lista, ListaPacientes *pacientes, char *sala) {
    No *aux = lista->cabeca->proximo;
    int encontrados = 0;

    printf("\n--- AGENDAMENTOS NA SALA %s ---\n", sala);
    while (aux != NULL) {
        Agendamento *a = (Agendamento*) aux->dados;
        if (strcmp(a->sala, sala) == 0) {
            Paciente *p = buscarPacientePorCPF(pacientes, a->cpf);
            if (p)
                printf("Paciente: %s | CPF: %s | Curso: %s | Data: %s | Hora: %s\n",
                       p->nome, a->cpf, p->curso, a->data, a->hora);
            else
                printf("CPF: %s | Data: %s | Hora: %s\n", a->cpf, a->data, a->hora);
            encontrados++;
        }
        aux = aux->proximo;
    }

    if (!encontrados)
        printf("Nenhum agendamento encontrado.\n");
}

int removerAgendamento(ListaCabecalho *lista, char *cpf, char *data) {
    No *ant = lista->cabeca;
    No *atual = lista->cabeca->proximo;

    while (atual != NULL) {
        Agendamento *a = (Agendamento*) atual->dados;
        if (strcmp(a->cpf, cpf) == 0 && strcmp(a->data, data) == 0) {
            ant->proximo = atual->proximo;
            free(a);
            free(atual);
            lista->tamanho--;
            printf("Agendamento removido com sucesso\n");
            return 1;
        }
        ant = atual;
        atual = atual->proximo;
    }

    printf("Agendamento nao encontrado.\n");
    return 0;
}
