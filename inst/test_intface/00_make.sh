#!/bin/sh

CC=`${R_HOME}/bin/R CMD config CC`
FC=`${R_HOME}/bin/R CMD config FC`

${CC} -c *.c
${FC} -c *.f
${FC} -o xintface *.o

./xintface
rm -f *.o xintface > /dev/null
