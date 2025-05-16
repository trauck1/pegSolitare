CXX = g++
CXXFLAGS = -Wall

driver: solitaire.o  driver.cpp
	$(CXX) $(CXXFLAGS) solitaire.o driver.cpp -o driver

mytest: solitaire.o  driver.cpp
	$(CXX) $(CXXFLAGS) solitaire.o mytest.cpp -o mytest

solitaire.o: solitaire.cpp solitaire.h
	$(CXX) $(CXXFLAGS) -c solitaire.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./driver

runTest:
	./mytest
