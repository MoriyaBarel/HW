CC=gcc
AR=ar
FLAGS= -Wall -g


all: libans.a  stringProg
 
stringProg :  main.o libans.a
	$(CC) $(FLAGS) -o stringProg main.o libans.a

ans.o: ans.c ans.h
	$(CC) $(FLAGS) -c ans.c

libans.a: ans.o 
	$(AR) -rcs libans.a ans.o 

main.o: main.c ans.h
	$(CC) $(FLAGS) -c main.c

clean:
	rm -f *.o *.a stringProg

.PHONY: clean all