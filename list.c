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
  lista->current = NULL;
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
  Node *datoNuevo;
  datoNuevo = createNode(data);
  datoNuevo-> next = list->head;
  if ((list -> head) != NULL){
    list->head->prev = datoNuevo;
    list->head = list->head->prev;
    list->head->prev = NULL;
    list->current = datoNuevo;
  }else{
    list->head = datoNuevo;
    list->current = datoNuevo;
    list->tail = datoNuevo;
  }

}

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
  Node *datoNuevo;
  datoNuevo = createNode(data);
  if(list->current == NULL){
    list->head = datoNuevo;
    list->tail = datoNuevo;
  }else if(list->current == list->tail){
    list->current->next = datoNuevo;
    datoNuevo->prev = list->current; 
    list -> tail = datoNuevo;
  }else{
    datoNuevo->prev = list-> current;
    datoNuevo->next = list->current->next; 
    list->current->next->prev = datoNuevo;
    list->current->next = datoNuevo; 
  }
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
  Node *guardarUltimo = list->current;
  if(list->current == list->head){
    list->head = list->current->next;
    list->head->prev = NULL;
  }else if(list->current == list->tail){
    list->tail = list->current->prev;
    list->tail->next = NULL;
  }else{
  
    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
    
  }
  return (void*)(guardarUltimo->data);
}

void cleanList(List * list) {
  while (list->head != NULL) {
    popFront(list);
  }
}