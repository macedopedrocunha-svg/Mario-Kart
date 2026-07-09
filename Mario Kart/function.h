#ifndef function_h
#define function_h

// 1. Definição das Estruturas de Dados Reais
typedef struct DADOS {
    char piloto[30];
    int categ, cont_trofeu, st_pil;
    int v_kart, ac, ctrl, resist, st_kart;
} personagem;

typedef struct NODE {
    personagem dado;
    struct NODE* prox;
} node;

typedef struct ITEM {
    int tipo; 
    int raridade; 
    int poder;
    int quantidade[8];
} itens;

typedef struct PISTA {
    int pista; 
    int num_voltas;
    int dificuldade; 
    int status; 
    int prioridade;
} corrida;

typedef struct NODE_CORRIDA {
    corrida dados_corrida;
    struct NODE_CORRIDA* prox; 
} node_corrida;

void print_menu();

// MÓDULO 1 - CORRIDA
void cadastrar_corrida(node_corrida** inicio_fila);

// MÓDULO 2 – REGISTRO DE PILOTOS
void criar_personagem(node** inicio);
void procurar_personagem(node* inicio);
void listar_personagens_banidos(node* inicio);

// MÓDULO 3 – ITENS
void menu_itens();
void inicializar_estoque(itens* estoque);
void exibir_estoque(itens* estoque);
void repor_estoque(itens* estoque);
void menu_itens_gerenciar(itens* estoque);
void item_dist(node* lista_pilotos, itens* estoque); 

// MÓDULO 4 – HISTÓRICO
void ordenar(node* cabeca);
void menu_ranking();

// MÓDULO 5 – OFICINA
void menu_oficina();
void oficina();

#endif
