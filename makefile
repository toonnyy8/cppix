all:./src/main.cpp
	cd ./lua && make all local
	clang++ -Wall -std=c++1z -llua -ldl -L./lua/install/lib -I./ -I./lua/install/include ./src/main.cpp -o cppix.out

debug:./src/main.cpp
	cd ./lua && make all local
	clang++ -Wall -std=c++1z -llua -ldl -L./lua/install/lib -I./ -I./lua/install/include -g ./src/main.cpp -o cppix.out

clean:
	rm -f cppix.out
