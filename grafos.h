#include <stdio.h>
#include <stdlib.h>

#define Type int

typedef struct {
    int V;
    int A;
    int **adj;
}Graph;

int** New_matrix(int row, int columns);
void count_edges(Graph *G);
Graph* New_Graph(int V);
void insert_arc(Graph *G, Type i, Type j, Type value);
void remove_arc(Graph *G, Type i, Type j);
void print_matrix(int **matrix, int rows, int columns);
void Graph_print(Graph *G);
void free_Graph(Graph *G);