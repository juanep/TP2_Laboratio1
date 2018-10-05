#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Empleados.h"

#define TAM 999
#define VACIO 1
#define OCUPADO 0

//void entero(int *x);
int main()
{
    char resp = 's';
    int control, legajo, bandera=0;
    float sueldoPromedio;
    eSector sectores[]={
        {1, "RRHH"},
        {2, "Ventas"},
        {3, "Compras"},
        {4, "Contable"},
        {5, "Sistemas"}
    };
    employee empleados[TAM];

    initEmployeeList(empleados, TAM);
    //harcodearEmpleados(empleados);

    do{
        switch(menu()){
            case 1:
                control = addEmployee(empleados, TAM, sectores, 5);
                if(control == -1){
                    printf("No hay lugar en el sistema.\n\n");
                }else if(control == 0){
                    printf("Registro cancelado.\n\n");
                }else{
                    printf("Empleado registrado con exito!!\n\n");
                }
                system("pause");
                break;
            case 2:
                control = comprobarRegistro(empleados, TAM);
                if(control == -1){
                    printf("\nHasta el momento no se ha registrado ningun empleado.\n\n");
                }else{
                    control = ModificarEmpleado(empleados, TAM, &legajo, sectores, 5);
                    if(control == -1){
                    printf("No hay ningun empleado con el legajo Nro. %d\n\n", legajo);
                    }else if(control == 0){
                    printf("Modificacion cancelada.\n\n");
                    }else{
                    printf("Modificacion exitosa!!\n\n");
                    }
                }
                system("pause");
                break;
            case 3:
                control = comprobarRegistro(empleados, TAM);
                if(control == -1){
                    printf("\nHasta el momento no se ha registrado ningun empleado.\n\n");
                }else{
                    control = bajaEmpleado(empleados, TAM, legajo, sectores, 5);
                    if(control == -1){
                        printf("No hay ningun empleado de legajo %d\n\n", legajo);
                    }else if(control == 0){
                        printf("Baja cancelada\n\n");
                    }else{
                        printf("Baja exitosa!\n\n");
                    }
                }
                system("pause");
                break;
            case 4:
                control = comprobarRegistro(empleados, TAM);
                if(control == -1){
                    printf("\nHasta el momento no se ha registrado ningun empleado.\n\n");
                }else{
                    sueldoPromedio = total_y_promedio(empleados, TAM);
                    orderEmployeesListBySectorAndLastName(empleados, TAM);
                    showEmployeesList(empleados, TAM, sectores, 5);
                    printf("El sueldo promedio es: %6.2f\n", sueldoPromedio);
                    empleadosQueSuperanPromedio(empleados, TAM, sueldoPromedio, sectores, 5);
                }
                system("pause");
                break;
            case 5:
                printf("\nSalir.\n\n");
                system("pause");
                printf("\n\n");
                bandera = 1;
                break;
            default:
                printf("\nOpcion incorrecta!!\n\n");
                system("pause");
        }
        if(bandera == 1){
            resp = 'n';
        }else{
            getChar(&resp, "\nDesea continuar? ... s/n: ", "Error, ingrese solo 's' o 'n': ", 'A', 'z', 3);
        }
    }while(resp == 's');

    return 0;
}

