#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int Numeroseleccionado;

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
 cout << "Generando fixture"<< endl;

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

    GenerarInterfaz();

    SeleccionDeOpcion(Numeroseleccionado);


    return 0;
}
