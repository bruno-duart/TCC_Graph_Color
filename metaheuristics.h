#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "grafos.h"
#include "forward_list.h"

typedef struct _solution_t{
    int *array;
    int fitness_value;
}solution_t;

solution_t *new_solution(int num_vertices);
void free_solution(solution_t *sol);
void fitness_calculation(solution_t *sol, Graph_t *graph);
solution_t *construct_first_solution(int num_color, Graph_t *graph);
void print_solution(solution_t *sol, int num_vertex);
void copy_solution(solution_t *new, solution_t *old, Graph_t *graph);
void explore_neighborhood(solution_t *new_sol, solution_t *sol, Graph_t *graph, int num_colors);
//solution_t *explore_neighborhood(solution_t *sol, Graph_t *graph, int num_colors);
solution_t *simulated_annealing(solution_t *sol, Graph_t *graph, int num_colors);
void insert_tabu_move(list_t *list, int undo_color, int index);
int is_tabu_move(list_t *list, int undo_color, int index);
void decrease_iterations(list_t *list);
solution_t *tabu_search(solution_t *sol, Graph_t *graph, int num_colors);