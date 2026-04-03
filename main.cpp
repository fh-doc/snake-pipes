//Creado por Juan Fernando Luque Pérez.
//Libre distribución con mención del autor.

#include <cstdlib>
#include <vector>
#include <iostream>
#include <utility>
#include <windows.h>
#include <ctime>
#include <limits>

#include "Pipe.h"
#include "Orientacion.h"

using namespace std; //Lo siento para cualquier senior que vomite al ver esto.

//Función cortesía de ChatGPT, incluida para un mensaje de
//depuración.
string orientacionToString(ORIENTACION o) {
    switch(o) {
        case ARRIBA:    return "ARRIBA   ";
        case IZQUIERDA: return "IZQUIERDA";
        case DERECHA:   return "DERECHA  ";
        case ABAJO:     return "ABAJO    ";
    }
}

//Muestra un mensaje string por pantalla y lee el valor pasado por
//el usuario.
template <typename T>
void pedirVariable(string mensaje, T& var){ 
    cout << mensaje << endl;
    cin >> var;

    if(cin.fail()){
        cin.clear();           
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return;
}

int main(){

    //Haciendo setup del output.
    system("chcp 65001");
    SetConsoleOutputCP(CP_UTF8);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    //Desbloquea un poco te contexto de la tubería debajo del mapa.
    //No funciona muy bien ahora mismo.
    bool debug_text = false;

    //Se randomiza la semilla de rand().
    srand(time(nullptr));

    system("CLS");
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    DWORD escrito;

    //Cuansas veces se ejecuta actualizarEstado() en cada ciclo.
    unsigned int actualizaciones_en_ciclo;

    bool criterio;
    do{
        pedirVariable("Introduzca el número de refrescos por ciclo (1-10): ", 
                                                   actualizaciones_en_ciclo);
        criterio = (1 <= actualizaciones_en_ciclo) &&
                   (actualizaciones_en_ciclo <= 10);

        if(!criterio){
            SetConsoleCursorPosition(h, {0, 1});
            for(int i = 0; i < 80; i++){
                cout << ' ';
            }
            SetConsoleCursorPosition(h, {0, 0});
        }
    }while(!criterio);

    //El tiempo en milisegundos que pasa entre ciclos.
    unsigned int ms_dormir;
    do{
        pedirVariable("Introduzca los milisegundos entre ciclo (0-10000): ",
                                                                 ms_dormir);
        criterio = (0 <= ms_dormir) && (ms_dormir <= 10000);

        if(!criterio){
            SetConsoleCursorPosition(h, {0, 3});
            for(int i = 0; i < 80; i++){
                cout << ' ';
            }
            SetConsoleCursorPosition(h, {0, 2});
        }
    }while(!criterio);

    //Dimensiones del mapa.
    unsigned int columnas, 
                 filas;

    do{
        pedirVariable("Introduzca el número de filas del mapa (5-100): ",
                                                                  filas);
        criterio = (5 <= filas) && (filas <= 100);

        if(!criterio){
            SetConsoleCursorPosition(h, {0, 5});
            for(int i = 0; i < 80; i++){
                cout << ' ';
            }
            SetConsoleCursorPosition(h, {0, 4});
        }
    }while(!criterio);

    do{
        pedirVariable("Introduzca el número de columnas del mapa (5-100): ",
                                                                  columnas);
        criterio = (5 <= columnas) && (columnas <= 100);

        if(!criterio){
            SetConsoleCursorPosition(h, {0, 7});
            for(int i = 0; i < 80; i++){
                cout << ' ';
            }
            SetConsoleCursorPosition(h, {0, 6});
        }
    }while(!criterio);

    //Creamos un mapa que es un vector (de vector (de par(de string e int.)))
    //El mapa es de dimensiones filas x columnas.
    //
    //Con esto básicamente simulamos una matriz de mapa que para cada espacio
    //del mapa guarda un caracter, vacio o de tubería, y un valor que usaremos
    //para guardar el color del gusano que puso ese caracter ahí.
    vector<vector<pair<string, int>>> mapa_visual(columnas, 
                vector<pair<string, int>>(filas, {" ", 7}));
    vector<vector<pair<string, int>>>* puntero_mapa = &mapa_visual;

    ORIENTACION orientacion;

    //Elegimos un color aleatorio para comenzar del 1-15.
    int color = ((rand() % 15) + 1);

    //Hacer el cursor invisible.
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(h, &cursor);
    cursor.bVisible = false;
    SetConsoleCursorInfo(h, &cursor);

    system("CLS");
    //Loop principal de simulación. Se repite para cada tubería nueva.
    while(true){
        //Elegir la casilla de salida.
        unsigned int tuberia_x = rand() % filas,
                     tuberia_y = rand() % columnas;
        
        // Se ciclan los colores del 1-15 para cada tubería.
        color = (color % 15) + 1;
                     
        //Elegir una orientación aleatoria para la tubería.
        //
        //Implementación alternativa de ChatGPT que no voy a implementar porque
        //lo ha hecho ChatGPT y no yo pero aún así me parece interesante
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
                     puntero_mapa, color);

        //Loop de simulación de una tubería. Termina cuando getVivo()
        //da false, es decir, cuando la tubería se acorrala y muere.
        do{
            //Actualizar el estado de la tubería.
            for(unsigned int i = 0; i < actualizaciones_en_ciclo; i++){
                tuberia.actualizarEstado();
            }

            //Hacer una filla que delimita el mapa por arriba.
            for(int i = 0; i < filas+2; i++){
                cout << "#";
            }
            cout << endl;

            //Iterar cada columna.
            int y = 0;
            for(vector<pair<string, int>> &v : mapa_visual){
                //Iterar cada fila de la columna
                int x = 0;
                cout << "#";
                for(pair<string, int> &car : v){
                    
                    //Comprobamos si el espacio en el que estamos es la cabeza
                    //de la tubería.
                    if(x == tuberia.getPosX() && y == tuberia.getPosY()){
                        //Sí es.
                        //Imprimimos un caracter diferente con el color
                        //de la tubería actual.
                        SetConsoleTextAttribute(h, color);
                        cout << "o";
                    }
                    else{
                        //No es.
                        //Cambiamos el color acorde con el espacio del mapa
                        //e imprimos el caracter.
                        SetConsoleTextAttribute(h, car.second);
                        cout << car.first;
                    }
                    x++;
                }
                //Cambiamos el color, ponemos un caracter delimitador y
                //terminamos la línea al terminar con la fila.
                SetConsoleTextAttribute(h, 7);
                cout << "#";
                cout << endl;
                y++;
            }

            //Hacer una filla que delimita el mapa por abajo.
            for(int i = 0; i < filas+2; i++){
                cout << "#";
            }

            cout << endl;

            //Texto de depuración curioso.
            if(debug_text){
                cout << "\nEste loop se ha realizado." << endl;
                cout << "Pipe en: (" << tuberia.getPosX() << 
                             "," << tuberia.getPosY() << ")" << endl;
                cout << "¿Vivo? " << tuberia.getVivo() << endl;

                cout << "Orientacion: " << 
                orientacionToString(tuberia.getOrientacion()) << endl;
            }

            //Esperamos un poco para claridad visual y devolvemos el cursor
            //al inicio.
            Sleep(ms_dormir);
            SetConsoleCursorPosition(h, {0, 0});
        }while(tuberia.getVivo());
    }

    return 0;
}