OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x

all: main binaryv1

main:
	g++ -o main.x main.cc $(OPCIONS)

binaryv1: 
	g++ -o binaryV1.x binaryV1.cc binaryV1.hh $(OPCIONS)

clean:
	rm *.x
