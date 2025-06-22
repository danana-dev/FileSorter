all: fileSorter.o

run:
	./fileSorter.o

fileSorter.o: fileSorter.cpp
	g++ -Wall fileSorter.cpp -o fileSorter.o

clean:
	rm *.o