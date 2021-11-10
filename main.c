#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "graph.h"
//#include "grafos.h"
#include "metaheuristics.h"

#define NUM_COLORS 50

int main(){
    int num_vertex;
    scanf("%d", &num_vertex);
    srand(time(NULL));

    solution_t *sol;// = new_solution(num_vertex);
    Graph_t *graph = New_Graph(num_vertex);

    printf("Iniciando\n\n");
    /*sol = reduce_conflicts(graph, NUM_COLORS);
    printf("---------------------------\n");
    //print_solution(sol, graph->V);
    printf("Conflitos: %d\tSpilling: %d\n", sol->num_conflitos, sol->spilling);*/
    sol = construct_first_solution(NUM_COLORS, graph);
    //print_solution(sol, num_vertex);
    printf("Número de conflitos: %d\n", sol->num_conflitos);

    printf("\n--------------------------------------------------\n\n");

    printf("Busca Tabu:\n");
    solution_t *new_sol_2 = tabu_search(sol, graph, NUM_COLORS);
    //print_solution(new_sol_2, num_vertex);
    printf("Número de conflitos: %d\n", new_sol_2->num_conflitos);
    
    /*int *array_solutions = count_conflicts(sol, graph);
    for(int i=0; i < graph->V; i++){
        printf("%d ",array_solutions[i]);
    }*/

    free_solution(sol);
    //free_solution(new_sol);
    //free_solution(new_sol_2);
    free_Graph(graph);
    //free(array_solutions);*/
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