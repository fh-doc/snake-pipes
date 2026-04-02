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

#pragma once

#include <vector>
#include "ORIENTACION.h"

using namespace std;

class Pipe{
    private:

        unsigned int pos_x = 0, pos_y = 0;
        unsigned int max_x = 10, max_y = 10;
        ORIENTACION orientacion = ORIENTACION::DERECHA;
        ORIENTACION old_orientacion = ORIENTACION::DERECHA;

        bool vivo = true;

        int color = 7;

        vector<vector<string>> mapa_propio;
        vector<vector<pair<string, int>>>* mapa_visual = nullptr;


        //Devuelve un bool que indica si la posición es válida para mover o
        //girar en su dirección. Esto se decide si los valores de x e y están
        //dentro del rango entre 0 y max_x/max_y, y si la casilla que se está
        //analizando está vacia en el mapa de visión propia de la tubería.
        bool posValida(unsigned int x, unsigned int y);

        //Llama a ponerEnMapa() y cambia el bool vivo a false.
        void matar();
        
        //Dependiendo de las variables orientacion y old_orientacion escribe
        //el caracter pertinente en tanto la matriz que se escribe por pantalla
        //como en la suya de visión propia.
        void ponerEnMapa();
    
        //Dependiendo de qué casillas estén libres al rededor, elige
        //una dirección para girar (o ninguna si no puede) actualizando
        //orientacion. Si no puede ni girar ni pudiera seguir avanzando 
        //llama a matar().
        void girar();
    
        //Devuelve true  : Se ha movido.
        //Devuelve false : No se ha movido.
        //
        //Determina segun la orientación a qué casilla tendría que moverse la
        //tubería, llama a ponerEnMapa(), actualiza la posición de la cabeza
        //de la tubería y retorna true. Si la tubería tuviera que moverse a una posición
        //no válida, se salta la rutina y decuelve false.
        bool moverYPoner();

    public:

        //Constructor con valores por defecto.
        Pipe();

        //Constructor normal.
        //Si se le pasan valores no válidos de posición utiliza los de 
        //por defecto.
        Pipe(unsigned int pos_x, unsigned int pos_y, 
              unsigned int max_x, unsigned int max_y, ORIENTACION orientacion,
              vector<vector<pair<string, int>>>* mapa_visual, int color);

        //Devuelve pos_x.
        unsigned int getPosX();

        //Devuelve pos_y.
        unsigned int getPosY();

        //Devuelve vivo.
        bool getVivo();

        //Devuelve la orientación. Para texto de depuración.
        ORIENTACION getOrientacion();

        //Rutina de simulación.
        //Llama a la rutina de movimiento y escritura y gira si la tubería
        //no pudo moverse (moverYPoner() retorna false). También tiene una
        //probabilidad de (1/5) de girar aleatoriamente.
        void actualizarEstado();
};