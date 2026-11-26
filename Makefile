CXX ?= g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
SRC = $(wildcard src/*.cpp)

budget-buddy: $(SRC) $(wildcard src/*.h)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@

run: budget-buddy
	./budget-buddy

clean:
	rm -f budget-buddy

.PHONY: run clean
