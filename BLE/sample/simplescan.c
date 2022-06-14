#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main(int argc, char **argv)
{
    inquiry_info *ii = NULL;
    /*
    typedef struct {
        bdaddr_t    bdaddr;
        uint8_t     pscan_rep_mode;
        uint8_t     pscan_period_mode;
        uint8_t     pscan_mode;
        uint8_t     dev_class[3];
        uint16_t    clock_offset;
    } __attribute__ ((packed)) inquiry_info;
    */
    int max_rsp, num_rsp;
    int dev_id, sock, len, flags;
    int i;
    char addr[19] = { 0 };
    char name[248] = { 0 };
    
    // specify which BLE adapter to use, NULL will give the
    // resource number for the default one
    dev_id = hci_get_route(NULL);
    // enable the BLE adapter with the dev_id to socket
    sock = hci_open_dev( dev_id );
    // check if the above steps have errors or not
    if (dev_id < 0 || sock < 0) {
        perror("opening socket");
        exit(1);
    }

    len  = 8;                   // last for 1.28*len seconds
    max_rsp = 255;              // max devices that will be return
    // IREQ_CACHE_FLUSH - previous detected cache will be flushed
    // 0 - previous data may get involved
    flags = IREQ_CACHE_FLUSH;
    // ii is where devices are stored
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
    // actual number of bluetooth device found
    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
    if( num_rsp < 0 ) perror("hci_inquiry");


    for (i = 0; i < num_rsp; i++) {
        // read addr and convert back to "XX:XX" form
        ba2str(&(ii+i)->bdaddr, addr);
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), 
            name, 0) < 0)
        strcpy(name, "[unknown]");
        printf("%s  %s\n", addr, name);
    }

    free( ii );
    close( sock );
    return 0;
}
