#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <iostream>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include "rlutil.h"
#include <windows.h>

//-----------
///FUNCIONES
//-----------


//comienza el juego
void Jugar(std::string &ganador, int &PDV);
//cuadro de estadisticas
void Estadisticas(std::string ganador, int PDV);
//cuadro creditos
void Creditos();
//tira los dados recibiendo el vector y la cantidad de dados
void tirar_dados(int vec_dados[],int cantdados);
//resetea el vector de dados en 0
void resetear_dados(int vec_dados[],int cantdados);
//esta dentro de jugar, me dice quien empieza la ronda 1
int quien_empieza(std::string njg1,std::string njg2,int vec_dados[],int cantdados);
//es el desarrollo del juego se repite con un for 10 veces
void desarrollar_ronda(int vec_hitos[],bool &turno,int ronda[],std::string nombrejugador, int cantdados,bool &barro,int lanzamientos,int vec_dados[],std::string njg1,std::string njg2,bool &porky1,bool &porky2);
//me dibuja los dados
void dibujar_dados(int vec_dados[],int cantdados);
//las siguientes 6 funciones contienen la construccion de cada dado
void one();
void two();
void three();
void four();
void five();
void six();

//es llamado cuando finaliza el for de 10 iteraciones, muestra los hitos y el ganador
void tabla_ganador(int vec_hitos[],std::string njg1,std::string njg2,std::string &ganador, int &PDV,bool porky1,bool porky2);
//me hace una linea de 120 guiones pasandole la posicion de y que quiero
void linea(int posy);
//me hace un cuadrado
void encuadrar(int posx,int posy,int ancho,int alto);
//usa la funcion encuadrar, donde le paso un texto y a donde quiero que lo coloque en x e y
void encuadrar_texto(std::string texto,int x,int y);
//el chanchito
void icono();
//muestra las trufas de ambos jugadores antes de cada ronda
void mostrar_trufas(int vec_hitos[],std::string njg1,std::string njg2);

#endif // FUNCIONES_H_INCLUDED
