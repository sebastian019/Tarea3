#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "hashmap.h"
#define BARRA "-------------------------------------------------------"

typedef struct{
    char tarea[21];
    unsigned short priority;
    bool completada;
    List* adyacentes;
    //struct Node* next;
} task;



void mostrarMenu(){
  puts(BARRA);
  printf("                         Menu\n");
  puts(BARRA);
  printf("\nSeleccione una opción:\n\n1. Agregar tarea\n2. Establecer precedencia entre tareas\n3. Mostrar tareas por hacer\n4. Marcar tarea como completada \n0. Salir\n\n");
  puts(BARRA);
}

void agregarTarea(char *nombre,unsigned short prioridad, HashMap* map){
  task* newTarea = (task*)malloc(sizeof(task));
  strcpy(newTarea -> tarea, nombre);
  newTarea -> priority = prioridad;
  newTarea -> completada = false;
  newTarea -> adyacentes = createList();
  insertMap(map, newTarea -> tarea, newTarea);
}

task *buscar(char *nombre, HashMap *map){
  return (task*)searchMap(map, nombre);
}

void precedencia(char *t1, char *t2,HashMap *map){
  task *tarea1 = (task*)searchMap(map, t1);
  task *tarea2 = (task*)searchMap(map, t2);

  if(tarea1 == NULL || tarea2 == NULL){
    printf("Una o las 2 taeras no existen\n");
    return;
  }
  tarea1 -> adyacentes = createList();
  pushBack(tarea1 -> adyacentes, tarea2);
}

void mostrarTareas(HashMap *map){
  Pair *a = firstMap(map);
  int cont = 1;
  while(a != NULL){
    task *t = (task*)a -> value;
    printf("%d %s (Prioridad: %hu)", cont, t->tarea,t -> priority);
    if(t -> adyacentes != NULL){
      printf(" - Precedente: ");
      for (List *e = firstList(t -> adyacentes); e != NULL; e = nextList(t->adyacentes)) {
        task *prec = (task *)nextList(e);
        printf("%s", prec->tarea);
        if(nextList(e) != NULL){
          printf(", ");
        }
      }
    }
    printf("\n");
    cont++;
    a = nextMap(map);
  }
}

int main(){
  unsigned short numIngresado, prioridadT;
  char nombreT[21];

  HashMap *map = createMap(100);
  
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
      agregarTarea(nombreT,prioridadT,map);
    }
    if (numIngresado == 2) {
      char t1[21],t2[21];
      printf("Ingrese el Nombre de la tarea 1\n");
      scanf(" %[^\n]", t1);
      printf("Ingrese el Nombre de la tarea 2\n");
      scanf(" %[^\n]", t2);
      precedencia(t1,t2,map);
    }
    if (numIngresado == 3) {
      mostrarTareas(map);
    }
    if (numIngresado == 4) {
      //completada();
    }
  }
  return 0;
}