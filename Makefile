all: test
	./test

test.o: test.cc
	g++  -Irapidcheck/include -march=native -std=c++14 -m64 -O2 -g -Wextra -Wall  -c -o $@ $^

test: test.o rapidcheck
	g++ -pthread -lstdc++ -m64 -g -march=native -flto  $< rapid.build/librapidcheck.a -o $@

test_xml.o: test_xml.cc
	g++  -Irapidcheck/include -I$(shell root-config --cflags) -march=native -std=c++14 -m64 -O2 -g -Wextra -Wall  -c -o $@ $^

test_xml: test_xml.o rapidcheck
	g++ -pthread -lstdc++ -m64 -g $(shell root-config --libs) -lTMVA -march=native -flto  $< rapid.build/librapidcheck.a -o $@

rapidcheck:
	mkdir -p rapid.build
	mkdir -p install
	(cd rapid.build && cmake ../rapidcheck -DCMAKE_INSTALL_PREFIX=../install && cmake --build .)

.PHONY: rapidcheck
