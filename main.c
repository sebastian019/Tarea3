#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#define BARRA "-------------------------------------------------------"

struct Nodo {
    char nombre[21]; // Descripción de la tarea
    int prioridad; // Prioridad de la tarea
    struct Nodo* vecinos[5]; // Arreglo de punteros a nodos vecinos (tareas precedentes)
    int numVecinos; // Número de vecinos
};

// Definición de la estructura de la cola de prioridad
struct ColaPrioridad {
    struct Nodo* tareas[1000]; // Arreglo de punteros a nodos de tareas
    int numTareas; // Número de tareas en la cola de prioridad
};

void mostrarMenu(){
  puts(BARRA);
  printf("                         Menu\n");
  puts(BARRA);
  printf("\nSeleccione una opción:\n\n1. Agregar tarea\n2. Establecer precedencia entre tareas\n3. Mostrar tareas por hacer\n4. Marcar tarea como completada \n0. Salir\n\n");
  puts(BARRA);
}

void ordenar(struct ColaPrioridad *cola){
  if(cola -> numTareas < 2){
    return;
  }
  int i = cola->numTareas - 1;
  while (i > 0 && cola->tareas[i]->prioridad > cola->tareas[(i-1)/2]->prioridad) {
    // Intercambiar la tarea con su padre si su prioridad es mayor
    struct Nodo* aux = cola->tareas[i];
    cola->tareas[i] = cola->tareas[(i-1)/2];
    cola->tareas[(i-1)/2] = aux;
    i = (i-1) / 2;
  }
}

void agregarTarea(char *nombreT, unsigned short prioridadT,struct ColaPrioridad *cola){
  struct Nodo * newTarea = (struct Nodo *)malloc(sizeof(struct Nodo));
  strcpy(newTarea -> nombre, nombreT);
  newTarea->prioridad = prioridadT;
  newTarea->numVecinos = 0;

  cola->tareas[cola->numTareas] = newTarea;
  cola->numTareas++;
  ordenar(cola);
}

void precedencia(char *t1, char *t2, struct ColaPrioridad *cola){
  int pos = -1;
  for(int i = 0 ; i < cola -> numTareas ; i++){
    if(strcmp(cola->tareas[i]->nombre,t1) == 0){
      pos = i;
      break;
    }
  }
  
  if(pos == -1){
    printf("Tarea 1 no encontrada\n");
    return;
  }
  
 int pos2 = -1;
  
  for(int i = 0 ; i < cola -> numTareas ; i++){
    if(strcmp(cola->tareas[i]->nombre,t2) == 0){
      pos2 = i;
      break;
    }
  }
  
  if(pos2 == -1){
    printf("Tarea 2 no encontrada\n");
    return;
  }
  cola -> tareas[pos2] -> vecinos[cola -> tareas[pos] -> numVecinos] = cola -> tareas[pos];
  cola -> tareas[pos2] -> numVecinos++;
}

void mostrarTareas(struct ColaPrioridad *cola){
  if(cola->numTareas == 0){
    printf("La cola esta vacia, agrege datos antes de mostrar\n");
    return;
  }
  struct ColaPrioridad copy = *cola;

  for(int i = 0 ; i < copy.numTareas ; i++) {
    for(int j = 0 ; j < i ; j++) {
      if(copy.tareas[j]->prioridad > copy.tareas[j+1]->prioridad) {
        struct Nodo* aux = copy.tareas[j];
        copy.tareas[j] = copy.tareas[j+1];
        copy.tareas[j+1] = aux;
      }
    }
  }

  for(int i = 0; i < copy.numTareas ; i++) {
    printf("%d. %s (Prioridad: %d)", i+1, copy.tareas[i]->nombre, copy.tareas[i]->prioridad);
    if(copy.tareas[i]->numVecinos > 0){
      printf(" - Precedente: ");
      for(int j = 0; j < copy.tareas[i]->numVecinos ; j++) {
        printf("%s", copy.tareas[i]->vecinos[j]->nombre);
        if(j != copy.tareas[i]->numVecinos - 1){
          printf(", ");
        }
      }
    }
    printf("\n");
  }
}


int main(){
  unsigned short numIngresado, prioridadT;
  char nombreT[21];
  struct ColaPrioridad *cola = (struct ColaPrioridad *)malloc(sizeof(struct ColaPrioridad)); 
  
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
      scanf(" %[^\n]", nombreT);
      printf("Ingrese la prioridad de la tarea\n");
      scanf("%hu", &prioridadT);
      agregarTarea(nombreT,prioridadT,cola);
    }
    if (numIngresado == 2) {
      char t1[21],t2[21];
      printf("Ingrese el Nombre de la tarea 1\n");
      scanf(" %[^\n]", t1);
      printf("Ingrese el Nombre de la tarea 2\n");
      scanf(" %[^\n]", t2);
      precedencia(t1,t2,cola);
    }
    if (numIngresado == 3) {
      mostrarTareas(cola);
    }
    if (numIngresado == 4) {
      //completada();
    }
  }
  return 0;
}