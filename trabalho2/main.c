// main provisorio para teste do cliente.c e cliente.h

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"

int main() {
    int opcao;
    char nome[50];
    int tipo, itens;

    Cliente* clienteTeste = NULL;

    do {
        printf("\n=================================\n");
        printf("     TESTE DO MODULO CLIENTE     \n");
        printf("=================================\n");
        printf("1 - Criar cliente\n");
        printf("2 - Verificar se eh preferencial\n");
        printf("3 - Calcular tempo de atendimento\n");
        printf("4 - Mostrar cliente criado\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch(opcao) {

            case 1:
                printf("\nDigite o nome do cliente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; // remover \n

                printf("Tipo (0 = comum, 1 = preferencial): ");
                scanf("%d", &tipo);

                printf("Quantidade de itens: ");
                scanf("%d", &itens);

                clienteTeste = criarCliente(nome, tipo, itens);

                if (clienteTeste != NULL)
                    printf("\nCliente criado com sucesso!\n");
                break;

            case 2:
                if (!clienteTeste) {
                    printf("\nNenhum cliente criado ainda!\n");
                } else {
                    if (isPreferencial(clienteTeste->tipo))
                        printf("\nO cliente é preferencial.\n");
                    else
                        printf("\nO cliente é comum.\n");
                }
                break;

            case 3:
                if (!clienteTeste) {
                    printf("\nCrie um cliente primeiro.\n");
                } else {
                    int tempo = calcularTempoAtendimento(clienteTeste->itens);
                    printf("\nTempo calculado: %d segundos\n", tempo);
                }
                break;

            case 4:
                if (!clienteTeste) {
                    printf("\nNenhum cliente criado ainda.\n");
                } else {
                    printf("\n--- Dados do Cliente ---\n");
                    imprimirCliente(clienteTeste);
                }
                break;

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    // liberar memoria se criada
    if (clienteTeste)
        free(clienteTeste);

    return 0;
}
