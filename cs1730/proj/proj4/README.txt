Youssef Gaballa (810-118-509)

Compilation Command:
$ make
OR
gcc -Wall -pedantic-errors proj4.c -g -c -pthread
gcc -Wall -pedantic-errors main.c -g -c
gcc -Wall -pedantic-errors main.o proj4.o -g -o proj4.out -pthread

Run Command:
$ ./proj4.out <input file> <output file> <sum> <# threads>


Findings:
Small grids using 1 vs 3 threads:
$ ./proj4.out in1.txt out1.txt 10 1
completed in 0.000003 seconds
$ ./proj4.out in1.txt out1.txt 10 3
completed in 0.000163 seconds.
It took longer with 3 threads becaue of the overhead in
creating new threads.

Large Grids:
$ ./proj4.out in4.txt out4.txt 13 2
completed in 0.531051 seconds.
$ ./proj4.out in5.txt out5.txt 1222 3
completed in 32.440324 seconds.
