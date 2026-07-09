#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

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
    printf("----------------------------------\n");
    printf("      RANKING (Módulo 4 em breve) \n");
    printf("----------------------------------\n");
}

void menu_itens() {
    printf("\n");
    printf("1 - Ver estoque \n");
    printf("2 - Ver itens em uso\n");
    printf("3 - Repor itens\n");
    printf("0 - Sair\n");
}

void ordenar(node* cabeca) {
    if (cabeca == NULL || cabeca->prox == NULL) {
        return;
    }

    int trocou;
    node* atual;
    node* ultimo = NULL;

    do {
        trocou = 0;
        atual = cabeca;

        while (atual->prox != ultimo) {
            if (atual->dado.cont_trofeu > atual->prox->dado.cont_trofeu) {
                personagem temp = atual->dado;
                atual->dado = atual->prox->dado;
                atual->prox->dado = temp;
                trocou = 1;
            }
            atual = atual->prox;
        }
        ultimo = atual; 
    } while (trocou);
}

void oficina() {
    int opcao_oficina;
    do {
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
                break;
            case 2:
                printf("\n-------------------------------------\n");
                printf("Iniciar reparo\n");
                printf("-------------------------------------\n");
                break;
            case 3:
                printf("\n-------------------------------------\n");
                printf("Ver Fila de Reparos\n");
                printf("-------------------------------------\n");
                break;
            case 0:
                printf("\nVoltando ao menu principal...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    } while(opcao_oficina != 0);
}

void criar_personagem(node** inicio) {
    int quant, temp_categ, pontos, temp_vkart, temp_ac, temp_ctrl, temp_resist;
    
    printf("\n");
    printf("===============================\n");
    printf("        CRIAR PERSONAGEM\n");
    printf("===============================\n");
    printf("Quantos personagens você quer criar? ");
    scanf("%d", &quant);
    getchar();

    for (int i = 0; i < quant; i++) {
        node* atual = (node*)malloc(sizeof(node));
        if (atual == NULL) {
            printf("Limite de memória atingido!\n");
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
                printf("Você usou %d pontos, tenha mais cuidado\n", 100 - pontos);
            }
        } while(pontos < 0);

        atual->dado.cont_trofeu = 0;
        atual->dado.st_pil = 0;
        atual->dado.st_kart = 0;
        atual->dado.categ = temp_categ;
        atual->dado.v_kart = temp_vkart; 
        atual->dado.ac = temp_ac;
        atual->dado.ctrl = temp_ctrl;
        atual->dado.resist = temp_resist;

        if (*inicio == NULL) {
            *inicio = atual;
        } else {
            node* temp = *inicio;
            while (temp->prox != NULL) {
                temp = temp->prox;
            }
            temp->prox = atual;
        }
        printf("\n[FMKR] Piloto '%s' criado com sucesso!\n", atual->dado.piloto);
    }
}

void procurar_personagem(node* inicio) {
    if (inicio == NULL) {
        printf("\nNenhum piloto cadastrado no sistema!\n");
        return;
    }

    char nome_busca[30];
    printf("\n===================================\n");
    printf("        PROCURAR PERSONAGEM\n");
    printf("===================================\n");
    printf("Digite o nome do piloto para buscar: ");
    fgets(nome_busca, 30, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    node* atual = inicio;
    int encontrado = 0;

    while (atual != NULL) {
        if (strcmp(atual->dado.piloto, nome_busca) == 0) {
            encontrado = 1;
            printf("\n--- Piloto Encontrado! ---");
            printf("\nNome: %s", atual->dado.piloto);
            printf("\nCategoria: %s", (atual->dado.categ == 1) ? "Leve" : (atual->dado.categ == 2) ? "Médio" : "Pesado");
            printf("\nTroféus: %d", atual->dado.cont_trofeu);
            printf("\nStatus do Piloto: %s", (atual->dado.st_pil == 0) ? "Ativo" : "Banido/Suspenso");
            printf("\nVelocidade: %d | Aceleração: %d | Controle: %d | Resistência: %d", 
                   atual->dado.v_kart, atual->dado.ac, atual->dado.ctrl, atual->dado.resist);
            printf("\nStatus do Kart: %s", (atual->dado.st_kart == 0) ? "Operacional" : "Danificado");
            printf("\n---------------------------\n");
            break;
        }
        atual = atual->prox;
    }

    if (!encontrado) {
        printf("\nPiloto '%s' não foi encontrado.\n", nome_busca);
    }
}

void listar_personagens_banidos(node* inicio) {
    if (inicio == NULL) {
        printf("\nNenhum piloto cadastrado no sistema.\n");
        return;
    }

    printf("\n===================================\n");
    printf("        PILOTOS BANIDOS\n");
    printf("===================================\n");

    node* atual = inicio;
    int cont_banidos = 0;

    while (atual != NULL) {
        if (atual->dado.st_pil != 0) {
            printf("- Piloto: %s | Troféus: %d\n", atual->dado.piloto, atual->dado.cont_trofeu);
            cont_banidos++;
        }
        atual = atual->prox;
    }

    if (cont_banidos == 0) {
        printf("Nenhum piloto banido por enquanto!\n");
    }
    printf("===================================\n");
}

void cadastrar_corrida(node_corrida** inicio_fila) {
    int quant_corridas;
    int opcao_pista;

    printf("\n===================================\n");
    printf("         AGENDAR CORRIDAS\n");
    printf("===================================\n");
    printf("Quantas corridas deseja agendar? ");
    scanf("%d", &quant_corridas);
    getchar();

    for (int i = 0; i < quant_corridas; i++) {
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
        getchar();

        switch (opcao_pista) {
        case 1: 
            novo->dados_corrida.pista = 0; 
            novo->dados_corrida.dificuldade = 15; 
            break;
        case 2: 
            novo->dados_corrida.pista = 1; 
            novo->dados_corrida.dificuldade = 20; 
            break;
        case 3: 
            novo->dados_corrida.pista = 2; 
            novo->dados_corrida.dificuldade = 30; 
            break;
        case 4: 
            novo->dados_corrida.pista = 3; 
            novo->dados_corrida.dificuldade = 45; 
            break;
        case 5: 
            novo->dados_corrida.pista = 4; 
            novo->dados_corrida.dificuldade = 60; 
            break;
        case 6: 
            novo->dados_corrida.pista = 5; 
            novo->dados_corrida.dificuldade = 75; 
            break;
        case 7: 
            novo->dados_corrida.pista = 6; 
            novo->dados_corrida.dificuldade = 90; 
            break;
        case 8: novo->dados_corrida.pista = 7; 
        novo->dados_corrida.dificuldade = 100; 
        break;
        default:
                printf("Opção inválida! Esta corrida específica não foi cadastrada.\n");
                free(novo);
                continue;  
        }

        do {
            printf("Digite o número de voltas para esta corrida (1 a 7): ");
            scanf("%d", &novo->dados_corrida.num_voltas);
            getchar(); 
            if (novo->dados_corrida.num_voltas < 1 || novo->dados_corrida.num_voltas > 7) {
                printf("Número de voltas inválido! Tente novamente.\n");
            }
        } while (novo->dados_corrida.num_voltas < 1 || novo->dados_corrida.num_voltas > 7);
        
        novo->dados_corrida.prioridade = novo->dados_corrida.dificuldade; 
        novo->dados_corrida.status = 0; 
        novo->prox = NULL;

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

void inicializar_estoque(itens* estoque) {
    estoque->quantidade[0] = 15; // Casco Verde
    estoque->quantidade[1] = 10; // Casco Vermelho
    estoque->quantidade[2] = 20; // Banana
    estoque->quantidade[3] = 12; // Cogumelo
    estoque->quantidade[4] = 8;  // Bob-omb
    estoque->quantidade[5] = 5;  // Raio
    estoque->quantidade[6] = 4;  // Bullet Bill
    estoque->quantidade[7] = 3;  // Casco Azul
    printf("\n Estoque inicializado com sucesso!\n");
}

void exibir_estoque(itens* estoque) {
    printf("\n===================================\n");
    printf("         ESTOQUE DE ITENS\n");
    printf("===================================\n");
    printf("0 - Casco Verde: %d unidades\n", estoque->quantidade[0]);
    printf("1 - Casco Vermelho: %d unidades\n", estoque->quantidade[1]);
    printf("2 - Banana: %d unidades\n", estoque->quantidade[2]);
    printf("3 - Cogumelo: %d unidades\n", estoque->quantidade[3]);
    printf("4 - Bob-omb: %d unidades\n", estoque->quantidade[4]);
    printf("5 - Raio: %d unidades\n", estoque->quantidade[5]);
    printf("6 - Bullet Bill: %d unidades\n", estoque->quantidade[6]);
    printf("7 - Casco Azul: %d unidades\n", estoque->quantidade[7]);
    printf("===================================\n");
}

void repor_estoque(itens* estoque) {
    int tipo, qtd;
    exibir_estoque(estoque);
    printf("Digite o número do item que deseja repor (0 a 7): ");
    scanf("%d", &tipo);
    if (tipo < 0 || tipo > 7) {
        printf("Item inválido!\n");
        return;
    }
    printf("Quantas unidades deseja adicionar ao estoque? ");
    scanf("%d", &qtd);
    estoque->quantidade[tipo] += qtd;
    printf("\n Estoque updated! Nova quantidade do item %d: %d\n", tipo, estoque->quantidade[tipo]);
}

void menu_itens_gerenciar(itens* estoque) {
    int opcao;
    do {
        menu_itens(); 
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();
        
    switch(opcao) {
        case 1: exibir_estoque(estoque); 
            break;
        case 2: 
            printf("\nItens em uso serão calculados durante a corrida!\n"); 
            break;
        case 3: 
            repor_estoque(estoque); 
            break;
        case 0: 
            printf("\nVoltando ao menu principal...\n"); 
            break;
        default: 
        printf("\nOpção inválida!\n"); 
        break;
        }
    } while (opcao != 0);
}

void item_dist(node* lista_pilotos, itens* estoque) {
    if (lista_pilotos == NULL) {
        printf("\nNão há pilotos na pista para receberem itens! Cadastre um piloto primeiro na opção 5.\n");
        return;
    }
    char nome_piloto[30];
    printf("\nDigite o nome do piloto que passou por uma Caixa de Item [?]: ");
    fgets(nome_piloto, 30, stdin);
    nome_piloto[strcspn(nome_piloto, "\n")] = 0;

    node* atual = lista_pilotos;
    while (atual != NULL) {
        if (strcmp(atual->dado.piloto, nome_piloto) == 0) {
            int item_sorteado = rand() % 8;

            if (estoque->quantidade[item_sorteado] > 0) {
                estoque->quantidade[item_sorteado]--;
                char* nomes_itens[] = {"Casco Verde", "Casco Vermelho", "Banana", "Cogumelo", "Bob-omb", "Raio", "Bullet Bill", "Casco Azul"};
                printf("\n[?] %s pegou um: %s! (1 unidade retirada do estoque global)\n", atual->dado.piloto, nomes_itens[item_sorteado]);
            } else {
                printf("\nO item sorteado está esgotado no estoque central! Tente novamente na próxima caixa.\n");
            }
            return;
    }
         atual = atual->prox;
    }
    printf("\nPiloto '%s' não está no grid de largada.\n", nome_piloto);
}
