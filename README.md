# Intérprete matemático [BISON]

### Introducción

En este proyecto se ha realizado la implementación de un intérprete
de expresiones matemáticas a través de la línea de comandos implementado
en C y apoyándose en Flex y Bison.

### Compilación y ejecución

Para realizar la compilación y ejecución del intérprete, se necesitará
una terminal **Linux con versión 18.04 o posterior**. Para ello, en
primer lugar habrá que estar en el directorio principal del proyecto
(directorio de los archivos *main.c* o *Makefile* entre otros), y se
realizará la siguiente secuencia de ejecuciones:


    $ flex lexico.l

Donde *lexico.l* es el archivo de entrada de *Flex*. Como resultado se
obtendrá el archivo *lex.yy.c* actualizado en función del contenido de
*lexico.l* tras su compilación. Una vez obtenida la compilación de *Flex*,
será hora de compilar el código generado con *Bison*.

    $ bison -d sintactico.y

Este comando generaŕa los archivos *sintactico.tab.c* y *sintactico.tab.h*.
Mediante estos archivos se conseguirá reconocer en lenguaje C la sintaxis
especificada en el archivo *sintactico.y*. Una vez obtenido el código que
reconoce la sintaxis, se procederá a compilar el proyecto. Para tener una
mayor agilidad a la hora de realizar este compilado, se contará con un 
archivo *Makefile* que contiene las instrucciones necesarias para realizar
dicha compilación. Para ello, se ejecutará:


    $ make

A través de este comando se consiguen generar los diferentes ficheros objeto
para llevar a cabo la generación del ejecutable asociado al analizador, y
se llevará a cabo la correspondiente eliminación de los ficheros objeto una
vez generado el ejecutable.

Una vez generado el ejecutable, se podrá llevar a cabo la ejecución. Para
ello, se ejecutará:


    $ ./calculadora


### Instrucciones de uso

Este intérprete tendrá una serie de características que permitirán al 
usuario poder trabajar de forma más cómoda. En primer lugar, cabe destacar
que el usuario puede realizar ciertas operaciones sin ver el resultado de
las mismas o pudiendo verlas. Esto se consigue mediante la inserción de un
**";"** al final de cada sentencia. Esto es:


    $ 1.43 + 2.5;
    > 3.93
    $ 1.43 + 2.5

    $

Se puede observar que en el primer caso se muestra el resultado de la
operación por pantalla debido a que al final de la sentencia se ha 
insertado el **";"**. En el segundo caso no se ha realizado dicha 
inserción, por lo que el resultado de la operación no se imprime. 
Además, el usuario contará con diferentes funcionalidades que le
permitirán interactuar con el intérprete de forma más cómoda:
- *Realización de operaciones matemáticas*: Como se ha mostrado
anteriormente, el usuario podrá realizar operaciones matemáticas
convencionales:


    $ (1.534 + 2.095) / (2.31 - 1);
    > 2.770229

- *Declaración y asignación de variables*: El usuario podrá declarar y
asignar un valor a ciertas variables. Para poder declarar y asignar variables,
el usuario deberá introducir el nombre de la variable e igualarlas a un valor.
Además, si una variable está creada, el usuario tendrá la posibilidad de modificar :


    $ a = 5.492

- *Llamadas a funciones matemáticas*: El usuario podrá llamar a funciones matemáticas 
declaradas en la librería matemática **math.h**. Cabe destacar que las
funciones matemáticas se cargan de forma dinámica a la tabla de símbolos, 
esto es, en primera instancia, el usuario no cuenta con ninguna función 
dentro de la tabla de símbolos, pero a medida que las va utilizando, estas
se van insertando para que posteriormente pueda acceder a ellas a través 
de la propia tabla de símbolos. Para su uso, cuando el usuario necesite 
realizar cálculos con una función determinada, simplemente deberá llamarla
para que se realice el cálculo de manera automática:


    $ sin(3 + 1.532);
    > -0.983774

- *Constantes matemáticas predefinidas*: El usuario tendrá a su disposición
ciertas constantes matemáticas con las que podrá realizar sus cálculos:


    $ PI + 3.1 - E;
    > 3.523311

- *Comandos predefinidos*: El usuario podrá utilizar diversos comandos
mediante los cuales visualizar diferente información o agilizar trabajo
al usuario:
  - **HELP**: Muestra ayuda al usuario por pantalla.
  - **WORKSPACE**: Muestra el espacio de trabajo del usuario (variables).
  - **TABLE**: Muestra el contenido de la tabla de símbolos (variables,
  funciones y constantes).
  - **CLEAR**: Limpia el WORKSPACE (elimina las variables de la tabla de 
  símbolos).
  - **LOAD**: Permite la carga de un archivo que contiene diferentes 
  comandos u operaciones para agilizar la ejecución en el intérprete.
  Después de la palabra clave *LOAD*, se deberá introducir el nombre del
  fichero que se desea cargar.
  - **EXIT**: Finaliza la ejecución del intérprete.