#include "ArrayEmployees.h"

#define VACIO 1
#define OCUPADO 0

/*
Employee getEmployee(){
    Employee empleado;
    empleado.id++;
    getString(empleado.name, "Ingrese nombre: ", "Error, ingrese solo letras respetando el rango (3 a 20): ", 3, 20, 3);
    getString(empleado.lastName, "Ingrese apellido: ", "Error, ingrese solo letras respetando el rango (3 a 20): ", 3, 20, 3);
    printf("ingrese salario: ");
    scanf("%f", &empleado.salary);
    getInt(&empleado.sector, 4, "ingrese sector: ", "Error, ingrese solo numeros respetando el rango (3 a 20): ", 1, 10, 3);
    return empleado;
}*/

int menu(){ // bien!
    int opcion, control;

    system("cls");
    printf("\n*** Menu de Opciones ***\n\n");
    printf(" 1- Alta\n");
    printf(" 2- Modificacion\n");
    printf(" 3- Baja\n");
    printf(" 4- Informar\n");
    printf(" 5- Salir\n\n");

    control = getInt(&opcion, "Ingrese opcion: ", "Error, ingrese una opcion de la lista: ", 1, 5, 3);
    if(control == -1){
        opcion = 0;
    }

    return opcion;
}

void initEmployeeList(Employee* lista, int tam){
    int* contador = (int*) malloc(sizeof(int));
    for(*contador = 0; *contador < tam; (*contador)++){
        (lista+(*contador))->isEmpty = VACIO;
    }
    free(contador);
}

int addEmployee(Employee lista[], int tam, eSector sectores[], int tamSector){
    int indice, control;
    Employee nuevoEmpleado;

    indice = buscarLibre(lista, tam);
    system("cls");
    printf("*** Alta empleado ***\n\n");
    if(indice == -1){
        control = -1;
    }else{
        nuevoEmpleado.id = indice + 1;
        control = getString(nuevoEmpleado.name, "Ingrese nombre: ", "Error, ingrese solo letras respetando el rango (3 - 19): ", 3, 19, 3);
        if(control == 0){
            printf("Se agotaron las chances y no se pudo ingresar el nombre.\n");
        }else{
            control = getString(nuevoEmpleado.lastName, "Ingrese apellido: ", "Error, ingrese solo letras respetando el rango (3 - 19): ", 3, 19, 3);
            if(control == 0){
                printf("Se agotaron las chances y no se pudo ingresar el apellido.\n");
            }else{
                control = getFloat(&nuevoEmpleado.salary, "Ingrese sueldo: ", "Error, ingrese solo numeros respetando el rango (10000.00 - 40000.00): ", 10000.00, 40000.00, 3);
                if(control == 0){
                    printf("Se agotaron las chances y no se pudo ingresar el sueldo.\n");
                }else{
                    listarSectores(sectores, tamSector);
                    control = getInt(&nuevoEmpleado.sector, "Ingrese sector: ", "Error, ingrese solo numeros respetando el rango (1 - 5): ", 1, 5, 3);
                    if(control == 0){
                        printf("Se agotaron las chances y no se pudo ingresar el sueldo.\n");
                    }else{
                        nuevoEmpleado.isEmpty = OCUPADO;
                        lista[indice] = nuevoEmpleado;
                    }
                }
            }
        }
    }
    return control;
}

int ModificarEmpleado(Employee lista[], int tam, int *legajo, eSector sectores[], int tamSector){
    int indice, control, bandera;
    char seguir;

    system("cls");
    printf("  *** Modificar empleado ***\n\n");
    control = getInt(legajo, "Ingrese legajo: ", "Error, ingrese solo numeros respetando el rango (1 - 1000): ", 1, 1000, 3);
    if(control != 1){
        bandera = 0;
        printf("No se obtuvo el numero de legajo.");
    }else{
        indice = findEmployeeById(lista, tam, *legajo);
        if(indice == -1){
            bandera = -1;
        }else{
            printf("Legajo   Nombre   Apellido     Sueldo     Sector\n");
            showEmployee(lista[indice], sectores, tamSector);
            printf("\nDesea modificar algun campo? s/n: ");
            fflush(stdin);
            scanf("%c", &seguir);
            while(!(seguir == 'n' || seguir == 's' || seguir == 'N' || seguir == 'S')){
                printf("Error, solo debe ingresar 's' o 'n', reingrese: ");
                fflush(stdin);
                scanf("%c", &seguir);
            }
            if(seguir == 'n' || seguir == 'N'){
                bandera = 0;
            }else{
                bandera = menuModificarEmpleado(lista, indice, sectores, tamSector);
            }
        }
    }
    return bandera;
}

int removeEmployee(Employee lista[], int tam, int legajo, eSector sectores[], int tamSector){
    int indice, control, bandera;
    char seguir;

    system("cls");
    printf("  *** Baja empelado ***\n\n");
    control = getInt(&legajo, "Ingrese legajo: ", "Error, ingrese solo numeros respetando el rango (1 - 1000): ", 1, 1000, 3);
     if(control != 1){
        bandera = 0;
        printf("No se pudo ingresar el numero de legajo.");
    }else{
        indice = findEmployeeById(lista, tam, legajo);
        if( indice == -1){
            bandera = -1;
        }else{
            printf("Legajo  Nombre   Apellido    Sueldo     Sector\n");
            showEmployee(lista[indice], sectores, tamSector);
            printf("\nConfima baja? s/n: ");
            fflush(stdin);
            scanf("%c", &seguir);
            while(!(seguir == 'n' || seguir == 's' || seguir == 'N' || seguir == 'S')){
                printf("Error, solo debe ingresar 's' o 'n', reingrese: ");
                fflush(stdin);
                scanf("%c", &seguir);
            }
            if(seguir == 'n' || seguir == 'N'){
                bandera = 0;
            }else{
                lista[indice].isEmpty = 1;
                bandera = 1;
            }
        }
    }
    return bandera;
}

int buscarLibre(Employee lista[], int tam){
    int indice = -1;
    for(int contador=0; contador < tam; contador++){
        if( lista[contador].isEmpty == 1){
            indice = contador;
            break;
        }
    }
    return indice;
}

int comprobarRegistro(Employee lista[], int tam){
    int bandera = -1;
    for(int contador=0; contador < tam; contador++){
        if( lista[contador].isEmpty == OCUPADO){
            bandera = contador;
            break;
        }
    }
    return bandera;
}

int findEmployeeById(Employee lista[], int tam, int legajo){
    int indice = -1;
    for(int contador=0; contador < tam; contador++){
        if( lista[contador].id == legajo && lista[contador].isEmpty == OCUPADO){
            indice = contador;
            break;
        }
    }
    return indice;
}

void showEmployee(Employee lista, eSector sectores[], int tamSector){
    char descSector[20];
    obtenerSector(sectores, tamSector, lista.sector, descSector);
    printf("%4d %10s %10s     %6.2f %10s\n", lista.id, lista.name, lista.lastName, lista.salary, descSector);
}

void obtenerSector(eSector sectores[], int tam, int idSector, char cadena[]){
    for(int contador=0; contador < tam; contador++){
        if( sectores[contador].id == idSector){
            strcpy(cadena, sectores[contador].descripcion);
        }
    }
}

void showEmployeesList(Employee lista[], int tam, eSector sectores[], int tamSector){
    system("cls");
    printf("       ****  Listado de empleados  **** \n\n");
    printf("Legajo   Nombre   Apellido      Sueldo      Sector\n\n");
    for(int contador=0; contador < tam; contador++){
        if( lista[contador].isEmpty == 0){
            showEmployee(lista[contador], sectores, tamSector);
        }
    }
    printf("\n");
}

void listarSectores(eSector sectores[], int tam){
  printf("\nId  Descripcion\n");
    for(int i=0; i< tam; i++){
      printf("%d   %10s\n", sectores[i].id, sectores[i].descripcion);
    }
    printf("\n");
}
/*
void orderEmployeesListByLastName(Employee list[], int tam){
    int count, contador;
    Employee aux;
    for(count=0; count<tam-1; count++){
        for(contador=count+1; contador<tam; contador++){
            if(strcmp(list[count].lastName , list[contador].lastName)>0){
                aux = list[count];
                list[count] = list[contador];
                list[contador] = aux;
            }
        }
    }
}*/

void orderEmployeesListBySectorAndLastName(Employee list[], int tam){
    int count, contador;
    Employee aux;
    for(count=0; count<tam-1; count++){
        for(contador=count+1; contador<tam; contador++){
            if(list[count].sector > list[contador].sector){
                aux = list[count];
                list[count] = list[contador];
                list[contador] = aux;
            }else{
                if((list[count].sector == list[contador].sector) && strncmp(list[count].lastName, list[contador].lastName, 6) > 0){
                    aux = list[count];
                    list[count] = list[contador];
                    list[contador] = aux;
                }
            }
        }
    }
}

int getString(char string[], char ing[], char err[], int inf, int sup, int chances){
    int length, control;
    printf("%s", ing);
    fflush(stdin);
    gets(string);
    control = validStrArr(string); // valida que todos los caracteres del array sean letras.
    length = strlen(string); // contabiliza los caracteres del array.
    chances--;
    while((length < inf || length > sup || control == 0) && chances >= 1){
        chances--;
        printf("%s", err);
        fflush(stdin);
        gets(string);
        control = validStrArr(string);
    }
    return control; // si (control = 0) no obtuvo la cadena.
}
/*
void lowToUpStr(char string[]){
	int i=0;
	int aux='a'-'A';
	for (i=0; string[i]!='\0'; ++i){
		if(string[i] >= 'a' && string[i] <= 'z'){
			string[i] = string[i] - aux;
		}
	}
}*/

int validStrArr(char string[]){
    int aux;
    for(int count = 0; count < strlen(string); count++){ // recorre el array.
        if(!(isalpha(string[count]))){
            aux = 0; // retorna 0 si algún caracter no es letra.
            break;
        }
        aux = 1;
    }
    return aux; // retorna 1 si todos los caracteres son letras.
}

int getInt(int *x, char ing[], char err[], int inf, int sup, int chances){
    int control, bandera = 0, aux;
    printf("%s", ing);
    control = scanf("%d", &aux);
    chances--;
    while((control != 1 || aux < inf || aux > sup) && chances>=1){
        printf("%s", err);
        fflush(stdin);
        control = scanf("%d", &aux);
        chances--;
    }
    if(control == 1){
        bandera = 1;
        *x = aux;
    }
    return bandera; // si (bandera == 0) no obtuvo el entero.
}

int getFloat(float *x, char ing[], char err[], float inf, float sup, int chances){
    int control, bandera = 0;
    float aux;
    printf("%s", ing);
    control = scanf("%f", &aux);
    chances--;
    while((control != 1 || aux < inf || aux > sup) && chances>=1){
        printf("%s", err);
        fflush(stdin);
        control = scanf("%f", &aux);
        chances--;
    }
    if(control == 1){
        bandera = 1;
        *x = aux;
    }
    return bandera; // si (bandera == 0) no obtuvo el flotante.
}

int getChar(char *x, char ing[], char err[], char inf, char sup, int chances){
    int control, bandera = 0;
    char auxChar;
    printf("%s", ing);
    fflush(stdin);
    control = scanf("%c", &auxChar);
    chances--;
    while((control != 1 || auxChar < inf || auxChar > sup) && chances>=1){
        printf("%s", err);
        fflush(stdin);
        control = scanf("%c", &auxChar);
        chances--;
    }
    if(control == 1){
        bandera = 1;
        *x = auxChar;
    }
    return bandera; // si (bandera == 0) no obtuvo el caracter.
}

float total_y_promedio(Employee lista[], int tam){
    float acumSueldo=0, promedio;
    int cantEmpleados=0;
    for(int contador=0; contador<tam; contador++){
        if(lista[contador].isEmpty == OCUPADO){
            acumSueldo = (float) acumSueldo + lista[contador].salary;
            cantEmpleados++;
        }
    }
    promedio = acumSueldo / (float) cantEmpleados;
    return promedio;
}

void empleadosQueSuperanPromedio(Employee lista[], int tam, float promedio, eSector sectores[], int tamSector){
    int empleadosGanadores=0;
    printf("\n  *** Empleados que superan el sueldo promedio ***  \n\n");
    printf("Legajo   Nombre   Apellido      Sueldo      Sector\n\n");
    for(int contador=0; contador<tam; contador++){
        if(lista[contador].salary > promedio && lista[contador].isEmpty == OCUPADO){
            empleadosGanadores++;
            showEmployee(lista[contador], sectores, tamSector);
        }
    }
    printf("\nLos empleados que superan el sueldo promedio: %d", empleadosGanadores);
    fflush(stdin);
    printf("\n");
}

int menuModificarEmpleado(Employee lista[], int indice, eSector sectores[], int tamSector){ // bien!
    int opcion, nuevoSector, control;
    char nuevoNombre[20], nuevoApellido[20];
    float nuevoSueldo;
    system("cls");
    printf("\nSeleccione el campo que desea modificar: \n\n");
    printf(" 1- Nombre\n");
    printf(" 2- Apellido\n");
    printf(" 3- Salario\n");
    printf(" 4- Sector\n\n");
    control = getInt(&opcion, "Ingrese opcion: ", "Error, opcion invalida. Reingrese: ", 1, 4, 3);
    switch(opcion){
        case 1:
            control = getString(nuevoNombre, "\n\nIngrese nuevo nombre: ", "Error, ingrese solo letras respetando el rango (3 a 19): ", 3, 19, 3);
            strcpy(lista[indice].name, nuevoNombre);
            break;
        case 2:
            control = getString(nuevoApellido, "\n\nIngrese nuevo apellido: ", "\nError, ingrese solo letras respetando el rango (3 a 19): ", 3, 19, 3);
            strcpy(lista[indice].lastName, nuevoApellido);
            break;
        case 3:
            control = getFloat(&nuevoSueldo, "\n\nIngrese nuevo sueldo: ", "\nError, ingrese solo numeros respetando el rango (10000 a 40000): ", 10000, 40000, 3);
            lista[indice].salary = nuevoSueldo;
            break;
        case 4:
            listarSectores(sectores, tamSector);
            control = getInt(&nuevoSector, "\nIngrese nuevo sector: ", "Error, opcion invalida. Reingrese: ", 1, 5, 3);
            lista[indice].sector = nuevoSector;
            break;
    }
    return control;
}

/*void harcodearEmpleados(Employee empleados[]){
    Employee x[]=
    {
        {111, "juan", "perez", 23000,1,0},
        {222, "luis", "aguilar", 18000, 1, 0},
        {234, "ana", "paez", 21000, 5,0},
        {643, "melisa", "gomez", 24000, 2, 0},
        {312, "mia", "ruiz", 34000, 3, 0},
        {768, "mauro", "viale", 19000,5, 0},
        {324, "alberto", "otero", 26000, 4,0},
        {876, "valentina", "cruz", 32000,5, 0}
    };
    for(int i=0; i < 8; i++){
        empleados[i] = x[i];
    }
}*/
