
#NDK

CC = gcc 
AR = ar 

FLAGS = 

#src-y = src/vcos-logic.c
src-y = $(wildcard *.c) 
#${info ${src-y}}

obj-y = $(patsubst %.c, %.o, ${src-y}) $(wildcard *.a)
#${info ${obj-y}}

all: build

build: testvcos.out

%.o:%.c inc.h
	${CC} ${FLAGS} -o $@  -c $< 

testvcos.out: ${obj-y}
	${CC} $^ -o $@
	
clean:
	@find . -name "*.o" -exec rm {} \;
	@find . -name "*.out" -exec rm {} \;
