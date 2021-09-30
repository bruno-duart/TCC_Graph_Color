#include <stdio.h>
#include <stdlib.h>

#define Type int

typedef struct _graph_t{
    int V;
    int A;
    int **adj;
}Graph_t;

int** New_matrix(int row, int columns);
void count_edges(Graph_t *G);
Graph_t* New_Graph(int V);
void insert_arc(Graph_t *G, Type i, Type j, Type value);
void remove_arc(Graph_t *G, Type i, Type j);
void print_matrix(int **matrix, int rows, int columns);
void Graph_print(Graph_t *G);
void free_Graph(Graph_t *G);