#include <cstdlib>
#include <vector>
#include <iostream>
#include <utility>
#include <windows.h>
#include <ctime>

#include "Pipe.h"
#include "Orientacion.h"

using namespace std;

//cout << "Hasta aquí bien." << endl;
//cin >> p;

//Creado por Juan Fernando Luque Pérez.
//Libre distribución con mención del autor.

void alCerrar(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


//Para debug por ChatGPT
string orientacionToString(ORIENTACION o) {
                switch(o) {
                    case ARRIBA:    return "ARRIBA";
                    case IZQUIERDA: return "IZQUIERDA";
                    case DERECHA:   return "DERECHA";
                    case ABAJO:     return "ABAJO";
                    default:        return "DESCONOCIDO";
                }
}

int main(){

    srand(time(nullptr));

    system("chcp 65001");
    SetConsoleOutputCP(CP_UTF8);

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    atexit(alCerrar);

    unsigned int columnas = 20, 
                 filas = 20;

    //Creamos un mapa que es un vector (de vector (de par(de string e int.)))
    //
    //Con esto básicamente simulamos una matriz de mapa que para cada espacio
    //del mapa guarda un caracter, vacio o de tubería, y un valor que usaremos
    //para guardar el color del gusano que puso ese caracter ahí.
    vector<vector<pair<string, int>>> mapa_visual(columnas, 
                vector<pair<string, int>>(filas, {" ", 7}));
    vector<vector<pair<string, int>>>* puntero_mapa = &mapa_visual;

    ORIENTACION orientacion;
    int color = ((rand() % 15) + 1);

    //Loop principal de simulación. Se repite para cada tubería nueva.
    while(true){
        //Elegir la casilla de salida.
        unsigned int tuberia_x = rand() % filas + 1,
                     tuberia_y = rand() % columnas + 1;
        
        // Escoger un color para la tubería.
        color = ((color + 1) % 15) + 1;

        //Elegir una orientación aleatoria para la tubería.
        //
        //Implementación alternativa de ChatGPT que no voy a implementar porque la
        //ha hecho ChatGPT y no yo pero aún así me parece interesante
        //conservarla para pensar en ella en el futuro.
        //------------------------------------------------------
        //ORIENTACION orientaciones[4]= {(las orientaciones)}:
        //orientacion = orientaciones[rand() % 4] 
        //------------------------------------------------------
        //Al menos como completo aficionado, me parece bastante elegante.
        switch(rand() % 4){
            case 0:
                orientacion = ORIENTACION::ARRIBA;
                break;

            case 1:
                orientacion = ORIENTACION::IZQUIERDA;
                break;

            case 2:
                orientacion = ORIENTACION::DERECHA;
                break;

            case 3:
                orientacion = ORIENTACION::ABAJO;
                break;
        }

        //Inicializar la tubería.
        Pipe tuberia(tuberia_x, tuberia_y, filas, columnas, orientacion,
                     puntero_mapa, (color));

        //Loop de simulación de una tubería. Termina cuando getVivo()
        //da false, es decir, cuando la tubería se acorrala y muere.
        system("CLS");
        do{
            //Actualizar el estado de la tubería.
            tuberia.actualizarEstado();

            //Hacer clear de la pantalla y monstrar mapa visual.
            //system("CLS");

            //Iterar cada columna.
            int y = 0;
            for(vector<pair<string, int>> &v : mapa_visual){
                //Iterar cada fila de la columna
                int x = 0;
                for(pair<string, int> &car : v){
                    //Cambiamos el color acorde con el espaciod el mapa
                    //e imprimos el caracter.
                    if(x == tuberia.getPosX() && y == tuberia.getPosY()){
                        SetConsoleTextAttribute(h, color);
                        cout << "o";
                    }
                    else{
                        SetConsoleTextAttribute(h, car.second);
                        cout << car.first;
                    }
                    x++;
                }
                //Terminamos la línea al terminar con una fila.
                cout << endl;
                y++;
            }
            //Esperamos un poco para claridad visual.
            cout << "\nEste loop se ha realizado." << endl;
            cout << "Pipe en: (" << tuberia.getPosX() << 
                             "," << tuberia.getPosY() << ")" << endl;
            cout << "¿Vivo? " << tuberia.getVivo() << endl;

            cout << "Orientacion: " << orientacionToString(tuberia.getOrientacion()) << endl;            

            Sleep(50);
            SetConsoleCursorPosition(h, {0, 0});
        }while(tuberia.getVivo());
    }

    return 0;
}