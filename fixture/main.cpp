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
    int guardarFixture=0;

}Fixture;

typedef struct {
Fixture fixtures [10];

}Fixtures;


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

Fixtures fixtures;

void GuardarEquipos(Equipos &equiposDefinitivo){

    FILE *pEquipo;
    pEquipo = fopen ("../equipos.txt", "r");

    if(pEquipo==NULL){

        cout << "Error al intentar abrir archivo"<< endl;

        exit(1);
    }

    Equipo equipo;
    Equipos equipos;

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

    bool equipoOcupado[equipos.n];

    for(int j=0;j<equipos.n;j++){
        equipoOcupado[j]=false;
    }


    for(int i=0;i<equipos.n;i++){
       int aleatorio;
       bool ocupado=true;
       while(ocupado==true){
            aleatorio=rand()%equipos.n;
            ocupado=equipoOcupado[aleatorio];

        }

        equiposDefinitivo.equipos[aleatorio]=equipos.equipos[i];
            equipoOcupado[aleatorio]=true;

        }
    equiposDefinitivo.n=equipos.n;

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


void GenerarFixture(Equipos &equipos, Fixture &fixture){

    GuardarEquipos(equipos);

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
            for(int m1=0;m1<equipos.n/2;m1++){
                fixture.fechas[m1].laFechaFueJugada=false;
            }

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
    if (fixture.fixtureGenerado==true){

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
else{
    cout<< "Genere un fixture primero."<< endl;
    return;

}

}


void Vertabladeposiciones(Equipos &equipos, Fixture &fixture){
    int x=0;
    int j=0;
    bool asignado[equipos.n];
    Equipos equiposOrden;

    if (fixture.fixtureGenerado==true){

        Equipos equiposOrden;

        for(int i=0;i<equipos.n;i++){
           asignado[i]=false;
        }


        for(int i=0;i<equipos.n;i++){

            int maximo=-1;
            int PosMax=-1;

            for(int k=0;k<equipos.n;k++){
                if (not asignado[k]){

                    if(equipos.equipos[k].puntos>=maximo){
                        maximo=equipos.equipos[k].puntos;
                        PosMax=k;
                    }
                }
            }

            asignado[PosMax]=true;
            equiposOrden.equipos[i]=equipos.equipos[PosMax];
        }

            cout<<"TABLA DE POSICIONES"<< endl;

            cout<< "\t Equipo "<<"\t"<<"Puntos"<<" "<<"PJ"<<" "<<"PG"<<" "<<"PE"<<" "<<"PP"<<" "<<"GF"<<" "<<"GC"<<" "<<"DG"<< endl;

            for (int z=0;z<equipos.n;z++){

            //cout<< equiposOrden.equipos[z].nombre<<"\t"<<equiposOrden.equipos[z].puntos<<"\t"<<equipos.equipos[z].partidosJugados<<"  "<<equipos.equipos[z].partidosGanados<<"  "<<equipos.equipos[z].partidosEmpatados<<"  "<<equipos.equipos[z].partidosPerdidos<<"  "<<equipos.equipos[z].golesFavor<<"  "<<equipos.equipos[z].golesEncontra<<"  "<<equipos.equipos[z].diferenciaDeGoles<< endl;
            printf("%-30s%-35d\t%d\n", equiposOrden.equipos[z].nombre, equiposOrden.equipos[z].puntos,equiposOrden.equipos[z].partidosJugados);
    }


    }

    else{
        cout<< "No hay resultados."<< endl;
    }
}

void GuardarFixture(Fixture &fixture,Fixtures &fixtures){

int numero;
char sobreescribir;


    if(fixture.fixtureGenerado==true){

        cout<<" Elija donde guardar el fixture: \n 1 \n 2 \n 3 \n 4 \n 5"<< endl;
        cin>>numero;

            if(fixtures.fixtures[numero].guardarFixture==0){
                cout<<"Guardando Fixture..."<< endl;
                fixtures.fixtures[numero]=fixture;
                fixtures.fixtures[numero].guardarFixture=1;
            }

            else{
                cout<<"Ya existe un fixture en ese slot. ¿Desea sobreescribir? S/N"<< endl;
                cin>> sobreescribir;
                if((sobreescribir=='S')||(sobreescribir=='s')){

                    cout<<"Guardando Fixture..."<< endl;
                    fixtures.fixtures[numero]=fixture;
                    fixtures.fixtures[numero].guardarFixture=1;

            }
        }
    }
    else{
        cout<<"Genere un fixture"<< endl;
    }
}

void CargarFixture(Equipos equipos,Fixture &fixture,Fixtures &fixtures){
int numero=0;

cout<<"Seleccione un fixture"<< endl;
cout<< "Slot 1 \n Slot 2 \n Slot 3 \n Slot 4"<< endl;
cin>> numero;

Fixture &Fixture=fixtures.fixtures[numero];

if(fixtures.fixtures[numero].guardarFixture==1){

    GenerarFixture(equipos,Fixture);

}
else{
    cout<< "No hay ningun fixture guardado en ese slot."<< endl;
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
        GuardarFixture(fixture,fixtures);
        cout <<"Elija una opcion: "<< endl;
        }
    if(numeroseleccionado==6){
        CargarFixture(equipos,fixture,fixtures);
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
