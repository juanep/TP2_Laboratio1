#ifndef ARRAYEMPLOYEES_H_INCLUDED
#define ARRAYEMPLOYEES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    int id;
    char name[20];
    char lastName[20];
    float salary;
    int sector;
    int isEmpty;
}Employee;

typedef struct{
    int id;
    char descripcion[20];
}eSector;


/** \brief Aporta opciones para realizar las operaciones de registro.
 * \return Devuelve la opcion elegida.
 */
int menu();

/** \brief To indicate that all position in the array are empty,
 *         this function put the flag (isEmpty) in TRUE in all position of the array.
 * \param list Employee Pointer to array of employees
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 * */
void initEmployeeList(Employee lista[], int tam);

/** \brief add in a existing list of employees the values received as parameters in the first empty position
 * \param lista es el listado de los empleados.
 * \param tam es la cantidad de empleados que pueden registrarse en el listado.
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without free space] - (0) if Ok
 **/
int addEmployee(Employee lista[], int tam, eSector sectores[], int tamSector);

/** \brief Recibe valores por parametro para modificar los campos del empleado,
 *          dicho empleado es elegido a travez del ingreso de su numero de legajo.
 * \param lista es el listado de los empleados.
 * \param tam es la cantidad de empleados que pueden estar registrados en el listado.
 * \param *legajo es el puntero a la variable legajo del main, para hallar al empleado y pueda ser usado en los informes.
 * \param sectores es el array de sectores para la distribucion de los empleados.
 * \param tamSector es la cantidad de sectores.
 * \return Devuelve (-1) si no encontro el indice, (0) si no pudo obtener los datos solicitados, (1) si obtuvo los datos.
 */
int ModificarEmpleado(Employee lista[], int tam, int *legajo, eSector sectores[], int tamSector);

/** \brief Recibe valores por parametro para dar de baja un empleado, dicho empleado
 *          es hallado a travez del ingreso de su numero de legajo.
 * \param  lista es el listado de empleados.
 * \param  tam es la cantidad limite de empleados que se pueden ingresar.
 * \return *legajo es el puntero a la variable legajo del main, para hallar al empleado y pueda ser usado en los informes.
 */
int removeEmployee(Employee lista[], int tam, int legajo, eSector sectores[], int tamSector);

/** \brief Recorre el listado de empleados en busca de un lugar disponible.
 * \param lista es el listado de los empleados.
 * \param tam es la cantidad limite de empleados que se pueden registrar en el listado.
 * \return (Indice = -1) si no encontro lugar disponible. (Indice = ubicacion del indice disponible)
 */
int buscarLibre(Employee lista[], int tam);

/** \brief Recorre el listado en busca de un empleado, utilizando como referencia el numero de legajo del mismo.
 * \param lista es el listado de empleados.
 * \param tam es la cantidad limite de empleados que pueden registrarse.
 * \param legajo es el numero de referencia utilizado para la busqueda.
 * \return (Indice = -1) si no encontro el empleado. (Indice = ubicacion del empleado segun su legajo)
 *
 */
int findEmployeeById(Employee lista[], int tam, int legajo);

/** \brief Muestra los datos de un empleado.
 * \param lista es el listado de empleados.
 * \param sectores es el array de sectores para la distribucion de los empleados.
 * \param tamSector la cantidad de sectores existentes.
 */
void showEmployee(Employee lista, eSector sectores[], int tamSector);

/** \brief Toma valores por parametro para obtener el nombre del sector al que corresponde el empleado.
 * \param sectores es el array de sectores para la distribucion de los empleados.
 * \param tam es la cantidad de sectores existentes.
 * \param idSector es el numero de sector correspondiente.
 * \param cadena es la variable que toma el nombre del sector, segun refencia del idSector.
 */
void obtenerSector(eSector sectores[], int tam, int idSector, char cadena[]);

/** \brief Muestra el listado completo de los empleados registrados.
 * \param lista es el listado de empleados.
 * \param tam es la cantidad limite de empleados que pueden registrarse.
 * \param sectores es el array de sectores para la distribucion de los empleados.
 * \param tamSector la cantidad de sectores existentes.
 */
void showEmployeesList(Employee lista[], int tam, eSector sectores[], int tamSector);

/** \brief Muestra el listado de los sectores con sus respectivos id y descripcion.
 * \param sectores es el array de sectores para la distribucion de los empleados.
 * \param tam es la cantidad de sectores existentes.
 */
void listarSectores(eSector sectores[], int tam);

/** \brief Ordena el listado de empleados por sector y apellido, con ese criterio de orden.
 * \param lista es el listado de empleados.
 * \param tam es la cantidad limite de empleados que pueden registrarse.
 */
void orderEmployeesListBySectorAndLastName(Employee lista[], int tam);

/** \brief Pide y valida un array de char.
 * \param String es el array en cuestion.
 * \param Ing es el texto explicito del input.
 * \param Err es el texto explicito si la validación lo pide.
 * \param Inf es limite menor de caracteres a ingresar.
 * \param Sup es el limite mayor de caracteres a ingresar.
 * \param Chances es la cantidad de oportunidades disponibles para cargar el array.
 * \return La cantidad de chances: Cero (0) si no cargó el array; Mayor o igual a Uno(>=1) si cargó el array.
 */
int getString(char string[], char ing[], char err[], int inf, int sup, int chances);

/** \brief Recorre el array buscando validar(en letras) los caracteres.
 * \param string es el array.
 * \return Retorna cero (0) si algún caracter del array NO es letra. Caso contrario retorna Uno (1).
 */
int validStrArr(char string[]);

/** \brief Pide y valida el ingreso de un entero.
 * \param *x es el puntero a entero empleado para pasar el input por referencia.
 * \param Ing es el texto explicito del input.
 * \param Err es el texto explicito si la validación lo pide.
 * \param Inf es limite menor de enteros a ingresar.
 * \param Sup es el limite mayor de enteros a ingresar.
 * \param Chances es la cantidad de oportunidades disponibles para cargar el número.
 * \return bandera: (-1) si no cargó el número; Uno (1) si cargó el número.
 */
int getInt(int *x, char ing[], char err[], int inf, int sup, int chances);

/** \brief Toma por input y valida un caracter, excluyendo letras y simbolos.
 * \param *x es el puntero a float para pasar el valor por referencia.
 * \param ing es el mensaje explicito para pedir el ingreso por input.
 * \param err es el mensaje explicito para la validacion del input.
 * \param inf es el limite inferior del rango para validar el flotante.
 * \param sup es el limite superior del rango para validar el flotante.
 * \return (0) si no obtuvo el flotante, (1) si lo obtuvo.
 */
int getFloat(float *x, char ing[], char err[], float inf, float sup, int chances);

/** \brief Toma por input y valida un caracter, excluyendo numeros y simbolos.
 * \param *x es el puntero a char para pasar el valor por referencia.
 * \param ing es el mensaje explicito para pedir el ingreso por input.
 * \param err es el mensaje explicito para la validacion del input.
 * \param inf es el limite inferior del rango para validar el caracter.
 * \param sup es el limite superior del rango para validar el caracter.
 * \return (0) si no obtuvo el caracter, (1) si lo obtuvo.
 */
int getChar(char *x, char ing[], char err[], char inf, char sup, int chances);

/** \brief Toma valores por parametro para calcular el Total y el Promedio de los sueldos.
 * \param lista es el listado de empleados.
 * \param tam es la cantidad limite de empleados que pueden registrarse.
 * \return Devuelve del promedio de sueldos.
 */
float total_y_promedio(Employee lista[], int tam);

/** \brief Busca y muestra los empleados que superan el sueldo promedio.
 * \param lista es el listado de empleados.
 * \param tam es la cantidad limite de empleados que pueden registrarse.
 * \param promedio es el promedio de sueldos.
 * \param sectores es el array de sectores para la distribucion de los empleados.
 * \param tamSector la cantidad de sectores existentes.
 */
void empleadosQueSuperanPromedio(Employee lista[], int tam, float promedio, eSector sectores[], int tamSector);

/** \brief Muestra los datos del empleado, de los cuales el usuario optara cual desea modificar.
 * \param indice es el indice donde se encuentra el registro del empleado.
 * \param sectores es el array de sectores para la distribucion de los empleados.
 * \param tamSector la cantidad de sectores existentes.
 * \return (-1) si no pudo modificar el dato. (0) si modifico correctamente el dato.
 */
int menuModificarEmpleado(Employee lista[], int indice, eSector sectores[], int tamSector);

//void harcodearEmpleados(Employee empleados[]);
/** \brief Verifica que se haya registrado al menos 1 empleado para habilitar las opciones 2, 3 y 4 del menu.
 * \param lista es el listado de empleados.
 * \param tam es la cantidad limite de empleados que pueden registrarse.
 * \return indice(-1) si no encontro registros. (indice = registro) cuando encuetre el 1er registro.
 */
int comprobarRegistro(Employee lista[], int tam);


#endif // ARRAYEMPLOYEES_H_INCLUDED
