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
    int golesLocal;
    int golesVisitante;
}Partido;

typedef struct{  // La estructura "Tipo Fecha"
    Partido partidos[MAX_PARTIDOS];
    int cantidadPartidos;
    bool laFechaFueJugada=false;

}Fecha;

typedef struct {  // Estructura de "Tipo Fixture"
    Fecha fechas [MAX_FECHAS];
    int cantidadFechas;
    bool fixtureGenerado=false;

}Fixture;


typedef struct{
    char nombre [31];
    int paramA;
    int paramB;
    int puntos=0;
    int partidosJugados=0;
    int partidosGanados=0;
    int partidosEmpatados=0;
    int partidosPerdidos=0;
    int golesFavor=0;
    int golesEncontra=0;
    int diferenciaDeGoles=0;
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

    char generarotravez='a';

    if (fixture.fixtureGenerado==true){

        cout<< "Fixture ya generado. ¿Generar otra vez?-S/N"<< endl;
        cin>>generarotravez;
        if((generarotravez=='s')||(generarotravez=='S')){


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
    else {
        return;
    }
        fixture.fixtureGenerado=true;
        }
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
        fixture.fixtureGenerado=true;
}


void SimularPartido(Equipos &equipos, Fixture &fixture){

    int i=0;
    int j=0;
    int m=0;
    char continuar='a';
    int golesLocal;
    int golesVisitante;

    if (fixture.fixtureGenerado==false){
        cout<<"No hay partidos para simular."<<"\n"<<"Por favor, genere un fixture primero."<< endl;
        return;
    }
    cout << "Ingrese una fecha: "<< endl;

    cin >> j;


    if (fixture.fechas[j].laFechaFueJugada==true){

        cout<< "La fecha"<< j << "ya fue simulada. ¿Continuar? S/N"<< endl;
        cin>> continuar;

        if((continuar=='S')||(continuar=='s')){

            cout << "estamos Simulando nuevamente"<< endl;

        }
    }
    if(j<=20) {

        for (int m=0;m<j;m++){

            fixture.fechas[m].laFechaFueJugada=true;
            Fecha &fecha = fixture.fechas[m];
            fecha.cantidadPartidos=equipos.n/2;
            cout<< "\n" << "SIMULANDO FECHA  "<< m+1 << "\n"<< endl;

            for (int i=0;i<fecha.cantidadPartidos;i++){

                Partido &partido = fecha.partidos[i];
                cout << "PARTIDO  "<< i+1 << endl;

                Equipo &Local=equipos.equipos[partido.local];
                Equipo &Visitante=equipos.equipos[partido.visitante];

                simularPartido(Local.paramA,Local.paramB,Visitante.paramA,Visitante.paramB,golesLocal,golesVisitante);

                cout<< equipos.equipos[partido.local].nombre <<" "<<golesLocal<<"-"<<" "<< golesVisitante <<equipos.equipos[partido.visitante].nombre<< endl;

                partido.golesLocal=golesLocal;
                partido.golesVisitante=golesVisitante;

                if (golesLocal==golesVisitante){
                    Local.puntos++;
                    Visitante.puntos++;

                    Local.partidosEmpatados++;
                    Local.partidosJugados++;
                    Visitante.partidosJugados++;
                    Visitante.partidosEmpatados++;

                    Local.golesFavor=Local.golesFavor+golesLocal;
                    Visitante.golesFavor=Visitante.golesFavor+golesVisitante;

                    Local.golesEncontra=Local.golesEncontra+golesVisitante;
                    Visitante.golesEncontra=Visitante.golesEncontra+golesLocal;


                }
                    if(golesLocal<golesVisitante){
                        Visitante.puntos=Visitante.puntos+3;
                        Visitante.partidosJugados++;
                        Local.partidosJugados++;
                        Visitante.partidosGanados++;
                        Local.partidosPerdidos++;

                        Visitante.golesFavor=Visitante.golesFavor+golesVisitante;
                        Local.golesFavor=Local.golesFavor+golesLocal;
                        Visitante.golesEncontra=Visitante.golesEncontra+golesLocal;
                        Local.golesEncontra=Local.golesEncontra+golesVisitante;


                        Visitante.diferenciaDeGoles=Visitante.diferenciaDeGoles+(golesVisitante-golesLocal);

                }
                    if (golesLocal>golesVisitante){
                        Local.puntos=Local.puntos+3;
                        Visitante.partidosJugados++;
                        Local.partidosJugados++;
                        Visitante.partidosGanados++;
                        Local.partidosPerdidos++;

                        Visitante.golesFavor=Visitante.golesFavor+golesVisitante;
                        Local.golesFavor=Local.golesFavor+golesLocal;
                        Visitante.golesEncontra=Visitante.golesEncontra+golesLocal;
                        Local.golesEncontra=Local.golesEncontra+golesVisitante;

                        Local.diferenciaDeGoles=Local.diferenciaDeGoles+(golesLocal-golesVisitante);
                    }


            }
        }


    }
    else{
        cout<< "La fecha "<< j <<" no es valida.Ingrese una fecha no mayor a "<< fixture.cantidadFechas+1 << endl;
        return;
        }

cout<<"\n"<< "SIMULACION TERMINADA \n "<< endl;
}



void VerEquipo(Equipos &equipos, Fixture &fixture){

    int numeroDeEquipo=0;

    cout<< "Elija un equipo: "<< endl;

    for (int variante=0;variante<equipos.n;variante++){

        cout<< variante+1 <<": "<< equipos.equipos[variante].nombre<< endl;
    }
    cin>> numeroDeEquipo;
    cout<<"Partidos de -"<<equipos.equipos[numeroDeEquipo-1].nombre<< endl;

    for (int j=0;j<fixture.cantidadFechas;j++){
        if(fixture.fechas[j].laFechaFueJugada==true){

            Fecha  &fecha=fixture.fechas[j];
            Equipo &Elegido=equipos.equipos[numeroDeEquipo-1];


              for (int i=0;i<=fecha.cantidadPartidos;i++){

                Partido &partido = fecha.partidos[i];
                Equipo &Local=equipos.equipos[fecha.partidos[i].local];
                Equipo &Visitante=equipos.equipos[fecha.partidos[i].visitante];

                if((Elegido.nombre==Local.nombre)||(Elegido.nombre==Visitante.nombre)){ //Problema a Resolver

                    cout<<Local.nombre<<" "<<partido.golesLocal<<"-"<<partido.golesVisitante<<" "<<Visitante.nombre<< endl;

                }
            }
        }

    }
    return;
}



void Vertabladeposiciones(Equipos equipos, Fixture &fixture){
    int aux=0;
    int j=0;
    int l=0;
    int x=0;

    Equipo Ordenados[equipos.n];

    for(int x=1;x<equipos.n;x++){

        Ordenados[x].puntos=0;
        cout<< Ordenados[x].puntos<< endl;
    }

    Equipo &Equipos=equipos.equipos[l];
        for (int j;j<equipos.n;j++){
        for (int l;l<equipos.n;l++){

            if(Ordenados[j].puntos<Equipos.puntos){

                Ordenados[j].puntos=Equipos.puntos;

            }
        }
        }
    for (int k=0;k<20;k++){
        cout<< Ordenados[k].puntos<< endl;
    }
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
        Vertabladeposiciones(equipos,fixture);
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
