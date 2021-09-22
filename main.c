#include <stdio.h>
//#include "graph.h"
#include "grafos.h"

#define solution_t int*

char is_solution(solution_t array, int** matrix, int num_vertex);

int main(){
    //graph_t *graph = new_graph();
    /*type_t value = (type_t)3;
    vertex_t *vertex = new_vertex(value);
    for(int i=4; i < 8; i++)
        list_push_back(vertex->adj, i);
    print_vertex(vertex);
    free_vertex(vertex);
    free_graph(graph);*/
    int num_vertex, num_colors = 3;
    int **matrix;  

    solution_t array; 
    
    scanf("%d",&num_vertex);
    array = malloc(sizeof(int)*num_vertex);
    matrix = New_matrix(num_vertex, num_vertex);

    print_matrix(matrix, num_vertex, num_vertex);
    array[0] = 1;
    array[1] = 2;
    array[2] = 1;
    array[3] = 3;
    array[4] = 2;
    
    printf("\n");
    for(int i=0; i < 5; i++)
        printf("%4d ", array[i]);
    printf("\n");

    printf("Is it a solution? %s\n", is_solution(array, matrix, num_vertex) == '1' ? "Yes" : "No");

    return 0;
}

char is_solution(solution_t array, int** matrix, int num_vertex){
    for(int i=0; i < num_vertex; i++){
        for(int j=i; j < num_vertex; j++){
            if(array[i] == array[j] && matrix[i][j] != 0){
                return '0';
            }
        }
    }
    return '1';
}