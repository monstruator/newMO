#
#  Makefile for USOI utils
#

all: cu

cu: cu.c
	cc -ms -o cu cu.c

clean:
	rm -f *.o *.err *.i

spotless: clean
	rm -f cu

install:
	-cp -vnf cu /usr/local/bin
