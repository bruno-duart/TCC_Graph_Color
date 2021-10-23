#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "graph.h"
//#include "grafos.h"
#include "metaheuristics.h"

#define NUM_COLORS 5

int main(){
    int num_vertex;
    scanf("%d", &num_vertex);
    srand(time(NULL));

    solution_t *sol;// = new_solution(num_vertex);
    Graph_t *graph = New_Graph(num_vertex);
    //int **matrix = New_matrix(num_vertex, num_vertex);

    /*sol->array[0] = 1;
    sol->array[1] = 2;
    sol->array[2] = 2;
    sol->array[3] = 3;
    sol->array[4] = 2;*/

    sol = construct_first_solution(NUM_COLORS, graph);
    fitness_calculation(sol, graph);
    print_solution(sol, num_vertex);
    printf("Número de conflitos: %d\n", sol->fitness_value);

    //solution_t *new_sol = explore_neighborhood(sol, graph, 3);

    solution_t *new_sol = simulated_annealing(sol, graph, NUM_COLORS);
    print_solution(new_sol, num_vertex);
    printf("Número de conflitos: %d\n", new_sol->fitness_value);

    free_solution(sol);
    free_solution(new_sol);
    free_Graph(graph);
    return 0;
}

/*char is_solution(solution_t array, int** matrix, int num_vertex){
    for(int i=0; i < num_vertex; i++){
        for(int j=i; j < num_vertex; j++){
            if(array[i] == array[j] && matrix[i][j] != 0){
                return '0';
            }
        }
    }
    return '1';
}*/