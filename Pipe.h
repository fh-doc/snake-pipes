#pragma once

#include <vector>
#include "ORIENTACION.h"

using namespace std;

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
//          *pos_x
//          *pos_y
//
//          *max_x
//          *max_y
//
//          *orientacion
//          *old_orientacion
//
//          *vivo
//
//          *color
//
//          *mapa_propio : La visión personal de la tubería.
//          *mapa_visual : Puntero al mapa que se muestra en pantalla.
//
//      -Constructores:
//          *Sin atributos. Atributos por defecto.
//          *Con todos los atributos.
//
//      -Métodos públicos:
//          *getPosX : Devuelve pos_x.
//          *getPosY : Devuelve pos_y.
//          *getVivo : Devuelve vivo;
//
//          *actualizarEstado : 
//              Obtiene caracter -> Mueve -> Si no mueve gira y vuelve a mover.
//                                        └> Si mueve termina.

class Pipe{
    private:

        unsigned int pos_x = 0, pos_y = 0;
        unsigned int max_x = 10, max_y = 10;
        ORIENTACION orientacion = ORIENTACION::DERECHA, old_orientacion;

        bool vivo = true;

        int color = 7;

        vector<vector<string>> mapa_propio;
        vector<vector<pair<string, int>>>* mapa_visual = nullptr;



        bool posValida(unsigned int x, unsigned int y);

        void matar();
        
        void ponerEnMapa();
    
        void girar();
    
        bool mover();

    public:

        //Constructor con valores por defecto.
        Pipe();

        //Constructor normal.
        //Si se le pasan valores no válidos de posición utiliza los de 
        //por defecto.
        Pipe(unsigned int pos_x, unsigned int pos_y, 
              unsigned int max_x, unsigned int max_y, ORIENTACION orientacion,
              vector<vector<pair<string, int>>>* mapa_visual, int color);

        unsigned int getPosX();

        unsigned int getPosY();

        bool getVivo();

        ORIENTACION getOrientacion();

        //Rutina de juego.
        //Se devuelve por referencia el caracter apropiado para poner en el
        //mapa.
        //
        //Pone en el mapa -> Mueve -> Si no mueve gira y vuelve a mover.
        //                         └> Si mueve termina.
        void actualizarEstado();
};