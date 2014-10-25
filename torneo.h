//
//  torneo.h
//  PruebaC
//
//  Created by Emanuel Andrada on 09/10/14.
//  Copyright (c) 2014 Emanuel Andrada. All rights reserved.
//

#ifndef __PruebaC__torneo__
#define __PruebaC__torneo__

#include <stdio.h>

#define NOMBRE_MAX_LEN  (30 + 1)

/// Lee un equipo desde un archivo de texto
/// La línea en el archivo debe tener el siguiente formato:
///    indice paramA paramB nombre_equipo
/// indice se ignora (solo para contar más fácil en el archivo)
/// parámetros:
///     archivo         un archivo de texto abierto para lectura
///     nombre          el nombre del equipo (salida)
///     paramA          paramA del equipo (salida)
///     paramB          paramB del equipo (salida)
bool leerEquipo(FILE *archivo, char nombre[NOMBRE_MAX_LEN], int &paramA, int &paramB);

/// Devuelve los equipos participantes en un partido dados la fecha y orden de partido.
/// Si hay un número impar de equipos la cantidad de fechas es igual a la de equipos.
/// Si hay un número par de equipos la cantidad de fechas es igual a la de equipos - 1.
/// La cantidad de partidos es igual a la mitad de la cantidad de equipos,
/// redondeando hacia abajo.
/// parámetros:
///     equipos         la cantidad de equipos en el torneo
///     fecha           la fecha que se quiere generar (1 a fechas)
///     partido         el numero de orden del partido (1 a partidos)
///     local           el indice de equipo local (0 a equipos - 1) (salida)
///     visitante       el indice de equipo visitante (0 a equipos - 1) (salida)
void generarPartido(int equipos, int fecha, int partido, int &local, int &visitante);

/// Simula los resultados de un partido.
/// parámetros:
///     localA          paramA del equipo local
///     localB          paramB del equipo local
///     visitanteA      paramA del equipo visitante
///     visitanteB      paramB del equipo visitante
///     golesLocal      goles del equipo local (salida)
///     golesVisitante goles del equipo visitante (salida)
void simularPartido(int localA, int localB, int visitanteA, int visitanteB, int &golesLocal, int &golesVisitante);

#endif /* defined(__PruebaC__torneo__) */
