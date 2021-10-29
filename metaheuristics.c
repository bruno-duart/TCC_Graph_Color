#include "metaheuristics.h"

#define T_MAX 10000
#define CONVERGE 1000
#define EQUILIBRIO 1000
#define T_MIN 10
#define MAX_TABU_SIZE 100
#define T_ITER 10
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

void insert_tabu_move(list_t *list, int undo_color, int index){
    list_push_back(list, index, undo_color, T_ITER);
}

int is_tabu_move(list_t *list, int undo_color, int index){
    node_t *node = list->head;
    int position = 0;

    while(node != NULL){
        if((node->index_i == index) && (node->undo_color == undo_color)){
            return position;
        }
        node = node->next;
        position++;
    }

    return 0;
}

void decrease_iterations(list_t *list){
    node_t *node = list->head;
    while(node != NULL){
        node->count_iter--;
        if(!node->count_iter){
            int position = list_search_by_value(list, node->index_i, node->undo_color);
            node = node->next;
            list_erase(list, position);
            continue;
        }
        node = node->next;
    }
}

solution_t *tabu_search(solution_t *sol, Graph_t *graph, int num_colors){
    solution_t *best_solution = new_solution(graph->V);
    solution_t *current = new_solution(graph->V);
    copy_solution(best_solution, sol, graph);
    copy_solution(current, sol, graph);

    int num_iter = 0, num_sol_geradas = (graph->V > 100) ? (graph->V*0.1) : 5;
    solution_t *arr_solutions[num_sol_geradas];

    for(int i=0; i < num_sol_geradas; i++)
        arr_solutions[i] = new_solution(graph->V);

    list_t *tabu_list = new_list();


    //Here goes the code
    while(num_iter < 100){//(best_solution->fitness_value > 0 && num_iter < EQUILIBRIO){
        //gerar um determinado número de soluções, e pegar a melhor
        int menor = 0, index, undo_color;
        for(int i=0; i<num_sol_geradas; i++){
            //copy_solution(arr_solutions[i], current, graph);
            explore_neighborhood(arr_solutions[i], current, graph, num_colors);

            if(arr_solutions[i]->fitness_value < arr_solutions[menor]->fitness_value){
                menor = i;
            }
        }

        for(int i=0; i < graph->V; i++){
            if(arr_solutions[menor]->array[i] != current->array[i]){
                undo_color = current->array[i];
                index = i;
                break;
            }
        }

        int is_tabu = is_tabu_move(tabu_list, undo_color, index);
        if(is_tabu == 0){
            copy_solution(current, arr_solutions[menor], graph);
            //print_solution(arr_solutions[menor], graph->V);
            //printf("Número de conflitos: %d\n", arr_solutions[menor]->fitness_value); //adicionar a inserção na lista
            insert_tabu_move(tabu_list, undo_color, index);
        } else if(arr_solutions[menor]->fitness_value < (current->fitness_value-1)){
            list_erase(tabu_list, is_tabu);
            copy_solution(current, arr_solutions[menor], graph);
        }
        // falta a parte de decrementar as iterações
        decrease_iterations(tabu_list);
        if(current->fitness_value < best_solution->fitness_value){
            copy_solution(best_solution, current, graph);
            num_iter = 0;
        }else {
            num_iter++;
        }
    }

    free_list(tabu_list);

    for(int i=0; i < num_sol_geradas; i++)
        free_solution(arr_solutions[i]);

    free_solution(current);
    return best_solution;
}