#include "metaheuristics.h"

#define T_MAX 10000
#define CONVERGE 1000
#define EQUILIBRIO 1000
#define T_MIN 10
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

void copy_solution(solution_t *new, solution_t *old, Graph_t *graph){
    for(int i=0; i < graph->V; i++){
        new->array[i] = old->array[i];
    }
    fitness_calculation(new, graph);
}

void explore_neighborhood(solution_t *new_sol, solution_t *sol, Graph_t *graph, int num_colors){
//solution_t *explore_neighborhood(solution_t *sol, Graph_t *graph, int num_colors){
    //solution_t *new_sol = new_solution(graph->V);
    int num_index = rand() % graph->V;

    //memcpy(new_sol, sol, sizeof(solution_t*));

    copy_solution(new_sol, sol, graph);

    do{
        new_sol->array[num_index] = (rand() % num_colors) + 1;
    }while(new_sol->array[num_index] == sol->array[num_index]);

    fitness_calculation(new_sol, graph);

    //return new_sol;
}

solution_t *simulated_annealing(solution_t *sol, Graph_t *graph, int num_colors){
    solution_t *best_solution = new_solution(graph->V);
    solution_t *current = new_solution(graph->V);
    int deltaE, num_iter=0, num_pioras=0;
    double probability;
    int T = T_MAX;

    //memcpy(best_solution, sol, sizeof(solution_t));
    copy_solution(best_solution, sol, graph);

    do{
        num_pioras = 0;
        do{
            //current = explore_neighborhood(sol, graph, num_colors);
            explore_neighborhood(current, sol, graph, num_colors);
            deltaE = current->fitness_value - sol->fitness_value;

            probability = ((double) rand()) / ((double) RAND_MAX);

            if (deltaE < 0){
                copy_solution(sol, current, graph);
                num_iter=0;
                if (sol->fitness_value < best_solution->fitness_value){
                    copy_solution(best_solution, sol, graph);
                }
            } else if(probability < exp(-deltaE/T)){
                num_iter=0;
                num_pioras++;
                copy_solution(sol, current, graph);
            } else{
                num_iter++;
            }

            if (best_solution->fitness_value == 0){
                break;
            }
            //printf("->%d\n", best_solution->fitness_value);
        }while((num_iter < CONVERGE) && (num_pioras < EQUILIBRIO));
        if (best_solution->fitness_value == 0){
            break;
        }
        //printf("%d\n", T);
        T *= 0.98;
    }while(T > T_MIN);

    free_solution(current);
    return best_solution;
}

solution_t *tabu_search(solution_t *sol, Graph_t *graph, int num_colors){
    solution_t *best_solution = new_solution(graph->V);
    solution_t *current = new_solution(graph->V);


    //Here goes the code


    free_solution(current);
    return best_solution;
}