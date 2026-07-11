#ifndef function_h
#define function_h

typedef struct DADOS personagem;
typedef struct NODE node;
typedef struct corrida;
typedef struct NODE_CORRIDA node_corrida;
typedef struct ITEM itens;
typedef struct NODE_HISTORICO node_historico;
typedef struct NODE_OFICINA node_oficina;

void print_menu();

// MÓDULO 1 - CENTRAL DE CORRIDAS
void cadastrar_corrida(node_corrida** inicio, node_corrida** fim);
void realizar_corrida(node_corrida** inicio, node_corrida** fim, node* lista_pilotos, node_historico** pilha_historico);

// MÓDULO 2 – REGISTRO DE PILOTOS
void criar_personagem(node** inicio);
void procurar_personagem(node* inicio);
void listar_personagens_banidos(node* inicio);
void ordenar(node* cabeca);

// MÓDULO 3 – ITENS
void menu_itens();
void inicializar_estoque(itens* estoque);
void exibir_estoque(itens* estoque);
void repor_estoque(itens* estoque);
void menu_itens_gerenciar(itens* estoque);
void item_dist(node* lista_pilotos, itens* estoque);

// MÓDULO 4 – HISTÓRICO (PILHA)
void empilhar_historico(node_historico** topo, char* pista, char* vencedor, int qtd_pilotos);
void exibir_historico(node_historico* topo);

// MÓDULO 5 – OFICINA
void oficina(node_oficina** fila_oficina, node* lista_pilotos);
void registrar_manutencao(node_oficina** topo_oficina, char* nome, int status);
void iniciar_reparo(node_oficina** topo_oficina, node* lista_pilotos);
void exibir_fila_oficina(node_oficina* topo_oficina);

#endif
