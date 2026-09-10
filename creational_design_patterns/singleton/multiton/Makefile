CC = g++
CFLAGS = -std=c++11 -Wall -pthread
DEBUG ?= 0

ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG
endif

SRCS = cloud_logger.cpp local_logger.cpp logger.cpp main.cpp
BINS = logger_demo

all: $(BINS)

$(BINS): $(SRCS) clean
	$(CC) $(CFLAGS) -o $@ $(SRCS)

clean:
	rm -f $(BINS) dummy_log.txt
