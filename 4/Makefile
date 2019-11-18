a.out: a.o md5.o
	gcc -o a.out a.o md5.o

a.o: a.c md5.h
	gcc -c a.c

md5.o: md5.c md5.h
	gcc -c md5.c
