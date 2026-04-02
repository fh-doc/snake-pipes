Realizado por Juan Fernando Luque Pérez.

Este proyecto está hecho con ligera asistencia de IA pero completamente diseñado y escrito por mi (menos una función de debugging
que detallo en main.cpp que me daba pereza implementar por simple y mundano).

Para compilar basta con hacer:
[g++ (-O2) main.cpp Pipe.cpp -o Pipes.exe]
dentro de la carpeta donde extraerás los archivos.

Está diseñado en y para windows, con las dependencias: cstdlib, vector, iostream, utility, windows.h y ctime.

Los comentarios aún están en progreso.

-------------------------
Cosas que editar a gusto:
-------------------------
*En main.cpp líneas 47 y 48, se puede redimensionar la matriz de mapa a gusto con las variables columnas y filas.
 Las tuberías funcionarán independientemente del tamaño o forma de la matriz de mapa.

*En main.cpp línea 30, la variable booleana debug_text puede activarse si se desea ver un poco de información sobre
 la tubería en movimiento. Esto puede provocar unerror gráfico en el momento.

*En main.cpp línea 172, hay comentado una función Sleep() que se puede descomentar y usar a gusto.
