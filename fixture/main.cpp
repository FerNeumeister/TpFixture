#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include "../torneo.h"
#include <cstring>

#define MAX_EQUIPOS 100
#define MAX_PARTIDOS (MAX_EQUIPOS/2)
#define MAX_FECHAS MAX_EQUIPOS

using namespace std;

int Numeroseleccionado;

typedef struct{   // La estructura "Tipo Partido"
    int local;
    int visitante;
}Partido;

typedef struct{  // La estructura "Tipo Fecha"
    Partido partidos[MAX_PARTIDOS];
    int cantidadPartidos;
    bool laFechaFueJugada;

}Fecha;

typedef struct {  // Estructura de "Tipo Fixture"
    Fecha fechas [MAX_FECHAS];
    int cantidadFechas;

}Fixture;


typedef struct{
    char nombre [31];
    int paramA;
    int paramB;
    int puntos;
} Equipo;

typedef struct{
    Equipo equipos[MAX_EQUIPOS];
    int n;
}Equipos;


void GuardarEquipos(Equipos &equipos){

    FILE *pEquipo;
    pEquipo = fopen ("../equipos.txt", "r");

    if(pEquipo==NULL){

        cout << "Error al intentar abrir archivo"<< endl;

        exit(1);
    }

    Equipo equipo;

    equipos.n=0 ;

    while (leerEquipo(pEquipo,equipo.nombre,equipo.paramA,equipo.paramB)){

        equipos.equipos[equipos.n].paramA=equipo.paramA;
        equipos.equipos[equipos.n].paramB=equipo.paramB;
        strcpy(equipos.equipos[equipos.n].nombre,equipo.nombre);
     //   cout << equipo.nombre<< endl;
     //   cout << equipos.equipos[equipos.n].nombre<< endl;
        equipos.n++;

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


void GenerarFixture(const Equipos &equipos, Fixture &fixture){


    if((equipos.n%2)==0){
        fixture.cantidadFechas=equipos.n-1;
    }
    else{
        fixture.cantidadFechas=equipos.n;
    }

    for (int i=0;i<fixture.cantidadFechas;i++){

        Fecha &fecha = fixture.fechas[i];

        cout << "Fecha: " << i << endl;

        fecha.cantidadPartidos=equipos.n/2;
        for(int j=0;j<fecha.cantidadPartidos;j++){

            Partido &partido = fecha.partidos[j];
            generarPartido(equipos.n,i+1,j+1,partido.local,partido.visitante);
            cout <<"Partido: "<< j <<" " << equipos.equipos[partido.local].nombre << "-" << equipos.equipos[partido.visitante].nombre<< endl;
        }
    }


}


void SimularPartido(Equipo equipos, Fixture fixture){

int i=0;
int j=0;
int x=0;
char continuar=a;


cout << "Ingrese una fecha: "<< endl;

cin >> fixture.fechas[j];

if (fixture.fechas[j].laFechaFueJugada=True){

        cout<< "La fecha"<< j << "ya fue simulada. ¿Continuar? S/N" endl;
        cin>> continuar;

        if(continuar==S||s){

            cout<< "estamos Simulando viejitaaa"<< ;
        }
        else{
            exit (1);
        }
}
else{


    for(x;x<j+1;x++){

        for(i;i<equipos.n/2;i++){

            simularPartido(equipos[i].paramA,equipos[i].paramB,equipos[i+1].paramA,equipos[i+1].paramB)

            if (goleslocal==golesVisitante){

                    equipos[i].puntos+1;
                    equipos[i+1].puntos+1;
            }
            if (goleslocal>golesVisitante){

                    equipos[i].puntos+3

            }
            else{
                    equipos[i+1].puntos+3
            }
        }

        fixture.fechas[j].laFechaFueJugada=true
    }

}






//for (i;i<equipos.n/2;i){

  //  simularPartido(equipos.equipos[i].paramA,equipos.equipos[i].paramB,equipos.equipos[i++].paramA,equipos.equipos[i++].paramB,);

}


void SeleccionDeOpcion(int Numeroseleccionado,const Equipos &equipos, Fixture &fixture){

    if(Numeroseleccionado==1){

    GenerarFixture(equipos,fixture);
}
    else {
        if (Numeroseleccionado==2){

            SimularPartido(equipos, fixture)


        }
    }
    }


void InicializarSimulacion (Fixture fixture){
    int p;

    for (p=0;p<MAX_FECHAS;p++){

        fixture.fechas[p].laFechaFueJugada=false;
    }


}

void InicializarPuntos (Equipo equipos){
    int p;

    for (p=0;p<MAX_EQUIPOS;p++){

       equipos[p].puntos=0;
    }
}


int main()
{
    Fixture fixture;
    srand (time(NULL));
    Equipos equipos;


    GuardarEquipos(equipos);

    GenerarInterfaz();

    InicializarPuntos(equipos)

    InicializarSimulacion(fixture);

    SeleccionDeOpcion(Numeroseleccionado,equipos,fixture);


    return 0;
}
