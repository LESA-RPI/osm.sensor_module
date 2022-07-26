# makefile for TMD3725 driver and code

# compiler and command
CC = gcc
CFLAGS = -Wall
INCLUDE = -I../include

# source codes
SRCS = i2c_pi.c color_alg.c data_get.c test.c

# object codes
OBJS = $(SRCS:.c=.o)

# execution file name
TARGET = TMD3725_test

.PHONY: all clean

all: $(TARGET)
	@echo TMD3725_test has been compiled

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $<  -o $@

# clean all the object codes
clean:
	$(RM) *.o