CXX = g++
CXXFLAGS = -Wall -g

Solitaire.o: Solitaire.cpp Solitaire.h
	$(CXX) $(CXXFLAGS) -c Solitaire.cpp
