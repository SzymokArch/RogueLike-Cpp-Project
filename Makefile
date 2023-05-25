output: main.cpp
	g++ main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -o output
	./output
clean:
	rm output