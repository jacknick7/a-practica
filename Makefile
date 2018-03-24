OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x

all: main 1-binary-v1 2-hash-v1

main:
	g++ -o main.x main.cc $(OPCIONS)

1-binary-v1: 
	g++ -o 1-binary-v1.x 1-binary-v1.cc $(OPCIONS)

2-hash-v1: 
	g++ -o 2-hash-v1.x 2-hash-v1.cc $(OPCIONS)

clean:
	rm *.x
