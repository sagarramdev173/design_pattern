CC = g++
CFLAGS = -std=c++11 -Wall

SRCS = $(wildcard *.cpp)
BINS = $(SRCS:.cpp=)

all: $(BINS)

%: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(BINS)