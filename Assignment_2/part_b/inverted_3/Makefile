invert : inverted.o InvertedIdx.o DLListStr.o
	gcc -o invert inverted.o InvertedIdx.o DLListStr.o

InvertedIdx.o : InvertedIdx.h InvertedIdx.c
	gcc -c InvertedIdx.h InvertedIdx.c 

inverted.o: inverted.c
	gcc -c inverted.c

DLListStr.o: DLListStr.c DLListStr.h
	gcc -c DLListStr.c DLListStr.h 