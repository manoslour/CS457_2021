all: crypto

crypto: hy457_crypto.o main.c
	gcc -o crypto main.c hy457_crypto.o

hy457_crypto.o: hy457_crypto.c
	gcc -c hy457_crypto.c

clean:
	rm *o