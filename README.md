# hashtagcounter

The goal of the project is to implement a system to find the ‘n’ most popular hashtags that appear on social media such as Facebook or Twitter. To implement this, we are using – Max Fibonacci Heap and Hash Table. There is a large number of hashtags appearing in the stream and we need to perform insert, increase key and remove maximum operation many times. Max Fibonacci heap is recommended because it has an amortized complexity of O(1) for the increase key operation. For the hash table, we are using `<map>` container from STL provided by C++ programming language.

## File Structure
This project consists of 5 files –
1.	Makefile – Contains build settings for the project
2.	main.cpp – Contains the main application driver code
3.	FibonacciHeap.h – Contains Max Fibonacci Heap declarations and Node structure
4.	FibonacciHeap.cpp – Contains definitions for Max Fibonacci Heap and Node
5.	Defs.h – Contains additional application supporting code

## How to run

To run the project simply follow the commands below –
- To create an executable

		$ make
- To run the executable

		$ ./hashtagcounter [inputfile.txt] [outputfile.txt]
- To clean the project (does not delete the old output file

		$ make clean
