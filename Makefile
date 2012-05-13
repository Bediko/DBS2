#
# GNU makefile fuer DBS Aufgabe 2a
#=================================


# compiler options
#--------------------------------
CC = g++
CFLAGS = -Wall -g -I`pg_config --includedir`
LDFLAGS = -L`pg_config --libdir` -lstdc++

# project files
#--------------------------------
PROGRAM = dbimp
OBJECTS = main.o db.o


# rules
#----------------------------------
all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $+ $(LDFLAGS) -lpq 

# generic rule for compiling *.cpp -> *.o
%.o: %.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $*.cpp

clean:
	rm -f $(PROGRAM) $(OBJECTS)

