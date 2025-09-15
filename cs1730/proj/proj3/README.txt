Youssef Gaballa (810-118-509)

Compilation Command:
$ make
OR
$ gcc -Wall -pedantic-errors proj3.c -g -o proj3.out

Run Command:
$ ./proj3.out <cmd>
where <cmd> are two input text files.

Step 1 is longer than step 2 since we are reading and writing one byte at a time, so a call to
read and write is needed for each character in the files.
Wheras for step 2 all that is needed are two calls to read() for each of the files (to put
their contents in two different buffers) with a loop to copy the different characters from
file 2.
