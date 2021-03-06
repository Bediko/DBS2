#
# GNU makefile fuer DBS Aufgabe 2a
#=================================


# compiler options
#--------------------------------
CC = g++ #compiler
CFLAGS = -Wall -g -I`pg_config --includedir` #compilerflags Wall= Alle Warnungen -g Debugging an -I includeverzeichnis 
LDFLAGS = -L`pg_config --libdir` -lstdc++    #Compilerflags für Libs libpq und STL

# project files
#--------------------------------
PROGRAM = dbimp	#Name des executables
OBJECTS = main.o db.o	#Name der binaries


# rules
#----------------------------------
all: $(PROGRAM)			
						#name des Gesamtoutputs(Programmname) (make all)

$(PROGRAM): $(OBJECTS)				
	$(CC) -o $@ $+ $(LDFLAGS) -lpq 	#Regeln für linking von libpq mit compilierten binaries

# generic rule for compiling *.cpp -> *.o
%.o: %.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $*.cpp 	#Compilierregel für benötigte cpp-dateien

clean:
	rm -f $(PROGRAM) $(OBJECTS)			#Löschen des Programms

