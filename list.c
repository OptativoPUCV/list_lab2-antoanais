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
/*  
  Es retornado el dato del primer nodo en la lista
*/
  return (void*) (list->head->data);
}

void * nextList(List * list) {
  if ((list -> current) == NULL) return NULL;
  if((list->current->next) == NULL) return NULL ;
/*
  El nuevo current es el dato siguiente al current
  anterior 
*/
  list->current = list->current->next;
  return (void*)(list->current->data);
}

void * lastList(List * list) {

  if ((list -> tail) == NULL) return NULL;
  list->current = list->tail;
  /*Retornamos el último dato de la lista*/
  return (void*) (list -> tail -> data);
}

void * prevList(List * list) {
  if ((list -> current) == NULL) return NULL;
  if ((list->current->prev) == NULL) return NULL;
/*
  El nuevo current es el dato previo al current
  anterior
*/
  list->current = list->current->prev;
  return (void*)(list->current->data);
}

void pushFront(List * list, const void * data) {
  Node *datoNuevo;
  datoNuevo = createNode(data);
/*
  Al dato siguiente del nuevo nodo, le damos el valor del primer elemento de la lista
*/
  datoNuevo-> next = list->head;
  if ((list -> head) != NULL){
/*
  Al dato anterior al primero le damos el valor del nuevo dato, y al primero de la lista le asignamos el nuevo dato para luego decir que el anterior a este será nulo
*/
    list->head->prev = datoNuevo;
    list->head = list->head->prev;
    list->head->prev = NULL;
    list->current = datoNuevo;
  }else{
/*
  Si el primer dato de la lista no existe, se le asigna al primer nodo y al último el dato nuevo
*/
    list->head = datoNuevo;
    list->current = datoNuevo;
    list->tail = datoNuevo;
  }

}

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data){
  Node *datoNuevo;
  datoNuevo = createNode(data);
  if(list->current == NULL){
/* 
  Si el current no existe, se le asigna al primer nodo y al último el nuevo dato, así mismo al current
*/
    list->head = datoNuevo;
    list->current = datoNuevo;
    list->tail = datoNuevo;

/*
  En caso de que el current sea el último dato de la lista, le asignamos el nuevo dato al siguiente del current, para dejarlo como el último dato
*/
  }else if(list->current == list->tail){
    list->current->next = datoNuevo;
    datoNuevo->prev = list->current; 
    list -> tail = datoNuevo;
/*
  Si el current está en cualquier otro lado de la lista, se inserta el dato nuevo entre el current y el siguiente de este
*/
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
  Node *guardarCurrent = list->current;
/*
  Se crea un puntero a void para guardar el dato que se encuentra en el current, para luego poder liberar la memoria del nodo
*/
  void *paraRetornar = (void*) guardarCurrent->data;
/* 
  En caso de que el current sea el primer elemento de la lista, le asignaremos al primer nodo el nodo siguiente del current
*/
  if(list->current == list->head){
    list->head = list->current->next;
    list->head->prev = NULL;
/*
  En caso de que el current sea el último elemento de la lista, le asignaremos al último nodo el nodo previo del current
*/
  }else if(list->current == list->tail){
    list->tail = list->current->prev;
    list->tail->next = NULL;
/*
  En caso de que el current esté en cualquier otro lugar de la lista, entre dos nodos, se realiza el proceso para que los nodos de los extremos del current se apunten entre ellos
*/ 
  }else{
  
    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
    
  }
  free(guardarCurrent);
  return paraRetornar;
}

void cleanList(List * list) {
  while (list->head != NULL) {
    popFront(list);
  }
}