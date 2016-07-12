#Makefile para el programa final de programacion.

CXX=g++
CFLAGS=
LDFLAGS=-L/usr/lib -liballegro -liballegro_primitives -liballegro_image -liballegro_acodec -liballegro_font -liballegro_ttf -liballegro_main -lm 
INCLUDE= -I/usr/include/allegro5 


OBJS = main.o Resistor.o allegro.o node.o programCore.o SetValue.o
OUT = program

all: program
	
clear:
	rm -rf *.o program
	
program: $(OBJS)
	$(CXX) -o $(OBJS) $(OUT) $(INCLUDE) $(CFLAGS) $(LDFLAGS)
	
main.o: main.cpp def.h allegro.h programCore.h Resistor.h
	$(CXX) -c main.cpp 

Resistor.o: Resistor.cpp Resistor.h
	$(CXX) -c Resistor.cpp
	
allegro.o: allegro.cpp allegro.h def.h
	$(CXX) -c allegro.cpp

node.o: node.cpp Node.h
	$(CXX) -c node.cpp

programCore.o: programCore.cpp programCore.h setValue.h
	$(CXX) -c programCore.cpp

setValue.o: setValue.cpp setValue.h def.h
	$(CXX) -c setValue.cpp
	

