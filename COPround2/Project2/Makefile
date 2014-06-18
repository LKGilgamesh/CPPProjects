CXX = g++
CXXFLAGS = -c -std=c++11 -Wall
LDFLAGS = 

all: Project2

Project2: main.o Project2.o
	$(CXX) $(LDFLAGS) -o Project2 main.o Project2.o

main.o: main.cpp Project2.h
	$(CXX) $(CXXFLAGS) main.cpp

Project2.o: Project2.cpp Project2.h
	$(CXX) $(CXXFLAGS) Project2.cpp

clean:
	rm -rf *.o Project2