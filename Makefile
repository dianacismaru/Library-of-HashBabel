# Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

TARGETS=commands.o hashtable.o utilities.o
CFLAGS=-g -Wall -Wextra -std=c99

VG=valgrind
VFLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes \
       --verbose

build: clean $(TARGETS)
	gcc $(CFLAGS) -o main $(TARGETS) main.c -lm
	rm -f $(TARGETS)

run-vg: build
	$(VG) $(VFLAGS) --log-file=VG_LOG.txt ./main

commands.o: commands.c
	$(CC) $(CFLAGS) -c -o $@ $^

hashtable.o: hashtable.c
	$(CC) $(CFLAGS) -c -o $@ $^

utilities.o: utilities.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f main *.o

pack:
	zip -FSr 311CA_CismaruDianaIuliana_Tema2_SD.zip README.md Makefile *.c *.h

.PHONY: pack clean
