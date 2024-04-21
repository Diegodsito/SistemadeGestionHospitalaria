#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct{
  char nombrePaciente[50];
  int edad;
  char sintoma[50];
  char prioridad[6];
  time_t hora;

} tipoPaciente;


// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); 
  getchar(); 
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

int lower_than(void *data1, void *data2){
  tipoPaciente *paciente1 = (tipoPaciente *)data1;
  tipoPaciente *paciente2 = (tipoPaciente *)data2;
  // Comparar por prioridad ALta
  if(strcmp(paciente1->prioridad, paciente2->prioridad) != 0)
    if(strcmp(paciente1->prioridad, "Alta") == 0 && strcmp(paciente2->prioridad, "Alta") != 0)         return 1;
    if(strcmp(paciente1->prioridad, "Alta") != 0 && strcmp(paciente2->prioridad , "Alta") == 0)      return 0;
  // Comparar por prioridad Media
  if(strcmp(paciente1->prioridad, "Media") == 0 && strcmp(paciente2->prioridad , "Media") != 0)
    return 1;
  if(strcmp(paciente1->prioridad, "Media") != 0 && strcmp(paciente2->prioridad , "Media") == 0)
    return 0;

  // Comparar por orden de llegada

  if(paciente1->hora < paciente2->hora) return 1;
  if(paciente1->hora > paciente2->hora) return 0;
}

void registrar_paciente(List *pacientes) {
  printf("Registrar nuevo paciente\n");
  
  tipoPaciente *auxPaciente; //auxiliar para guardar los datos del                                                            paciente
  auxPaciente = malloc(sizeof(tipoPaciente));

  //Pedir datos del paciente
  printf("Ingrese el nombre del paciente: ");
  scanf(" %[^\n]", auxPaciente->nombrePaciente);
  printf("Ingrese la edad del paciente : ");
  scanf("%d", &auxPaciente->edad);
  printf("Ingrese el sintoma del paciente : ");
  scanf(" %[^\n]", auxPaciente->sintoma);
  strcpy(auxPaciente->prioridad , "Baja");  //Asignamos prioridad baja por defecto       
  auxPaciente->hora = time(NULL); //Obtenemos la hora actual

  list_sortedInsert(pacientes, auxPaciente, lower_than); //Agregamos el paciente a la lista
}

void mostrar_lista_pacientes(List *pacientes){
  // Mostrar pacientes en la cola de espera
  
  tipoPaciente* actual = list_first(pacientes);
  if(!actual){  //Validacion si se encuentran pacientes
    printf("No hay pacientes registrados\n\n");
    presioneTeclaParaContinuar();
    return;
  }
  
  printf("Pacientes en espera: \n\n");

  int cont = 1;
  printf("Lista de Espera\n");    //Mostrando lista de espera
  while(actual != NULL){
    printf("%i.- %s\n", cont ,actual->nombrePaciente);
    cont++;
    actual = list_next(pacientes);
  }
}



void asignar_prioridad(List *pacientes){

  tipoPaciente* actual = list_first(pacientes);
  if(!actual){  //Validacion si se encuentran pacientes
    printf("No se han ingresados pacientes\n\n");
    return;
  }
  
  char pacienteBuscado[50];
  
  while(1){
    printf("Ingrese el nombre del paciente a asignar prioridad: "); //Buscando paciente.
    scanf(" %[^\n]", pacienteBuscado);
    
    if(strcmp(actual->nombrePaciente, pacienteBuscado) == 0) break;
    else{ 
      actual= list_next(pacientes);
      if(actual == NULL){
        printf("Paciente no encontrado\n");
        return;
        }
      }
    }

  char prioridadNueva[6];
  printf("Asigne nueva prioridad (Baja, Media, Alta): ");
  scanf( " %[^\n]", prioridadNueva);

  tipoPaciente *auxPaciente;
  
  auxPaciente = malloc(sizeof(tipoPaciente));

  strcpy(auxPaciente->prioridad, prioridadNueva);
  strcpy(auxPaciente->nombrePaciente , actual->nombrePaciente);
  auxPaciente->edad = actual->edad;
  strcpy(auxPaciente->sintoma , actual->sintoma);
  auxPaciente->hora = actual->hora;
  list_popCurrent(pacientes);
  free(actual);
  list_sortedInsert(pacientes, auxPaciente, lower_than);
}

void atender_paciente(List *pacientes){
  // Atender al siguiente paciente
  tipoPaciente* actual = list_first(pacientes);
  if(!actual){ //Validacion si se encuentran pacientes
    printf("No hay pacientes registrados\n\n");
    presioneTeclaParaContinuar();
    return;
  }

  printf("Atendiendo al siguiente paciente: \n\n");
  printf("Nombre: %s\n", actual->nombrePaciente);

  list_popCurrent(pacientes);
  free(actual);
}

void mostrar_pacientes_por_prioridad(List *pacientes){

  List *pacientesPrioridad = list_create();
  tipoPaciente *actual = list_first(pacientes);

  if(actual == NULL){ //Validacion si se encuentran pacientes
    printf("No hay pacientes registrados\n\n");
    return;
  }
  char prioridad[6];
  printf("Ingrese prioridad a mostrar (Baja, Media, Alta): \n");
  scanf(" %[^\n]", prioridad);

  while(actual != NULL){
    if(strcmp(actual->prioridad, prioridad) == 0)
      list_pushFront(pacientesPrioridad, actual);
    actual = list_next(pacientes);
  }
  
  if(strcmp(prioridad,"Alta") != 0 && strcmp(prioridad,"Media") != 0 && strcmp(prioridad,"Baja") != 0){
    printf("Opcion no validad, regresando al menu... \n");
    return;
  }
  
  if(pacientesPrioridad == NULL){
    printf("No hay pacientes con prioridad %s\n\n", prioridad);
    return;
  }

  printf("Pacientes con prioridad %s: \n\n", prioridad);
  mostrar_lista_pacientes(pacientesPrioridad);

}

int main() {
  char opcion;
  List *pacientes = list_create();

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); 

    switch (opcion) {
    case '1':
      registrar_paciente(pacientes);
      break;
    case '2':
      asignar_prioridad(pacientes);
      break;
    case '3':
      mostrar_lista_pacientes(pacientes);
      break;
    case '4':
      atender_paciente(pacientes);
      break;
    case '5':
      mostrar_pacientes_por_prioridad(pacientes);
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(pacientes);

  return 0;
}