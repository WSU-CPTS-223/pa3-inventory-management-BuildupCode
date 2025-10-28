out: clean compile execute

compile: main.cpp inventory.cpp parser.cpp product.cpp hashmap.h vector.h
	g++ -g -Wall -std=c++11 -Iinclude $^ -o mainexe

execute: mainexe
	./mainexe

test: simple_test.cpp inventory.cpp parser.cpp product.cpp hashmap.h vector.h
	g++ -g -Wall -std=c++11 -Iinclude $^ -o testexe

runtest: test
	./testexe

clean:
	rm -f mainexe testexe
