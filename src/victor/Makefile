VPATH=../jon

OBJS = main.o operator_plus.o fractional.o operator_mult.o function_power.o function_cos.o function_sin.o function_exp.o function_ln.o variable.o function.o operator.o
HEADERS = (patsubst %.o,%.hh,$(OBJS))
PROGRAM = main

CC = g++
LD = g++

CXXFLAGS += -g -I../jon

all : $(PROGRAM)

me :
	rm -f main.o
	$(CC) $(CXXFLAGS) -c -o main.o main.cpp

mini:
	rm -f main.o
	rm -f $(PROGRAM)

clean :
	rm -f $(OBJS)
	rm -f $(PROGRAM)

$(PROGRAM) : $(OBJS)
