all: 
	$(CC) -Wall -o sample main.c
	$(CC) -Wall -shared -fPIC -o urandom.so urandom.c -ldl
	$(CC) -Wall -shared -fPIC -o uprintf.so uprintf.c -ldl
clean: 
	rm -rf urandom.so uprintf.so sample
