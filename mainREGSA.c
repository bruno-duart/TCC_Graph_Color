#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "metaheuristics.h"

int main(int argc, char *argv[]){
    int num_vertex, num_colors, equilibrio, converge, t_iter, num_registers;
    clock_t init_time;
    solution_t *meta_sol;
    Graph_t *graph;
    FILE *fp;
    char *instance, *output;

    
    instance = argv[1];
    equilibrio = atoi(argv[2]);
    converge = atoi(argv[3]);
    t_iter = atoi(argv[4]);
    output = argv[5];
    num_registers = atoi(argv[6]);

    fp = fopen(instance, "r");
    fscanf(fp, "%d", &num_vertex);
    fscanf(fp, "%d", &num_colors);
    graph = new_graph_from_file(fp, num_vertex);
    fclose(fp);

    init_time = clock();
    meta_sol = reduce_conflicts(graph, num_registers, equilibrio, converge, t_iter, 's'); 
    init_time = clock() - init_time;
    fp = fopen(output, "a");
    fprintf(fp ,"%d,%d,%d,%d,%.5f,%d,%d,%d\n", num_registers, meta_sol->num_conflitos, meta_sol->spilling, meta_sol->iter,  (double)init_time/(CLOCKS_PER_SEC), converge,equilibrio,t_iter);
    fclose(fp);

    free_solution(meta_sol);
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