GCC = gcc
SOURCES = $(wildcard *.c)
BINAIRES = $(patsubst %.c,%.o,${SOURCES})

all: main

main: ${BINAIRES}
	${GCC} $^ -o $@

%.o: %.c
	${GCC} -c $<
	
clean:
	rm main
	rm *.o
