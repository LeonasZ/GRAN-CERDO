#include <iostream>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include "rlutil.h"
#include <windows.h>
#include "funciones.h"
using namespace std;

///MENU DE INICIO


int main(){
rlutil::hidecursor();
HANDLE hconsole= GetStdHandle(STD_OUTPUT_HANDLE);
srand(time(NULL));


    int op=0; //variable para seleccionar una opcion dentro del menu principal
    char confirm; //usado para confirmar salir del juego
    string ganador;
    int PDV;


    //inicializo las estadisticas con un relleno para que muestre algo en caso de ingresar antes de comenzar un juego.
    ganador="SIN CERDOS";
    PDV=0;


    int y=0; //variable que me va a marcar la posicion del cursor

    //uso un ciclo para que no se corte la ejecucion del programa a menos que el jugador decida salir
        do {
            rlutil::locate(1,20);
            icono();



            encuadrar_texto("GRAN CERDO",100,1);
            linea(4);
            encuadrar_texto("UTN FRGP",1,1);

            rlutil::locate(53,13);
            cout << " JUGAR";
            rlutil::locate(53,14);
            cout << " ESTADISTICAS";
            rlutil::locate(53,15);
            cout << " CREDITOS";
            rlutil::locate(53,16);
            cout << " SALIR";

            rlutil::locate(52,13+y);
            cout<<(char)254;            //cursor de y que se mueve


            switch(rlutil::getkey()){
            case 14: //flecha arriba
                rlutil::locate(52,13+y);
                cout<<" ";
                y--;                    //resta y para que resten filas
                if(y<0){
                    y=0; //minimo valor de y
                }
                break;
            case 15: //flecha abajo
                rlutil::locate(52,13+y);
                cout<<" ";
                y++;                     //suma y para bajar en filas
                if(y>3){
                    y=3; //maximo valor de y
                }
                break;
            case 1: //enter
                switch(y){
                case 0:
                    //llama a la funcion que da inicio al juego
                    Jugar(ganador,PDV);
                    rlutil::cls();
                    break;
                case 1:
                    //llama a la funcion que muestra estadisticas
                    Estadisticas(ganador,PDV);
                    rlutil::cls();
                    break;
                case 2:
                    //llama a la funcion que muestra creditos
                    Creditos();
                    rlutil::cls();
                    break;
                case 3:
                    cout << endl << "ESTAS SEGURO QUE DESEAS SALIR? S/N" << endl << endl;
                    //uso un ciclo para asegurarme de que el jugador no use nada distinto de s/S/n/N
                    do {
                        cin >> confirm;
                    if (confirm != 's' && confirm != 'S' && confirm != 'n' && confirm != 'N'){
                        cout << "LAS OPCIONES SON S/N";
                    }
                    } while (confirm != 's' && confirm != 'S' && confirm != 'n' && confirm != 'N');

                    if (confirm == 's' || confirm == 'S'){
                    rlutil::locate(1,19);
                    cout << "FIN...";
                    op=3;
                    }
                    else{
                        rlutil::cls(); //si no desea salir, borra los mensajes y vuelve al menu
                    }

                    break;
                }
            }

        }while(op!=3);

        return 0;
    }

