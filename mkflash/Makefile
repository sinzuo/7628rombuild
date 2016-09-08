
CC=gcc

all:cpe
	@echo 

makeflash:makeflash.c
	gcc -o makeflash makeflash.c

cpe:makeflash
	cp makeflash ../util/.


clean:
	rm makeflash -f
	rm *.o -f

