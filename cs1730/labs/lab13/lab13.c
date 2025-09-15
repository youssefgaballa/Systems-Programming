#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * Contains the code for the server program and the client program.
 * When the program runs with 3 command line arguments, it uses the server code
 * to listen and accept connections at the ip address and port specified
 * in the command line arguments. If the program runs with 4 command line arguments
 * it will run the client code which connects to the server (assuming the ip address
 * and port arguments are the same) and sends a message.
 */
int main(int argc, char * argv[]) {
    //if (argc == 3 || argc == 4) {
    // can't put in if statement or compiler will comlain that addrlen, saddr_in isn't initialized.
        struct sockaddr_in saddr_in;
        saddr_in.sin_family = AF_INET;
        saddr_in.sin_port = atoi(argv[2]);
        in_addr_t ipAddr = inet_addr(argv[1]);
        if (ipAddr < 0) {
            printf("Invalid ip-address using dot notation.\n");
            exit(0);
        }
        saddr_in.sin_addr.s_addr = ipAddr;
        socklen_t addrlen = sizeof(saddr_in);
        //}

    if (argc == 4) { // client code
        int client_sfd = socket(AF_INET, SOCK_STREAM, 0);
        if (client_sfd < 0) {
            printf("call to socket() failed for client.\n");
            //exit(0);
        }

        int status = connect(client_sfd, (struct sockaddr *) &saddr_in, addrlen);
        if (status < 0) {
            printf("Client failed a call to connect().\n");
            //exit(0);
        }
        int bytesSent = send(client_sfd, argv[3], strlen(argv[3]), 0);
        if (bytesSent < strlen(argv[3])) {
            printf("Client failed to send the message \"%s\"\n", argv[3]);
        }
        printf("The server recieved: %s\n", argv[3]);

        int close_client_sfd = close(client_sfd);
        if (close_client_sfd < 0) {
            printf("Client failed to close socket client_sfd.\n");
        }
        /*
    } else if (argc == 3)  { // server code
        int server_sfd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_sfd < 0) {
            printf("call to socket() failed for server.\n");
            //exit(0);
        }

        int bind_rv = bind(server_sfd, (struct sockaddr *) &saddr_in, addrlen);
        if (bind_rv != 0) {
            printf("Server failed a call to bind().\n");
            //exit(0);
        }

        int listen_rv = listen(server_sfd, 2);
        if (listen_rv != 0) {
            printf("Server failed a call to listen().\n");
        }
        printf("Server listening for connections on %s:%s\n", argv[1], argv[2]);
        int connection_sfd = accept(server_sfd,(struct sockaddr *) &saddr_in, &addrlen);
        if (connection_sfd < 0) {
            printf("Server failed to accept a connection.\n");
            //exit(0);
        }

        unsigned int size = 64;
        char * buffer = (char *) malloc(sizeof(char) * size); // can recieve up to 64 characters
        buffer[size - 1] = '\0';
        int bytesReceived = recv(connection_sfd, buffer, sizeof(char) * size, 0);
        if (bytesReceived < 0) {
            printf("Server failed to recieve the message.\n");
        }
        printf("The server recieved: %s\n", buffer);

        int close_server_sfd = close(server_sfd);
        if (close_server_sfd < 0) {
            printf("Server failed to close socket server_sfd.\n");
        }
        int close_connection_sfd = close(connection_sfd);
        if (close_connection_sfd < 0) {
            printf("Server failed to close socket connection_sfd.\n");
        }
        free(buffer);
        */
    } else {
        //printf("Usage for server: $%s <ip address> <port>\n", argv[0]);
        printf("Usage for client: $%s <ip address> <port> <message>\n", argv[0]);
    }
    return 0;
}
