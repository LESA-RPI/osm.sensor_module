#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main(int argc, char **argv)
{
    struct sockaddr_rc addr = { 0 };
    int s, status;
    char dest[18] = "B8:27:EB:6E:E0:74";

    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );

    // connect to server
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

    // send a message
    if( status == 0 ) {
        printf("COMM Line initialized.\n");
        status = write(s, "connected", 10);
        while (1) {
            char* msg = calloc(1024, sizeof(char));
            fgets(msg, 1024, stdin);
            *(msg + strlen(msg) - 1) = '\0';

            if (strlen(msg) == 0) {
                free(msg);
                break;
            }
            status = write(s, msg, 1024);
            free(msg);
        }
    }

    if( status < 0 ) perror("uh oh");

    close(s);
    return 0;
}