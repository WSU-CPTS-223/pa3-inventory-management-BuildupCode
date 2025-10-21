out: clean compile execute

compile: $(wildcard src/*.cpp)
	g++ -g -Wall -std=c++11 -Iinclude $^ -o mainexe

execute: mainexe
	./mainexe

clean:
	rm -f mainexe