CC=g++
TARGET=genetics
DEBUG=
LFLAGS=-Wall $(DEBUG)
CFLAGS=-Wall $(DEBUG) -c -O3
FRAMEWORKS=-lpthread
DEPS= PDParam.o PIDAlgo.o PID1DProcessor.o gsl/libgsl.a rand.o

all: $(TARGET)

$(TARGET) : main.cpp $(DEPS) God.hpp Heap.hpp
	    $(CC) $(LFLAGS) main.cpp -o $(TARGET) $(FRAMEWORKS) $(DEPS)

PDParam.o : PDParam.cpp PDParam.hpp Param.hpp
	$(CC) $(CFLAGS) $<

PIDAlgo.o : PIDAlgo.cpp PIDAlgo.hpp Algo.hpp Param.hpp rand.h
	$(CC) $(CFLAGS) $<

PID1DProcessor.o : PID1DProcessor.cpp PID1DProcessor.hpp Processor.hpp Algo.hpp
	$(CC) $(CFLAGS) $<

rand.o : rand.c rand.h
	$(CC) $(CFLAGS) $<

gsl/libgsl.a : FORCE_MAKE
	cd gsl && make

FORCE_MAKE :
	true

.IGNORE .PHONY clean :
	rm $(TARGET)
	rm *.o
	rm -r $(TARGET).dSYM
	cd gsl && make clean
