CC=gcc -std=gnu99
FC=gfortran

all: xintface
	$(FC) -o xintface *.co *.fo

xintface: Cintface.co Fintface.fo

clean :
	@rm -f Cintface.co Fintface.fo xintface

.SUFFIXES: .fo .co
.f.fo : 
	$(FC) -o $*.fo -c $*.f
.c.co : 
	$(CC) -o $*.co -c $*.c
