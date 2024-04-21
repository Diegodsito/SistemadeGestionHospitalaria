//Sistema de Gestion Hospitalaria//

Bienvenido! Este es un sistema simple programado en C para gestionar pacientes de un hospital. Permite registrar pacientes (Nombre, edad, sintomas), a los cuales se les asigna una prioridad baja por defecto. Tambien podemos modificar la prioridad de estos pacientes clasificadas en alta, media y baja (Esto afectara en la lista de espera). 
Podemos mostrar la lista de espera y tambien podemos mostrarla segun prioridad.
Al atender un paciente se mostrara su nombre y sera eliminado de la lista de espera automaticamente.

//Como ejecutar y compilar//

La manera mas facil y sencilla es ejecutarlo en replit.

1. Visita replit.com
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: "https://replit.com/@diegoalvaradom/Sistema-de-Gestion-Hospitalaria#readme.md".
5. replit.com clonará el repositorio y preparará un entorno de ejecución.
6. Presiona el botón "Run" para compilar y ejecutar la aplicación.


//Funcionalidades//

Ingreso de pacientes:  Registra pacientes con su nombre, edad y sintomas. (El nombre y sintomas no debe superar los 49 caracteres)
Asignacion o modificacion de prioridad del paciente: Se asigna o modifica con Alta, Media o Baja.
Mostrar lista de espera : Se muestra segun prioridad y hora de ingreso.
Atender al siguiente paciente.

//Posibles Problemas//

El programa a veces tiende a repetir "Presiona una tecla para continuar" o instrucciones que ya se solicitaron. Esto se puede solucionar volviendo a presionar la tecla o volviendo a ingresar el dato si se solicita nuevamente. Aun se busca la causa de este problema.

//A mejorar//

Mostrar datos extras como la hora de ingreso y mejorar la interfaz del programa.

//Ejemplo de uso//

Primer paso:
Registramos paciente para ingresarlo al sistema
1) Registrar paciente.
   Ingrese nombre: Tilin Insano
   Edad: 9
   Sintomas: Dolor guata
   
Por defecto se le asigna prioridad baja.
La hora queda ingresada automaticamente.

Segundo paso:

2) Asignar prioridad a paciente
   Ingrese nombre del paciente: Tilin Insano 
   Asigne nueva prioridad (Alta, Media o Baja) : Alta
   
El nombre debe ser exactamente como fue ingresado, incluyendo mayusculas, minusculas, espacios, etc. Asi mismo el ingreso de prioridad debe ingresarse como en el ejemplo.

Tercer paso:

4) Atender al siguiente paciente.

Muestra el nombre del paciente a atender y se borra de la lista de espera, respetando la prioridad y orden de llegada.

