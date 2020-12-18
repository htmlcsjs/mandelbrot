CXXFLAGS = -Wall -g
LDFLAGS = 

all: main

main: 
	$(CXX) $(CXXFLAGS) -o $@.out $@.cpp $^ $(LDFLAGS)

test:
	$(CXX) $(CXXFLAGS) -o $@.out $@.cpp $^ $(LDFLAGS)

install:
	cp main.out /usr/local/bin/fractal 

check: main
	./main.out 

clean:
	$(RM) main.out
	$(RM) aurman.o
	$(RM) test.out
