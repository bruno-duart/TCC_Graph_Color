#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grafos.h"

typedef struct _solution_t{
    int *array;
    int fitness_value;
}solution_t;

solution_t *new_solution(int num_vertices);
void free_solution(solution_t *sol);
void fitness_calculation(solution_t *sol, Graph_t *graph);
solution_t *construct_first_solution(int num_color, Graph_t *graph);
void print_solution(solution_t *sol, int num_vertex);