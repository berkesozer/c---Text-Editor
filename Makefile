target: compile run

compile: main.cpp
	g++ main.cpp -o main -Wall -Werror -g

run:
	./main