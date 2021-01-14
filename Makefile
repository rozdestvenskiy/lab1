.PHONY: all 

all:
		gcc -fPIC -w -c mac.c
		gcc -shared -o mac.so mac.o
		gcc main.c -o lab1 -ldl -w
		rm -rf mac.o		

