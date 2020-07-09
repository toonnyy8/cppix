all:./src/main.cpp
	clang++ ./src/main.cpp -o cppix.out

debug:./src/main.cpp
	clang++ -g ./src/main.cpp -o cppix.out

clean:
	rm -f cppix.out
