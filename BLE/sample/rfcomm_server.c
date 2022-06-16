#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

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

    // allocate socket, standard network stuff
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    // loc_addr.rc_channel = (uint8_t) 1;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);

    // accept the first pending connection and store the
    // device information in rem_addr
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);

    // print then clear the address
    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));

    // read data from the client
    bytes_read = read(client, buf, sizeof(buf));
    if( bytes_read > 0 ) {
        printf("RMT_side status [%s]\n", buf);
    }

    while(1) {
        char* msg_buf = calloc(1024, sizeof(char));
        bytes_read = read(client, msg_buf, 1024);
        if(bytes_read <= 0) {
            free(msg_buf);
            break;
        }
        printf("%s\n", msg_buf);
        free(msg_buf);
    }

    // close connection
    close(client);
    close(s);
    return 0;
}