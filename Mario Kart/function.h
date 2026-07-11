#ifndef function_h
#define function_h

// ==========================================
// ESTIDADE 1: PILOTO & KART (Lista Encadeada)
// ==========================================
typedef struct DADOS {
    char piloto[30];
    int categ;          // 1-Leve, 2-Médio, 3-Pesado
    int cont_trofeu;    // Pontuação acumulada no campeonato
    int st_pil;         // 0-Ativo, 1-Suspenso
    int v_kart, ac, ctrl, resist; // Atributos do Kart
    int st_kart;        // 0-Operacional, 1-Danificado, 2-Destruído
} personagem;

typedef struct NODE {
    personagem dado;
    struct NODE* prox;
} node;

// ==========================================
// ENTIDADE 2: CENTRAL DE CORRIDAS (Fila FIFO)
// ==========================================
typedef struct PISTA {
    int pista;         // ID da pista (0 a 7)
    int num_voltas;
    int dificuldade;   // Nível de Perigo (1 a 100)
    int status;        // 0-Aguardando, 1-Em andamento, 2-Finalizada
} corrida;

typedef struct NODE_CORRIDA {
    corrida dados_corrida;
    struct NODE_CORRIDA* prox; 
} node_corrida;

// ==========================================
// ENTIDADE 3: ARSENAL DE ITENS (Estrutura Global)
// ==========================================
typedef struct ITEM {
    int quantidade[8]; // Estoque das 8 variedades de itens
} itens;

// ==========================================
// ENTIDADE 4: HISTÓRICO (Pilha LIFO - Nova!)
// ==========================================
typedef struct NODE_HISTORICO {
    char pista_nome[50];
    char vencedor_nome[30];
    int total_pilotos;
    struct NODE_HISTORICO* topo; // Aponta para a corrida anterior na pilha
} node_historico;

// ==========================================
// ENTIDADE 5: OFICINA (Fila de Prioridade)
// ==========================================
typedef struct NODE_OFICINA {
    char piloto_nome[30];
    int status_kart; // 1-Danificado, 2-Destruído
    struct NODE_OFICINA* prox;
} node_oficina;

// ==========================================
//                  MODULOS
// ==========================================
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
