C++ = g++
# C++ = /usr/local/Cellar/gcc/8.2.0/bin/g++-8 # for re-linked g++ in Macs with Homebrew
C++FLAGS = -pedantic -Wall -Wextra -std=c++11

hotelTester:
	$(C++) $(C++FLAGS) -o hotelTester *.cpp 