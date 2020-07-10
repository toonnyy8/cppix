all:./src/main.cpp
	clang++ ./src/main.cpp -o cppix.out -llua -ldl -L./lua/lib

debug:./src/main.cpp
	clang++ -g ./src/main.cpp -o cppix.out -llua -ldl -L./lua/lib

clean:
	rm -f cppix.out
