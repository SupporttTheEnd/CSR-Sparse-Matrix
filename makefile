CXX = g++
CXXFLAGS = -Wall

p: mytest.cpp csr.o 
	$(CXX) $(CXXFLAGS) mytest.cpp csr.o -o proj1

d: driver.cpp csr.o 
	$(CXX) $(CXXFLAGS) driver.cpp csr.o -o proj1

csr.o: csr.h csr.cpp
	$(CXX) $(CXXFLAGS) -c csr.cpp

clean:
	rm *.o*
	rm *~ 

v:
	valgrind --leak-check=full --track-origins=yes ./proj1

r:
	./proj1
