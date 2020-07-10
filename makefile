all:./src/main.cpp
	cd ./lua && make all local
	clang++ ./src/main.cpp -o cppix.out -llua -ldl -L./lua/install/lib

test:./add.cpp
	cd ./lua && make all local
	clang++ ./add.cpp -o add.out -llua -ldl -L./lua/install/lib

debug:./src/main.cpp
	cd ./lua && make all local
	clang++ -g ./src/main.cpp -o cppix.out -llua -ldl -L./lua/install/lib

clean:
	rm -f cppix.out
