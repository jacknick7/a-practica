OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x

binarySearch: 
	g++ -o binarySearch binarySearch.cc $(OPCIONS)


clean:
	rm *.exe
