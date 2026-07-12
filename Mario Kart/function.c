#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

typedef struct DADOS {
    char piloto[30];
    int categ; // 0 - Leve, 1 - Médio, 2 - Pesado
    int cont_trofeu, st_pil; // 0 - Disponível, 1 - Acidentado, 2 - Banido
    int v_kart, ac, ctrl, resist, st_kart; // 0 - Operacional, 1 - Danificado. 2 - Destruído
    int performance;
} personagem;

typedef struct NODE {
    personagem dado;
    struct NODE* prox;
} node;

typedef struct ITEM {
    int tipo; //  0 - casco verde, 1 - casco vermelho, 2 - banana, 3 - cogumelo, 4 - bob-omb, 5 - raio, 6 - bullet bill, 7 - casco azul;
    int raridade; // 0 - comum, 1 - raro, 2 - épico, 3 - lendário
    int poder;
    int quantidade[8];

}itens;

typedef struct PISTA {
    int pista; // 0 - Circuito Luigi, 1 - Circuito Mario , 2 - Circuito Peach , 3 - Circuito Yoshi  , 4 - Circuito Donkey Kong , 5 - Circuito Wario , 6 - Circuito Bowser, 7 - Circuito Rainbow Road
    int num_voltas;
    int dificuldade; // de 1 a 100
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
    struct NODE_HISTORICO* topo; // Aponta para a corrida anterior na pilha
} node_historico;

typedef struct NODE_OFICINA {
    char piloto_nome[30];
    int status_kart; // 1 - Danificado, 2 - Destruído
    struct NODE_OFICINA* prox;
} node_oficina;

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
    printf("---------------------------------\n");
    printf("   RANKING (Módulo 4 em breve)\n");
    printf("---------------------------------\n");
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

void oficina(node* lista_pilotos) { // Adicionado o parâmetro para poder atualizar o status do piloto
    static node_oficina* fila_oficina = NULL; // Mantém a fila da oficina viva entre as chamadas
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
        getchar(); // Limpa o buffer

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
            // passando a fila e a lista geral de pilotos para atualizar o grid
            iniciar_reparo(&fila_oficina, lista_pilotos);
            break;
        case 3:
            printf("\n-------------------------------------\n");
            printf("Ver Fila de Reparos\n");
            printf("-------------------------------------\n");
            exibir_fila_oficina(fila_oficina);
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
    // CORREÇÃO: Varre até o ponteiro ser NULL para não ignorar o último elemento
    while (temp != NULL) { 
        if (!strcmp(nome, temp->dado.piloto)) {
            encontrado = 1;
            break; // Para o loop no nó correto
        }
        temp = temp->prox;
    }
    
    if (encontrado) {
        printf("\n==================================\n");
        printf("              PILOTO              \n");
        printf("==================================\n");
        printf("Nome: %s\n", temp->dado.piloto);
                                     // CORREÇÃO: Mudado de 'atual' para 'temp'
        printf("Categoria: %s\n", (temp->dado.categ == 1) ? "Leve" : (temp->dado.categ == 2) ? "Médio" : "Pesado");
        printf("Status: %s\n", (temp->dado.st_pil == 0) ? "Disponível" : (temp->dado.st_pil == 1) ? "Acidentado" : "Banido");
        printf("Quantidade de Troféus: %d\n", temp->dado.cont_trofeu);
        printf("Velocidade: %d\n", temp->dado.v_kart);
        printf("Aceleração: %d\n", temp->dado.ac);
        printf("Controle: %d\n", temp->dado.ctrl);
        printf("Resistência: %d\n", temp->dado.resist);
        printf("Status do Kart: %s\n", (temp->dado.st_kart == 0) ? "Operacional" : (temp->dado.st_kart == 1) ? "Danificado" : "Destruído");
        printf("===================================\n");
    } else {
        printf("Piloto não encontrado!\n");
    }
}

void pers_banidos() {
    // APENAS ABRIR O ARQUIVO DE PERSONAGENS BANIDOS E IMPRIMIR
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

            novo->dados_corrida.status = 0; // Aguardando
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

void menu_itens_gerenciar(itens* estoque) {
    int opcao;
    do {
        menu_itens();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
        case 1: exibir_estoque(estoque);
            break;
        case 2:
            case 2:
            printf("\n===================================\n");
            printf("        ITENS EM USO NA PISTA      \n");
            printf("===================================\n");
            printf("Analisando Karts...\n");
            printf("-----------------------------------\n");
            
            // varre os pilotos exibindo o último status de itens
            if (lista_pilotos == NULL) {
                printf("Nenhum piloto na pista no momento para monitorar.\n");
            } else {
                node* temp_piloto = lista_pilotos;
                int tem_item = 0;
                while (temp_piloto != NULL) {
                    // Se o piloto já correu e ganhou performance através de itens
                    if (temp_piloto->dado.performance > 0) {
                        printf("🏎️  Piloto: %s | Modificador de Performance: +%d pts\n", 
                               temp_piloto->dado.piloto, temp_piloto->dado.performance);
                        tem_item = 1;
                    }
                    temp_piloto = temp_piloto->prox;
                }
                if (!tem_item) {
                    printf("Todos os pilotos estão com os karts limpos. Nenhum item ativo nesta rodada.\n");
                }
            }
            printf("===================================\n");
            break;//ARRUMADO 
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
    int sortear_item_com_porcentagem(itens* estoque) {
    int r = rand() % 100; // Gera um número de 0 a 99
    int item_sorteado = 2; // Padrão: Banana (mais comum)

    // definição das faixas de probabilidade baseadas na raridade:
    // Comuns (0 a 2): 60% de chance (r < 60)
    // Raros (3 e 4): 25% de chance (60 <= r < 85)
    // Épicos (5 e 6): 12% de chance (85 <= r < 97)
    // Lendários (7): 3% de chance (97 <= r < 100)
    
    if (r < 30) {
        item_sorteado = 2; // Banana (Comum)
    } else if (r < 50) {
        item_sorteado = 0; // Casco Verde (Comum)
    } else if (r < 60) {
        item_sorteado = 3; // Cogumelo (Comum)
    } else if (r < 75) {
        item_sorteado = 1; // Casco Vermelho (Raro)
    } else if (r < 85) {
        item_sorteado = 4; // Bob-omb (Raro)
    } else if (r < 92) {
        item_sorteado = 5; // Raio (Épico)
    } else if (r < 97) {
        item_sorteado = 6; // Bullet Bill (Épico)
    } else {
        item_sorteado = 7; // Casco Azul (Lendário)
    }

    // Verifica se tem no estoque global. Se não tiver, tenta dar uma Banana (por ser o mais comum).
    if (estoque->quantidade[item_sorteado] > 0) {
        estoque->quantidade[item_sorteado]--;
        return item_sorteado;
    } else if (estoque->quantidade[2] > 0) { // Backup de segurança se o item esgotar
        estoque->quantidade[2]--;
        return 2;
    }

    return -1; // Estoque completamente zerado
}

// agora ela recebe o piloto atual e calcula o bônus automaticamente
int item_dist_automatica(char* nome_piloto, itens* estoque) {
    char* nomes_itens[] = { "Casco Verde", "Casco Vermelho", "Banana", "Cogumelo", "Bob-omb", "Raio", "Bullet Bill", "Casco Azul" };
    
    int item = sortear_item_com_porcentagem(estoque);
    
    if (item != -1) {
        printf("  [?] %s pegou uma Caixa [?]: %s!\n", nome_piloto, nomes_itens[item]);
        
        // retorna o valor de poder/bônus que esse item vai somar na performance da corrida
        switch (item) {
            case 7: return 25; // Casco Azul (Destrói o líder/Dá muito bônus)
            case 6: return 20; // Bullet Bill
            case 5: return 18; // Raio
            case 4: return 15; // Bob-omb
            case 1: return 12; // Casco Vermelho
            case 3: return 10; // Cogumelo
            case 0: return 8;  // Casco Verde
            default: return 5; // Banana
        }
    }
    
        printf("  [?] %s passou por uma caixa, mas os itens do estoque global acabaram!\n", nome_piloto);
        return 0;
    }
} //ARRUMADO

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

// insere na fila respeitando a prioridade: Destruído (2) > Danificado (1)
void registrar_manutencao(node_oficina** topo_oficina, char* nome, int status) {
    node_oficina* novo = (node_oficina*)malloc(sizeof(node_oficina));
    if (!novo) {
        printf("[!] Erro de alocação de memória na oficina.\n");
        return;
    }
    strcpy(novo->piloto_nome, nome);
    novo->status_kart = status;
    novo->prox = NULL;

    // se a fila estiver vazia ou o novo tiver maior prioridade que o primeiro
    if (*topo_oficina == NULL || status > (*topo_oficina)->status_kart) {
        novo->prox = *topo_oficina;
        *topo_oficina = novo;
        printf("[✔] Kart de %s enviado para a oficina com prioridade máxima!\n", nome);
        return;
    }

    // varre a fila para encontrar a posição correta (inserção por prioridade)
    node_oficina* atual = *topo_oficina;
    while (atual->prox != NULL && atual->prox->status_kart >= status) {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
    printf("Kart de %s adicionado à fila de reparos.\n", nome);
}

// remove o primeiro da fila (maior prioridade), conserta e atualiza no grid de pilotos
void iniciar_reparo(node_oficina** topo_oficina, node* lista_pilotos) {
    if (*topo_oficina == NULL) {
        printf("\n[!] Nenhum kart aguardando manutenção na oficina.\n");
        return;
    }

    node_oficina* repara_agora = *topo_oficina;
    char nome_do_kart[50] = "Kart não identificado"; // String de segurança

    // procura o piloto na lista geral para voltar o status do kart para Operacional (0)
    node* p_atual = lista_pilotos;
    while (p_atual != NULL) {
        if (strcmp(p_atual->dado.piloto, repara_agora->piloto_nome) == 0) {
            p_atual->dado.st_kart = 0; // Volta a ser Operacional!
            strcpy(nome_do_kart, p_atual->dado.st_kart); // Puxa o nome real do modelo do Kart
            break;
        }
        p_atual = p_atual->prox;
    }

    printf("\n===================================\n");
    printf(" REPARO CONCLUÍDO PELO PROFESSOR E. GADD \n");
    printf("===================================\n");
    // agora usando o nome do piloto e o modelo do Kart recuperado com segurança:
    printf("O Kart '%s' do piloto %s foi totalmente reparado!\n", nome_do_kart, repara_agora->piloto_nome);
    printf("Situação anterior: %s\n", (repara_agora->status_kart == 2) ? " Estava Destruído" : " Estava Danificado");
    printf("Status atualizado para: OPERACIONAL! \n");
    printf("===================================\n");

    // varre a fila e libera a memória do nó da oficina
    *topo_oficina = (*topo_oficina)->prox;
    free(repara_agora);
}

// exibe quem está na fila e a gravidade do problema
void exibir_fila_oficina(node_oficina* topo_oficina) {
    if (topo_oficina == NULL) {
        printf("\n[Oficina Vazia] Todos os karts estão operacionais na pista!\n");
        return;
    }

    printf("\n===================================\n");
    printf("  FILA DE MANUTENÇÃO ATUAL \n");
    printf("===================================\n");

    node_oficina* atual = topo_oficina;
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



//Simulacao da Corrida (Módulo 1) 
void realizar_corrida(node_corrida** inicio_fila, node* lista_pilotos) {
    if (*inicio_fila == NULL) {
        printf("\n Não há corridas agendadas na fila! Agende uma corrida primeiro (Opção 1).\n");
        return;
    }
    if (lista_pilotos == NULL) {
        printf("\n Não há pilotos cadastrados para correr! Cadastre pilotos primeiro (Opção 5).\n");
        return;
    }

    double sorte;
    int rclima = rand() % 3;
    node_corrida* corrida_atual = *inicio_fila;
    corrida dados = corrida_atual->dados_corrida;

    char* nomes_pistas[] = {
        "Circuito Luigi", "Circuito Mario", "Circuito Peach", "Circuito Yoshi",
        "Circuito Donkey Kong", "Circuito Wario", "Circuito Bowser", "Circuito Rainbow Road"
    };
    char clima[] = { "Sol", "Chuva", "Neve" };

    printf("\n==================================================\n");
    printf("  A CORRIDA VAI COMEÇAR! \n");
    printf("==================================================\n");
    printf("Pista: %s\n", nomes_pistas[dados.pista]);
    printf("Voltas: %d | Dificuldade/Perigo: %d\n", dados.num_voltas, dados.dificuldade);
    printf("Clima: %s", clima[rclima]);
    printf("--------------------------------------------------\n");
    printf("3... 2... 1... VAI VAI VAI!!! \n\n");

    // simulacao da corrida com base nos atributos dos pilotos e na dificuldade da pista
    node* piloto_atual = lista_pilotos;

   printf("--- DESEMPENHO NA PISTA ---\n");
    while (piloto_atual != NULL) {
        sorte = (double)rand() / RAND_MAX;
        int performance = 0;

        if (rclima == 0) { // Sol
            performance = (piloto_atual->dado.v_kart + piloto_atual->dado.ac + piloto_atual->dado.ctrl - (int)((dados.dificuldade / (piloto_atual->dado.resist)) * sorte));
        } else if (rclima == 1) { // Chuva (usando 1.5 em vez de 1,5)
            performance = (piloto_atual->dado.v_kart + (int)(piloto_atual->dado.ac / 1.5) + (int)(piloto_atual->dado.ctrl * 1.5) - (int)((dados.dificuldade / (piloto_atual->dado.resist)) * sorte));
        } else if (rclima == 2) { // Neve (usando 3.0 em vez de 3)
            performance = (piloto_atual->dado.v_kart + (int)(piloto_atual->dado.ac / 3.0) + (int)(piloto_atual->dado.ctrl * 3.0) - (int)((dados.dificuldade / (piloto_atual->dado.resist)) * sorte));
        }

        piloto_atual->dado.performance = performance;

        printf("• %s cruzou a linha de chegada (Score de Corrida: %d)\n", piloto_atual->dado.piloto, performance);
        piloto_atual = piloto_atual->prox;
    }

    ordenar(lista_pilotos);

    printf("\n==================================================\n");
    printf(" 🏆 CLASSIFICAÇÃO OFICIAL DA CORRIDA (TABELA FMKR) 🏆\n");
    printf("==================================================\n");

    piloto_atual = lista_pilotos;
    int posicao = 1;

    while (piloto_atual != NULL) {
        int pontos_corrida = 0;

       atualizar_pontuacao_corrida(lista_pilotos, posicao, piloto_atual);

        posicao++;
        piloto_atual = piloto_atual->prox;
        

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

    printf("\n[✔] Corrida finalizada! Pontos computados no Ranking da Temporada. [✔]\n");
    printf("==================================================\n");

    // Remove a corrida executada da fila de pendentes (Central de Corridas)
    *inicio_fila = (*inicio_fila)->prox;
    free(corrida_atual);
}

//MODULO 6 - INFORMAÇÕES GERAIS

void atualizar_pontuacao_corrida(node* lista_pilotos, int posicao, node* piloto) {
    int pontos_corrida = 0;

    switch (posicao) {
        case 1: 
            pontos_corrida = 15; piloto->dado.cont_trofeu++; 
            break; // Ganha troféu no 1º lugar
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
    // Atualiza a pontuação do piloto na lista
    piloto->dado.cont_trofeu += pontos_corrida;
    // Exibe a posição e os pontos ganhos na temporada
    printf("  %dº Lugar: %s | +%d Pontos na Temporada!\n", posicao, piloto->dado.piloto, pontos_corrida);
}

// Consulta: Exibe o Top 10 ou a classificação completa ordenada
void exibir_ranking_campeonato(node* lista_pilotos) {
    if (lista_pilotos == NULL) {
        printf("\n[!] Nenhum piloto pontuou no campeonato ainda.\n");
        return;
    }

    // Garante que a lista está ordenada pelos pontos/troféus acumulados antes de exibir
    ordenar(lista_pilotos); 

    printf("\n==================================================\n");
    printf("  CLASSIFICAÇÃO OFICIAL DO CAMPEONATO \n");
    printf("==================================================\n");

    node* atual = lista_pilotos;
    int pos = 1;

    // Varre exibindo e limitando ao Top 10 se necessário, tratando empates visuais
    while (atual != NULL && pos <= 10) {
        printf(" %dº Lugar -> %s | Categoria: %s | Pontuação Histórica: %d Troféus\n",
               pos,
               atual->dado.piloto,
               (atual->dado.categ == 1) ? "Leve" : (atual->dado.categ == 2) ? "Médio" : "Pesado",
               atual->dado.cont_trofeu);
        
        // Detecção simples de empate com o próximo da lista
        if (atual->prox != NULL && atual->dado.cont_trofeu == atual->prox->dado.cont_trofeu) {
            printf("  Empate técnico momentâneo com o próximo piloto!\n");
        }
        
        pos++;
        atual = atual->prox;
    }
    printf("==================================================\n");
}

// Operação: Determina e premia o Campeão da Temporada
void determinar_campeao_temporada(node* lista_pilotos) {
    if (lista_pilotos == NULL) {
        printf("\n[!] Não há pilotos para disputar o título.\n");
        return;
    }

    ordenar(lista_pilotos); // O primeiro da lista após ordenar por troféus é o campeão

    printf("\n==============================================\n");
    printf("  O GRANDE CAMPEÃO DA TEMPORADA FOI DEFINIDO!\n");
    printf("====================================================\n");
    printf("  PARABÉNS, %s!!! \n", lista_pilotos->dado.piloto);
    printf("  Dominou as pistas com a categoria %s e acumulou %d troféus!\n",
           (lista_pilotos->dado.categ == 1) ? "Leve" : (lista_pilotos->dado.categ == 2) ? "Médio" : "Pesado",
           lista_pilotos->dado.cont_trofeu);
    printf("====================================================\n");
}
