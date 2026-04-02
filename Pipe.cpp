#include <cstdlib>
#include <vector>
#include <utility>
#include <iostream>

#include "ORIENTACION.h"
#include "Pipe.h"

using namespace std;

string orientacionToString2(ORIENTACION o) {
                switch(o) {
                    case ARRIBA:    return "ARRIBA   ";
                    case IZQUIERDA: return "IZQUIERDA";
                    case DERECHA:   return "DERECHA  ";
                    case ABAJO:     return "ABAJO    ";
                }
}

//Creado por Juan Fernando Luque Pérez.
//Libre distribución con mención del autor.
//(Vamos a ser sinceros, quién va a querer compartir esto.)
//
//Si eres gringo y no entiendes nada, espabila y aprende español
//que la vida te va a comer ay gringuito.
//
//   ╔═╗
//   ║ ║
//   ╚═╝
//
// Clase Pipe:
//      -Atributos:
//      unsigned int
//          *pos_x : Posición en el eje X.
//          *pos_y : Posición en el eje Y.
//
//          *max_x : Borde máximo en el eje X.
//          *max_y : Borde máximo en el eje Y.
//
//      ORIENTACION
//          *orientacion : Hacia donde va la tubería.
//          *old_orientacion : De donde venía la tubería.
//
//      bool
//          *vivo : Indica si se ha acorralado la tubería.
//
//      vector<vector<string>>
//          *mapa_propio : La visión personal de la tubería.
//      vector<vector<pair<string, int>>>*
//          *mapa_visual : Puntero al mapa que se muestra en pantalla.
//
//      -Constructores:
//          *Sin atributos. Atributos por defecto.
//          *Con todos los atributos.
//
//      -Métodos públicos:
//      unsigned int
//          *getPosX : Devuelve pos_x.
//          *getPosY : Devuelve pos_y.
//      bool
//          *getVivo : Devuelve vivo;
//      void
//          *actualizarEstado : 
//              1. Escribe caracter en mapa.
//              2. Aleatoriamente elige girar. (1/5 de probabilidad)
//              3. Mueve la tubería. Si no puede moverse gira y vuelve a mover.

bool Pipe::posValida(unsigned int x, unsigned int y){
    bool valida = true;

    //cout << "Validando posicion." << endl;

    if(((max_x <= x) || (max_y <= y)) || (mapa_propio[y][x] != " ")){
        valida = false;
    }

    return valida;
}

void Pipe::matar(){

    //cout << "Pipe muerto."" << endl;

    ponerEnMapa();
    vivo = false;
}
        
void Pipe::ponerEnMapa(){

    //cout << "Poniendo en mapa." << endl;
    //cout << "Orientacion: " << orientacionToString2(orientacion) << endl;
    //cout << "Old Orientacion: " << orientacionToString2(old_orientacion) << endl;

    string out;

    //   ╔═╗
    //   ║ ║
    //   ╚═╝

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
    //cout << (*mapa_visual)[pos_y][pos_x].first << " Valor de color." << endl;
}
    
bool Pipe::girar(){

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
    return !no_puede;
}
    
bool Pipe::mover(bool girado){
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

    //if(movido && !girado){
    old_orientacion = orientacion;
    //}

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

unsigned int Pipe::getPosX(){
    return pos_x;
}

unsigned int Pipe::getPosY(){
    return pos_y;
}

bool Pipe::getVivo(){
    return vivo;
}

ORIENTACION Pipe::getOrientacion(){
    return orientacion;
}

//Rutina de juego.
//Se devuelve por referencia el caracter apropiado para poner en el
//mapa.
//
//Pone en el mapa -> Mueve -> Si no mueve gira y vuelve a mover.
//                         └> Si mueve termina.
void Pipe::actualizarEstado(){

    //cout << "\nActualizando estado." << endl;

    bool movido, girado = false;

    if(rand() % 5 == 0){
        girado = girar();
    }

    //int contador = 0;
    do{

        //cout << "Contador: " << contador << endl;

        movido = mover(girado);
        if(!movido){
            girado = girar();
        }

        //if(contador < 15){
        //    contador++;
        //}
        //else{
        //    break;
        //}
    }while(!movido && vivo);
}