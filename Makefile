OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x

all: main binaryv1

main:
	g++ -o main.x *.cc *.hh $(OPCIONS)

binaryv1: 
	g++ -o binaryV1.x main.cc binaryV1.cc binaryV1.hh $(OPCIONS)

clean:
	rm *.x
