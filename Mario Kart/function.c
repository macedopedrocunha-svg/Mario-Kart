#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

typedef struct DADOS {
    char piloto[30];
    int categ; // 0 - Leve, 1 - Médio, 2 - Pesado
    int cont_trofeu, st_pil; // 0 - Disponível, 1 - Acidentado, 2 - Banido
    int v_kart, ac, ctrl, resist, st_kart; // 0 - Operacional, 1 - Danificado. 2 - Destruído
    int hp;
    int item;
    int performance;
} personagem;

typedef struct NODE {
    personagem dado;
    struct NODE* prox;
} node;

typedef struct ITEM {
    int tipo; //  0 - banana, 1 - casco verde, 2 - cogumelo, 3 - casco vermelho, 4 - bob-omb, 5 - raio, 6 - bullet bill, 7 - casco azul;
    int quantidade[8];
}itens;

typedef struct PISTA {
    int pista; // 0 - Circuito Luigi, 1 - Circuito Mario , 2 - Circuito Peach , 3 - Circuito Yoshi  , 4 - Circuito Donkey Kong , 5 - Circuito Wario , 6 - Circuito Bowser, 7 - Circuito Rainbow Road
    int num_voltas, dificuldade;
    int status; // 0 - aguardando, 1 - em andamento, 2 - finalizada
}corrida;

typedef struct NODE_CORRIDA {
    corrida dados_corrida;
    struct NODE_CORRIDA* prox;
}node_corrida;

typedef struct NODE_HISTORICO {
    char pista_nome[50];
    char vencedor_nome[30];
    int total_pilotos;
    struct NODE_HISTORICO* topo;
} node_historico;

typedef struct OFICINA {
    char piloto_nome[30];
    int status_kart; // 1 - Danificado, 2 - Destruído
    struct OFICINA* prox;
} oficina;

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

void ordenar_performance(node* lista_pilotos) {
    if (lista_pilotos == NULL || lista_pilotos->prox == NULL) {
        return;
    }

    int trocou;
    node* atual;
    node* ultimo = NULL;

    do {
        trocou = 0;
        atual = lista_pilotos;

        while (atual->prox != ultimo) {
            if (atual->dado.performance > atual->prox->dado.performance) {
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

void menu_oficina(oficina** fila_oficina, node* lista_pilotos) { 
    int opcao_oficina;
    char nome_p[30];
    int status_k;

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
        getchar();

        switch (opcao_oficina) {
        case 1:
            printf("\n-------------------------------\n");
            printf("Registro de Karts\n");
            printf("-------------------------------\n");
            printf("Nome do piloto para manutenção: ");
            fgets(nome_p, 30, stdin);
            nome_p[strcspn(nome_p, "\n")] = 0;
            printf("Estado do Kart (1 - Danificado | 2 - Destruído): ");
            scanf("%d", &status_k);
            getchar();
            
            registrar_manutencao(&fila_oficina, nome_p, status_k);
            break;
        case 2:
            printf("\n-------------------------------------\n");
            printf("Iniciar reparo\n");
            printf("-------------------------------------\n");
            iniciar_reparo(&fila_oficina, lista_pilotos);
            break;
        case 3:
            printf("\n-------------------------------------\n");
            printf("Ver Fila de Reparos\n");
            printf("-------------------------------------\n");
            exibir_fila_oficina(*fila_oficina);       
            break;
        case 0:
            printf("\nVoltando ao menu principal...\n");
            break;
        default:
            printf("\nOpção inválida! Tente novamente.\n");
            break;
        }
    } while (opcao_oficina != 0);
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

        printf("Digite o nome do piloto %d: ", i + 1);
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
        } while (pontos < 0);

        atual->dado.cont_trofeu = 0;
        atual->dado.st_pil = 0;
        atual->dado.st_kart = 0;
        atual->dado.hp = 100;
        atual->dado.item = 8;
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
        printf("\nPiloto '%s' criado com sucesso!\n", atual->dado.piloto);
    }
}

void procurar_personagem(node** inicio) {
    if (*inicio == NULL) {
        printf("Nenhum personagem criado");
        return;
    }

    int encontrado = 0;
    char nome[30];
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    node* temp = *inicio;
    while (temp->prox != NULL) {
        if (!strcmp(nome, temp->dado.piloto)) {
            encontrado = 1;
            break;
        }
        temp = temp->prox;
    }
    if (encontrado) {
        printf("\n==================================\n");
        printf("              PILOTO              \n");
        printf("==================================\n");
        printf("Nome: %s\n", temp->dado.piloto);
        printf("Categoria: %s\n", (temp->dado.categ == 1) ? "Leve" : (temp->dado.categ == 2) ? "Médio" : "Pesado");
        printf("Status: %s\n", (temp->dado.st_pil == 0) ? "Disponível" : (temp->dado.st_pil == 1) ? "Acidentado" : "Banido");
        printf("Quantidade de Troféus: %d\n", temp->dado.cont_trofeu);
        printf("Velocidade: %d\n", temp->dado.v_kart);
        printf("Aceleração: %d\n", temp->dado.ac);
        printf("Controle: %d\n", temp->dado.ctrl);
        printf("Resistência: %d\n", temp->dado.resist);
        printf("Status do Kart %s", (temp->dado.st_kart == 0) ? "Operacional" : (temp->dado.st_kart == 1) ? "Danificado" : "Destruído");
        printf("===================================\n");
    } else {
        printf("Piloto não encontrado!\n");
    }
}

void pers_banidos() {
    char token_nome[30];
    int token_trofeu, encontrou = 0;
    FILE* arq = fopen("ban.txt", "r");

    if (arq == NULL) {
        printf("Falha em carregar os dados!");
        return;
    }

    while (fscanf(arq, " %[^;];%d", token_nome, &token_trofeu) == 2) {
        printf("Jogador: %s | Pontos: %d\n", token_nome, token_trofeu);
        encontrou = 1;
    }
    if (!encontrou) {
        printf("Nenhum piloto banido!");
    }
}

//MODULO 1 - CORRIDA

void cadastrar_corrida(node_corrida** inicio_fila) {
    int quant_corridas;
    int opcao_pista;

    do {
        printf("\n===================================\n");
        printf("         AGENDAR CORRIDAS\n");
        printf("===================================\n");
        printf("Quantas corridas deseja agendar? (Máximo 8)");
        scanf("%d", &quant_corridas);
        getchar();
    } while (quant_corridas < 1 || quant_corridas > 8);

    for (int i = 0; i < quant_corridas; i++) {
        node_corrida* novo = (node_corrida*)malloc(sizeof(node_corrida));
        if (novo == NULL) {
            printf("\nErro ao alocar a memória.\n");
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
            free(novo);
            opcao_pista = -1;
            continue;
        }

        if (opcao_pista != -1) {
            do {
                printf("Digite o número de voltas para esta corrida (1 a 7): ");
                scanf("%d", &novo->dados_corrida.num_voltas);
                getchar();
                if (novo->dados_corrida.num_voltas < 1 || novo->dados_corrida.num_voltas > 7) {
                    printf("Número de voltas inválido! Tente novamente.\n");
                }
            } while (novo->dados_corrida.num_voltas < 1 || novo->dados_corrida.num_voltas > 7);

            novo->dados_corrida.status = 0;
            novo->prox = NULL;

            if (*inicio_fila == NULL || novo->dados_corrida.dificuldade < (*inicio_fila)->dados_corrida.dificuldade) {
                novo->prox = *inicio_fila;
                *inicio_fila = novo;
            } else {
                node_corrida* atual = *inicio_fila;
                while (atual->prox != NULL && atual->prox->dados_corrida.dificuldade <= novo->dados_corrida.dificuldade) {
                    atual = atual->prox;
                }
                novo->prox = atual->prox;
                atual->prox = novo;
            }

            printf(" Corrida %d adicionada com sucesso na fila ordenada!\n", i + 1);
        }
    }
}

// MÓDULO 3 - ITENS

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

void menu_itens_gerenciar(node* lista_pilotos, itens* estoque) {
    int opcao, contador[] = {0,0,0,0,0,0,0,0};
    do {
        menu_itens();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
        case 1: exibir_estoque(estoque);
            break;
        case 2:
            printf("\n===================================\n");
            printf("        ITENS EM USO NA PISTA      \n");
            printf("===================================\n");
            printf("Analisando Karts...\n");
            printf("-----------------------------------\n");

            if (lista_pilotos == NULL) {
                printf("Nenhum piloto na pista no momento para monitorar.\n");
            } else {
                node* temp_piloto = lista_pilotos;
                while (temp_piloto != NULL) {
                    if (temp_piloto->dado.item == 0) {
                        contador[0]++;
                    } else if(temp_piloto->dado.item == 1) {
                        contador[1]++;
                    } else if (temp_piloto->dado.item == 2) {
                        contador[2]++;
                    } else if (temp_piloto->dado.item == 3) {
                        contador[3]++;
                    } else if (temp_piloto->dado.item == 4) {
                        contador[4]++;
                    } else if (temp_piloto->dado.item == 5) {
                        contador[5]++;
                    } else if (temp_piloto->dado.item == 6) {
                        contador[6]++;
                    } else if (temp_piloto->dado.item == 7) {
                        contador[7]++;
                    }
                    temp_piloto = temp_piloto->prox;
                }
                printf("Bananas: %d\nCascos Verdes: %d\nCogumelos: %d\nCascos Vermelhos: %d\nBob-Ombs: %d\nRaios: %d\nBullet Bills: %d\nCascos Azuis: %d",
                    contador[0], contador[1], contador[2], contador[3], contador[4], contador[5], contador[6], contador[7]);
            }
            printf("===================================\n");
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

void item_dist(node* lista_pilotos, itens* estoque) {
    if (lista_pilotos == NULL) {
        printf("\nNão há pilotos na pista para receberem itens! Cadastre um piloto primeiro na opção 5.\n");
        return;
    }
    node* piloto_atual = lista_pilotos;
    int menor = piloto_atual->dado.performance;
    int sucesso;
    
    while (piloto_atual != NULL) { // acha a menor performance para o casco azul
        if (piloto_atual->dado.performance < menor) {
            menor = piloto_atual->dado.performance;
        }
        piloto_atual = piloto_atual->prox;
    }
    piloto_atual = lista_pilotos;

    while (piloto_atual != NULL) {
        if (piloto_atual->dado.performance == menor) {
            sucesso = rand() % 100;
            if (sucesso < 50) {
                piloto_atual->dado.item = 7;
                estoque->quantidade[7]--;
            }
        } else {
            sucesso = rand() % 100;
            if (sucesso < 20 && estoque->quantidade[0] > 0) {
                piloto_atual->dado.item = 0;
                estoque->quantidade[0]--;
            } else if (sucesso < 40 && estoque->quantidade[1] > 0) {
                piloto_atual->dado.item = 1;
                estoque->quantidade[1]--;
            } else if (sucesso < 60 && estoque->quantidade[2] > 0) {
                piloto_atual->dado.item = 2;
                estoque->quantidade[2]--;
            } else if (sucesso < 74 && estoque->quantidade[3] > 0) {
                piloto_atual->dado.item = 3;
                estoque->quantidade[3]--;
            } else if (sucesso < 88 && estoque->quantidade[4] > 0) {
                piloto_atual->dado.item = 4;
                estoque->quantidade[4]--;
            } else if (sucesso < 94 && estoque->quantidade[5] > 0) {
                piloto_atual->dado.item = 5;
                estoque->quantidade[5]--;
            } else if (estoque->quantidade[6] > 0) {
                piloto_atual->dado.item = 6;
                estoque->quantidade[6]--;
            } else {
                piloto_atual->dado.item = -1;
            }
        }
        piloto_atual = piloto_atual->prox;
    }
}

//MODULO 4 - HISTORICO

void exibir_historico(node* lista_pilotos) {
    if (lista_pilotos == NULL) {
        printf("\nNenhum piloto cadastrado no sistema!\n");
        return;
    }

    ordenar(lista_pilotos);

    printf("\n===================================\n");
    printf("         HISTÓRICO DE PILOTOS\n");
    printf("===================================\n");

    node* atual = lista_pilotos;
    while (atual != NULL) {
        printf("Piloto: %s | Categoria: %s | Troféus: %d | Status do Piloto: %s | Status do Kart: %s\n",
            atual->dado.piloto,
            (atual->dado.categ == 1) ? "Leve" : (atual->dado.categ == 2) ? "Médio" : "Pesado",
            atual->dado.cont_trofeu,
            (atual->dado.st_pil == 0) ? "Disponível" : (atual->dado.st_pil == 1) ? "Acidentado" : "Banido",
            (atual->dado.st_kart == 0) ? "Operacional" : "Danificado");

        atual = atual->prox;
    }
}

// MODULO 5 - OFICINA 

void registrar_manutencao(oficina** topo_oficina, char* nome, int status) {
    oficina* novo = (oficina*)malloc(sizeof(oficina));
    if (!novo) {
        printf("[!] Erro de alocação de memória na oficina.\n");
        return;
    }
    strcpy(novo->piloto_nome, nome);
    novo->status_kart = status;
    novo->prox = NULL;

    if (*topo_oficina == NULL || status > (*topo_oficina)->status_kart) {
        novo->prox = *topo_oficina;
        *topo_oficina = novo;
        printf("Kart de %s enviado para a oficina com prioridade máxima!\n", nome);
        return;
    }

    // varre a fila para encontrar a posição correta (inserção por prioridade)
    oficina* atual = *topo_oficina;
    while (atual->prox != NULL && atual->prox->status_kart >= status) {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
    printf("Kart de %s adicionado à fila de reparos.\n", nome);
}

void iniciar_reparo(oficina** topo_oficina, node* lista_pilotos) {
    if (*topo_oficina == NULL) {
        printf("\nNenhum kart aguardando manutenção na oficina.\n");
        return;
    }

    oficina* repara_agora = *topo_oficina;

    node* p_atual = lista_pilotos;
    while (p_atual != NULL) {
        if (strcmp(p_atual->dado.piloto, repara_agora->piloto_nome) == 0) {
            p_atual->dado.st_kart = 0; // Volta a ser Operacional!
            break;
        }
        p_atual = p_atual->prox;
    }

    printf("\n===================================\n");
    printf(" REPARO CONCLUÍDO PELO PROFESSOR E. GADD \n");
    printf("===================================\n");        
    printf("O Kart do piloto %s foi totalmente reparado!\n", repara_agora->piloto_nome);
    printf("Situação anterior: %s\n", (repara_agora->status_kart == 2) ? " Estava Destruído" : " Estava Danificado");
    printf("Status atualizado para: OPERACIONAL! \n");
    printf("===================================\n");

    *topo_oficina = (*topo_oficina)->prox;
    free(repara_agora);
}

void exibir_fila_oficina(oficina* topo_oficina) {
    if (topo_oficina == NULL) {
        printf("\n[Oficina Vazia] Todos os karts estão operacionais na pista!\n");
        return;
    }

    printf("\n===================================\n");
    printf("  FILA DE MANUTENÇÃO ATUAL \n");
    printf("===================================\n");

    oficina* atual = topo_oficina;
    int pos = 1;
    while (atual != NULL) {
        printf("%dº -> Piloto: %s | Estado: %s\n",
            pos++,
            atual->piloto_nome,
            (atual->status_kart == 2) ? " DESTRUÍDO (Prioridade Máxima)" : " DANIFICADO");
        atual = atual->prox;
    }
    printf("===================================\n");
}

void realizar_corrida(node_corrida** inicio_fila, node* lista_pilotos, itens* estoque, int* cont_acidentes) {
    if (*inicio_fila == NULL) {
        printf("\n Não há corridas agendadas na fila! Agende uma corrida primeiro (Opção 1).\n");
        return;
    }
    if (lista_pilotos == NULL) {
        printf("\n Não há pilotos cadastrados para correr! Cadastre pilotos primeiro (Opção 5).\n");
        return;
    }

    int tempv, contador = 0;
    int sorte, efeito_item[2];
    int rclima = rand() % 3;
    node_corrida* corrida_atual = *inicio_fila;
    corrida dados = corrida_atual->dados_corrida;

    char* nomes_pistas[] = {
        "Circuito Luigi", "Circuito Mario", "Circuito Peach", "Circuito Yoshi",
        "Circuito Donkey Kong", "Circuito Wario", "Circuito Bowser", "Circuito Rainbow Road"
    };
    char* clima[] = {"Sol", "Chuva", "Neve"};

    printf("\n==================================================\n");
    printf("  A CORRIDA VAI COMEÇAR! \n");
    printf("==================================================\n");
    printf("Pista: %s\n", nomes_pistas[dados.pista]);
    printf("Voltas: %d | Dificuldade/Perigo: %d\n", dados.num_voltas, dados.dificuldade);
    printf("Clima: %s", clima[rclima]);
    printf("--------------------------------------------------\n");
    printf("3... 2... 1... VAI VAI VAI!!! \n\n");

    node* piloto_atual = lista_pilotos;

    printf("--- DESEMPENHO NA PISTA ---\n");
    for (int i = 0; i < dados.num_voltas; i++) {
        contador = 0;
        item_dist(lista_pilotos, estoque);
        while (piloto_atual != NULL) {
            sorte = (rand() % 30) + 1;
            int performance = 0;

            if (contador != 0) {
                tempv = piloto_atual->dado.v_kart - efeito_item[1];
            } else {
                tempv = piloto_atual->dado.v_kart;
            }

            if (!strcmp(clima[rclima], "Sol")) {
                performance = (tempv + (piloto_atual->dado.ac / piloto_atual->dado.categ + 1) + piloto_atual->dado.ctrl - (dados.dificuldade / (piloto_atual->dado.resist + 1)) + sorte);
            } else if (!strcmp(clima[rclima], "Chuva")) {
                performance = (tempv + (piloto_atual->dado.ac / (6/(piloto_atual->dado.categ + 1))) + (piloto_atual->dado.ctrl * 1.5) - (dados.dificuldade / (piloto_atual->dado.resist + 1)) + sorte);
            } else if (!strcmp(clima[rclima], "Neve")) {
                performance = (tempv + (piloto_atual->dado.ac / (12/piloto_atual->dado.categ + 1)) + (piloto_atual->dado.ctrl * 3) - (dados.dificuldade / (piloto_atual->dado.resist + 1)) + sorte);
            }
            piloto_atual->dado.performance += performance;

            if (piloto_atual->dado.item == 0) { // banana
                efeito_item[0] = 0;
                efeito_item[1] = 30;
            } else if (piloto_atual->dado.item == 1) { // casco verde
                efeito_item[0] = 20;
                efeito_item[1] = 10;
            } else if (piloto_atual->dado.item == 2) { // cogumelo
                piloto_atual->dado.performance += 20;
            } else if (piloto_atual->dado.item == 3) { // casco vermelho
                efeito_item[0] = 40;
                efeito_item[1] = 20;
            } else if (piloto_atual->dado.item == 4) { // bob-omb
                efeito_item[0] = 50;
                efeito_item[1] = 0;
            } else if (piloto_atual->dado.item == 5) {  // raio
                efeito_item[0] = 20;
                efeito_item[1] = 40;
            } else if (piloto_atual->dado.item == 6) { // bullet bill
                efeito_item[0] = 80;
                efeito_item[1] = 0;
            } else if (piloto_atual->dado.item == 7) {  // casco azul
                efeito_item[0] = 60;
                efeito_item[1] = 30;
            } else if (piloto_atual->dado.item == -1) { // sem item
                efeito_item[0] = 0;
                efeito_item[1] = 0;
            }

            if (piloto_atual->prox != NULL) {
                piloto_atual = piloto_atual->prox;
                piloto_atual->dado.hp -= efeito_item[0];
            } else {
                node* temp = lista_pilotos;
                temp->dado.hp -= efeito_item[0];
                if (piloto_atual->dado.item != 2) {
                    temp->dado.performance -= efeito_item[1];
                }
            }

            contador++;

        }
    }

    piloto_atual = lista_pilotos;
    while (piloto_atual != NULL) {
        if (piloto_atual->dado.hp <= 0) {
            piloto_atual->dado.performance = 0;
            (*cont_acidentes)++;
            printf("• %s sofreu um acidente e não completou a corrida!\n", piloto_atual->dado.piloto);
        }
        if (piloto_atual->dado.performance > 0) {
            printf("• %s cruzou a linha de chegada (Score de Corrida: %d)\n", piloto_atual->dado.piloto, piloto_atual->dado.performance);
        }
    }   
    
    ordenar_performance(lista_pilotos); 

    printf("\n==================================================\n");
    printf(" CLASSIFICAÇÃO OFICIAL DA CORRIDA (TABELA FMKR) \n");
    printf("==================================================\n");

    piloto_atual = lista_pilotos;
    int posicao = 1;

    while (piloto_atual != NULL) {
        int pontos_corrida = 0;

        switch (posicao) {
        case 1: pontos_corrida = 15; break;
        case 2: pontos_corrida = 12; break;
        case 3: pontos_corrida = 10; break;
        case 4: pontos_corrida = 8;  break;
        case 5: pontos_corrida = 6;  break;
        default: pontos_corrida = 0; break;
        }

        piloto_atual->dado.cont_trofeu += pontos_corrida;

        if (posicao == 1) {
            printf(" 1º Lugar: %s! (+15 Pontos) -> VITÓRIA ABSOLUTA! \n", piloto_atual->dado.piloto);
        } else if (posicao == 2) {
            printf(" 2º Lugar: %s! (+12 Pontos)\n", piloto_atual->dado.piloto);
        } else if (posicao == 3) {
            printf(" 3º Lugar: %s! (+10 Pontos)\n", piloto_atual->dado.piloto);
        } else {
            printf("  %dº Lugar: %s (+%d Pontos)\n", posicao, piloto_atual->dado.piloto, pontos_corrida);
        }

        posicao++;
        piloto_atual = piloto_atual->prox;
    }

    printf("\nCorrida finalizada! Pontos computados no Ranking da Temporada. \n");
    printf("==================================================\n");

    *inicio_fila = (*inicio_fila)->prox;
    free(corrida_atual);
}

void atualizar_pontuacao_corrida(node* lista_pilotos, int posicao, node* piloto) {
    int pontos_corrida = 0;

    switch (posicao) {
        case 1: 
            pontos_corrida = 15; piloto->dado.cont_trofeu++; 
            break;
        case 2:
            pontos_corrida = 12; 
            break;
        case 3: 
            pontos_corrida = 10;
            break;
        case 4: 
            pontos_corrida = 8;  
            break;
        case 5: 
            pontos_corrida = 6;  
            break;
        default: 
            pontos_corrida = 0;     
            break;
    }

    piloto->dado.cont_trofeu += pontos_corrida;
    printf("%dº Lugar: %s | +%d Pontos na Temporada!\n", posicao, piloto->dado.piloto, pontos_corrida);
}

void exibir_ranking_campeonato(node* lista_pilotos) {
    if (lista_pilotos == NULL) {
        printf("\n[!] Nenhum piloto pontuou no campeonato ainda.\n");
        return;
    }

    ordenar(lista_pilotos); 

    printf("\n==================================================\n");
    printf("  CLASSIFICAÇÃO OFICIAL DO CAMPEONATO \n");
    printf("==================================================\n");

    node* atual = lista_pilotos;
    int pos = 1;

    while (atual != NULL && pos <= 10) {
        printf(" %dº Lugar -> %s | Categoria: %s | Pontuação Histórica: %d Troféus\n",
               pos,
               atual->dado.piloto,
               (atual->dado.categ == 1) ? "Leve" : (atual->dado.categ == 2) ? "Médio" : "Pesado",
               atual->dado.cont_trofeu);
        
        // Detecção de empate
        if (atual->prox != NULL && atual->dado.cont_trofeu == atual->prox->dado.cont_trofeu) {
            printf("Empate técnico momentâneo com o próximo piloto!\n");
        }
        
        pos++;
        atual = atual->prox;
    }
    printf("==================================================\n");
}

void determinar_campeao_temporada(node* lista_pilotos) {
    if (lista_pilotos == NULL) {
        printf("\nNão há pilotos para disputar o título.\n");
        return;
    }

    ordenar(lista_pilotos);

    printf("\n==============================================\n");
    printf("  O GRANDE CAMPEÃO DA TEMPORADA FOI DEFINIDO!\n");
    printf("====================================================\n");
    printf("  PARABÉNS, %s!!! \n", lista_pilotos->dado.piloto);
    printf("  Dominou as pistas com a categoria %s e acumulou %d troféus!\n",
        (lista_pilotos->dado.categ == 1) ? "Leve" : (lista_pilotos->dado.categ == 2) ? "Médio" : "Pesado",
        lista_pilotos->dado.cont_trofeu);
    printf("====================================================\n");
}

// SISTEMA DE ARMAZENAMENTO

void salvar(node* lista_pilotos) {
    FILE* arq = fopen("pilotos.txt", "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo de salvamento dos pilotos.\n");
        return;
    }

    node* atual = lista_pilotos;
    while (atual != NULL) {
        fprintf(arq, "%s;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
            atual->dado.piloto, atual->dado.categ, atual->dado.cont_trofeu,
            atual->dado.st_pil, atual->dado.v_kart, atual->dado.ac,
            atual->dado.ctrl, atual->dado.resist, atual->dado.st_kart,
            atual->dado.hp, atual->dado.item, atual->dado.performance);

        atual = atual->prox;
    }

    fclose(arq);
    printf("Dados dos pilotos salvos com sucesso!\n");
}

void carregar(node** lista_pilotos, oficina** fila_oficina) {
    FILE* arq = fopen("pilotos.txt", "r");
    if (arq == NULL) {
        printf("Nenhum save de pilotos encontrado. A temporada começará do zero.\n");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arq)) {
        node* novo = (node*)malloc(sizeof(node));
        if (novo == NULL) break;

        sscanf(linha, "%[^;];%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d",
            novo->dado.piloto, &novo->dado.categ, &novo->dado.cont_trofeu,
            &novo->dado.st_pil, &novo->dado.v_kart, &novo->dado.ac,
            &novo->dado.ctrl, &novo->dado.resist, &novo->dado.st_kart,
            &novo->dado.hp, &novo->dado.item, &novo->dado.performance);

        novo->prox = NULL;

        if (*lista_pilotos == NULL) {
            *lista_pilotos = novo;
        } else {
            node* temp = *lista_pilotos;
            while (temp->prox != NULL) temp = temp->prox;
            temp->prox = novo;
        }

        if (novo->dado.st_kart > 0) {
            registrar_manutencao(fila_oficina, novo->dado.piloto, novo->dado.st_kart);
        }
    }

    fclose(arq);
    printf("Pilotos e fila da Oficina carregados com sucesso!\n");
}

void salvar_historico(node_historico* pilha_historico) {
    FILE* arq = fopen("historico.txt", "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo de histórico.\n");
        return;
    }

    node_historico* atual = pilha_historico;
    while (atual != NULL) {
        fprintf(arq, "%s;%s;%d\n", atual->pista_nome, atual->vencedor_nome, atual->total_pilotos);
        atual = atual->topo;
    }

    fclose(arq);
    printf("Histórico salvo com sucesso!\n");
}

void carregar_historico(node_historico** pilha_historico) {
    FILE* arq = fopen("historico.txt", "r");
    if (arq == NULL) {
        printf("Nenhum histórico antigo encontrado.\n");
        return;
    }

    char linha[256];
    node_historico* ultimo = NULL;

    while (fgets(linha, sizeof(linha), arq)) {
        node_historico* novo = (node_historico*)malloc(sizeof(node_historico));
        if (novo == NULL) break;

        sscanf(linha, "%[^;];%[^;];%d", novo->pista_nome, novo->vencedor_nome, &novo->total_pilotos);
        novo->topo = NULL;

        if (*pilha_historico == NULL) {
            *pilha_historico = novo;
        } else {
            ultimo->topo = novo;
        }
        ultimo = novo;
    }

    fclose(arq);
    printf("Histórico carregado com sucesso!\n");
}
