all:./src/main.cpp
	clang++ ./src/main.cpp -o cppix.out -Wall -std=c++1z -llua -ldl -L./lua/install/lib

debug:./src/main.cpp
	clang++ -glldb ./src/main.cpp -o cppix.out -Wall -std=c++1z -llua -ldl -L./lua/install/lib

clean:
	cd ./lua && make clean
	rm -f cppix.out

lua:dummy
	cd ./lua && make all local

dummy: