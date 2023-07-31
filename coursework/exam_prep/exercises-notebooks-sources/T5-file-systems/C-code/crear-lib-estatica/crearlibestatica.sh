
#José Manuel Pérez Lobato
#script para crear la librería estática y ejecutar el programa de prueba

#creamos los ficheros objeto
gcc -g -c -O cubo.c
gcc -g -c -O cuadrado.c

#creamos la librería
ar cru libpotencia.a cubo.o cuadrado.o
ranlib libpotencia.a

#creamos un ejecutable para probar la librería
gcc -o usolibreriaestatica usolibreria.c -L. -lpotencia

#ejecutamos el programa de prueba
usolibreriaestatica
