//
//  torneo.cpp
//  PruebaC
//
//  Created by Emanuel Andrada on 09/10/14.
//  Copyright (c) 2014 Emanuel Andrada. All rights reserved.
//

#include "torneo.h"
#include <cstdlib>
#include <math.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 1024

bool leerEquipo(FILE *archivo, char nombre[31], int &paramA, int &paramB)
{
    int i;
    char buff[BUFFER_SIZE];
    fscanf(archivo, "%d %d %d", &i, &paramA, &paramB);
    fgets(buff, BUFFER_SIZE, archivo);
    strncpy(nombre, buff, 30);
    size_t len = strlen(nombre);
    if (len > 0 && nombre[len - 1] == '\n') {
        nombre[len - 1] = '\0';
    }
    return !feof(archivo);
}

void generarPartido(int equipos, int fecha, int partido, int &local, int &visitante)
{
    local = equipos + fecha - partido;
    visitante = equipos + fecha + partido;
    if (equipos % 2 == 0) {
        if (fecha < partido - 1) {
            visitante--;
        }
        else if (fecha * 2 >= equipos && fecha + partido >= equipos) {
            local++;
        }
        else if (partido - fecha == 1 || partido + fecha == equipos - 1) {
            local = fecha;
            visitante = equipos - 1;
        }
    }
    if (fecha % 2 == 0) {
        int aux = local;
        local = visitante;
        visitante = aux;
    }
    local = local % equipos;
    visitante = visitante % equipos;
}

int generarNumeroAleatorio()
{
    return rand()%2;
    //return .5;
}

void simularPartido(int localA, int localB, int visitanteA, int visitanteB, int &golesLocal, int &golesVisitante)
{
    golesLocal = round((double)(localA + visitanteB) * .003 * pow(generarNumeroAleatorio(), 2) * generarNumeroAleatorio());
    golesVisitante = round((double)(visitanteA + localB) * .003 * pow(generarNumeroAleatorio(), 2) * generarNumeroAleatorio());
}
