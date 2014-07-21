CXX = g++
CXXFLAGS = -c -Wall
LDFLAGS = 

all: Project3

Project3: COP3503su14_Proj3_main_Kian.o COP3503su14_Proj3_Kian.o tinyxml2.o
	$(CXX) $(LDFLAGS) COP3503su14_Proj3_main_Kian.o COP3503su14_Proj3_Kian.o  -o Project3

COP3503su14_Proj3_main_Kian.o: main.cpp COP3503su14_Proj3_Kian.h tinyxml2.h
	$(CXX) $(CXXFLAGS) COP3503su14_Proj3_main_Kian.cpp

COP3503su14_Proj3_Kian.o: COP3503su14_Proj3_Kian.cpp COP3503su14_Proj3_Kian.h tinyxml2.h
	$(CXX) $(CXXFLAGS) COP3503su14_Proj3_Kian.cpp

tinyxml2.o: tinyxml2.h tinyxml2.cpp
	$(CXX) $(CXXFLAGS) tinyxml2.cpp
clean:
	rm -rf *.o Project2