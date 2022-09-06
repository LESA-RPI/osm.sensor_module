#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <pthread.h>                // for the threading process

typedef struct comm_info_pack {
    int client;
    int s;
} cip;

void recv_msg(cip* info) {
    char* msg_buf = calloc(1024, sizeof(char));     // alloc heap for buffer
    int recv_sta;
    while((strcmp(msg_buf, "quit")) != 0) {
        strcpy(msg_buf, "");
        recv_sta = read(info->client, msg_buf, 1024);
        printf("[received]\t%s\n", msg_buf);
    }
    write(info->client, "quit", 5);
    printf("Offline......\n");
    free(msg_buf);
    close(info->client);
    close(info->s);
    exit(0);
}

void send_msg(cip* info) {
    char* msg = calloc(1024, sizeof(char));         // alloc heap for buffer
    while ((strcmp(msg, "quit")) != 0) {
        strcpy(msg, "");
        fgets(msg, 1024, stdin);
        *(msg + strlen(msg) - 1) = '\0';                // add ending char for string
        if( write(info->client, msg, 1024) < 0 ) perror("uh oh");
    }
    write(info->client, "quit", 5);
    free(msg);
    close(info->client);
    close(info->s);
    exit(0);
}

int main(int argc, char **argv)
{
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    /*
    struct sockaddr_rc {
        sa_family_t	rc_family;
        bdaddr_t	rc_bdaddr;
        uint8_t		rc_channel;
    };
    */
    char buf[1024] = { 0 };
    int s, client, bytes_read;
    socklen_t opt = sizeof(rem_addr);
    pthread_t thread_recv;
    cip info_pack;

    // let device be detectable
    system("sudo hciconfig -a hci0 piscan");
    // allocate socket, standard network stuff
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;      // specify the port number to use
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);

    // accept the first pending connection and store the
    // device information in rem_addr
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);

    // print then clear the address
    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "[Accepted connection from %s]\n", buf);
    memset(buf, 0, sizeof(buf));

    // read data from the client
    bytes_read = read(client, buf, sizeof(buf));
    if( bytes_read > 0 ) {
        // remain connected but let it be undetactable
        system("sudo hciconfig -a hci0 noscan");
        printf("Client status [%s]\n\nMSG:\n", buf);
    }

    info_pack.client = client;
    info_pack.s = s;

    pthread_create(&thread_recv, NULL, (void *) send_msg, &info_pack);
    recv_msg(&info_pack);

    // close connection
    pthread_exit(NULL);
    // close(client);
    // close(s);
    return 0;
}