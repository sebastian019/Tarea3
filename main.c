#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#define BARRA "-------------------------------------------------------"

typedef struct _tarea Tarea;
typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

typedef struct NodoT {
  Tarea *tarea;
  List *adyacentes; // lista de nodos adyacentes
} NodoT;

typedef struct _tarea {
  char nombre[21];
  unsigned short priority;
  bool completada;
  NodoT *nodo; // nodo asociado a la tarea
} Tarea;

typedef struct _grafo {
  List *nodos; // lista de nodos del grafo
} Grafo;

void mostrarMenu() {
  puts(BARRA);
  printf("                         Menu\n");
  puts(BARRA);
  printf("\nSeleccione una opción:\n\n1. Agregar tarea\n2. Establecer precedencia entre tareas\n3. Mostrar tareas por hacer\n4. Marcar tarea como completada \n0. Salir\n\n");
  puts(BARRA);
}

void agregarTarea(char nombre[],unsigned short prioridad, Grafo *grafo){
  Tarea* newTarea = (Tarea*)malloc(sizeof(Tarea));
  strcpy(newTarea -> nombre, nombre);
  newTarea -> priority = prioridad;
  newTarea -> completada = false;

  NodoT *node = (NodoT*)malloc(sizeof(NodoT));
  node -> tarea = newTarea;
  node -> adyacentes = createList();

  pushBack(grafo -> nodos, node);
  newTarea -> nodo = node;
}


/*Tarea *existe(Grafo *grafo, char *nombreTarea) {
  NodoT *current = NULL;
  
  for (Node *node = firstList(grafo->nodos); node != NULL; node = nextList(grafo -> nodos)) {
    printf("hola\n");
    current = (NodoT*) node->data;
    printf("hola\n");
    Tarea *tareaA = current->tarea;
    printf("hola\n");
    
    if (strcmp(tareaA->nombre, nombreTarea) == 0) {
      return tareaA;
    }
  }
  // No se encontró ninguna tarea con el nombre buscado
  return NULL;
}*/

void precedencia(Grafo *grafo){
  char nom1[21],nom2[21];
  printf("Ingrese el nombre de la tarea 1\n");
  scanf(" %[^\n]", nom1);
  /*Tarea *tarea1 = existe(grafo,nom1);

  if(tarea1 == NULL){
    printf("Tarea 1 no encontrada\n");
    return;
  }
  
  printf("Ingrese el nombre de la tarea 2\n");
  scanf(" %[^\n]", nom2);
  Tarea *tarea2 = existe(grafo,nom2);

  if(tarea2 == NULL){
    printf("Tarea 2 no encontrada");
    return;
  }

  NodoT *nodoTarea1 = tarea1->nodo;
  NodoT *nodoTarea2 = tarea2->nodo;
  pushBack(nodoTarea2->adyacentes, nodoTarea1);*/
}

void mostrarTareas(Grafo *grafo){
  List *porHacer = createList();
  for(Node* n = firstList(grafo -> nodos) ; n != NULL ; n = nextList(grafo -> nodos)){
    NodoT *nodo = (NodoT*)n -> data;
    Tarea *tarea = nodo -> tarea;

    if(tarea -> completada == false){
      
    }
  }
  
}

int main(){
  unsigned short numIngresado, prioridad;
  char nombre[21];
  Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));
  grafo -> nodos = createList();
  while(true){
    mostrarMenu();

    scanf("%hu", &numIngresado);
    while (numIngresado > 4 || numIngresado < 0) {
      printf("Ingrese un número válido \n");
      scanf("%hu", &numIngresado);
    }
    
    if (numIngresado == 0) {
      printf("\n");
      puts(BARRA);
      printf("                   Fin Del Programa\n");
      puts(BARRA);
      return 0;
    }
    if (numIngresado == 1) {
      printf("Ingrese el Nombre de la tarea\n");
      scanf(" %[^\n]", nombre);
      printf("Ingrese la prioridad de la tarea\n");
      scanf("%hu", &prioridad);
      agregarTarea(nombre,prioridad,grafo);
    }
    if (numIngresado == 2) {
      precedencia(grafo);
    }
    if (numIngresado == 3) {
      mostrarTareas(grafo);
    }
    if (numIngresado == 4) {
      //completada();
    }
  }
  return 0;
}