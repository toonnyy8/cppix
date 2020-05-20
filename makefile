all:./src/main.cpp
	clang++ ./src/main.cpp -o main.out

clean:
	rm -f main.out
