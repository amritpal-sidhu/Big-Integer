CXX = g++
CXXFLAGS = -c -g -W -Werror -pedantic
LDFLAGS =

testBigInt.exe: testBigInt.o BigInt.o
	$(CXX) $(LDFLAGS) testBigInt.o BigInt.o -o testBigInt.exe

testBigInt.o: testBigInt.cpp BigInt.h
	$(CXX) $(CXXFLAGS) testBigInt.cpp

BigInt.o: BigInt.cpp BigInt.h
	$(CXX) $(CXXFLAGS) BigInt.cpp

clean:
	rm -f *o testBigInt.exe
