// ===============================================
// agendamento.c
// Funções de agendamento
// ===============================================

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
    // Por padrão, um novo agendamento está Ativo
    novo->status = 1;
    return novo;
}

// -----------------------------------------------------
// Cadastra um agendamento (insere na lista com cabeçalho)
// -----------------------------------------------------
void cadastrarAgendamento(ListaCabecalho *lista) {
    char cpf[15], sala[10], data[11], hora[6];

    printf("\n--- CADASTRO DE AGENDAMENTO ---\n");
    printf("CPF do paciente: ");
    scanf("%s", cpf);
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

    printf("Agendamento cadastrado com sucesso!\n");
}

// -----------------------------------------------------
// Função de comparação (usada para busca e remoção)
// -----------------------------------------------------
int compararAgendamento(void *dados, void *chave) {
    Agendamento *a = (Agendamento*) dados;
    ChaveAgendamento *c = (ChaveAgendamento*) chave;

    return (strcmp(a->cpf, c->cpf) == 0) && (strcmp(a->data, c->data) == 0);
}

// -----------------------------------------------------
// Mostra um agendamento na tela
// -----------------------------------------------------
void mostrarAgendamento(void *dados) {
    Agendamento *a = (Agendamento*) dados;
    printf("CPF: %s | Sala: %s | Data: %s | Hora: %s\n",
           a->cpf, a->sala, a->data, a->hora);
}

// -----------------------------------------------------
// Lista todos os agendamentos de um CPF
// -----------------------------------------------------
void listarAgendamentosPorCPF(ListaCabecalho *lista, char *cpf) {
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

// -----------------------------------------------------
// Lista todos os agendamentos de uma sala
// -----------------------------------------------------
void listarAgendamentosPorSala(ListaCabecalho *lista, char *sala) {
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

// -----------------------------------------------------
// Remove um agendamento (usando CPF + data como chave)
// -----------------------------------------------------
int removerAgendamento(ListaCabecalho *lista, char *cpf, char *data) {
    No *ant = lista->cabeca;
    No *atual = lista->cabeca->proximo;

    while (atual != NULL) {
        if (compararAgendamento(atual->dados, &chave)) {
            ant->proximo = atual->proximo;
            free(a);
            free(atual);
            lista->tamanho--;
            printf("🗑️  Agendamento removido com sucesso!\n");
            return 1;
        }
        ant = atual;
        atual = atual->proximo;
    }

    printf("5Agendamento não encontrado.\n");
    return 0;
}

