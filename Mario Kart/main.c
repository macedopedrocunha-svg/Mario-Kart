#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "function.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    // Ponteiros das Estruturas de Dados Obrigatórias do Trabalho
    node* lista_pilotos = NULL;            // 1. Lista Encadeada
    node_corrida* fila_corrida_inicio = NULL; // 2. Fila (Início)
    node_corrida* fila_corrida_fim = NULL;    // 2. Fila (Fim)
    node_historico* pilha_historico = NULL;// 3. Pilha de Histórico
    oficina* fila_oficina = NULL;     // 4. Fila de Prioridade da Oficina

    itens estoque_central;
    inicializar_estoque(&estoque_central);

    int resp_menu, cont_acidentes = 0;
    do {
        print_menu();
        printf("Escolha uma opção: ");
        if (scanf("%d", &resp_menu) != 1) {
            resp_menu = -1;
            getchar();
        }
        getchar(); // Limpa o buffer

        switch (resp_menu) {
        case 1: {
            int sub;
            printf("\n--- MÓDULO 1: CORRIDAS ---\n");
            printf("1 - Agendar Nova Corrida\n");
            printf("2 - Iniciar Próxima Corrida da Fila\n");
            printf("Escolha: ");
            scanf("%d", &sub);
            getchar();
            if (sub == 1) {
                cadastrar_corrida(&fila_corrida_inicio);
            } else if (sub == 2) {
                realizar_corrida(&fila_corrida_inicio, lista_pilotos, &estoque_central, &cont_acidentes);
            } else {
                printf("Opção inválida.\n");
            }
            break;
        }
        case 2:
            menu_oficina(&fila_oficina, lista_pilotos);
            break;
        case 3:
            exibir_ranking_campeonato(lista_pilotos);
            break;
        case 4:
            exibir_historico(lista_pilotos);
            break;
        case 5:
            criar_personagem(&lista_pilotos);
            break;
        case 6:
            procurar_personagem(&lista_pilotos);
            break;
        case 7:
            pers_banidos();
            break;
        case 8:
            menu_itens_gerenciar(lista_pilotos, &estoque_central);
            break;
        case 0:
            determinar_campeao_temporada(lista_pilotos);
            printf("Precione ENTER para sair... ");
            getchar();
            printf("\nEncerrando o sistema oficial da FMKR. Até mais!\n");
            break;
        default:
            printf("\nOpção Inválida!\n");
            break;
        }
    } while (resp_menu != 0);

    // Desalocação de memória ao sair
    while (lista_pilotos != NULL) {
        node* aux = lista_pilotos; lista_pilotos = lista_pilotos->prox;
        free(aux);
    }
    while (fila_corrida_inicio != NULL) {
        node_corrida* aux = fila_corrida_inicio; fila_corrida_inicio = fila_corrida_inicio->prox;
        free(aux);
    }
    while (pilha_historico != NULL) {
        node_historico* aux = pilha_historico; pilha_historico = pilha_historico->topo;
        free(aux);
    }
    while (fila_oficina != NULL) {
        oficina* aux = fila_oficina; fila_oficina = fila_oficina->prox;
        free(aux);
    }

    return 0;
}
