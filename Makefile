all: ccraft

ccraft: ccraft2.c
	gcc -o ccraft2 ccraft2.c 

clean:
	rm -f ccraft2
