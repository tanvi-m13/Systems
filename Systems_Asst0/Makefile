all:simpleCSVsorter

simpleCSVsorter:simpleCSVsorter.h mergesort.c simpleCSVsorter.c
	gcc -Wall -Werror -fsanitize=address -lm mergesort.c simpleCSVsorter.c -o simpleCSVsorter

clean:
	rm -rf simpleCSVsorter
