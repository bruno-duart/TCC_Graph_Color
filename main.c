#include <stdio.h>
//#include "graph.h"
#include "grafos.h"

#define solution_t int*

int main(){
    //graph_t *graph = new_graph();
    /*type_t value = (type_t)3;
    vertex_t *vertex = new_vertex(value);
    for(int i=4; i < 8; i++)
        list_push_back(vertex->adj, i);
    print_vertex(vertex);
    free_vertex(vertex);
    free_graph(graph);*/
    int num_vertex;
    int **matrix;  

    solution_t array; 
    
    scanf("%d",&num_vertex);
    array = malloc(sizeof(int)*num_vertex);
    matrix = New_matrix(num_vertex, num_vertex);

    print_matrix(matrix, num_vertex, num_vertex);

    return 0;
}