OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x

all: main

main:
	g++ -o main.x *.cc *.hh $(OPCIONS)

clean:
	rm *.x
