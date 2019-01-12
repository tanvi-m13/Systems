all:scannerCSVsorter

scannerCSVsorter:scannerCSVsorter.h mergesort.c scannerCSVsorter.c
	gcc -Wall -Werror -fsanitize=address -lm mergesort.c scannerCSVsorter.c -o scannerCSVsorter

clean:
	rm -rf scannerCSVsorter
