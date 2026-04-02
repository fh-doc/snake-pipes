//Creado por Juan Fernando Luque Pérez.
//Libre distribución con mención del autor.
//(Vamos a ser sinceros, quién va a querer compartir esto.)
//
//Si eres gringo y no entiendes nada, espabila y aprende español
//que la vida te va a comer ay gringuito jajajajaj.
//
//   ╔═╗
//   ║ ║
//   ╚═╝
//
// Clase Pipe:
//      -Atributos:
//      unsigned int
//          *pos_x : Posición en el eje X de la cabeza de la tubería.
//          *pos_y : Posición en el eje Y de la cabeza de la tubería.
//
//          *max_x : Borde máximo en el eje X.
//          *max_y : Borde máximo en el eje Y.
//
//      ORIENTACION
//          *orientacion     : Hacia dónde va la cabeza de la tubería.
//          *old_orientacion : La anterior orientación de la cabeza de la
//                             tubería.
//
//      bool
//          *vivo : Indica si se ha acorralado la tubería.
//
//      vector<vector<string>>
//          *mapa_propio : Mapa de visión personal de la tubería.
//
//      vector<vector<pair<string, int>>>*
//          *mapa_visual : Puntero al mapa que se muestra en pantalla.
//
//      int
//          *color : Valor usada para marcar el color de la casilla
//                   que pinta la tubería.
//
//      -Constructores:
//          *Sin atributos. Atributos por defecto.
//          *Con todos los atributos.
//
//      -Métodos públicos:
//      unsigned int
//          *getPosX : Devuelve la variable pos_x.
//          *getPosY : Devuelve la variable pos_y.
//      bool
//          *getVivo : Devuelve la variable vivo;
//      void
//          *actualizarEstado : Rutina de la tubería.
//             Llama a la rutina de movimiento y escritura y gira si la tubería
//             no pudo moverse (moverYPoner() retorna false). También tiene una
//             probabilidad de (1/5) de girar aleatoriamente.
//

#include <cstdlib>
#include <vector>
#include <utility>
#include <iostream>

#include "ORIENTACION.h"
#include "Pipe.h"

using namespace std;

//Función cortesía de ChatGPT, incluida para un mensaje de
//depuración.
string orientacionToString2(ORIENTACION o) {
    switch(o) {
        case ARRIBA:    return "ARRIBA   ";
        case IZQUIERDA: return "IZQUIERDA";
        case DERECHA:   return "DERECHA  ";
        case ABAJO:     return "ABAJO    ";
    }
}

//Devuelve true  : Posición válida.
//Devuelve false : Posición no válida.
//
//Devuelve un bool que indica si la posición es válida para mover o
//girar en su dirección. Esto se decide si los valores de x e y están
//dentro del rango entre 0 y max_x/max_y, y si la casilla que se está
//analizando está vacia en el mapa de visión propia de la tubería.
bool Pipe::posValida(unsigned int x, unsigned int y){
    bool valida = true;

    //cout << "Validando posicion." << endl;

    if(((max_x <= x) || (max_y <= y)) || (mapa_propio[y][x] != " ")){
        valida = false;
    }

    return valida;
}

//Llama a ponerEnMapa() y cambia el bool vivo a false.
void Pipe::matar(){

    //cout << "Pipe muerto."" << endl;

    ponerEnMapa();
    vivo = false;
}
        
//Dependiendo de las variables orientacion y old_orientacion escribe
//el caracter pertinente en tanto la matriz que se escribe por pantalla
//como en la de su visión propia.
void Pipe::ponerEnMapa(){

    //cout << "Poniendo en mapa." << endl;
    //cout << "Orientacion: " << orientacionToString2(orientacion) << endl;
    //cout << "Old Orientacion: " << orientacionToString2(old_orientacion) << endl;

    string out;

    //   ╔═╗   X=X
    //   ║ ║   H H
    //   ╚═╝   X=X

    switch(orientacion){
        case ORIENTACION::ARRIBA:
                    
            switch(old_orientacion){
                case ORIENTACION::IZQUIERDA:
                    //out = "X";
                    out = "╚";
                    break;
                case ORIENTACION::DERECHA:
                    //out = "X";
                    out = "╝";
                    break;
                case ORIENTACION::ARRIBA:
                    //out = "H";
                    out = "║";
                    break;
            }
            break;    
                
        case ORIENTACION::IZQUIERDA:
    
            switch(old_orientacion){
                case ORIENTACION::ARRIBA:
                    //out = "X";
                    out = "╗";
                    break;
                case ORIENTACION::IZQUIERDA:
                    //out = "=";
                    out = "═";
                    break;
                case ORIENTACION::ABAJO:
                    //out = "X";
                    out = "╝";
                    break;
            }
            break;
                
        case ORIENTACION::DERECHA:
    
            switch(old_orientacion){
                case ORIENTACION::ARRIBA:
                    //out = "X";
                    out = "╔";
                    break;
                case ORIENTACION::DERECHA:
                    //out = "=";
                    out = "═";
                    break;
                case ORIENTACION::ABAJO:
                    //out = "X";
                    out = "╚";
                    break;
            }
            break;
                
        case ORIENTACION::ABAJO:
    
            switch(old_orientacion){
                case ORIENTACION::ABAJO:
                    //out = "H";
                    out = "║";
                    break;
                case ORIENTACION::IZQUIERDA:
                    //out = "X";
                    out = "╔";
                    break;
                case ORIENTACION::DERECHA:
                    //out = "X";
                    out = "╗";
                    break;
            }
            break;
    }
    
    //cout << "Cacarcter: " << out << " seleccionado." << endl;

    mapa_propio[pos_y][pos_x] = out;
    (*mapa_visual)[pos_y][pos_x].first = out;
    (*mapa_visual)[pos_y][pos_x].second = color;

    //cout << (*mapa_visual)[pos_y][pos_x].first << " Insertado en el mapa." << endl;
    //cout << (*mapa_visual)[pos_y][pos_x].second << " Valor de color." << endl;
}
    
//Dependiendo de qué casillas estén libres al rededor, elige
//una dirección para girar (o ninguna si no puede) actualizando
//orientacion. Si no puede ni girar ni pudiera seguir avanzando 
//llama a matar().
void Pipe::girar(){

    //cout << "Se supone que ahora gira." << endl;
    
    bool girar_l, no_puede = false;
    girar_l = rand() % 2;
    
    switch(orientacion){
        case ORIENTACION::ARRIBA:
                    
            if(!posValida(pos_x+1, pos_y) && !posValida(pos_x-1, pos_y)){
                no_puede = true;
                if(!posValida(pos_x, pos_y+1)){
                    matar();
                }
            }
            else if(!posValida(pos_x+1, pos_y)){
                girar_l = true;
            }
            else if(!posValida(pos_x-1, pos_y)){
                girar_l = false;
            }
    
            if(!no_puede){
                if(girar_l){
                    old_orientacion = ORIENTACION::ARRIBA;
                    orientacion = ORIENTACION::IZQUIERDA;
                }
                else{
                    old_orientacion = ORIENTACION::ARRIBA;
                    orientacion = ORIENTACION::DERECHA;
                }
            }
            break;
                
        case ORIENTACION::IZQUIERDA:
                    
            if(!posValida(pos_x, pos_y+1) && !posValida(pos_x, pos_y-1)){
                no_puede = true;
                if(!posValida(pos_x-1, pos_y)){
                    matar();
                }
            }
            else if(!posValida(pos_x, pos_y+1)){
                girar_l = false;
            }
            else if(!posValida(pos_x, pos_y-1)){
                girar_l = true;
            }
    
            if(!no_puede){
                if(girar_l){
                    old_orientacion = ORIENTACION::IZQUIERDA;
                    orientacion = ORIENTACION::ABAJO;
                }
                else{
                    old_orientacion = ORIENTACION::IZQUIERDA;
                    orientacion = ORIENTACION::ARRIBA;
                }
            }
            break;
                
        case ORIENTACION::DERECHA:
                    
            if(!posValida(pos_x, pos_y+1) && !posValida(pos_x, pos_y-1)){
                no_puede = true;
                if(!posValida(pos_x+1, pos_y)){
                    matar();
                }
            }
            else if(!posValida(pos_x, pos_y+1)){
                girar_l = true;
            }
            else if(!posValida(pos_x, pos_y-1)){
                girar_l = false;
            }
    
            if(!no_puede){
                if(girar_l){
                    old_orientacion = ORIENTACION::DERECHA;
                    orientacion = ORIENTACION::ARRIBA;
                }
                else{
                    old_orientacion = ORIENTACION::DERECHA;
                    orientacion = ORIENTACION::ABAJO;
                }
            }
            break;
    
        case ORIENTACION::ABAJO:
    
            if(!posValida(pos_x+1, pos_y) && !posValida(pos_x-1, pos_y)){
                no_puede = true;
                if(!posValida(pos_x, pos_y+1)){
                    matar();
                }
            }
            else if(!posValida(pos_x+1, pos_y)){
                girar_l = false;
            }
            else if(!posValida(pos_x-1, pos_y)){
                girar_l = true;
            }

            if(!no_puede){
                if(girar_l){
                    old_orientacion = ORIENTACION::ABAJO;
                    orientacion = ORIENTACION::DERECHA;
                }
                else{
                    old_orientacion = orientacion;
                    orientacion = ORIENTACION::IZQUIERDA;
                }
            }
            break;
    }
    return;
}

//Devuelve true  : Se ha movido.
//Devuelve false : No se ha movido.
//
//Determina segun la orientación a qué casilla tendría que moverse la
//tubería, llama a ponerEnMapa(), actualiza la posición de la cabeza
//de la tubería y retorna true. Si la tubería tuviera que moverse a una posición
//no válida, se salta la rutina y decuelve false.
bool Pipe::moverYPoner(){
    bool movido = false;
    
    switch(orientacion){
        case ORIENTACION::ARRIBA:
    
            if(posValida(pos_x, pos_y-1)){
                ponerEnMapa();
                pos_y--;
                movido = true;
            }
            break;

        case ORIENTACION::IZQUIERDA:
    
            if(posValida(pos_x-1, pos_y)){
                ponerEnMapa();
                pos_x--;
                movido = true;
            }
            break;
                
        case ORIENTACION::DERECHA:
    
            if(posValida(pos_x+1, pos_y)){
                ponerEnMapa();
                pos_x++;
                movido = true;
            }
            break;
                
        case ORIENTACION::ABAJO:
    
            if(posValida(pos_x, pos_y+1)){
                ponerEnMapa();
                pos_y++;
                movido = true;
            }
            break;
    }

    old_orientacion = orientacion;

    return movido;
}

//Constructor con valores por defecto.
Pipe::Pipe(){
    mapa_propio = vector<vector<string>>(max_y, vector<string>(max_x, " "));
    old_orientacion = orientacion;
}

//Constructor normal.
//Si se le pasan valores no válidos de posición utiliza los de 
//por defecto.
Pipe::Pipe(unsigned int pos_x, unsigned int pos_y, 
           unsigned int max_x, unsigned int max_y, ORIENTACION orientacion, 
           vector<vector<pair<string, int>>>* mapa_visual, int color){

    this->max_x = max_x;
    this->max_y = max_y;

    mapa_propio = vector<vector<string>>(max_y, vector<string>(max_x, " "));

    if(posValida(pos_x, pos_y)){
        this->pos_x = pos_x;
        this->pos_y = pos_y;
    }

    this->orientacion = orientacion;
    this->old_orientacion = orientacion;

    this->mapa_visual = mapa_visual;

    this->color = color;
}

//Devuelve pos_x.
unsigned int Pipe::getPosX(){
    return pos_x;
}

//Devuelve pos_y.
unsigned int Pipe::getPosY(){
    return pos_y;
}

//Devuelve vivo.
bool Pipe::getVivo(){
    return vivo;
}

//Devuelve la orientación. Para texto de depuración.
ORIENTACION Pipe::getOrientacion(){
    return orientacion;
}

//Rutina de simulación.
//Llama a la rutina de movimiento y escritura y gira si la tubería
//no pudo moverse (moverYPoner() retorna false). También tiene una
//probabilidad de (1/5) de girar aleatoriamente.
void Pipe::actualizarEstado(){

    //cout << "\nActualizando estado." << endl;

    bool movido;

    if(rand() % 5 == 0){
        girar();
    }

    do{
        movido = moverYPoner();
        if(!movido){
            girar();
        }
    }while(!movido && vivo);
}