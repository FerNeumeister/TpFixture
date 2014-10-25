#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include "../torneo.h"
#include <cstring>

using namespace std;

int Numeroseleccionado;

void GuardarEquipos(){

    FILE *pEquipo;
    pEquipo = fopen ("../equipos.txt", "r");

    if(pEquipo==NULL){

        cout << "Error al intentar abrir archivo"<< endl;

        exit(1);
    }

    typedef struct{
        char nombre [31];
        int paramA;
        int paramB;
    } Equipo;


    // tipo verctor enteros
    typedef struct{
        Equipo equipos[100];

    }Equipos;

    Equipo equipo;
    Equipos equipos;

    int n=0;

    while (leerEquipo(pEquipo,equipo.nombre,equipo.paramA,equipo.paramB)){

        equipos.equipos[n].paramA=equipo.paramA;
        equipos.equipos[n].paramB=equipo.paramB;
        strcpy(equipos.equipos[n].nombre,equipo.nombre);
        n++;

    }

    fclose(pEquipo);
}


void GenerarInterfaz (){

    cout << "1. Generar Fixture." << endl;
    cout << "2. Simular partidos."<< endl;
    cout << "3. Ver equipos." << endl;
    cout << "4. Ver tabla de posiciones" << endl;
    cout << "5. Guardar fixture"<< endl;
    cout << "6. Cargar Fixture"<< endl;
    cout << "7. Salir"<< endl;
    cout << "Elija una opcion:"<< endl;

    cin >> Numeroseleccionado;

}

void GenerarFixture(){







}

void SimularPartido(){
cout << "Simulando Partido"<< endl;
}

void SeleccionDeOpcion(int Numeroseleccionado){

    if(Numeroseleccionado==1){

    GenerarFixture();
}
    else {
        if (Numeroseleccionado==2){

    SimularPartido();


        }
    }
    }


int main()
{
    srand (time(NULL));

    GuardarEquipos();

    GenerarInterfaz();

    SeleccionDeOpcion(Numeroseleccionado);


    return 0;
}
