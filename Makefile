CC = g++ -std=c++17

hashtagcounter: FibonacciHeap.o main.o
	$(CC) -o hashtagcounter FibonacciHeap.o main.o

main.o: main.cpp
	$(CC) -g -c main.cpp

FibonacciHeap.o: FibonacciHeap.cpp
	$(CC) -g -c FibonacciHeap.cpp

clean: 
	rm -f *.o
	rm -f *.out
	rm -f hashtagcounter