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
  List *adyacentes;
} task;

typedef struct{
  char pre[21];
}adyacentes;


void mostrarMenu(){
  puts(BARRA);
  printf("                         Menu\n");
  puts(BARRA);
  printf("\nSeleccione una opción:\n\n1. Agregar tarea\n2. Establecer precedencia entre tareas\n3. Mostrar tareas por hacer\n4. Marcar tarea como completada \n0. Salir\n\n");
  puts(BARRA);
}

void agregarTarea(char *nombre,unsigned short prioridad, HashMap* map, int *cont){
  task* newTarea = (task*)malloc(sizeof(task));
  strcpy(newTarea -> tarea, nombre);
  newTarea -> priority = prioridad;
  newTarea -> completada = false;
  insertMap(map, newTarea -> tarea, newTarea);
  (*cont)++;
}

void precedencia(char *t1, char *t2,HashMap *map){
  Pair* i=searchMap(map, t2);
  if(((task *)i->value)->adyacentes==NULL){
    ((task*)i->value)->adyacentes = createList();
  }
  Pair* l=searchMap(map, t1);
  if(l == NULL || l == NULL){
    printf("Una o dos de las tareas no existe");
    return;
  }
  pushBack(((task *)i->value)->adyacentes, l->key);
}

void mostrarTareas(HashMap *map, int conT) {
  Pair *a = firstMap(map);
  if (a == NULL) {
    printf("No se ha ingresado ninguna tarea\n");
    return;
  }

  int numTareas = conT;
  task **tareasAux = malloc(sizeof(task *) * numTareas);
  int *indices = malloc(sizeof(int) * numTareas);
  int index = 0;

  int cont = 1;
  while (a != NULL) {
    task *o = (task *)a->value;
    tareasAux[index] = o;
    indices[index] = index;
    index++;

    a = nextMap(map);
  }

  // Ordenar los índices según la prioridad de las tareas
  for (int i = 1; i < numTareas; i++) {
    int j = i;
    while (j > 0 && tareasAux[indices[j - 1]]->priority > tareasAux[indices[j]]->priority) {
      int temp = indices[j];
      indices[j] = indices[j - 1];
      indices[j - 1] = temp;
      j--;
    }
  }

  // Mostrar las tareas ordenadas por prioridad con precedencia
  printf("Tareas ordenadas por prioridad:\n");
  for (int i = 0; i < numTareas; i++) {
    task *o = tareasAux[indices[i]];
    printf("%d. %s (Prioridad: %hu)", i + 1, o->tarea, o->priority);

    if (firstList(o->adyacentes) != NULL) {
      printf(" - Precedente: ");
      int cont2 = 0;
      for (char *j = firstList(o->adyacentes); j != NULL; j = nextList(o->adyacentes)) {
        if (cont2 == 0) {
          printf("%s", j);
          cont2++;
        } else {
          printf(", %s", j);
        }
      }
    }

    printf("\n");
  }
}

void completada(HashMap *map, char *nombre, int *cont) {
  task *tarea = (task *)searchMap(map, nombre); // Obtener la tarea del HashMap
  
  if (tarea == NULL) {
    printf("La tarea no existe.\n");
    return;
  }
  
  if (tarea->adyacentes != NULL) {
    printf("¿Estás seguro que deseas eliminar la tarea? (s/n):\n ");
    char respuesta;
    scanf(" %c", &respuesta);
    
    if (respuesta != 's') {
      printf("La tarea no ha sido eliminada.\n");
      return;
    }
  }
  
  tarea->completada = true; // Marcar la tarea como completada
  
  eraseMap(map, nombre); // Eliminar la tarea del HashMap
  
  printf("La tarea \"%s\" ha sido eliminada.\n", nombre);
  (*cont)--;
}



int main(){
  unsigned short numIngresado, prioridadT;
  char nombreT[21];
  HashMap *map = createMap(22);
  int conT = 0;
  
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

      int largoName = strlen(nombreT);
          
      while (largoName > 21 || largoName < 1) {
        printf("Ingrese un nombre válido (hasta 20 caracteres)\n");
        scanf(" %[^\n]", nombreT);
        largoName = strlen(nombreT);
      }
      
      printf("Ingrese la prioridad de la tarea\n");
      scanf("%hu", &prioridadT);
      agregarTarea(nombreT,prioridadT,map,&conT);
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
      mostrarTareas(map,conT);
    }
    if (numIngresado == 4) {
      char name[21];
      printf("Ingrese el Nombre de la tarea\n");
      scanf(" %[^\n]", name);
      completada(map,name,&conT);
    }
  }
  return 0;
}