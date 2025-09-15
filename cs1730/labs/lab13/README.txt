Youssef Gaballa (810-118-509)

Compilation command:
$ make
OR
$ gcc -Wall -pedantic-errors lab13.c -o lab13.out

Run Command:
Finding an ip-address and port:
First find the ip address of the vcf nodes using
$ nslookup vcf<int>.cs.uga.edu
OR
$ host vcf<int>.cs.uga.edu
where <int> = {0, 1, 2, 3} cooresponding to one of the four vcf nodes.

Server Program:
After that run the server program with three command-line arguments
with two of them cooresponding to the ip-address and port for the server
to listen for connections. Note that the grader will use their own server program
so I have the server code commented out. So for the program to run with the lab13.c
implementation of the server code (the command below), it should be uncommented.
$ ./lab13.out <ip-address> <port>

Client Program:
Use the same ip-address and port obtained above to run the client code with a message
to send to the server, using 4 command line arguments in total.
$ ./lab13.out <ip-address> <port> "<message>"
