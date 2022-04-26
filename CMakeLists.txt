cmake_minimum_required(VERSION 3.22)
project(practica3 C)

set(CMAKE_C_STANDARD 99)

add_executable(practica3 main.c ABB/abb.c GestionErrores/GestionErrores.c TablaSimbolos/TablaSimbolos.c semantico.tab.c lex.yy.c)

target_link_libraries(practica3 m)