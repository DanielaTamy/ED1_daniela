#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "fila.h"

int main() {
    int opcao;
    char nome[50];
    int itens;

    Fila filaComum, filaPreferencial;
    
    inicializarFila(&filaComum);
    inicializarFila(&filaPreferencial);

    do {
        printf("\n=================================\n");
        printf("    SISTEMA SUPERMERCADO   \n");
        printf("=================================\n");
        printf("1 - Enfileirar cliente  - Comum\n");
        printf("2 - Enfileirar cliente - Preferencial\n");
        printf("3 - Desenfileirar cliente - Comum\n");
        printf("4 - Desenfileirar cliente - Preferencial\n");
        printf("5 - Exibir filas\n");
        printf("6 - Estatisticas das filas\n");
        printf("7 - Funcionalidades cliente\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {

            case 1: {
                printf("\n--- Novo Cliente Comum ---\n");
                printf("Nome do cliente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Quantidade de itens: ");
                scanf("%d", &itens);

                Cliente novoCliente = criarCliente(nome, 0, itens); // tipo 0 = comum
                enfileirar(&filaComum, novoCliente); // CORRETO: passa por valor
                printf("Cliente comum enfileirado com sucesso!\n");
                break;
            }

            case 2: {
                printf("\n--- Novo Cliente Preferencial ---\n");
                printf("Nome do cliente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Quantidade de itens: ");
                scanf("%d", &itens);

                Cliente novoCliente = criarCliente(nome, 1, itens); // tipo 1 = preferencial
                enfileirar(&filaPreferencial, novoCliente); // CORRETO: passa por valor
                printf("Cliente preferencial enfileirado com sucesso!\n");
                break;
            }

            case 3:
                if (filaVazia(&filaComum)) {
                    printf("\nFila comum está vazia!\n");
                } else {
                    Cliente atendido = desenfileirar(&filaComum);
                    printf("\nCliente atendido (Comum):\n");
                    imprimirCliente(&atendido); // CORRETO: passa endereço
                    printf("Tempo estimado: %d segundos\n", 
                           calcularTempoAtendimento(atendido.itens));
                }
                break;

            case 4:
                if (filaVazia(&filaPreferencial)) {
                    printf("\nFila preferencial está vazia!\n");
                } else {
                    Cliente atendido = desenfileirar(&filaPreferencial);
                    printf("\nCliente atendido (Preferencial):\n");
                    imprimirCliente(&atendido); // CORRETO: passa endereço
                    printf("Tempo estimado: %d segundos\n", 
                           calcularTempoAtendimento(atendido.itens));
                }
                break;

            case 5:
                printf("\n=== EXIBIR FILAS ===\n");
                exibirFila(&filaComum, "COMUM");
                exibirFila(&filaPreferencial, "PREFERENCIAL");
                break;

            case 6:
                printf("\n=== ESTATÍSTICAS DAS FILAS ===\n");
                printf("Fila Comum: %d clientes\n", filaComum.tamanho);
                printf("Fila Preferencial: %d clientes\n", filaPreferencial.tamanho);
                
                int totalItens = 0;
                NoFila* atual = filaComum.inicio;
                while (atual != NULL) {
                    totalItens += atual->cliente.itens;
                    atual = atual->proximo;
                }
                atual = filaPreferencial.inicio;
                while (atual != NULL) {
                    totalItens += atual->cliente.itens;
                    atual = atual->proximo;
                }
                printf("Total de itens nas filas: %d\n", totalItens);
                break;

            case 7: {
                printf("\n--- FUNCIONALIDADES CLIENTE ---\n");
                Cliente teste = criarCliente("Cliente Teste", 1, 15); 
                printf("Cliente criado: ");
                imprimirCliente(&teste); 
                printf("É preferencial? %s\n", isPreferencial(teste.tipo) ? "Sim" : "Não");
                printf("Tempo de atendimento: %d segundos\n", calcularTempoAtendimento(teste.itens));
                break;
            }

            case 0:
                printf("\nSaindo...\n");
                liberarFila(&filaComum);
                liberarFila(&filaPreferencial);
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}