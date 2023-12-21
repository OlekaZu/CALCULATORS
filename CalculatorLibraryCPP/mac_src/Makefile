GCC=g++
CPPFLAGS=-lstdc++ -std=c++17
LIBDIR=../lib_src
MODEL=Calculation.cpp Credit.cpp Deposit.cpp
LIBFLAGS=--verbose -dynamiclib

dylib:
	$(GCC) $(CPPFLAGS) $(LIBFLAGS) $(MODEL) -o libSmC.dylib

clean:
	rm -rf *.o *.dylib