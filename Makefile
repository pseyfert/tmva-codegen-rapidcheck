main.o: main.cc
	g++  -march=native -std=c++11 -m64 -O2 -g -Wextra -Wall -Wshadow  -c -o main.o main.cc

main: main.o
	g++ -pthread -lstdc++ -m64 -g -march=native -flto  main.o   -o main
