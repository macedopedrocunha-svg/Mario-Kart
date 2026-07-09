#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "function.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL)); // Inicializa o gerador de números aleatórios para o sorteio de itens

    
    node* lista_pilotos = NULL;
    node_corrida* fila_corridas = NULL;
    itens estoque_central;
    inicializar_estoque(&estoque_central);

    int resp_menu;
    do {
        print_menu();
        printf("Escolha uma opção do Menu Principal: ");
        scanf("%d", &resp_menu);
        getchar();

        switch (resp_menu) {
            case 0:
                printf("\nVai e não volta mais >:(\n");
                break;
            case 1:
                cadastrar_corrida(&fila_corridas);
                break;
            case 2:
                oficina();
                break;
            case 3:
                menu_ranking();
                break;
            case 4:
                item_dist(lista_pilotos, &estoque_central);
                break;
            case 5:
                criar_personagem(&lista_pilotos);
                break;
            case 6:
                procurar_personagem(lista_pilotos);
                break;
            case 7:
                listar_personagens_banidos(lista_pilotos);
                break;
            case 8:
                menu_itens_gerenciar(&estoque_central);
                break;
            default:
                printf("\nRESPOSTA ERRADA!\n");
                break;
        }
    } while (resp_menu != 0);

    while(lista_pilotos != NULL){
        node* aux = lista_pilotos;
        lista_pilotos = lista_pilotos->prox;
        free(aux);
    }
    while(fila_corridas != NULL){
        node_corrida* aux = fila_corridas;
        fila_corridas = fila_corridas->prox;
        free(aux);
    }

    return 0;
}
