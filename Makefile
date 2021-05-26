CXX = g++
CXXFLAGS = -c -g -Wall -W -Werror -pedantic
LDFLAGS =

testBigInt: testBigInt.o BigInt.o
	$(CXX) $(LDFLAGS) testBigInt.o BigInt.o -o testBigInt

testBigInt.o: testBigInt.cpp BigInt.h
	$(CXX) $(CXXFLAGS) testBigInt.cpp

BigInt.o: BigInt.cpp BigInt.h
	$(CXX) $(CXXFLAGS) BigInt.cpp

clean:
	rm -f *o testBigInt
