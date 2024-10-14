CXX = g++

CXXFLAGS = -std=c++11 -Wall -Wextra -I/usr/local/include/date

all: event

event: event.cpp
	$(CXX) $(CXXFLAGS) event.cpp -o event

run: event
	./event

clean:
	rm -f event

