#include "metaheuristics.h"

#define T_MAX 10000
#define CONVERGE 1000
#define EQUILIBRIO 5000
#define T_MIN 10
#define T_ITER 50

solution_t *new_solution(int num_vertices){
    /**
     * Função para inicializar uma nova solução. 
     * @param num_vertices : número de vértices contidos em uma solução
     * @return solution_t : uma nova solução
    */
    solution_t *sol = malloc(sizeof(solution_t));
    sol->array = malloc(sizeof(int)*num_vertices);
    sol->num_conflitos = 0;
    sol->spilling = 0;

    return sol;
}

void free_solution(solution_t *sol){
    /**
     * Função para liberar a memória alocada de uma solução.
     * É liberada a memória do array de vértices e em seguida
     * a memória da estrutura solution_t
     * @param sol : solução a ter sua memória liberada
    */
    free(sol->array);
    free(sol);
}

void fitness_calculation(solution_t *sol, Graph_t *graph){
    /**
     * Função para calcular a fitness de cada solução. Comparam-se as cores
     * de cada vértice com as cores de seus adjacentes. A matriz é percorrida
     * linha a linha, e conta o número de conflitos.
     * @param sol : solução a ter sua fitness calculada
     * @param graph : grafo que contém a matriz de adjacências
     * 
    */
    sol->num_conflitos = 0;
    for(int i=0; i < graph->V; i++){
        if(graph->adj[i][i] != -1){
            for(int j=i+1; j < graph->V; j++){
                if(sol->array[i] == sol->array[j] && graph->adj[i][j] != 0){
                    sol->num_conflitos++;
                }
            }
        }
    }
    for(int i=0; i < graph->V; i++){
        if(sol->array[i] == -1){
            sol->spilling++;
        }
    }
}

solution_t *construct_first_solution(int num_color, Graph_t *graph){
    /**
     * Função para construir uma solução inicial. As cores de cada
     * vértice são escolhidas aleatoriamente. Após o término dos 
     * sorteios, a fitness é calculada.
     * @param num_color : número de cores disponíveis para seleção
     * @param graph : grafo a partir do qual a solução é criada
     * @return solution_t : uma nova solução
    */
    solution_t* sol = new_solution(graph->V);

    for(int i=0; i<graph->V; i++){
        if(graph->adj[i][i] == -1){
            sol->array[i] = -1;
        } else{
            sol->array[i] = (rand() % num_color) + 1;
        }
    }

    fitness_calculation(sol, graph);

    return sol;
}

void print_solution(solution_t *sol, int num_vertex){
    /**
     * Função para exibir o array de cores de uma solução.
     * @param sol: solução a ser exibida
     * @param num_vertex: número de vértices a ser exibido
    */
    for(int i=0; i<num_vertex; i++){
        printf("%4d ",sol->array[i]);
    }
    printf("\n");
}

void copy_solution(solution_t *new, solution_t *old, Graph_t *graph){
    /**
     * Função para copiar as cores e a fitness de uma solução 
     * para outra. 
     * @param new : solução que vai receber a cópia
     * @param old : solução que vai ser copiada
     * @param graph : grafo que contém os vértices
    */
    for(int i=0; i < graph->V; i++){
        new->array[i] = old->array[i];
    }
    new->num_conflitos = old->num_conflitos;
}

void explore_neighborhood(solution_t *new_sol, solution_t *sol, Graph_t *graph, int num_colors){
    /**
     * Função para realizar uma exploração na vizinhança.
     * Uma nova solução é obtida ao variar a cor de um unico vértice.
     * @param new_sol : endereço de memória para a nova solução
     * @param sol: solução a ter a vizinhança explorada
     * @param graph: grafo de adjacências 
     * @param num_colors: número de cores disponíveis
    */
    int num_index;
    do{
        num_index = rand() % graph->V;
    }while(graph->adj[num_index][num_index] == -1);

    copy_solution(new_sol, sol, graph);

    do{
        new_sol->array[num_index] = (rand() % num_colors) + 1;
    }while(new_sol->array[num_index] == sol->array[num_index]);

    fitness_calculation(new_sol, graph);
}

solution_t *simulated_annealing(solution_t *sol, Graph_t *graph, int num_colors){
    /**
     * Meta-heurística Simulated Annealing. Realiza a busca por
     * uma solução de melhor qualidade.
     * @param sol: solução inicial
     * @param graph: grafo de adjacência
     * @param num_colors: número de cores disponível
     * @return best_solution: melhor solução encontrada
    */
    solution_t *best_solution = new_solution(graph->V);
    solution_t *current = new_solution(graph->V);
    int deltaE, num_iter=0, num_pioras=0;
    double probability;
    int T = T_MAX;

    copy_solution(best_solution, sol, graph); // Copia a solução inicial para a melhor encontrada

    do{
        num_pioras = 0;
        do{
            explore_neighborhood(current, sol, graph, num_colors); // explora a vizinhança
            deltaE = current->num_conflitos - sol->num_conflitos; // Calcula a variação de energia das soluções

            probability = ((double) rand()) / ((double) RAND_MAX);

            if (deltaE < 0){ // Caso a nova solução gerada seja melhor que a corrente
                copy_solution(sol, current, graph);
                num_iter=0;
                if (sol->num_conflitos < best_solution->num_conflitos){ // Se for melhor que a melhor corrente
                    copy_solution(best_solution, sol, graph);
                }
            } else if(probability < exp(-deltaE/T)){ // Solução gerada é pior, mas é aceita por probabilidade
                num_iter=0;
                num_pioras++;
                copy_solution(sol, current, graph);
            } else{ // Solução não aceita
                num_iter++;
            }

            if (best_solution->num_conflitos == 0){ // Se tiver atingido zero conflitos
                break;
            }
            
        }while((num_iter < CONVERGE) && (num_pioras < EQUILIBRIO)); // Até que uma condição de equilíbrio seja satisfeita
        if (best_solution->num_conflitos == 0){
            break;
        }
        
        T *= 0.9;
    }while(T > T_MIN); // Enquanto a temperatura atual for maior que a mínima

    free_solution(current);
    fitness_calculation(best_solution, graph);
    return best_solution;
}

void insert_tabu_move(list_t *list, int undo_color, int index){
    /**
     * Insere um movimento tabu no final da lista
     * @param list: lista a ter um elemento inserido
     * @param undo_color: cor que desfaz o movimento
     * @param index: vértice que desfaz o movimento
    */
    list_push_back(list, index, undo_color, T_ITER);
}

int is_tabu_move(list_t *list, int undo_color, int index){
    /**
     * Verifica se o movimento é tabu, ou seja, se está na lista
     * @param list: lista ser verificada
     * @param undo_color: cor que desfaz o movimento
     * @param index: vértice correspondente
    */
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
    /**
     * Decrementa o número de iterações de restrição
     * dos movimentos da lista. Se o número atinge zero, 
     * o elemento é removido. Remove-se sempre o primeiro 
     * elemento da lista, pois novos elementos são sempre adicionados
     * ao final.
     * @param list: lista a ser análisada
    */
    node_t *node = list->head;
    while(node != NULL){
        node->count_iter--;
        if(!node->count_iter){
            node = node->next;
            list_pop_front(list);
            continue;
        }
        node = node->next;
    }
}

solution_t *tabu_search(solution_t *sol, Graph_t *graph, int num_colors){
    /**
     * Meta-heurística Busca Tabu. Realiza a busca por
     * uma solução de melhor qualidade.
     * @param sol: solução inicial
     * @param graph: grafo de adjacência
     * @param num_colors: número de cores disponível
     * @return best_solution: melhor solução encontrada
    */
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
    while(best_solution->num_conflitos > 0 && num_iter < EQUILIBRIO){
        // Gerar um determinado número de soluções, e pega a melhor
        int menor = 0, index, undo_color;
        for(int i=0; i<num_sol_geradas; i++){
            explore_neighborhood(arr_solutions[i], current, graph, num_colors);

            if(arr_solutions[i]->num_conflitos < arr_solutions[menor]->num_conflitos){
                menor = i;
            }
        }

        for(int i=0; i < graph->V; i++){ // Verifica qual o movimento inverso, e qual vértice é alterado
            if(arr_solutions[menor]->array[i] != current->array[i]){
                undo_color = current->array[i];
                index = i;
                break;
            }
        }

        int is_tabu = is_tabu_move(tabu_list, undo_color, index); // Verifica se é movimento tabu
        if(is_tabu == 0){ //Se não for movimento tabu, aceita a solução e insere o movimento inverso na lista tabu
            copy_solution(current, arr_solutions[menor], graph);
            insert_tabu_move(tabu_list, undo_color, index);
        } else if(arr_solutions[menor]->num_conflitos < (current->num_conflitos-1)){ // Se for tabu, mas o ganho for considerável
            list_erase(tabu_list, is_tabu); // Remove o movimento da lista tabu
            copy_solution(current, arr_solutions[menor], graph); // Aceita a solução
        }
        // Decrementar as iterações
        decrease_iterations(tabu_list);

        // Atualizar a melhor solução encontrada
        if(current->num_conflitos < best_solution->num_conflitos){
            copy_solution(best_solution, current, graph);
            num_iter = 0;
        }else {
            num_iter++;
        }
    }

    // Libera a memória alocada
    free_list(tabu_list);

    for(int i=0; i < num_sol_geradas; i++)
        free_solution(arr_solutions[i]);

    free_solution(current);
    fitness_calculation(best_solution, graph);
    return best_solution;
}

int *count_conflicts(solution_t *sol, Graph_t *graph){
    int *array_conflicts = malloc(sizeof(int)*graph->V);

    for(int i=0; i<graph->V; i++){
        array_conflicts[i] = 0;
    }

    for(int i=0; i<graph->V; i++){
        if(graph->adj[i][i] != -1){
            for(int j=0; j<graph->V; j++){
                if((graph->adj[i][j] != 0) && (sol->array[i] == sol->array[j])){
                    array_conflicts[i]++;
                }
            }
        }
    }
    return array_conflicts;
}

int find_max_conflicts(int *arr, int arr_size){
    int max = 0;
    for(int i=1; i < arr_size; i++){
        if(arr[i] > arr[max]){
            max = i;
        }
    }
    return max;
}

void remove_vertex(Graph_t *graph, solution_t *sol){
    int *arr_conflicts = count_conflicts(sol, graph);
    int num_vertex = find_max_conflicts(arr_conflicts, graph->V);

    graph->adj[num_vertex][num_vertex] = -1;

    free(arr_conflicts);
}

solution_t *reduce_conflicts(Graph_t *graph, int num_color){
    solution_t *initial_solution, *best_current_solution;//, *best_global_solution;
    int num_iter = 0;

    do{
        initial_solution = construct_first_solution(num_color, graph);
        //best_current_solution = simulated_annealing(initial_solution, graph, num_color);
        best_current_solution = tabu_search(initial_solution, graph, num_color);

        if ((best_current_solution->num_conflitos == 0) || (num_iter > graph->V)){
            break;
        }
        //print_solution(best_current_solution, graph->V);
        printf("Conflitos: %d\tSpilling: %d\n", best_current_solution->num_conflitos, best_current_solution->spilling);
        remove_vertex(graph, best_current_solution);
        free_solution(initial_solution);
        free_solution(best_current_solution);
        num_iter++;
    }while(1);
    free_solution(initial_solution);
    return best_current_solution;
}