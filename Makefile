output: main.o mapa.o entity.o bullet.o
	g++ main.o mapa.o entity.o bullet.o -lm -Wall -lraylib -lGL -lpthread -ldl -lrt -lX11 -o output
	rm *.o
	./output

main.o: main.cpp
	g++ -c main.cpp -lm -Wall

bullet.o: bullet.cpp bullet.h
	g++ -c bullet.cpp -lm -Wall

entity.o: entity.cpp entity.h
	g++ -c entity.cpp -lm -Wall

mapa.o: mapa.cpp mapa.h
	g++ -c mapa.cpp -lm -Wall

clean:
	rm output
