#include "grafos.h"

int** New_matrix(int row, int columns){
    /**
     * Função para criação de nova matriz.
     * @param row : número de linhas
     * @param columns : número de colunas
     * Retorna um ponteiro para uma matriz de 
     * inteiros alocada dinamicamente.
     * 
    */
    int val;
    int **m = malloc(sizeof(int*) * row);
    for(Type i = 0; i < row; i++)
        m[i] = malloc(sizeof(int) * columns);
    for(Type i = 0; i < row; i++)
        for(Type j = 0; j < columns; j++){
            scanf("%d", &val);
            m[i][j] = val;
        }
    return m;
}

void count_edges(Graph_t *G){
    /**
     * Função para contar o número de arestas
     * no grafo. Considerando que o grafo é
     * não direcionado, uma aresta entre o
     * vértice 'a' e 'b' é equivalente a 
     * aresta entre os vértices 'b' e 'a', 
     * sendo contabilizadas apenas uma vez.
     * @param G: grafo a ter o número de
     * arestas contabilizado.
    */
    for(int i=0; i < G->V; i++){
        for(int j=i; j < G->V; j++){
            if(G->adj[i][j]){
                G->A++;
            }
        }
    }
}

Graph_t* New_Graph(int V){
    /**
     * Função para criação de novos grafos na 
     * forma de matriz de adjacências. 
     * @param V : número de vértices do Grafo.
     * Retorna o novo grafo criado.
    */
    Graph_t *G = malloc(sizeof(Graph_t));
    G->V = V;
    G->A = 0;
    G->adj = New_matrix(V, V);
    count_edges(G);
    return G;
}

void insert_arc(Graph_t *G, Type i, Type j, Type value){
    /**
     * Função para inserir uma nova aresta 
     * no grafo. 
     * @param G: o grafo a ter uma nova aresta inserida.
     * @param i: o índice do primeiro vértice.
     * @param j: o índice do segundo vértice.
     * @param value: valor (peso) da aresta.
    */
    if (G->adj[i][j] == 0){
        G->adj[i][j] = value;
        G->A++;
    }
}

void remove_arc(Graph_t *G, Type i, Type j){
    /**
     * Função para remover uma aresta do grafo. 
     * @param G: o grafo a ter uma nova aresta inserida.
     * @param i: o índice do primeiro vértice.
     * @param j: o índice do segundo vértice.
    */
    if(G->adj[i][j] != 0){
        G->adj[i][j] = 0;
        G->A--;
    }
}

void print_matrix(int **matrix, int rows, int columns){
    /**
     * Função para printar uma matriz de inteiros genérica.
     * @param matrix: ponteiro para a matriz de inteiros.
     * @param rows: número de linhas da matriz.
     * @param columns: número de colunas da matriz.
    */
    for(int i=0; i < rows; i++){
        for(int j=0; j < columns; j++)
            printf("%4d ", matrix[i][j]);
        printf("\n");
    }
}

void Graph_print(Graph_t *G){
    /**
     * Função para printar a matriz de adjacências de um
     * grafo.
     * @param G: o grafo a ser printado.
    */
    for(int i=0; i < G->V; i++){
        for(int j=0; j < G->V; j++)
            printf("%4d ", G->adj[i][j]);
        printf("\n");
    }
}

void free_Graph(Graph_t *G){
    /**
     * Função para liberar a memória alocada para o grafo.
     * @param G: o grafo a ter memória liberada.
    */
    for(int i=0; i < G->V; i++)
        free(G->adj[i]);
    free(G->adj);
    free(G);
}