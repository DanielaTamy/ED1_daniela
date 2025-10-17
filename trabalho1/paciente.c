// ===============================================
// paciente.c
// Funções de Pacientes
// Nathalia e Leonardo
// ===============================================
#include "paciente.h"
#include <string.h> 

int compararCPF(void *dadosPaciente, void *chaveCPF) { //usada para comparar os cpfs (ver se já existe ou se são iguais)
    Paciente *p = (Paciente*) dadosPaciente; //ponteiro genérico que fazcom que sabemos que é um *Paciente*
    char *cpf = (char*) chaveCPF; //traduz a chave de busca para uma string (char*)
    return (strcmp(p->cpf, cpf) == 0); //compara o CPF do paciente (p->cpf) com o CPF que estamos buscando (cpf)
}

void mostrarPaciente(void *dadosPaciente) { //ensina a lista genérica como exibir todos os dados de um paciente
    Paciente *p = (Paciente*) dadosPaciente;
    printf("Nome: %s |", p->nome);
    printf("Cpf: %s |", p->cpf);
    printf("Grr: %s |", p->grr);
    printf("Curso: %s\n", p->curso);
}

void liberarDadosPaciente(void *dadosPaciente) { //ensina a lista genérica como apagar um Paciente da memória (fundamental)
    free(dadosPaciente);
}

//funções prncipais que o main2.c vai chamar 

ListaPacientes* criarListaPacientes() {
    ListaPacientes* lista = (ListaPacientes*) malloc(sizeof(ListaPacientes)); // aloca a estrutura da própria lista
    if (lista != NULL) { // usa a função para preparar a lista para usar
        inicializarLista(lista);
    }
    return lista;
}

void liberarListaPacientes(ListaPacientes *lista) {
    if (lista == NULL) return; // usa a função, passando o callback que sabe como liberar cada Paciente
    liberarLista(lista, liberarDadosPaciente); //callback 
    free(lista); //libera a estrutura da lista
}

void cadastrarPaciente(ListaPacientes *lista, char nome[], char cpf[], char grr[], char curso[]) {
    //nao permite cpf's duplicados
    if (buscarPacientePorCPF(lista, cpf) != NULL) {
        printf("Paciente com o CPF %s ja esta cadastrado\n", cpf);
        return;
    }
    //aloca memoria para a estrutura de um paciente *novo*
    Paciente *novoPaciente = (Paciente*) malloc(sizeof(Paciente));
    if (novoPaciente == NULL) {
        printf("Falha na alocacao de memoria para o paciente novo\n");
        return;
    }
    //copia os dados para a estrutura nova (pacienre novo)
    strncpy(novoPaciente->nome, nome, sizeof(novoPaciente->nome) - 1);
    novoPaciente->nome[sizeof(novoPaciente->nome) - 1] = '\0';
    strncpy(novoPaciente->cpf, cpf, sizeof(novoPaciente->cpf) - 1);
    novoPaciente->cpf[sizeof(novoPaciente->cpf) - 1] = '\0';
    strncpy(novoPaciente->grr, grr, sizeof(novoPaciente->grr) - 1);
    novoPaciente->grr[sizeof(novoPaciente->grr) - 1] = '\0';
    strncpy(novoPaciente->curso, curso, sizeof(novoPaciente->curso) - 1);
    novoPaciente->curso[sizeof(novoPaciente->curso) - 1] = '\0';
    
    //chama a função para adicionar o paciente novo no final da lista
    inserirNoFim(lista, novoPaciente);
}

Paciente* buscarPacientePorCPF(ListaPacientes *lista, char cpf[]) {
    //chama a função, passando o callback do cpf (comparar)
    return (Paciente*) buscarElemento(lista, compararCPF, cpf);
}

void exibirPacientes(ListaPacientes *lista) {
    if (lista == NULL || lista->tamanho == 0) {
        printf("\nNenhum paciente cadastrado no sistema.\n");
        return;
    }
    printf("\n=== Lista de Pacientes Cadastrados ===\n");
    //chama a função, passando o callback que mostra os dados do paciente (usado pra saber que é um paciente)
    percorrerLista(lista, mostrarPaciente);
}

int removerPacientePorCPF(ListaPacientes *lista, char cpf[]) {
    //chama a função, passando o criterio de busca (compararCPF)
    // e a função para liberar os dados do paciente
    return removerElemento(lista, compararCPF, cpf, liberarDadosPaciente);
}
