
Configuracion Geany para automatizar tests: 
for x in "%e"*.in ; do echo $x; cat $x; echo ---------- time "./%e" < "$x" ; echo "=======================";done

Para consola linux:
for x in *.in ; do echo $x ; time ./main < "$x";echo "==================";done

Ej.1 TP1 Algo3 2c2023
L I # + 
+ - - -
I I I -
- - L -

- Representar las posibles rotaciones del casillero con numeros
- Armar una matriz de booleanos para asegurar recorrer los casilleros una sola vez.
- Para hacer la lógica ahora decimos lo siguiente: L así nomas es O, despues incremento en 1 por cada rotación horaria de 90° (0-3); para el I, 4 representa el horizontal y 5 el vertical

Variables globales : T,MIN,MAX,USADOS
sigCasilla(i,j,Move) ->() 
(i,j) denota la casilla del momento actual y Move es un indicador de "desde donde vengo"
             { POSIBLE      Si (i,j)=(M,N)
             { IMPOSIBLE    Si (i,j)!=(M,N) and (T[i][j]==# or USADOS[i][j]==TRUE or !noVálido(i,j,T))
f(i,j,Move)= { moveL        Si T[i][j] == L
             { moveI        Si T[i][j] == I 
             { f(i,j+1,up) or f(i+1,j,left) or f(i,j-1,down) or f(i-1,j,right)        Si T[i][j] == +

======================================================================================================
Ej. 2

2 1 3
4 5 6

3 2 1

3   +  1  + 2
3*6 + 4*5 + 6*4 

Poda: Si el descontento general es mayor al minimo actual corto.
======================================================================================================
Ej.3
