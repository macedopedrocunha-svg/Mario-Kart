#ifndef function_h
#define function_h

typedef struct DADOS personagem;
typedef struct NODE node;
typedef struct ITEM itens;
typedef struct PISTA corrida;

typedef struct NODE_CORRIDA {
    corrida dados_corrida;
    struct NODE_CORRIDA* prox; 
}node_corrida;

void print_menu();

// MÓDULO 1 - CORRIDA
void cadastrar_corrida(node_corrida** inicio);
corrida iniciar_corrida(node_corrida** inicio_fila, int*sucesso);
void visualizar_corridas(node_corrida* inicio);

//MÓDULO 2 – REGISTRO DE PILOTOS
void criar_personagem(node** inicio);
void procurar_personagem(node* inicio);
void listar_personagens_banidos(node* inicio);

//MÓDULO 3 – ITENS
void menu_itens();
void item_dist();

//MÓDULO 4 – HISTÓRICO
void ordenar(node* cabeca);
void menu_ranking();
void historico();

//MÓDULO 5 – OFICINA
void menu_oficina();

//MÓDULO 6 – CAMPEONATO E PONTUAÇÃO

#endif