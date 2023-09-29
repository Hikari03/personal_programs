all: calculator

calculator: main.o Calculator.o
	g++ -o calculator main.o Calculator.o
	rm -f Calculator.o main.o

main.o: main.cpp
	g++ -c main.cpp -o main.o

Calculator.o: Calculator.cpp Calculator.h
	g++ -c Calculator.cpp -o Calculator.o