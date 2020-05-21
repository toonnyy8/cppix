all:./src/main.cpp
	clang++ ./src/main.cpp -o cppix.out

clean:
	rm -f cppix.out
