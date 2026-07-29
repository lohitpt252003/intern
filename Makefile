CXX ?= c++
CXXFLAGS ?= -O2 -Wall -Wextra -std=c++17

all: sender receiver

sender: sender.c
	$(CXX) $(CXXFLAGS) -o sender sender.c

receiver: receiver.c
	$(CXX) $(CXXFLAGS) -o receiver receiver.c

clean:
	rm -f sender receiver
