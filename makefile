CC=g++
STD=c++17

main: lexicalinterp.cpp lexicalinterp.cpp
	$(CC) -o ./builds/lexical -std=$(STD) ./lexicalinterp.cpp
