#
# PROGRAM:    Assignment 7
# PROGRAMMER: your name
# LOGON ID:   your z-id
# DATE DUE:   due date of program
#
    
# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11 -g
        
# Rule to link object code files to create executable file
inpost: inpost_main.o inpost.o mystack.o
	$(CXX) $(CXXFLAGS) -o inpost $^

mystacktest: mystacktest.o mystack.o
	$(CXX) $(CXXFLAGS) -o mystacktest $^

# Rules to compile source code file to object code
inpost_main.o: inpost_main.cpp inpost.h
inpost.o: inpost.cpp inpost.h mystack.h
mystack.o: mystack.cpp mystack.h
mystacktest.o: mystacktest.cpp mystack.h

# Pseudo-target to remove object code and executable files
clean:
	rm -f inpost *.o
