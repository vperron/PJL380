
OBJS = main.o operator_plus.o fractional.o operator_mult.o function_power.o variable.o
HEADERS = (patsubst %.o,%.hh,$(OBJS))
PROGRAM = main

CC = g++
LD = g++

CXXFLAGS += -g

all : $(PROGRAM)
clean :
	rm -f $(OBJS)
	rm -f $(PROGRAM)

$(PROGRAM) : $(OBJS)
