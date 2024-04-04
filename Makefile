all: gerabin principal clean

gerabin:
	gcc -c *.c

principal:
	gcc *.o -Wall -Wextra -o exec

clean:
	rm -rf *.o