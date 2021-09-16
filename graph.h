#include <stdio.h>
#include <stdlib.h>

typedef int type_t;

typedef struct _node_t{
    struct _node_t *next;
    type_t value;
}node_t;

typedef struct _list_t{
    node_t *head;
    int size_list;
}list_t;

node_t *new_node(type_t value);
list_t *new_list();
void free_list(list_t *l);

node_t *list_at(list_t *l, int position);
void list_set(list_t *l, int position, type_t value);
type_t list_size(list_t *l);
void print_list(list_t *l);

void list_insert(list_t *l, type_t value, int position);
void list_push_front(list_t *l, type_t value);
void list_push_back(list_t *l, type_t value);

type_t list_erase(list_t *l, int position);
type_t list_pop_front(list_t *l);
type_t list_pop_back(list_t *l);