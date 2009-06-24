
OBJS = main.o operator_plus.o fractional.o operator_mult.o function_power.o variable.o operator.o function.o function_sin.o function_cos.o function_exp.o function_ln.o
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
