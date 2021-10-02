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

solution_t *explore_neighborhood(solution_t *sol, Graph_t *graph, int num_vertex, int num_colors){
    solution_t *new_sol = new_solution(num_vertex);
    int num_index = rand() % num_vertex;

    memcpy(new_sol->array, sol->array, sizeof(int)*num_vertex);
    do{
        new_sol->array[num_index] = (rand() % num_colors) + 1;
    }while(new_sol->array[num_index] == sol->array[num_index]);

    fitness_calculation(new_sol, graph);

    return new_sol;
}

solution_t *simulated_annealing(solution_t *sol, Graph_t *graph, int num_colors){
    solution_t *best_solution = new_solution(graph->V);
    solution_t *current = new_solution(graph->V);

    memcpy(best_solution, sol, sizeof(solution_t));
    memcpy(current, sol, sizeof(solution_t));
    
    return best_solution;
}