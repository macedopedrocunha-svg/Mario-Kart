#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "function.h"

int main() {
    int resp_menu;
    do {
        print_menu();
        scanf("%d", &resp_menu);
        getchar();
        switch (resp_menu) {
            case 0:
                printf("\nVai e não volta mais >:(\n");
                break;
            case 1:
                printf("\nEm andamento! :/\n\n");
                // corrida()
                break;
            case 2:
                menu_oficina();
                break;
            case 3:
                printf("\nSe a opção correr está em andamento, o que tu esperava do ranking?????\n");
                // ranking()
                break;
            case 4:
                printf("\nVai ser curioso na casa do caralho\n");
                break;
            case 5:
                printf("\nOlha aqui meu personagem Ó 8======D\n");
                // criar()
                break;
            case 6:
                printf("\nVai ser curioso na casa do caralho 2\n");
                break;
            case 7:
                printf("\nSe tu foi banido, ta fazendo o que aqui seu merda!\n");
                break;
            case 8:
                printf("\nQUER ACESSAR OS ITENS PQ????\n");
                break;
            default:
                printf("\nRESPOSTA ERRADA!\n");
                break;
        }
    } while (resp_menu != 0);
}