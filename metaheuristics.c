#include "metaheuristics.h"
//#include "grafos.h"

solution_t *new_solution(int num_vertices){
    solution_t *sol = malloc(sizeof(solution_t));
    sol->array = malloc(sizeof(int)*num_vertices);
    sol->fitness_value = 0;

    return sol;
}

void free_solution(solution_t *sol){
    free(sol->array);
    free(sol);
}

void fitness_calculation(solution_t *sol, Graph_t *graph){
    sol->fitness_value = 0;
    for(int i=0; i < graph->V; i++){
        for(int j=i+1; j < graph->V; j++){
            if(sol->array[i] == sol->array[j] && graph->adj[i][j] != 0){
                sol->fitness_value++;
            }
        }
    }
}

solution_t *construct_first_solution(int num_color, Graph_t *graph){
    solution_t* sol = new_solution(graph->V);

    for(int i=0; i<graph->V; i++)
        sol->array[i] = (rand() % num_color) + 1;

    fitness_calculation(sol, graph);

    return sol;
}

void print_solution(solution_t *sol, int num_vertex){
    for(int i=0; i<num_vertex; i++){
        printf("%4d ",sol->array[i]);
    }
    printf("\n");
}