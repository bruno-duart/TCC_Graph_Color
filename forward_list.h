#include <stdio.h>
#include <stdlib.h>

typedef struct _node_t{
    struct _node_t *next;
    int count_iter;
    int index_i;
    int undo_color;
}node_t;

typedef struct _list_t{
    node_t *head;
    int size_list;
}list_t;

node_t *new_node(int index_i, int undo_color, int T_iter);
list_t *new_list();
void free_list(list_t *l);

node_t *list_at(list_t *l, int position);
void list_set(list_t *l, int position, int index_i, int undo_color);
int list_search_by_value(list_t *l, int index_i, int undo_color);
int list_size(list_t *l);
void print_list(list_t *l);

void list_insert(list_t *l, int index_i, int undo_color, int T_iter, int position);
void list_push_front(list_t *l, int index_i, int undo_color, int T_iter);
void list_push_back(list_t *l, int index_i, int undo_color, int T_iter);

int * list_erase(list_t *l, int position);
int * list_pop_front(list_t *l);
int * list_pop_back(list_t *l);
