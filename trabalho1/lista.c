// ===============================================
// lista.c
// Implementação das funções de listas lineares
// Daniela
// ===============================================

#include "lista.h"

// -------------------------------
// Lista simples
// -------------------------------

// Inicializa uma lista vazia encadeada simples (para paciente)
void inicializarLista(Lista *lista) {
    lista->inicio = NULL;
    lista->tamanho = 0;
}

// Insere no final da lista simples
void inserirNoFim(Lista *lista, void *dados) {
    No *novo = (No*) malloc(sizeof(No));
    novo->dados = dados;
    novo->proximo = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        No *aux = lista->inicio;
        while (aux->proximo != NULL)
            aux = aux->proximo;
        aux->proximo = novo;
    }
    lista->tamanho++;
}

// Busca um elemento usando uma função de critério (compararCPF)
void *buscarElemento(Lista *lista, int (*criterio)(void*, void*), void *chave) {
    No *aux = lista->inicio;
    while (aux != NULL) {
        if (criterio(aux->dados, chave))
            return aux->dados;
        aux = aux->proximo;
    }
    return NULL;
}

// Remove elemento conforme critério
int removerElemento(Lista *lista, int (*criterio)(void*, void*), void *chave, void (*liberarDados)(void*)) {
    No *anterior = NULL;
    No *atual = lista->inicio;

    while (atual != NULL) {
        if (criterio(atual->dados, chave)) {
            if (anterior == NULL) {
                lista->inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            if (liberarDados != NULL) {
                liberarDados(atual->dados); //libera a memoria do paciente
            }

            free(atual); //libera a memória do nó
            lista->tamanho--;
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return 0;
}

//percorre e aplica função que mostra em cada elemento
void percorrerLista(Lista *lista, void (*mostrar)(void*)) {
    No *aux = lista->inicio;
    while (aux != NULL) {
        mostrar(aux->dados);
        aux = aux->proximo;
    }
}

//libera toda a lista
void liberarLista(Lista *lista, void (*liberarDados)(void*)) {
    No *aux = lista->inicio;
    while (aux != NULL) {
        No *prox = aux->proximo;
        if (liberarDados != NULL) {
            liberarDados(aux->dados); //libera a memoria do dado
        }

        free(aux);
        aux = prox;
    }
    lista->inicio = NULL;
    lista->tamanho = 0;
}

// -------------------------------
// Lista com cabeçalho (sentinela)
// -------------------------------

// Inicializa a lista com cabeçalho
void inicializarListaCabecalho(ListaCabecalho *lista) {
    lista->cabeca = (No*) malloc(sizeof(No));  // nó sentinela 
    lista->cabeca->proximo = NULL;
    lista->cabeca->dados = NULL;
    lista->tamanho = 0;
}

// Insere no fim da lista com cabeçalho
void inserirNoFimCabecalho(ListaCabecalho *lista, void *dados) {
    No *novo = (No*) malloc(sizeof(No)); //aloca memória para o novo nó
    novo->dados = dados; //armazena os dados
    novo->proximo = NULL; 

    No *aux = lista->cabeca;
    while (aux->proximo != NULL)
        aux = aux->proximo;

    aux->proximo = novo;
    lista->tamanho++;
}

// Percorre lista com cabeçalho
void percorrerListaCabecalho(ListaCabecalho *lista, void (*mostrar)(void*)) {
    No *aux = lista->cabeca->proximo; //começa pelo primeiro elemento
    while (aux != NULL) {
        mostrar(aux->dados);
        aux = aux->proximo;
    }
}

// Libera memória da lista com cabeçalho
void liberarListaCabecalho(ListaCabecalho *lista, void (*liberarDados)(void*)) {
    No *aux = lista->cabeca->proximo;
    while (aux != NULL) {
        No *prox = aux->proximo;
        // Usa a função de callback para liberar os dados (ex: o Agendamento)
        if (liberarDados != NULL && aux->dados != NULL) {
            liberarDados(aux->dados);
        }
        free(aux); // Libera o nó
        aux = prox;
    }
    free(lista->cabeca); // Libera o nó sentinela
    lista->cabeca = NULL;
    lista->tamanho = 0;
}

