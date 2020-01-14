# Trabajo-2
Bosquedas y ordenamiento

#UNIVERSIDAD DE SANTIAGO DE CHILE
#FACULTAD DE CIENCIAS
#DEPARTAMENTO DE MATEM�TICA Y CIENCIA DE LA COMPUTACI�N
#LICENCIATURA EN CIENCIA DE LA COMPUTACI�N
#Profesor(es): Nicolas Th�riault
#Segundo Semestre de 2019
#Departamento de Matem�tica y Ciencia de la Computaci�n { USACH { 2019
#Programaci�n Avanzada { Laboratorio 2

#1. Objetivos

Objetivo principal: aplicar algoritmos de ordenamiento de datos para hacer un an�lisis estad�stico de unas series de datos.
Objetivos espec�ficos:
1. encontrar los valores m�nimos y m�ximos;
2. encontrar la mediana, los cuartiles y los deciles;
3. determinar los valores m�s repetidos y la cantidad de valores distintos
4. comparar la eficiencia de las diferentes estrategias.
El laboratorio se trabajar� en grupos de 2 o 3 alumnos, entregando un resultado (informe y
programas) por grupo.

#2. Programaci�n

La programaci�n debe ser en C (no en C++), utilizando a lo mas las libreras est�ndares
siguientes:
stdio.h
stdlib.h
math.h
time.h
Adem�s, para evitar cualquier problemas de compatibilidad, se recomienda utilizar solamente la
funci�n clock() para la medici�n de tiempo.
Archivos a analizar (simulados):
Examenes m�dicos
Notas de alumnos
Puntos flotantes (sin m�s restricciones)

El formato de los datos ser�: archivos de tipo \.tex" con 10 entradas por linea, en formato
decimales (ej: \3.6") o exponenciales (ej: \1.257e-4")
Crear funciones para:
1. Leer los archivos y liberar la memoria activa antes de cerrar el programa;
2. Devolver los resultados;
3. Dos funciones que ordenan el listado (arreglo o enlazado) directamente:
Ordenar por mezcla;
Quicksort;
4. Dos funciones que ordenan utilizando �rboles, entre:
Ordenar por mont�culos;
�rboles AVL;
5. Una funci�n que utiliza una estrategia \intercambio tiempo-memoria" (para utilizar en a
lo menos un de los archivo), elegida entre:
Ordenar por conteo;
Listado de repeticiones de valores;

#3. Se solicita

1. Programar los diferentes algoritmos en C, asegurando que hacen un uso apropiado de
memoria (por ejemplo que se liberan corectamente todos los espacios de memoria utilizados
al terminar las funciones).
2. La selecci�n de los distintos algoritmos/funciones y la lectura de los archivos se debe hacer
a trav�s de un menu (selecci�n de opciones) que incluye el cierre del programa.
3. Para cada archivo de datos, determinar si hay valores repetidos, y en el caso positivo
encontrar el valor m�s repetido.
4. El informe deber� detallar:
La estructura de datos utilizada para los diferentes algoritmos (con las razones generales
de porque se eligi�).
Las estrategias utilizadas en cada caso.
Como se hicieron las mediciones de tiempo (en que computador/procesador, etc).
Conclusiones obtenida de los an�lisis de tiempos.

#4. Evaluaci�n
La nota del laboratorio se calcular� seg�n la ponderaci�n siguiente:
Algoritmos [25 %]:
El informe detalla las eleciones que se utilizaron durante la implementaci�n.
An�lisis [15 %]:
El an�lisis estad�stico es correcto y completo.
Informe [10 %]:
El informe est� escrito en lenguaje apropiado, sin faltas de ortograf�a o gram�atica..
Implementaci�n [20 %]
El programa est� escrito de forma que puede ser le�do y/o re-utilizado f�cilmente por otros
programadores: la redacci�n es limpia (con espacios y divisiones claras) y bien documentada,
las sub-funciones y las variables tienen nombres naturales (que indican a que sirven) o
van acompa~nadas de comentarios aclarando a que sirven.
Se libera el espacio antes de cerrar las funciones.
Todos los algoritmos dan resultados correcto.
Eficiencia [30 %]
Los tiempos de calculo de ordenamiento comparados con una implementaci�n b�sica" (que
satisface lo solicitado).

#Rangos de notas:

 1: no ordena correctamente.
 1.1{2.4: m�s de 20 veces m�s lenta
 2.5{3.9: 5 a 20 veces m�s lenta
 4{5.4: 2 a 5 veces m�s lenta
 5.5{6.9: a lo m�s 2 veces m�s lenta
 7: tiempos parecidos o mejores
