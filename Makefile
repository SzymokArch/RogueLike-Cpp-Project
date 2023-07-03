output: main.o mapa.o movement.o
	g++ main.o mapa.o movement.o -lm -Wall -lraylib -lGL -lpthread -ldl -lrt -lX11 -o output
	rm *.o
	./output

main.o: main.cpp
	g++ -c main.cpp -lm -Wall

movement.o: movement.cpp movement.h
	g++ -c movement.cpp -lm -Wall -lraylib

mapa.o: mapa.cpp mapa.h
	g++ -c mapa.cpp -lm -Wall

clean:
	rm output
