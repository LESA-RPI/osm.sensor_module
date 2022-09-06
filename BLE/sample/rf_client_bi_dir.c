#include <stdio.h>
#include <string.h>                 // for str manipulation funcs
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>                // for the threading process
// bluetooth and socket related libs
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

void recv_msg(int* server) {
    char* msg_buf = calloc(1024, sizeof(char)); // alloc heap for buffer
    int recv_sta;
    while((strcmp(msg_buf, "quit")) != 0) {
        strcpy(msg_buf, "");
        recv_sta = read(*server, msg_buf, 1024);
        printf("[received]\t%s\n", msg_buf);
    }
    write(*server, "quit", 5);
    printf("\nOffline......\n");
    free(msg_buf);
    close(*server);
    exit(0);
}

void send_msg(int* server) {
    char* msg = calloc(1024, sizeof(char));     // alloc heap for buffer
    while ((strcmp(msg, "quit")) != 0) {
        strcpy(msg, "");
        fgets(msg, 1024, stdin);
        *(msg + strlen(msg) - 1) = '\0';            // add ending char for string
        if( write(*server, msg, 1024) < 0 ) perror("uh oh");
    }
    write(*server, "quit", 5);
    free(msg);
    close(*server);
    exit(0);
}

int main(int argc, char **argv)
{
    struct sockaddr_rc addr = { 0 };
    int s, status;
    char dest[18] = "B8:27:EB:6E:E0:74";
    pthread_t thread_recv;

    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;      // specify the port number to connect to
    str2ba( dest, &addr.rc_bdaddr );

    // connect to server
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

    // send an init message and then start the communication process
    if( status == 0 ) {
        printf("COMM Line initialized.\n");
        status = write(s, "connected", 10);

        pthread_create(&thread_recv, NULL, (void *) recv_msg, &s);
        send_msg(&s);
    }

    // free memory
    pthread_exit(NULL);
    // close(s);
    return 0;
}