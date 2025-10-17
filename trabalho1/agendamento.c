// ===============================================
// agendamento.c
// Funções de agendamento
// Nathalia e Leonardo
// ===============================================
#include "paciente.h"
#include "agendamento.h"

// -----------------------------------------------------
// Cria um novo agendamento na memória
// -----------------------------------------------------
Agendamento* criarAgendamento(char *cpf, char *sala, char *data, char *hora) {
    Agendamento *novo = (Agendamento*) malloc(sizeof(Agendamento));
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
void cadastrarAgendamento(ListaCabecalho *lista, Historico *historico, char *cpf_paciente) {
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
    // Adiciona ao histórico
    adicionarHistorico(historico, novo);
    printf("Agendamento cadastrado\n");
}

// -----------------------------------------------------
// Lista todos os agendamentos de um CPF
// -----------------------------------------------------
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

// -----------------------------------------------------
// Lista todos os agendamentos de uma sala
// -----------------------------------------------------
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

// -----------------------------------------------------
// Remove um agendamento (usando CPF + data como chave)
// -----------------------------------------------------
int removerAgendamento(ListaCabecalho *lista, Historico *historico, char *cpf, char *data) {
    No *ant = lista->cabeca;
    No *atual = lista->cabeca->proximo;

    while (atual != NULL) {
        Agendamento *a = (Agendamento*) atual->dados;
        if (strcmp(a->cpf, cpf) == 0 && strcmp(a->data, data) == 0) {
            // 1. Antes de remover, adiciona ao histórico como cancelado
            a->status = 0; // Marca como cancelado
            adicionarHistorico(historico, a);

            // 2. Agora remove da lista de agendamentos ativos
            ant->proximo = atual->proximo;
            free(a);
            free(atual);
            lista->tamanho--;
            return 1;
        }
        ant = atual;
        atual = atual->proximo;
    }

    return 0;
}

// -----------------------------------------------------
// Mostra um agendamento na tela
// -----------------------------------------------------
void mostrarAgendamento(void *dados) {
    Agendamento *a = (Agendamento*) dados;
    const char *status_str = (a->status == 1) ? "Ativo" : "Cancelado";
    printf("CPF: %s | Sala: %s | Data: %s | Hora: %s | Status: %s\n",
           a->cpf, a->sala, a->data, a->hora, status_str);
}

// Cria e inicializa a estrutura de histórico
Historico* criarHistorico() {
    Historico *novo = (Historico*) malloc(sizeof(Historico));
    if (novo == NULL) {
        printf("Erro ao criar histórico!\n");
        exit(1);
    }
    novo->total_agendamentos = 0;
    novo->agendamentos_ativos = 0;
    novo->agendamentos_cancelados = 0;
    inicializarListaCabecalho(&novo->registros); // Inicializa a lista interna
    return novo;
}

// Adiciona uma cópia do agendamento ao histórico e atualiza as estatísticas
void adicionarHistorico(Historico *historico, Agendamento *agendamento) {
    if (historico == NULL || agendamento == NULL) return;

    // Cria uma cópia para o histórico, para não interferir na lista de ativos
    Agendamento *copia = (Agendamento*) malloc(sizeof(Agendamento));
    if (copia == NULL) {
        printf("Erro ao adicionar ao histórico!\n");
        return;
    }
    memcpy(copia, agendamento, sizeof(Agendamento));

    inserirNoFimCabecalho(&historico->registros, copia);

    // Atualiza contadores
    historico->total_agendamentos++;
    if (copia->status == 1) { // Agendamento novo
        historico->agendamentos_ativos++;
    } else { // Agendamento cancelado
        // Como o agendamento ativo foi removido, o total de ativos diminui
        historico->agendamentos_ativos--; 
        historico->agendamentos_cancelados++;
    }
}

// Mostra o histórico completo de agendamentos
void exibirHistorico(Historico *historico) {
    if (historico == NULL || historico->registros.tamanho == 0) {
        printf("\nNenhum registro no historico.\n");
        return;
    }
    printf("\n--- HISTORICO COMPLETO DE AGENDAMENTOS ---\n");
    percorrerListaCabecalho(&historico->registros, mostrarAgendamento);
}

// Mostra as estatísticas do histórico
void exibirEstatisticasHistorico(Historico *historico) {
    if (historico == NULL) return;

    printf("\n--- ESTATISTICAS DE AGENDAMENTOS ---\n");
    printf("Total de Agendamentos Criados: %d\n", historico->total_agendamentos);
    printf("Agendamentos Ativos Atualmente: %d\n", historico->agendamentos_ativos);
    printf("Agendamentos Removidos (Cancelados): %d\n", historico->agendamentos_cancelados);
    printf("======================================\n");
}

// Libera toda a memória usada pelo histórico
void liberarHistorico(Historico *historico) {
    if (historico == NULL) return;
    liberarListaCabecalho(&historico->registros, free); // Libera todos os agendamentos copiados
    free(historico);
}