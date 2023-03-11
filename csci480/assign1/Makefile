# Standard compiler variables
CXX = g++
CXXFLAGS = -Wall -g

# Rules
assign1: assign1.o
	$(CXX) $(CXXFLAGS) -o assign1 $^

assign1.o: assign1.cpp

clean:
	-rm assign1 *.o
