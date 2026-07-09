#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

typedef struct DADOS{
    char piloto[30];
    int categ, cont_trofeu, st_pil;
    int v_kart, ac, ctrl, resist, st_kart;
} personagem;

typedef struct NODE {
    personagem dado;
    struct NODE* prox;
} node;

typedef struct ITEM{
    int tipo; //  0 - casco_verde, 1 - casco_vermelho, 2 - banana, 3 - cogumelo, 4 - bob_omb, 5 - raio, 6 - bullet_bill, 7 - casco_azul;
    int raridade; // 0 - comum, 1 - raro, 2 - épico, 3 - lendário
    int poder;
    int quantidade[8];

}itens;

typedef struct PISTA{
    int pista; // 0 - Circuito Luigi, 1 - Circuito Mario , 2 - Circuito Peach , 3 - Circuito Yoshi  , 4 - Circuito Donkey Kong , 5 - Circuito Wario , 6 - Circuito Bowser, 7 - Circuito Rainbow Road
    int num_voltas;
    int dificuldade; // de 1 a 100
    int status; // 0 - aguardando, 1 - em andamento, 2 - finalizada
    int prioridade;

}corrida;

void print_menu() {
    printf("\n");
    printf("1 - Correr!\n");
    printf("2 - Oficina\n");
    printf("3 - Ranking\n");
    printf("4 - Informações gerais\n");
    printf("5 - Criar Um Personagem\n");
    printf("6 - Procurar Personagem\n");
    printf("7 - Personagens Banidos\n");
    printf("8 - Estoque de itens\n");
    printf("0 - Encerrar\n");
}

void menu_oficina() {
    printf("\n");
    printf("1 - Registro de Karts\n");
    printf("2 - Iniciar reparos\n");
    printf("3 - Ver Fila\n");
    printf("0 - Voltar\n");
}

void menu_ranking() {
    printf("----------------------------------");

    printf("----------------------------------");
}

void menu_itens() {
    printf("\n");
    printf("1 - Ver estoque \n");
    printf("2 - Ver itens em uso\n");
    printf("3 - Repor itens\n");
    printf("0 - Sair\n");
    
}

void ordenar(node* cabeca) {
    // Se a lista estiver vazia ou tiver apenas um elemento, já está ordenada
    if (cabeca == NULL || cabeca->prox == NULL) {
        return;
    }

    int trocou;
    node* atual;
    node* ultimo = NULL; // Otimização: marca o final da parte já ordenada

    do {
        trocou = 0;
        atual = cabeca;

        while (atual->prox != ultimo) {
            // Se o nó atual tiver mais pontos que o próximo, trocamos (ordem crescente)
            if (atual->dado.cont_trofeu > atual->prox->dado.cont_trofeu) {
                
                // Troca apenas o conteúdo (os dados), não os ponteiros!
                personagem temp = atual->dado;
                atual->dado = atual->prox->dado;
                atual->prox->dado = temp;
                
                trocou = 1; // Registra que houve uma troca nesta passagem
            }
            atual = atual->prox;
        }
        // O último elemento avaliado já é o maior, não precisamos checá-lo novamente
        ultimo = atual; 
        
    } while (trocou); // Continua até passar pela lista toda sem fazer nenhuma troca
}


void oficina() {
    int opcao_oficina;
    do{
        printf("\n");
        printf("===============================\n");
        printf("            OFICINA\n");
        printf("===============================\n");
        printf("1 - Registro de Karts\n");
        printf("2 - Iniciar reparo\n");
        printf("3 - Ver Fila de Reparos\n");
        printf("0 - Voltar\n");
        printf("===============================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao_oficina);

        switch(opcao_oficina) {
            case 1:
                printf("\n-------------------------------\n");
                printf("Registro de Karts\n");
                printf("-------------------------------\n");
                // print_karts();
                break;
            case 2:
                printf("\n-------------------------------------\n");
                printf("Inciar reparo\n");
                printf("-------------------------------------\n");
                // iniciar_reparo();
                break;
            case 3:
                printf("\n-------------------------------------\n");
                printf("Ver Fila de Reparos\n");
                printf("-------------------------------------\n");
                //mostrar_fila();
                break;
            case 0:
                printf("\nVoltando ao menu princial...\n");
                break;
                
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
            
        }
    } while(opcao_oficina != 0);
}

void criar_personagem(struct NODE** inicio) {
    int quant, temp_categ, pontos, temp_vkart, temp_ac, temp_ctrl, temp_resist;
    
    printf("\n");
    printf("===============================\n");
    printf("        CRIAR PERSONAGEM\n");
    printf("===============================\n");
    printf("Quantos personagens você quer criar? ");
    scanf("%d", &quant);
    getchar();

    for (int i = 0; i < quant; i++) {
        struct NODE* atual = (struct NODE*)malloc(sizeof(struct NODE));
        if (atual == NULL) {
            printf("Limite de memória atingido!");
            return;
        }
        atual->prox = NULL;

        printf("Digite o nome do piloto %d: ", i+1);
        fgets(atual->dado.piloto, 30, stdin);
        atual->dado.piloto[strcspn(atual->dado.piloto, "\n")] = 0;

        printf("\nDigite a categoria do piloto:\n1 - Leve | 2 - Médio | 3 - Pesado\n ");
        scanf("%d", &temp_categ);
        getchar();
        do {
            pontos = 100;
            printf("\nEscolha com cuidado, você tem 100 pontos para gastar no seu Kart:\n");

            printf("Velocidade: ");
            scanf("%d", &temp_vkart);
            pontos -= temp_vkart;

            printf("%d pontos restantes.", pontos);
            getchar();
            printf("\nAceleração: ");
            scanf("%d", &temp_ac);
            getchar();
            pontos -= temp_ac;

            printf("%d pontos restantes.", pontos);
            printf("\nControle: ");
            scanf("%d", &temp_ctrl);
            getchar();
            pontos -= temp_ctrl;

            printf("%d pontos restantes.", pontos);
            printf("\nResistência: ");
            scanf("%d", &temp_resist);
            getchar();
            pontos -= temp_resist;

            if (pontos < 0) {
                printf("Você usou %d pontos, tenha mais cuidado", 100 - pontos);
            }
        } while(pontos < 0);

        atual->dado.cont_trofeu = 0;
        atual->dado.st_pil = 0;
        atual->dado.st_kart = 0;
        atual->dado.categ = temp_categ;
        atual->dado.vkart = temp_vkart;
        atual->dado.ac = temp_ac;
        atual->dado.ctrl = temp_ctrl;
        atual->dado.resist = temp_resist;

        if (*inicio == NULL) {
            *inicio = atual;
        } else {
            struct NODE* temp = *inicio;
            while (temp->prox != NULL) {
                temp = temp->prox;
            }
            temp->prox = atual;
        }
    }
}

void item_dist() {

}
    //MODULO 1 - CORRIDA

void cadastrar_corrida(node_corrida** inicio_fila) {
    int quant_corridas;
    int opcao_pista;

    printf("\n===================================\n");
    printf("         AGENDAR CORRIDAS\n");
    printf("===================================\n");
    printf("Quantas corridas deseja agendar? ");
    scanf("%d", &quant_corridas);
    getchar(); // Limpa o buffer do teclado

    // O laço 'for' vai rodar a quantidade de vezes que foi escolhida
    for (int i = 0; i < quant_corridas; i++) {
        
        // Alocamos a memória para cada novo nó DENTRO do laço
        node_corrida* novo = (node_corrida*)malloc(sizeof(node_corrida));
        if (novo == NULL) {
            printf("\nErro ao alocar a memória para a central de corridas.\n");
            return; 
        }

        printf("\n--- Escolha a corrida %d de %d ---\n", i + 1, quant_corridas);
        printf("1 - Circuito Luigi (Perigo: 15)\n");
        printf("2 - Circuito Mario (Perigo: 20)\n");
        printf("3 - Circuito Peach (Perigo: 30)\n");
        printf("4 - Circuito Yoshi (Perigo: 45)\n");
        printf("5 - Circuito Donkey Kong (Perigo: 60)\n");
        printf("6 - Circuito Wario (Perigo: 75)\n");
        printf("7 - Circuito Bowser (Perigo: 90)\n");
        printf("8 - Circuito Rainbow Road (Perigo: 100)\n");
        printf("===================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao_pista);
        getchar(); // Limpa o buffer do teclado

        switch (opcao_pista) {
            case 1:
                novo->dados_corrida.pista = 0; // 0 - Circuito Luigi
                novo->dados_corrida.dificuldade = 15;
                break;
            case 2:
                novo->dados_corrida.pista = 1; // 1 - Circuito Mario
                novo->dados_corrida.dificuldade = 20;
                break;
            case 3:
                novo->dados_corrida.pista = 2; // 2 - Circuito Peach
                novo->dados_corrida.dificuldade = 30;
                break;
            case 4:
                novo->dados_corrida.pista = 3; // 3 - Circuito Yoshi
                novo->dados_corrida.dificuldade = 45;
                break;
            case 5:
                novo->dados_corrida.pista = 4; // 4 - Circuito Donkey Kong
                novo->dados_corrida.dificuldade = 60;
                break;
            case 6:
                novo->dados_corrida.pista = 5; // 5 - Circuito Wario
                novo->dados_corrida.dificuldade = 75;
                break;
            case 7:
                novo->dados_corrida.pista = 6; // 6 - Circuito Bowser
                novo->dados_corrida.dificuldade = 90;
                break;
            case 8:
                novo->dados_corrida.pista = 7; // 7 - Circuito Rainbow Road
                novo->dados_corrida.dificuldade = 100;
                break;
            default:
                printf("Opção inválida! Esta corrida específica não foi cadastrada.\n");
                free(novo); // Libera o nó se digitou errado para não vazar memória
                continue;  
        }

        // Validação do número de voltas (Máximo 7)
        do {
            printf("Digite o número de voltas para esta corrida (1 a 7): ");
            scanf("%d", &novo->dados_corrida.num_voltas);
            getchar(); 
            if (novo->dados_corrida.num_voltas < 1 || novo->dados_corrida.num_voltas > 7) {
                printf("Número de voltas inválido! Tente novamente.\n");
            }
        } while (novo->dados_corrida.num_voltas < 1 || novo->dados_corrida.num_voltas > 7);
        
        // Configura a prioridade da corrida com base na dificuldade e define o status inicial
        novo->dados_corrida.prioridade = novo->dados_corrida.dificuldade; 
        novo->dados_corrida.status = 0; // 0 - aguardando
        novo->prox = NULL;

        //  algoritmo de inserção crescente (mais fáceis no início)
        if (*inicio_fila == NULL || novo->dados_corrida.prioridade < (*inicio_fila)->dados_corrida.prioridade) {
            novo->prox = *inicio_fila;
            *inicio_fila = novo;
        } else {
            node_corrida* atual = *inicio_fila;
            while (atual->prox != NULL && atual->prox->dados_corrida.prioridade <= novo->dados_corrida.prioridade) {
                atual = atual->prox;
            }
            novo->prox = atual->prox;
            atual->prox = novo;
        }

        printf(" Corrida %d adicionada com sucesso na fila ordenada!\n", i + 1);
    }
}

