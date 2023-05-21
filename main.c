#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "hashmap.h"
#define BARRA "-------------------------------------------------------"

typedef struct{
  char tarea[21]; //Nombre de la tarea
  unsigned short priority; //Prioridad de la tarea
  bool completada; // Con esta variable se verfica si se completo la tarea
  List *adyacentes; // Lista de las tareas precedentes
} task;

typedef struct{
  char pre[21];
}adyacentes;


void mostrarMenu(){//Funcion que muestra el menu
  puts(BARRA);
  printf("                         Menu\n");
  puts(BARRA);
  printf("\nSeleccione una opción:\n\n1. Agregar tarea\n2. Establecer precedencia entre tareas\n3. Mostrar tareas por hacer\n4. Marcar tarea como completada \n0. Salir\n\n");
  puts(BARRA);
}

//En esta funcion de agrega tarea a un mapa, en el cual la calve es el nombre de la tarea
void agregarTarea(char *nombre,unsigned short prioridad, HashMap* map, int *cont){
  task* newTarea = (task*)malloc(sizeof(task)); // se le reserva memoria a la nueva tarea
  strcpy(newTarea -> tarea, nombre); // se copia en el struct
  newTarea -> priority = prioridad;
  newTarea -> completada = false;// Se inician todas las "nuevas tareas" como falsas
  insertMap(map, newTarea -> tarea, newTarea);//se inserta en el mapa
  (*cont)++; // Este contador se utiliza para llevar la cuenta de cuantos datos hay en el mapa
}

// En esta funcion se establece la precedencia entre tareas
void precedencia(char *t1, char *t2,HashMap *map){ 
  Pair* i=searchMap(map, t2); // Se busca si en el mapa existe la tarea 2
  if(((task *)i->value)->adyacentes==NULL){// Si este dato del mapa no tenia una lista de precedencia, se crea
    ((task*)i->value)->adyacentes = createList();
  }
  Pair* l=searchMap(map, t1);//Se busca si en el mapa existe la tarea 2
  if(l == NULL || l == NULL){ // si alguno de los "serchMap" retorna "NULL", se imprime el mensaje correspondiente y se finaliza el proceso
    printf("Una o dos de las tareas no existe");
    return;
  }
  pushBack(((task *)i->value)->adyacentes, l->key);// La tarea 1 se ingresa a la lista de precedencia de la tarea 2
}

// En esta funcion se mustran las tareas y su precedencia ordenadas por prioridad 
void mostrarTareas(HashMap *map, int conT) { 
  Pair *a = firstMap(map);//Esta variable se utiliza para recorrer el mapa, desde el inicio 
  if (a == NULL) {// En caso de que no se haya ingresado nonguna tarea o se hayan eliminado mostrara el mensaje correspondiente
    printf("No se ha ingresado ninguna tarea\n");
    return;
  }

  int numTareas = conT; // Esta variable se inicializa con el valor del contador en ese momento
  task **tareasAux = malloc(sizeof(task *) * numTareas);// Se crea aun arrgelo axuiliar
  int *indices = malloc(sizeof(int) * numTareas);// Se crea indices para no modificar la estructura del arreglo
  int pos = 0;

  while (a != NULL) {// En este ciclo los datos del mapa se ingresan al arreglo auxiliar
    task *o = (task *)a->value;
    tareasAux[pos] = o;
    indices[pos] = pos;
    pos++;

    a = nextMap(map);
  }

  // Ordenar los índices según la prioridad de las tareas
  for (int i = 1; i < numTareas; i++) {
    int j = i;
    while (j > 0 && tareasAux[indices[j - 1]]->priority > tareasAux[indices[j]]->priority) {
      int aux = indices[j];
      indices[j] = indices[j - 1];
      indices[j - 1] = aux;
      j--;
    }
  }

  // Mostrar las tareas ordenadas por prioridad con precedencia
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

// En esta funcion recibe una tarea, la cual sera maracada como "completada" y eliminada del mapa
void completada(HashMap *map, char *nombre, int *cont) {
  Pair *e = searchMap(map, nombre);
  if(e == NULL){// Se busca si existe la tarea
    printf("No se encontro la tarea\n");
    return;
  }
  char conf[2];
  
  if (((task *)e->value)->adyacentes != NULL) { // Se verifica si la tarea a eliminar tiene lista de precedencia
    printf("¿Quiere eliminar la tarea? (s/n)");
    scanf(" %[^\n]", conf);
    printf("%s\n", conf);
    if (strcmp(conf, "n") == 0)
      return;
  }
  eraseMap(map, nombre); // Se elimina del mapa
  for(Pair *a = firstMap(map) ; a != NULL ; a = nextMap(map)){ 
    List *o=((task*)a->value)->adyacentes;
    if (firstList(o) != NULL) {
      for (char *j = firstList(o); j != NULL;j = nextList(o)) {
        if (strcmp(j, nombre)==0) {
          popCurrent(o); // Se elimina de la lista 
        }
      }
    }
  }
  (*cont)--; // se decrementa el contador, ya que se elimino una tarea
}

// Desde el main se llaman todas las funciones y se ingresan los nombres de las tareas, ademas de crear el mapa
int main(){
  unsigned short numIngresado, prioridadT;
  char nombreT[21];
  HashMap *map = createMap(22); // se crea el mapa
  int conT = 0; // Aqui se inicializa el contador que llevara la cuenta de cuantos valores hay en el mapa
  
  while(true){
    mostrarMenu();
    scanf("%hu", &numIngresado);
    while (numIngresado > 4 || numIngresado < 0) {
      printf("Ingrese un número válido \n");
      scanf("%hu", &numIngresado);// Aqui se asegura de ingresar un numero correcto para el menu
    }
    
    if (numIngresado == 0) {// Si se ingrea 0 se termina el programa
      printf("\n");
      puts(BARRA);
      printf("                   Fin Del Programa\n");
      puts(BARRA);
      return 0;
    }
    if (numIngresado == 1) {// Si se ingrea 1 se agrega tarea
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
    if (numIngresado == 2) {// Si se ingrea 2 se establece precedencia entre tareas
      char t1[21],t2[21];
      printf("Ingrese el Nombre de la tarea 1\n");
      scanf(" %[^\n]", t1);
      printf("Ingrese el Nombre de la tarea 2\n");
      scanf(" %[^\n]", t2);
      precedencia(t1,t2,map);
    }
    if (numIngresado == 3) {// Si se ingrea 3 se muestran las tareas ordenadas por prioridad
      mostrarTareas(map,conT);
    }
    if (numIngresado == 4) {// Si se ingrea 4 se elimina una tarea del mapa
      char name[21];
      printf("Ingrese el Nombre de la tarea\n");
      scanf(" %[^\n]", name);
      completada(map,name,&conT);
    }
  }
  return 0;
}