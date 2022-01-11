CC=g++ -c -g  -Wall -ansi -pedantic -std=c++11

runMe:  Interactor.o Polynomial.o Term.o Token.o
	g++ -o runMe Interactor.o Polynomial.o Term.o Token.o

Interactor.o: Interactor.cpp Term.cpp Polynomial.cpp
	$(CC) Interactor.cpp
	
Polynomial.o:  Polynomial.cpp Polynomial.hpp 
	$(CC) Polynomial.cpp
	
Term.o:  Term.hpp Term.cpp
	$(CC) Term.cpp

Token.o: Token.hpp Token.cpp
	$(CC) Token.cpp	
