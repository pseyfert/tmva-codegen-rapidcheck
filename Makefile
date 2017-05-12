
threadtest.o: threadtest.cc
	g++  -Irapidcheck/include -march=native -std=c++14 -m64 -O2 -g -Wextra -Wall  -c -o $@ $^

test.o: test.cc
	g++  -Irapidcheck/include -march=native -std=c++14 -m64 -O2 -g -Wextra -Wall  -c -o $@ $^

threadtest: threadtest.o
	g++ -pthread -lstdc++ -m64 -g -march=native -flto  $^ rapid.build/librapidcheck.a -o $@

test: test.o
	g++ -pthread -lstdc++ -m64 -g -march=native -flto  $^ rapid.build/librapidcheck.a -o $@

%.o: %.cc
	g++  -march=native -std=c++11 -m64 -O2 -g -Wextra -Wall -Wshadow  -c -o $@ $^

%: %.o
	g++ -pthread -lstdc++ -m64 -g -march=native -flto  $^   -o $@

rapidcheck:
	mkdir -p rapid.build
	(cd rapid.build; cmake ../rapidcheck -DCMAKE_INSTALL_PREFIX=../install; cmake --build .; cmake --target install)

.PHONY: rapidcheck
