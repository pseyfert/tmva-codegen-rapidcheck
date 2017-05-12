test.o: test.cc
	g++  -Irapidcheck/include -march=native -std=c++14 -m64 -O2 -g -Wextra -Wall  -c -o test.o test.cc

test: test.o
	g++ -pthread -lstdc++ -m64 -g -march=native -flto  test.o rapid.build/librapidcheck.a -o test

main.o: main.cc
	g++  -march=native -std=c++11 -m64 -O2 -g -Wextra -Wall -Wshadow  -c -o main.o main.cc

main: main.o
	g++ -pthread -lstdc++ -m64 -g -march=native -flto  main.o   -o main

rapidcheck:
	mkdir -p rapid.build
	(cd rapid.build; cmake ../rapidcheck -DCMAKE_INSTALL_PREFIX=../install; cmake --build .; cmake --target install)

.PHONY: rapidcheck
