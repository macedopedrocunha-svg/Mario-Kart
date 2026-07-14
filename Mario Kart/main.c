#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "function.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    node* lista_pilotos = NULL;
    node_corrida* fila_corrida = NULL;
    node_historico* pilha_historico = NULL;
    oficina* fila_oficina_inicio = NULL;
    oficina* fila_oficina_fim = NULL;
    corrida* estatisticas_pistas = alocar_estatisticas();
    itens* estoque_central = alocar_estoque();
    
    printf("\nIniciando o Sistema FMKR...\n");
    inicializar_estoque(estoque_central);
    carregar(&fila_oficina_inicio, &fila_oficina_fim, &lista_pilotos);
    carregar_pistas(estatisticas_pistas);
    carregar_historico(&pilha_historico);

    int resp_menu;
    do {
        print_menu();
        printf("Escolha uma opção: ");
        if (scanf("%d", &resp_menu) != 1) {
            resp_menu = -1;
            getchar();
        }
        getchar();

        switch (resp_menu) {
        case 1: {
            int sub;
            do {
                printf("\n--- MÓDULO 1: CORRIDAS ---\n");
                printf("1 - Agendar Nova Corrida\n");
                printf("2 - Iniciar Próxima Corrida da Fila\n");
                printf("0 - Voltar\n");
                printf("Escolha: ");
                scanf("%d", &sub);
                getchar();
                if (sub == 1) {
                    cadastrar_corrida(&fila_corrida);
                } else if (sub == 2) {
                    realizar_corrida(&fila_corrida, lista_pilotos, estoque_central, estatisticas_pistas);
                } else if (sub == 0) {
                    break;
                } else {
                    printf("Opção inválida.\n");
                }
            } while (sub != 0);
            break;
        }
        case 2:
            menu_oficina(&fila_oficina_inicio, &fila_oficina_fim, lista_pilotos);
            break;
        case 3:
            exibir_ranking_campeonato(lista_pilotos);
            break;
        case 4:
            exibir_historico(estatisticas_pistas, lista_pilotos);
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
            menu_itens_gerenciar(lista_pilotos, estoque_central);
            break;
        case 9:
            determinar_campeao_temporada(lista_pilotos);
            inicializar_estoque(estoque_central);
            break;
        case 0:
            printf("\nSalvando o progresso da temporada...\n");
            salvar(lista_pilotos);
            salvar_pistas(estatisticas_pistas);
            salvar_historico(pilha_historico);

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
    liberar_pilotos(&lista_pilotos);
    liberar_corridas(&fila_corrida);
    liberar_estatisticas(&estatisticas_pistas);
    liberar_historico(&pilha_historico);
    liberar_oficina(&fila_oficina_inicio);
    liberar_estoque(&estoque_central);

    return 0;
}
