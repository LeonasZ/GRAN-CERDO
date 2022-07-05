
#include "funciones.h"
using namespace std;

//Funcion que muestra el cuerpo de las estadisticas
    void Estadisticas(string ganador, int PDV){
        HANDLE hconsole= GetStdHandle(STD_OUTPUT_HANDLE);
        rlutil::cls();

        rlutil::locate(1,20);
        icono();
        encuadrar_texto("GRAN CERDO",100,1);
        linea(4);
        encuadrar_texto("ESTADISTICAS",1,1);

        rlutil::locate(45,13);
        cout<<"GANADOR HISTORICO CON MAYOR PDV";
        rlutil::locate(52,15);
        cout<<ganador<<endl;
        if(PDV!=0){
            rlutil::locate(52+ganador.size(),15);
            cout<<" PDV: "<<PDV;
        }
        //bloquesito adorno
        SetConsoleTextAttribute(hconsole,3);
        rlutil::locate(50,15);
        cout<<(char)254;
        SetConsoleTextAttribute(hconsole,5);


        rlutil::anykey();
    }



//funcion que muestra el cuerpo de creditos
    void Creditos(){
        HANDLE hconsole= GetStdHandle(STD_OUTPUT_HANDLE);
        rlutil::cls();
        rlutil::locate(1,20);
        icono();
        encuadrar_texto("GRAN CERDO",100,1);
        linea(4);
        encuadrar_texto("CREDITOS",1,1);
        rlutil::locate(53,13);
        cout<<"CERDITOS";
        SetConsoleTextAttribute(hconsole,3);
        rlutil::locate(45,15);
        cout<<(char)254<<" ZIDONIS, LEONAS. LEG 26867";
        SetConsoleTextAttribute(hconsole,5);

        rlutil::anykey();

    }


//funcion que inicia el juego
    void Jugar(string &ganador, int &PDV){
    rlutil::cls();
    HANDLE hconsole= GetStdHandle(STD_OUTPUT_HANDLE);
    encuadrar_texto("GRAN CERDO",100,1);
    linea(4);
    encuadrar_texto("UTN FRGP",1,1);
    SetConsoleTextAttribute(hconsole,12);
    string  njg1,njg2; //nombres de los jugadores
    int cantdados=2; //cantidad de dados con los que empezamos
    int vec_dados[3]={}; //vector que guarda la tirada de los dados, lo inicializo en 0
    bool turno; //usado para indicar de quien es el turno
    bool barro=false; //usado para saber si alguno se hundio en el barro
    int vec_ronda[2]; //vector que cuenta las rondas de ambos
    int vec_hitos[8]={};
    int empieza; //me sirve para el comienzo de la ronda
    bool activar=false; // una vez que se activaron los 3 dados se activa y deja de mencionar los 3 dados
    /*vector donde se guarda lo siguiente:
    0:TRUFAS JG1 - 1:cantidad de oinks JG1 - 2 Mayor numero de lanzamientos en una misma ronda JG1 - 3 PuntosDeVictoria JG1

    4:TRUFAS JG2 - 5:cantidad de oinks JG2 - 6 Mayor numero de lanzamientos en una misma ronda JG2 - 7 PuntosDeVictoria JG2
    */
    int lanzamientos=0; //conteo de lanzamientos realizados en la ronda del jugador actual
    bool porky1=false,porky2=false;

    rlutil::locate(1,5);
    cout << endl << "COMENZANDO PARTIDA..." << endl << endl;
    rlutil::locate(1,8);
    cout<<"NOMBRE JUGADOR 1:";
    rlutil::locate(19,8);
    cin>>njg1;

    rlutil::locate(1,9);
    cout<<"NOMBRE JUGADOR 2:";
    rlutil::locate(19,9);
    cin>>njg2;


    //para ver quien empieza la ronda se tiran los dados
    do{

        empieza=quien_empieza(njg1,njg2,vec_dados,cantdados);

        if(empieza==1){
            cout<<njg1<<" COMENZARA LA RONDA 1..."<<endl;
            turno=1;
        }
        else if(empieza==0){
            cout<<njg2<<" COMENZARA LA RONDA 1..."<<endl;
            turno=0;
        }
        resetear_dados(vec_dados,cantdados);

    }
    while(empieza==3);
    SetConsoleTextAttribute(hconsole,12);

    vec_ronda[0]=1;
    vec_ronda[1]=1;

    rlutil::anykey();
    rlutil::cls();


    for (int i=0;i<=9;i++){

        //con turno se define que jugador puede accionar y mientras no cambie de estado continua siendo el turno del jugador actual (asi se le da la posibilidad de volver a tirar si los dados son diferentes entre si y distintos de 1)
        if (turno == true){
            while (turno == true){
                if ((barro == true || vec_hitos[0]>=50 || vec_hitos[4]>=50) && (activar==false)){
                    //si algun cerdo se hundio en el barro o supero las 50 trufas, se juega con 3 dados
                    cantdados=3;
                    SetConsoleTextAttribute(hconsole,11);
                    cout<<endl<<"3 DADOS ACTIVADOS."<<endl;
                    SetConsoleTextAttribute(hconsole,12);
                    activar=true;

                }

                lanzamientos++;

                desarrollar_ronda(vec_hitos,turno,vec_ronda,njg1,cantdados,barro,lanzamientos,vec_dados,njg1,njg2,porky1,porky2);

                if (turno == false){
                    lanzamientos = 0; //reseteo la cantidad de lanzamientos para pasar a contar los del siguiente jugador
                }
            }

        } else {
            while (turno == false){
                if ((barro == true || vec_hitos[0]>=50 || vec_hitos[4]>=50) && (activar==false)){
                    //si algun cerdo se hundio en el barro o supero las 50 trufas, se juega con 3 dados
                    cantdados = 3;
                    SetConsoleTextAttribute(hconsole,11);
                    cout<<endl<<"3 DADOS ACTIVADOS."<<endl;
                    SetConsoleTextAttribute(hconsole,12);
                    activar=true;
                }


                lanzamientos++;

                desarrollar_ronda(vec_hitos,turno,vec_ronda,njg2,cantdados,barro,lanzamientos,vec_dados,njg1,njg2,porky1,porky2);


                if (turno == true){
                    lanzamientos = 0; //reseteo la cantidad de lanzamientos para pasar a contar los del siguiente jugador
                }
            }
        }
    }

    //una vez que terminan las 5 rondas sumo los hitos

    //ganador del juego
    tabla_ganador(vec_hitos,njg1,njg2,ganador,PDV,porky1,porky2);
    //una vez terminada la partida se vuelve al menu principal
    rlutil::locate(1,17);
    cout << "REGRESANDO AL MENU PRINCIPAL...";

    rlutil::anykey();


    }

    //funcion dibujo dados
    void one()
    {
    HANDLE hconsole= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole,11);

    cout << "=============" << endl;
    cout << "|           |" << endl;
    cout << "|     o     |" << endl;
    cout << "|           |" << endl;
    cout << "=============" << endl;
    SetConsoleTextAttribute(hconsole,12);
    }
    void two()
    {
    HANDLE hconsole= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole,11);
    cout << "=============" << endl;
    cout << "| o         |" << endl;
    cout << "|           |" << endl;
    cout << "|         o |" << endl;
    cout << "=============" << endl;
    SetConsoleTextAttribute(hconsole,12);
    }
    void three()
    {
    HANDLE hconsole= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole,11);
    cout << "=============" << endl;
    cout << "| o         |" << endl;
    cout << "|     o     |" << endl;
    cout << "|         o |" << endl;
    cout << "=============" << endl;
    SetConsoleTextAttribute(hconsole,12);
    }
    void four()
    {
    HANDLE hconsole= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole,11);
    cout << "=============" << endl;
    cout << "| o       o |" << endl;
    cout << "|           |" << endl;
    cout << "| o       o |" << endl;
    cout << "=============" << endl;
    SetConsoleTextAttribute(hconsole,12);
    }
    void five()
    {
    HANDLE hconsole= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole,11);
    cout << "=============" << endl;
    cout << "| o       o |" << endl;
    cout << "|     o     |" << endl;
    cout << "| o       o |" << endl;
    cout << "=============" << endl;
    SetConsoleTextAttribute(hconsole,12);
    }
    void six()
    {
    HANDLE hconsole= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole,11);
    cout << "=============" << endl;
    cout << "| o       o |" << endl;
    cout << "| o       o |" << endl;
    cout << "| o       o |" << endl;
    cout << "=============" << endl;
    cout << endl;
    SetConsoleTextAttribute(hconsole,12);
    }
    void dibujar_dados(int vec_dados[],int cantdados){
        for (int i=0;i<cantdados;i++){
            switch(vec_dados[i]){
            case 1:
                one();
                break;
            case 2:
                two();
                break;
            case 3:
                three();
                break;
            case 4:
                four();
                break;
            case 5:
                five();
                break;
            case 6:
                six();
                break;
            default:
                cout<<"NOTANUMBER";
            }
        }
    }

    //funcion que tira los dados y me los carga en el vector de dados
    void tirar_dados(int vec_dados[],int cantdados){
        for(int i=0;i<cantdados;i++){
            vec_dados[i]+=1+rand()%6;
        }
    }

    //funcion que me inicializa en 0 la posicion del vec_dados para poder volver a utilizarlo
    void resetear_dados(int vec_dados[],int cantdados){
        for(int i=0;i<cantdados;i++){
            vec_dados[i]=0;
        }
    }

    //funcion que devuelve un true si empieza el jugador 1 o un false si empieza el jugador 2
    int quien_empieza(string njg1,string njg2,int vec_dados[],int cantdados){
        HANDLE hconsole= GetStdHandle(STD_OUTPUT_HANDLE);
        rlutil::cls();
        SetConsoleTextAttribute(hconsole,5);
        encuadrar_texto("GRAN CERDO",100,1);
        linea(4);
        encuadrar_texto("UTN FRGP",1,1);
        SetConsoleTextAttribute(hconsole,12);
        int dadomaxjg1=0,dadomaxjg2=0,puntosjg1,puntosjg2;
        srand(time(NULL));
        rlutil::locate(1,10);
        cout<<endl<<"LOS JUGADORES TIRARAN LOS DADOS,EL QUE OBTENGA MAYOR PUNTAJE COMIENZA LA RONDA";
        rlutil::anykey();
        rlutil::locate(1,12);
        cout<<njg1<< " TIRA LOS DADOS...";
        tirar_dados(vec_dados,cantdados);
        rlutil::locate(1,14);
        dibujar_dados(vec_dados,cantdados);
        puntosjg1=vec_dados[0]+vec_dados[1];
        rlutil::locate(1,25);
        cout<<njg1<<" SUMA: "<<puntosjg1<<endl;

        //ciclo para guardar el dado mas alto del jg1 en caso de empate
        for(int i=0;i<cantdados;i++){
            if(vec_dados[i]>dadomaxjg1){
                dadomaxjg1=vec_dados[i];
            }
        }
        rlutil::locate(1,26);
        cout<<"SIGUE "<<njg2<<endl;
        rlutil::anykey();

        cout<<njg2<<" TIRA LOS DADOS..."<<endl;
        resetear_dados(vec_dados,cantdados);
        tirar_dados(vec_dados,cantdados);

        dibujar_dados(vec_dados,cantdados);
        puntosjg2=vec_dados[0]+vec_dados[1];

        cout<<endl<<njg2<<"  SUMA: "<<puntosjg2<<endl;

        //ciclo para guardar el dado mas alto del jg2 en caso de empate
        for(int i=0;i<cantdados;i++){
            if(vec_dados[i]>dadomaxjg2){
                dadomaxjg2=vec_dados[i];
            }
        }

        if(puntosjg1>puntosjg2){
            SetConsoleTextAttribute(hconsole,3);
            cout<<njg1<<" OBTUVO MAYOR PUNTAJE."<<endl;

            return 1;
        }
        else if (puntosjg2>puntosjg1){
            SetConsoleTextAttribute(hconsole,3);
            cout<<njg2<<" OBTUVO MAYOR PUNTAJE."<<endl;

            return 0;
        }

        if(puntosjg1==puntosjg2){
            if(dadomaxjg1>dadomaxjg2){
                SetConsoleTextAttribute(hconsole,3);
                cout<<njg1<<" OBTUVO EL DADO MAS ALTO."<<endl;
                return 1;//empieza jugador 1
            }
            else if (dadomaxjg1<dadomaxjg2){
                SetConsoleTextAttribute(hconsole,3);
                cout<<njg2<<" OBTUVO EL DADO MAS ALTO."<<endl;
                return 0;//empieza jugador 2
            }
            else if(dadomaxjg1==dadomaxjg2){
                SetConsoleTextAttribute(hconsole,3);
                cout<<"EMPATE. SE TIRAN LOS DADOS NUEVAMENTE."<<endl;
                rlutil::anykey();
                rlutil::cls();
                return 3;//se tiran los dados de nuevo

            }
        }

    }


    void desarrollar_ronda( int vec_hitos[],bool &turno,int ronda[],string nombrejugador, int cantdados,bool &barro,int lanzamientos,int vec_dados[],string njg1,string njg2,bool &porky1,bool &porky2){
    HANDLE hconsole= GetStdHandle(STD_OUTPUT_HANDLE);


    /*vec_hitos donde se guarda lo siguiente:
    0:TRUFAS JG1 - 1:cantidad de oinks JG1 - 2 Mayor numero de lanzamientos en una misma ronda JG1 - 3 PuntosDeVictoria JG1

    4:TRUFAS JG2 - 5:cantidad de oinks JG2 - 6 Mayor numero de lanzamientos en una misma ronda JG2 - 7 PuntosDeVictoria JG2
    */
    char continuar;
    int suma_dados=0;

        mostrar_trufas(vec_hitos,njg1,njg2);
        cout <<endl<< "ES EL TURNO DE " << nombrejugador << endl;
        SetConsoleTextAttribute(hconsole,4);
        if (turno == true){
            cout << "RONDA " << ronda[0] << endl;
        }
        else {
            cout << "RONDA  " << ronda[1] << endl;
        }


        SetConsoleTextAttribute(hconsole,12);
        cout << nombrejugador << " LANZA LOS DADOS!" << endl;

        rlutil::anykey();

        resetear_dados(vec_dados,cantdados);
        tirar_dados(vec_dados,cantdados);
        dibujar_dados(vec_dados,cantdados);
        SetConsoleTextAttribute(hconsole,4);
        cout<<"LANZAMIENTOS EN ESTE TURNO: "<<lanzamientos<<endl;
        SetConsoleTextAttribute(hconsole,12);

        ///PORKY
        if((porky1==false && porky2==false)&&(cantdados==2)&&((vec_dados[0]+1==vec_dados[1])||(vec_dados[1]+1==vec_dados[1])||(vec_dados[0]-1==vec_dados[1])||(vec_dados[1]-1==vec_dados[1]))){
            if (turno==true){
                if(vec_dados[0]!=1 && vec_dados[1]!=1){
                    vec_hitos[0]+=vec_dados[0]+vec_dados[1];
                }
                porky1=true;
                SetConsoleTextAttribute(hconsole,11);
                cout<<"PORKY JG1"<<endl;
                SetConsoleTextAttribute(hconsole,12);


            }
            else if(turno==false){
                if(vec_dados[0]!=1 && vec_dados[1]!=1){
                    vec_hitos[4]+=vec_dados[0]+vec_dados[1];
                }
                porky2=true;
                SetConsoleTextAttribute(hconsole,11);
                cout<<"PORKY JG2"<<endl;
                SetConsoleTextAttribute(hconsole,12);
            }

        }

        //caso que salgan 3 ases con 3 dados
        else if((cantdados==3) &&(vec_dados[0]==1 && vec_dados[1]==1 && vec_dados[2]==1)){
            if(turno==true){
                vec_hitos[4]+=vec_hitos[0];
                vec_hitos[0]=0;
                turno=false;
                barro=true;
                ronda[0]++;
                if(lanzamientos>vec_hitos[2]){
                    vec_hitos[2]=lanzamientos;
                }
            }
            else if (turno==false){
                vec_hitos[0]+=vec_hitos[4];
                vec_hitos[4]=0;
                turno=true;
                barro=true;
                ronda[1]++;
                if(lanzamientos>vec_hitos[6]){
                    vec_hitos[6]=lanzamientos;
                }
            }
            SetConsoleTextAttribute(hconsole,11);
            cout << "TRES ASES!" << endl;
            SetConsoleTextAttribute(hconsole,12);
            cout << nombrejugador << " SE HUNDE EN EL BARRO Y PIERDE EL TURNO!" << endl;
            cout << "TODAS SUS TRUFAS PASAN AL OTRO JUGADOR!" << endl << endl;

        }

        //caso de un as con 3 dados
        else if((cantdados==3) && ((vec_dados[0] == 1 && vec_dados[1] != 1 && vec_dados[2] != 1) || (vec_dados[1]==1 && vec_dados[0]!=1 && vec_dados[2]!=1) || (vec_dados[2]==1 && vec_dados[1]!=1 && vec_dados[0]!=1))){

            if(turno==true){
                turno=false;
                barro=true;
                ronda[0]++;
                if(lanzamientos>vec_hitos[2]){
                    vec_hitos[2]=lanzamientos;
                }
            }
            else if (turno==false){
                turno=true;
                barro=true;
                ronda[1]++;
                if(lanzamientos>vec_hitos[6]){
                    vec_hitos[6]=lanzamientos;
                }
            }
            SetConsoleTextAttribute(hconsole,11);
            cout << "UN AS!" << endl;
            SetConsoleTextAttribute(hconsole,12);
            cout << nombrejugador << " PIERDE EL TURNO!" << endl;
            cout << "NO SUMA TRUFAS POR ESTE LANZAMIENTO!" << endl << endl;

        }
        //caso de dos ases con 3 dados
        else if((cantdados==3) && (vec_dados[0]==1 && vec_dados[1]==1 && vec_dados[2]!=vec_dados[1]) || (vec_dados[1]==1 && vec_dados[2]==1 && vec_dados[0]!=vec_dados[1]) || (vec_dados[0]==1 && vec_dados[2]==1 && vec_dados[1]!=vec_dados[0])){
            if(turno==true){
                vec_hitos[0]=0;
                turno=false;
                barro=true;
                ronda[0]++;
                if(lanzamientos>vec_hitos[2]){
                    vec_hitos[2]=lanzamientos;
                }
            }
            else if (turno==false){
                vec_hitos[4]=0;
                turno=true;
                barro=true;
                ronda[1]++;
                if(lanzamientos>vec_hitos[6]){
                    vec_hitos[6]=lanzamientos;
                }
            }
            SetConsoleTextAttribute(hconsole,11);
            cout << "DOS ASES!" << endl;
            SetConsoleTextAttribute(hconsole,12);
            cout << nombrejugador << " SE HUNDE EN EL BARRO Y PIERDE EL TURNO!" << endl;
            cout << "PIERDE TODAS SUS TRUFAS" << endl << endl;
        }
        //caso de dos ases con dos dados
        else if((cantdados==2)&&(vec_dados[0]==1 && vec_dados[1]==1)){
            if(turno==true){
                vec_hitos[0]=0;
                turno=false;
                barro=true;
                ronda[0]++;
                if(lanzamientos>vec_hitos[2]){
                    vec_hitos[2]=lanzamientos;
                }
            }
            else if (turno==false){
                vec_hitos[4]=0;
                turno=true;
                barro=true;
                ronda[1]++;
                if(lanzamientos>vec_hitos[6]){
                    vec_hitos[6]=lanzamientos;
                }
            }
            SetConsoleTextAttribute(hconsole,11);
            cout << "DOS ASES!" << endl;
            SetConsoleTextAttribute(hconsole,12);
            cout << nombrejugador << " SE HUNDE EN EL BARRO Y PIERDE EL TURNO!" << endl;
            cout << "PIERDE TODAS SUS TRUFAS!" << endl << endl;
        }
        //caso de un as con dos dados
        else if((cantdados==2)&&(vec_dados[0]==1 && vec_dados[1]!=1) ||(vec_dados[1]==1 && vec_dados[0]!=1) ){
            if(turno==true){
                turno=false;

                ronda[0]++;
                if(lanzamientos>vec_hitos[2]){
                    vec_hitos[2]=lanzamientos;
                }
            }
            else if (turno==false){
                turno=true;

                ronda[1]++;
                if(lanzamientos>vec_hitos[6]){
                    vec_hitos[6]=lanzamientos;
                }
            }
            SetConsoleTextAttribute(hconsole,11);
            cout << "UN AS!" << endl;
            SetConsoleTextAttribute(hconsole,12);
            cout << nombrejugador << " PIERDE EL TURNO!" << endl;
            cout << "NO SUMA TRUFAS POR ESTE LANZAMIENTO!" << endl << endl;
        }

       //oink con 3 dados
        else if(cantdados==3 && (vec_dados[0]!=1 && vec_dados[0]==vec_dados[1] && vec_dados[1]==vec_dados[2])){
            SetConsoleTextAttribute(hconsole,11);
            cout << "OINK!" << endl;
            SetConsoleTextAttribute(hconsole,12);

                for (int i = 0; i < 3; i++){
                    suma_dados += vec_dados[i]*2;
                }

            cout << nombrejugador << " SUMA " << suma_dados << " TRUFAS Y CONTINUA SU TURNO!" << endl << endl;

            if (turno == true){
                vec_hitos[0] += suma_dados;
                vec_hitos[1]++;
            }
            else {
                vec_hitos[4] += suma_dados;
                vec_hitos[5]++;
            }
        }
        //oink con 2 dados
        else if((cantdados==2)&&(vec_dados[0]==vec_dados[1]&&vec_dados[0]!=1)){
            SetConsoleTextAttribute(hconsole,11);
            cout << "OINK!" << endl;
            SetConsoleTextAttribute(hconsole,12);

                for (int i = 0; i < 2; i++){
                    suma_dados += vec_dados[i]*2;
                }

            cout << nombrejugador << " SUMA " << suma_dados << " TRUFAS Y CONTINUA SU TURNO!" << endl << endl;

            if (turno == true){
                vec_hitos[0] += suma_dados;
                vec_hitos[1]++;
            }
            else {
                vec_hitos[4] += suma_dados;
                vec_hitos[5]++;
            }

        }
        else {
        //caso de dos o tres dados diferentes y distintos de 1

            for (int i = 0; i < cantdados; i++){
                suma_dados += vec_dados[i];
            }

            cout << nombrejugador << " SUMA " << suma_dados << " TRUFAS. CONTINUAR TIRANDO?" << endl << "S/N" << endl;

                //SUMA LOS DADOS DEL LANZAMIENTO

            if (turno == true){
                vec_hitos[0] += suma_dados;
                turno = true;
                if (lanzamientos > vec_hitos[2]){
                    vec_hitos[2] = lanzamientos;
                }
            }
            else {
                vec_hitos[4] += suma_dados;
                turno = false;
                if (lanzamientos > vec_hitos[6]){
                    vec_hitos[6] = lanzamientos;
                }
            }




        // Y LUEGO PREGUNTA SI QUIERE SEGUIR TIRANDO

        //uso un ciclo para controlar que el jugador no ponga nada distinto de s/S/n/N
        do {


            cin >> continuar;

            if (continuar == 'S' || continuar == 's'){

            cout << nombrejugador << " ELIGE LANZAR DE NUEVO!" << endl << endl;

            } else if (continuar == 'N' || continuar == 'n'){

            cout << "TERMINA EL TURNO DE " << nombrejugador << endl << endl;

            if(turno==true){
                turno=false;
                ronda[0]++;
            }
            else{
                turno=true;
                ronda[1]++;
            }


            }
            else {

            cout << "POR FAVOR INGRESE S/N" << endl << endl;
            }
        } while (continuar != 's' && continuar != 'S' && continuar != 'n' && continuar != 'N');


        }
    cout<<"-----------------------------------------------------"<<endl;
    }
    void tabla_ganador(int vec_hitos[],string njg1,string njg2,string &ganador, int &PDV,bool porky1,bool porky2){
    rlutil::cls();
    HANDLE hconsole= GetStdHandle(STD_OUTPUT_HANDLE);



        encuadrar_texto("GRAN CERDO",100,1);
        linea(4);
        encuadrar_texto("RESUMEN DEL JUEGO",1,1);
        rlutil::locate(1,5);
        cout<<"       HITOS        ";
        linea(6);
        rlutil::locate(35,5);
        cout<<njg1;
        rlutil::locate(65,5);
        cout<<njg2;

        rlutil::locate(1,7);
        cout<<"MAS TRUFAS EN TOTAL ";
        rlutil::locate(1,8);
        cout<<"   CADA 50 TRUFAS   ";
        rlutil::locate(1,9);
        cout<<"       OINKS        ";
        rlutil::locate(1,10);
        cout<<"  CERDO CODICIOSO   ";
        rlutil::locate(1,11);
        cout<<"       PORKY        ";
        rlutil::locate(1,12);
        cout<<"       TOTAL        ";
        linea(13);


            //mas trufas en total
        if(vec_hitos[0]>vec_hitos[4]){
            vec_hitos[3]+=5;
            rlutil::locate(35,7);
            cout<<"5 PDV ("<<vec_hitos[0]<<" trufas)";
            rlutil::locate(65,7);
            cout<<"0 PDV ("<<vec_hitos[4]<<" trufas)";
        }
        else if(vec_hitos[4]>vec_hitos[0]){
            vec_hitos[7]+=5;
            rlutil::locate(35,7);
            cout<<"0 PDV ("<<vec_hitos[0]<<" trufas)";
            rlutil::locate(65,7);
            cout<<"5 PDV ("<<vec_hitos[4]<<" trufas)";
        }
        else if(vec_hitos[4]==vec_hitos[0]){ //caso de empate en trufas le sumo 5 a los dos
            vec_hitos[3]+=5;
            vec_hitos[7]+=5;
            rlutil::locate(35,7);
            cout<<"5 PDV ("<<vec_hitos[0]<<" trufas)";
            rlutil::locate(65,7);
            cout<<"5 PDV ("<<vec_hitos[4]<<" trufas)";
        }

        // cada 50 trufas 1 pdv
        //njg1
        rlutil::locate(35,8);
        cout<<vec_hitos[0]/50<<" PDV ("<<(vec_hitos[0]/50)*50<<" trufas)";
        vec_hitos[3]+=(vec_hitos[0]/50);
        //njg2
        rlutil::locate(65,8);
        cout<<vec_hitos[4]/50<<" PDV ("<<(vec_hitos[4]/50)*50<<" trufas)";
        vec_hitos[7]+=(vec_hitos[4]/50);

        //2 pdv * cantidad de oinks
        //jg1
        rlutil::locate(35,9);
        cout<<vec_hitos[1]*2<<" PDV ("<<vec_hitos[1]<<" Oinks)";
        vec_hitos[3]+=vec_hitos[1]*2;
        //jg2
        rlutil::locate(65,9);
        cout<<vec_hitos[5]*2<<" PDV ("<<vec_hitos[5]<<" Oinks)";
        vec_hitos[7]+=vec_hitos[5]*2;

        //cerdo codicioso : ronda con mayor cant de lanzamientos
        if(vec_hitos[2]>vec_hitos[6]){
            vec_hitos[3]+=3;
            rlutil::locate(35,10);
            cout<<"3 PDV ("<<vec_hitos[2]<<" lanzamientos)";
            rlutil::locate(65,10);
            cout<<"0 PDV ("<<vec_hitos[6]<<" lanzamientos)";
        }
        else if(vec_hitos[6]>vec_hitos[2]){
            vec_hitos[7]+=3;
            rlutil::locate(35,10);
            cout<<"0 PDV ("<<vec_hitos[2]<<" lanzamientos)";
            rlutil::locate(65,10);
            cout<<"3 PDV ("<<vec_hitos[6]<<" lanzamientos)";
        }
        //caso de que ambos sean cerdos codiciosos
        else if(vec_hitos[6]==vec_hitos[2]){
            vec_hitos[3]+=3;
            vec_hitos[7]+=3;
            rlutil::locate(35,10);
            cout<<"3 PDV ("<<vec_hitos[2]<<" lanzamientos)";
            rlutil::locate(65,10);
            cout<<"3 PDV ("<<vec_hitos[6]<<" lanzamientos)";
        }

            //PORKY lo cambie de lugar, lo puse abajo de todo una vez que ya estan hechos los calculos
        if(porky1==true){
            rlutil::locate(35,11);
            cout<<"1 PDV";
            vec_hitos[3]+=1; //suma un punto si o si
            if(vec_hitos[3]<10){
            rlutil::locate(65,11);
            cout<<"-1 PDV";
            vec_hitos[7]-=1;
            }
            else if (vec_hitos[3]>9){
            rlutil::locate(65,11);
            cout<<"-2 PDV";
            vec_hitos[7]-=2;

            }
            else if(vec_hitos[3]>15){
            rlutil::locate(65,11);
            cout<<"-3 PDV";
            vec_hitos[7]-=3;

            }


        }
        else if(porky2==true){
            rlutil::locate(65,11);
            cout<<"1 PDV";
            vec_hitos[7]+=1;
            if(vec_hitos[7]<10){
            rlutil::locate(35,11);
            cout<<"-1 PDV";
            vec_hitos[3]-=1;
            }
            else if(vec_hitos[7]>9){
            rlutil::locate(35,11);
            cout<<"-2 PDV";
            vec_hitos[3]-=2;

            }
            else if(vec_hitos[7]>15){
            rlutil::locate(35,11);
            cout<<"-3 PDV";
            vec_hitos[3]-=3;

            }
        }
        // total PDV abajo de cada jugador
        //njg1
        rlutil::locate(35,12);
        cout<<vec_hitos[3]<<" PDV";
        //njg2
        rlutil::locate(65,12);
        cout<<vec_hitos[7]<<" PDV";


        if(vec_hitos[3]>vec_hitos[7]){
            SetConsoleTextAttribute(hconsole,3);
            rlutil::locate(1,15);
            cout<<"GANADOR: "<<njg1<< " con "<<vec_hitos[3]<<" Puntos De Victoria";
            ganador=njg1;
            PDV=vec_hitos[3];
        }
        else if(vec_hitos[7]>vec_hitos[3]){
            SetConsoleTextAttribute(hconsole,3);
            rlutil::locate(1,15);
            cout<<"GANADOR: "<<njg2<< " con "<<vec_hitos[7]<<" Puntos De Victoria";
            ganador=njg2;
            PDV=vec_hitos[7];
        }
        else if(vec_hitos[7]==vec_hitos[3]){
            SetConsoleTextAttribute(hconsole,3);
            rlutil::locate(1,15);
            cout<<"EMPATE TOTAL"<<endl;
        }




        SetConsoleTextAttribute(hconsole,8);
        rlutil::locate(100,20);
        icono();

    }


    void linea(int posy){
        for(int i=1;i<=120;i++){
            rlutil::locate(i,posy);
            cout<<"-";
        }
    }

    void encuadrar(int posx,int posy,int ancho,int alto){

        //lineas de arriba y abajo del cuadro
        for(int x=1;x<=ancho;x++){
            rlutil::locate(x + posx,posy);
            cout<<(char)205;

            rlutil::locate(x+posx,posy + alto+1);
            cout<<(char)205;
        }
        //lineas de los costados
        for(int y=1;y<=alto;y++){
            rlutil::locate(posx,posy+y);
            cout<<(char)186;
            rlutil::locate(posx+ancho+1,posy+y);
            cout<<(char)186;

        }
        //las cuatro esquinas
        rlutil::locate(posx,posy);
        cout<<(char)201;
        rlutil::locate(posx,posy+alto+1);
        cout<<(char)200;
        rlutil::locate(posx+ancho+1,posy);
        cout<<(char)187;
        rlutil::locate(posx+ancho+1,posy+alto+1);
        cout<<(char)188;

    }
    void encuadrar_texto(string texto,int x,int y){
        encuadrar(x,y,texto.size()+2,1);
        rlutil::locate(x+2,y+1);
        cout<<texto;
    }
    void icono(){
        HANDLE hconsole= GetStdHandle(STD_OUTPUT_HANDLE);

        int matriz[10][10]=
        {{0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,1,1,1,1,0,0},
        {0,0,0,1,1,1,1,1,0,0},
        {0,0,0,2,0,1,0,2,0,0},
        {0,0,0,1,1,1,1,1,0,0},
        {0,0,0,1,3,3,3,1,0,0},
        {0,0,0,1,3,4,3,1,0,0},
        {0,0,0,1,1,1,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}};

        for(int i=0;i<10;i++){
            for(int x=0;x<10;x++){
                if(matriz[i][x]==1){
                    SetConsoleTextAttribute(hconsole,5);
                    cout<<(char)219;
                }
                else if(matriz[i][x]==2) {
                    SetConsoleTextAttribute(hconsole,8);
                    cout<<(char)219;
                }
                else if(matriz[i][x]==3) {
                    SetConsoleTextAttribute(hconsole,13);
                    cout<<(char)219;
                }
                else{
                    cout<<" ";
                }

            }
            cout<<endl;
        }

    }

    void mostrar_trufas(int vec_hitos[],string njg1,string njg2){
        HANDLE hconsole= GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hconsole,4);
        cout<<endl<<"TRUFAS "<<njg1<< ":"<<vec_hitos[0];
        cout<<endl<<"TRUFAS "<<njg2<< ":"<<vec_hitos[4]<<endl;
        SetConsoleTextAttribute(hconsole,12);

    }
