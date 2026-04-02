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