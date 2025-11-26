#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "fila.h"
#include "atendimento.h"

// função  para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// função para criar as filas automaticamente para fazer um teste rápido
void popularFilasTeste(Fila* comum, Fila* pref) {
    printf("\nGerando dados de teste...\n");
    
    // adiciona 3 comuns
    enfileirar(comum, criarCliente("Gabriel (Comum)", 0, 5));
    enfileirar(comum, criarCliente("Maria Cristina (Comum)", 0, 10));
    enfileirar(comum, criarCliente("Pedro Torres (Comum)", 0, 2));
    
    // adiciona 2 preferenciais
    enfileirar(pref, criarCliente("Senhora Ana Padilha (Preferencial)", 1, 3));
    enfileirar(pref, criarCliente("Senhor Jose da Silva (Preferencial)", 1, 8));

    printf("3 Clientes Comuns e 2 Preferenciais adicionados!\n");
    printf(" Use a opcao 3 repetidamente para testar\n");
}

int main() {
    int opcao;
    char nome[50];
    int itens;

    // inicializa as filas de clientes
    Fila filaComum, filaPreferencial;
    inicializarFila(&filaComum);
    inicializarFila(&filaPreferencial);

    // inicializa o módulo de estatísticas e atendimento
    Atendimento* a = inicializarAtendimento();
    do {
        printf("\n=================================\n");
        printf("    SISTEMA SUPERMERCADO   \n");
        printf("=================================\n");
        printf("1 - Adicionar cliente na fila Comum\n");
        printf("2 - Adicionar cliente na fila Preferencial\n");
        printf("3 - Atender proximo cliente (Processar Fila)\n");
        printf("4 - Exibir filas de espera\n");
        printf("5 - Exibir historico de atendidos\n");
        printf("6 - Exibir estatisticas finais\n");
        printf("7 - Testar funcionalidades isoladas do Cliente\n");
        printf("8 - gerar filas automaticamente (Teste Rapido)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        limparBuffer(); 

        switch(opcao) {
            case 1: {
                printf("\n--- Novo Cliente Comum ---\n");
                printf("Nome do cliente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; 

                printf("Quantidade de itens: ");
                scanf("%d", &itens);
                limparBuffer();

                Cliente novoCliente = criarCliente(nome, 0, itens);
                enfileirar(&filaComum, novoCliente);
                printf("Cliente comum adicionado com sucesso!\n");
                break;
            }
            case 2: {
                printf("\n--- Novo Cliente Preferencial ---\n");
                printf("Nome do cliente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Quantidade de itens: ");
                scanf("%d", &itens);
                limparBuffer();

                Cliente novoCliente = criarCliente(nome, 1, itens);
                enfileirar(&filaPreferencial, novoCliente);
                printf("Cliente preferencial adicionado com sucesso!\n");
                break;
            }
            case 3:
                //lógica de atendimento 
                atenderProximoCliente(&filaComum, &filaPreferencial, a);
                break;
            case 4:
                printf("\n--- STATUS DAS FILAS ---\n");
                exibirFila(&filaComum, "COMUM");
                printf("\n");
                exibirFila(&filaPreferencial, "PREFERENCIAL");
                break;

            case 5:
                exibirHistoricoAtendimentos(a);
                break;

            case 6:
                exibirEstatisticasFinais(a);
                break;

            case 7: {
                printf("\n--- TESTE: CLIENTE ---\n");
                Cliente teste = criarCliente("Cliente Teste", 1, 15); 
                printf("Objeto criado:\n");
                imprimirCliente(&teste); 
                printf("Verificacao Preferencial: %s\n", isPreferencial(teste.tipo) ? "PASSOU (Sim)" : "FALHOU");
                int tempoCalculado = calcularTempoAtendimento(teste.itens);
                printf("Teste calculo de tempo (15 itens): %d segundos (Esperado: 90)\n", tempoCalculado);
                break;
            }
            case 8:
                popularFilasTeste(&filaComum, &filaPreferencial);
                break;
            case 0:
                printf("\nEncerrando o sistema e liberando memoria...\n");
                liberarFila(&filaComum);
                liberarFila(&filaPreferencial);
                liberarAtendimento(a);
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
    return 0;
}