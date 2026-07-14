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
void realizar_corrida(node_corrida** inicio_fila, node* lista_pilotos, itens* estoque, corrida* estat);
corrida* alocar_estatisticas();

// MÓDULO 2 – REGISTRO DE PILOTOS
void criar_personagem(node** inicio);
void procurar_personagem(node** inicio);
void pers_banidos();
void ordenar(node* cabeca);
void ordenar_performance(node* lista_pilotos);
void print_pilotos(node* lista_pilotos);

// MÓDULO 3 – ITENS
void menu_itens();
itens* alocar_estoque();
void inicializar_estoque(itens* estoque);
void exibir_estoque(itens* estoque);
void repor_estoque(itens* estoque);
void menu_itens_gerenciar(node* lista_pilotos, itens* estoque);
void item_dist(node* lista_pilotos, itens* estoque);

// MÓDULO 4 – HISTÓRICO (PILHA)
void exibir_historico(corrida* estat, node* lista_pilotos);

// MÓDULO 5 – OFICINA
void menu_oficina(oficina** inicio_oficina, oficina** fim_oficina, node* lista_pilotos);
void registrar_manutencao(oficina** inicio, oficina** fim, char* nome, int status);
void iniciar_reparo(oficina** inicio, oficina** fim, node* lista_pilotos);
void exibir_fila_oficina(oficina* inicio);

// MÓDULO 6 - SISTEMA E INFORMAÇÕES GERAIS
void atualizar_pontuacao_corrida(node* lista_pilotos, int posicao, node* piloto);
void exibir_ranking_campeonato(node* lista_pilotos);
void determinar_campeao_temporada(node* lista_pilotos);

// SISTEMA DE ARMAZENAMENTO
void salvar(node* lista_pilotos);
void carregar(oficina** fila_oficina_inicio, oficina** fila_oficina_fim, node** lista_pilotos);
void salvar_pistas(corrida* estatisticas_gerais);
void carregar_pistas(corrida* estatisticas_gerais);
void salvar_historico(node_historico* pilha_historico);
void carregar_historico(node_historico** pilha_historico);

// DESALOCAÇÃO DE MEMÓRIA
void liberar_pilotos(node** lista);
void liberar_corridas(node_corrida** fila);
void liberar_historico(node_historico** pilha);
void liberar_estatisticas(corrida** est);
void liberar_oficina(oficina** fila);
void liberar_estoque(itens** estoque);

#endif
