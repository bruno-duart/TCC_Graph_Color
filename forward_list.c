#include "forward_list.h"

node_t *new_node(int index_i, int undo_color, int T_iter){
    node_t *node = malloc(sizeof(node_t));
    
    node->index_i = index_i;
    node->undo_color = undo_color;
    node->count_iter = T_iter;
    node->next = NULL;
    
    return node;
}

list_t *new_list(){
    list_t *list = malloc(sizeof(list_t));

    list->head = NULL;
    list->size_list = 0;

    return list;
}

void free_list(list_t *list){
    
    while(list->head != NULL){
        node_t *aux;
        aux = list->head;
        list->head = aux->next;
        free(aux);
    }

    free(list);
}

node_t *list_at(list_t *list, int position){
    node_t *aux = list->head;

    for(int i=0; i < position && aux != NULL; i++){
        aux = aux->next;
    }
    return aux;
}

void list_set(list_t *list, int position, int index_i, int undo_color){
    node_t *node = list_at(list, position);
    node->index_i = index_i;
    node->undo_color = undo_color;
}

int list_search_by_value(list_t *list, int index_i, int undo_color){
    node_t *aux = list->head;
    int position = 0;

    while(aux != NULL){
        if((aux->index_i == index_i) && (aux->undo_color == undo_color)){
            return position;
        }
        aux = aux->next;
        position++;
    }
    return position;
}

int list_size(list_t *list){
    node_t *aux = list->head;
    int i = 0;

    while(aux != NULL){
        i++;
        aux = aux->next;
    }
    list->size_list = i;
    return (int) i;
}

void print_list(list_t *list){
    node_t *aux = list->head;
    while(aux != NULL){
        printf("(%d,%d)", aux->index_i, aux->undo_color);
        if(aux->next != NULL){
            printf("->");
        }
        aux = aux->next;
    }
    printf("\n");
}

void list_insert(list_t *l, int index_i, int undo_color, int T_iter, int position){
    node_t *node = new_node(index_i, undo_color, T_iter);

    if(position == 0){
        node->next = l->head;
        l->head = node;
    } else{
        node_t *aux = list_at(l, position-1);
        node->next = aux->next;
        aux->next = node;
    }
    l->size_list++;
}

void list_push_front(list_t *l, int index_i, int undo_color, int T_iter){
    list_insert(l, index_i, undo_color, T_iter, 0);
}

void list_push_back(list_t *l, int index_i, int undo_color, int T_iter){
    list_insert(l, index_i, undo_color, T_iter, l->size_list);
}

int * list_erase(list_t *l, int position){
    node_t *aux, *ptr;
    int value[2];
    if(position == 0){
        ptr = l->head;
        l->head = ptr->next;
        value[0] = ptr->index_i;
        value[1] = ptr->undo_color;
    } else{
        aux = list_at(l, position-1);
        ptr = aux->next;
        value[0] = ptr->index_i;
        value[1] = ptr->undo_color;
        aux->next = ptr->next;
    }
    free(ptr);
    l->size_list--;
    return value;
}

int * list_pop_front(list_t *l){
    return list_erase(l, 0);
}

int * list_pop_back(list_t *l){
    return list_erase(l, l->size_list-1);
}