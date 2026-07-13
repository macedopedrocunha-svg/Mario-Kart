#ifndef function_h
#define function_h

typedef struct DADOS personagem;
typedef struct NODE node;
typedef struct PISTA corrida;
typedef struct NODE_CORRIDA node_corrida;
typedef struct ITEM itens;
typedef struct NODE_HISTORICO node_historico;
typedef struct OFICINA oficina;

void print_menu();

// MÓDULO 1 - CENTRAL DE CORRIDAS
void cadastrar_corrida(node_corrida** inicio_fila);
void realizar_corrida(node_corrida** inicio_fila, node* lista_pilotos, itens* estoque, int* cont_acidentes);

// MÓDULO 2 – REGISTRO DE PILOTOS
void criar_personagem(node** inicio);
void procurar_personagem(node** inicio);
void pers_banidos();
void ordenar(node* cabeca);
void ordenar_performance(node* lista_pilotos);

// MÓDULO 3 – ITENS
void menu_itens();
void inicializar_estoque(itens* estoque);
void exibir_estoque(itens* estoque);
void repor_estoque(itens* estoque);
void menu_itens_gerenciar(node* lista_pilotos, itens* estoque);
void item_dist(node* lista_pilotos, itens* estoque);

// MÓDULO 4 – HISTÓRICO (PILHA)
void exibir_historico(node* lista_pilotos);

// MÓDULO 5 – OFICINA
void menu_oficina(oficina** fila_oficina, node* lista_pilotos);
void registrar_manutencao(oficina** topo_oficina, char* nome, int status);
void iniciar_reparo(oficina** topo_oficina, node* lista_pilotos);
void exibir_fila_oficina(oficina* topo_oficina);

// MÓDULO 6 - SISTEMA E INFORMAÇÕES GERAIS
void atualizar_pontuacao_corrida(node* lista_pilotos, int posicao, node* piloto);
void exibir_ranking_campeonato(node* lista_pilotos);
void determinar_campeao_temporada(node* lista_pilotos);

// SISTEMA DE ARMAZENAMENTO

void salvar(node* lista_pilotos);
void carregar(node** lista_pilotos, oficina** fila_oficina);
void salvar_historico(node_historico* pilha_historico);
void carregar_historico(node_historico** pilha_historico);

#endif
