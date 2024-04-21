#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct{
  char nombrePaciente[50];
  int edad;
  char sintoma[50];
  char prioridad[6];
  char hora[6];

} tipoPaciente;


// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
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

void registrar_paciente(List *pacientes) {
  printf("Registrar nuevo paciente\n");
  
  tipoPaciente *auxPaciente; //auxiliar para guardar los datos del                                    paciente
  auxPaciente = malloc(sizeof(tipoPaciente));

  //Pedir datos del paciente
  printf("Ingrese el nombre del paciente: ");
  scanf(" %[^\n]", auxPaciente->nombrePaciente);
  printf("Ingrese la edad del paciente : ");
  scanf("%d", &auxPaciente->edad);
  printf("Ingrese el sintoma del paciente : ");
  scanf(" %[^\n]", auxPaciente->sintoma);
  strcpy(auxPaciente->prioridad , "Baja");  //Asignamos prioridad baja por defecto       
  printf("Hora de ingreso : ");
  scanf(" %[^\n]", auxPaciente->hora);

  list_pushFront(pacientes, auxPaciente); //Agregamos el paciente a la lista
  // Aquí implementarías la lógica para registrar un nuevo paciente
}

void mostrar_lista_pacientes(List *pacientes){
  // Mostrar pacientes en la cola de espera
  
  tipoPaciente* actual = list_first(pacientes);
  if(!actual){
    printf("No hay pacientes\n\n");
    presioneTeclaParaContinuar();
    return;
  }
  
  printf("Pacientes en espera: \n\n");
 
  while(actual != NULL){
    limpiarPantalla();
    printf("Nombre: %s\n", actual->nombrePaciente);
    printf("Edad: %d\n",  actual->edad);
    printf("Sintoma: %s\n",  actual->sintoma);
    printf("Prioridad: %s\n",  actual->prioridad);
    printf("\nSiguiente Paciente \n");
    actual = list_next(pacientes);
  }
  // Aquí implementarías la lógica para recorrer y mostrar los pacientes
}

void asignar_prioridad(List *pacientes){
  // Asignar prioridad a un paciente
  tipoPaciente* actual = list_first(pacientes);
  if(!actual){
    printf("No han ingresados pacientes\n\n");
    presioneTeclaParaContinuar();
    return;
  }

  char pacienteBuscado[50];
  while(1){
    scanf(" %[^\n]", pacienteBuscado);
    

    
  }

  
  while(actual != NULL){
    char prioridadNueva[6];
    printf("Nombre: %s\n", actual->nombrePaciente);
    printf("Edad: %d\n",  actual->edad);
    printf("Sintoma: %s\n",  actual->sintoma);
    printf("Asigne nueva prioridad (Baja, Media, Alta): ");
    scanf( " %[^\n]", prioridadNueva);
    
    if(strcmp(actual->prioridad , prioridadNueva) != 0){
      tipoPaciente *auxPaciente;

      auxPaciente = malloc(sizeof(tipoPaciente));
      strcpy(auxPaciente->nombrePaciente, actual->nombrePaciente);
      auxPaciente->edad = actual->edad;
      strcpy(auxPaciente->sintoma, actual->sintoma);
      strcpy(auxPaciente->prioridad, prioridadNueva);
      list_popCurrent(pacientes);
      if (strcmp(actual->prioridad , "Alta") == 0){
        list_pushBack(pacientes, auxPaciente);
      }
      else if(strcmp(actual->prioridad, "Media") == 0){
        
      }
    }
      
    
    actual = list_next(pacientes);
  }
}

void atender_paciente(List *pacientes){
  // Atender al siguiente paciente
  tipoPaciente* actual = list_first(pacientes);
  if(!actual){
    printf("No hay pacientes registrados\n\n");
    presioneTeclaParaContinuar();
    return;
  }

  printf("Atendiendo al siguiente paciente: \n\n");
  printf("Nombre: %s\n", actual->nombrePaciente);

  list_popCurrent(pacientes);
  
  
}

int main() {
  char opcion;
  List *pacientes = list_create(); // puedes usar una lista para gestionar los pacientes

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_paciente(pacientes);
      break;
    case '2':
      asignar_prioridad(pacientes);
      // Lógica para asignar prioridad
      break;
    case '3':
      mostrar_lista_pacientes(pacientes);
      break;
    case '4':
      atender_paciente(pacientes);// Lógica para atender al siguiente paciente
      break;
    case '5':
      // Lógica para mostrar pacientes por prioridad
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