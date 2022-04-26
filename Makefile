CC= gcc
CFLAGS = -Wall
HEADER_FILES_DIR = .
INCLUDES = -I $(HEADER_FILES_DIR)
EXEC= calculadora
SOURCE = main.c ABB/abb.c GestionErrores/GestionErrores.c TablaSimbolos/TablaSimbolos.c lex.yy.c sintactico.tab.c
DEPENDENCIES = lex.yy.h sintactico.tab.h ABB/abb.h GestionErrores/GestionErrores.h TablaSimbolos/TablaSimbolos.h
OBJECTS = $(SOURCE:.c=.o)
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXEC) -lm -ldl
	rm -f *.o
%.o: %.c $(DEPENDENCIES)
	$(CC) -c $< $(INCLUDES)
cleanall: 
	rm -f *.o *~
	rm -f $(EXEC)
