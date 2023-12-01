all: ccraft

ccraft: ccraft.c
	gcc -o ccraft ccraft.c 

clean:
	rm -f ccraft

run: ccraft
	./ccraft
