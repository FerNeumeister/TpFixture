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

int numeroseleccionado;

typedef struct{   // La estructura "Tipo Partido"
    int local;
    int visitante;
}Partido;

typedef struct{  // La estructura "Tipo Fecha"
    Partido partidos[MAX_PARTIDOS];
    int cantidadPartidos;
    bool laFechaFueJugada=false;

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

    cin >> numeroseleccionado;

}


void GenerarFixture(const Equipos &equipos, Fixture &fixture){


    if((equipos.n%2)==0){
        fixture.cantidadFechas=equipos.n-1;
    }
    else{
        fixture.cantidadFechas=equipos.n;
    }

    for (int i=0;i<=fixture.cantidadFechas;i++){

        Fecha &fecha = fixture.fechas[i];

        cout << "Fecha: " << i+1 << endl;

        fecha.cantidadPartidos=equipos.n/2;
        for(int j=0;j<fecha.cantidadPartidos;j++){

            Partido &partido = fecha.partidos[j];
            generarPartido(equipos.n,i+1,j+1,partido.local,partido.visitante);
            cout <<"Partido: "<< j+1 <<" " << equipos.equipos[partido.local].nombre << "-" << equipos.equipos[partido.visitante].nombre<< endl;

        }
    }

}


void SimularPartido(Equipos &equipos, Fixture &fixture){

    int i=0;
    int j=0;
    int m=0;
    char continuar='a';
    int golesLocal;
    int golesVisitante;



    cout << "Ingrese una fecha: "<< endl;

    cin >> j;

    if (fixture.fechas[j].laFechaFueJugada==true){

        cout<< "La fecha"<< j << "ya fue simulada. ¿Continuar? S/N"<< endl;
        cin>> continuar;

        if((continuar=='S')||(continuar=='s')){

            cout << "estamos Simulando nuevamente"<< endl;
        }

}
    else {

        for (int m=1;m<=j;m++){

            Fecha &fecha = fixture.fechas[m];
            fecha.cantidadPartidos=equipos.n/2;
            cout<< "\n" << "SIMULANDO FECHA  "<< m << "\n"<< endl;
            fecha.laFechaFueJugada=true;

            for (int i=1;i<=fecha.cantidadPartidos;i++){

                Partido &partido = fecha.partidos[i];
                cout << "PARTIDO  "<< i << endl;

                Equipo &Local=equipos.equipos[partido.local];
                Equipo &Visitante=equipos.equipos[partido.visitante];

                simularPartido(Local.paramA,Local.paramB,Visitante.paramA,Visitante.paramB,golesLocal,golesVisitante);

                cout<< equipos.equipos[partido.local].nombre <<" "<<golesLocal<<"-"<<" "<< golesVisitante <<equipos.equipos[partido.visitante].nombre<< endl;


                if (golesLocal==golesVisitante){
                    Local.puntos++;
                    Visitante.puntos++;
                }
                else{
                    if(golesLocal<golesVisitante){
                        Visitante.puntos+3;
                }
                    else{
                        Local.puntos+3;
                }
            }
        }
    }
}

    cout<<"\n"<< "SIMULACION TERMINADA "<< endl;

}


void VerEquipo(Equipos equipos, Fixture fixture){

    int numeroDeEquipo=0;

    cout<< "Elija un equipo: "<< endl;

    for (int i=0;i<equipos.n;i++){
        cout<<i+1<<":"<< equipos.equipos[i].nombre<< endl;
    }
    cin>> numeroDeEquipo;




}



void SeleccionDeOpcion(int numeroseleccionado, Equipos equipos, Fixture &fixture){

    while (numeroseleccionado!=7){
    if (numeroseleccionado==1){
        GenerarFixture(equipos,fixture);
        cout <<"Elija una opcion: "<< endl;
        }
    if (numeroseleccionado==2){
        SimularPartido(equipos,fixture);
        cout <<"Elija una opcion: "<< endl;
        }
    if (numeroseleccionado==3){
        VerEquipo(equipos,fixture);
        cout <<"Elija una opcion: "<< endl;
        }
    if(numeroseleccionado==4){
        //Vertabladeposiciones();
        cout <<"Elija una opcion: "<< endl;
        }
    if(numeroseleccionado==5){
        //GuardarFixture();
        cout <<"Elija una opcion: "<< endl;
        }
    if(numeroseleccionado==6){
        //CargarFixture();
        cout <<"Elija una opcion: "<< endl;
        }
        cin>>numeroseleccionado;
    if(numeroseleccionado==7){}
    }
}



int main()
{
    Fixture fixture;
    srand (time(NULL));
    Equipos equipos;


    GuardarEquipos(equipos);

    GenerarInterfaz();

    SeleccionDeOpcion(numeroseleccionado,equipos,fixture);



    return 0;
}
