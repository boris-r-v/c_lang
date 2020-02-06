

all:  main.c
	rm -f list-test
	gcc -Wall -Werror -Wpedantic -std=c11 main.c -o list-test


doc:
	doxygen ./doxygen.config

memcheck:
	valgrind  ./list-test

