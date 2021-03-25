#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *lista = (List*)malloc(sizeof(List));
  lista -> head = NULL;
  lista -> tail = NULL;
  return lista;
}

void * firstList(List * list) {
  if ((list -> head) == NULL) return NULL;
  list->current = list->head;
  return (void*) (list -> head -> data);
}

void * nextList(List * list) {
  if ((list -> current) == NULL) return NULL;
  if((list->current->next) == NULL) return NULL ;
  list->current = list->current->next;
  return (void*)(list->current->data);
}

void * lastList(List * list) {
  //if ((list -> head) == NULL) return NULL;
  if ((list -> tail) == NULL) return NULL;
  list->current = list->tail;
  return (void*) (list -> tail -> data);
}

void * prevList(List * list) {
  if ((list -> current) == NULL) return NULL;
  if((list->current->prev) == NULL) return NULL ;
  list->current = list->current->prev;
  return (void*)(list->current->data);
}

void pushFront(List * list, const void * data) {
  if ((list -> head) != NULL){
    Node *datoNuevo;
    datoNuevo = createNode(data);
    list->head->prev = datoNuevo;
    list->head = datoNuevo;
    datoNuevo->prev = NULL;
  };

}

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}