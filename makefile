all:./src/main.cpp
	cd ./lua && make all local
	clang++ ./src/main.cpp -o cppix.out -Wall -std=c++1z -llua -ldl -L./lua/install/lib -I./ -I./lua/install/include

debug:./src/main.cpp
	cd ./lua && make all local
	clang++ -g ./src/main.cpp -o cppix.out -Wall -std=c++1z -llua -ldl -L./lua/install/lib -I./ -I./lua/install/include

clean:
	rm -f cppix.out
