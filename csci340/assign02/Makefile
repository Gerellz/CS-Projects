
# once you add matrix_sub.cc, you need to modify Makefile to include matrix_sub.cc as a dependency
matrix: matrix.cc matrix.h matrix_sub.cc
	g++ -std=c++11 -Wall -Wextra -pedantic -o matrix matrix.cc matrix_sub.cc

clean:
	rm matrix
