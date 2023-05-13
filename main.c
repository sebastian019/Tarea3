#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#define BARRA "-------------------------------------------------------"

typedef struct _tarea Tarea;

typedef struct _nodo {
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

void existe(Grafo *grafo, char *tarea){
  
}

void precedencia(Grafo *grafo){
  char tarea1[21],tarea2[21];
  printf("Ingrese el nombre de la tarea 1\n");
  scanf(" %[^\n]", tarea1);
  existe(grafo,tarea1);
  
  printf("Ingrese el nombre de la tarea 2\n");
  scanf(" %[^\n]", tarea2);
  existe(grafo,tarea2);
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
      //mostrarTareas();
    }
    if (numIngresado == 4) {
      //completada();
    }
  }
  return 0;
}