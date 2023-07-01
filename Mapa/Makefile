output: main.o mapa.o
	g++ main.o mapa.o -lm -Wall -lraylib -lGL -lpthread -ldl -lrt -lX11 -o output
	rm *.o
	./output

main.o: main.cpp
	g++ -c main.cpp -lm -Wall

mapa.o: mapa.cpp mapa.h
	g++ -c mapa.cpp -lm -Wall

clean:
	rm output