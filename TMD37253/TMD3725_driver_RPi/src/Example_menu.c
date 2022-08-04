#include <stdio.h>
#include "../include/registers.h"
#include "../include/i2c_pi.h"
#include "../include/color_alg.h"
#include "../include/data_get.h"
#include "../include/setting_ctrl.h"
#include "../include/example_1.h"
#include "../include/example_2.h"
#include "../include/example_3.h"

#define I2C_ADDRESS 0x39

int main() {

    int fd, ex_choice;
    int reginfo[35];
    optics_val color_data;

    //----- Init the sensor -----
    if ((fd = I2CSetup(I2C_ADDRESS)) != -1) {
        printf("TMD3725 is successfully setup at 0x%X\n", I2C_ADDRESS);
    }
    else { 
        printf("TMD3725 is not found on I2C bus.\n"); 
        return -1;
    }
    if ((get_data(fd, reginfo)) != -1) {
        printf("[DEVICE-0x%X]Successfully get all registers values\n", reginfo[16]);
    }
    else {
        printf("Can't read the register values of TMD3725.\n");
        return -1;
    }
    //----- -----
    
    //----- Settup commend ------/
    if ((set_atime(fd, reginfo, 32)) != -1) {
        printf("[DEVICE-0x%X]Set integration time to 32 integrated cycles.\n", reginfo[16]);
    } 
    else {
        printf("Failed to set integration time.\n");
        return -1;
    }
    if ((set_cfg1(fd, reginfo, 0, x4)) != -1) {
        printf("[DEVICE-0x%X]Set gain to 4x./n", reginfo[16]);
    }
    else {
        printf("Failed to set gain.\n");
    }
    if ((enable_sensor(fd, reginfo, 0, 0, 1)) != -1) {
        printf("[DEVICE-0x%X]Enable color integration cycle.\n", reginfo[16]);
    }
    else {
        printf("Failed to enable.\n");
        return -1;
    }
    //----- -----

    //----- Choose example function -----
    while (1) {
        printf("\nSelect an example from below to start the demonstration: \n"
               "-------------------------------------------------------- \n");
        printf("[Type 1]Example-1: Basic integration (one cycle)\n"
               "[Type 2]Example-2: Basic integration (ten cycle)\n"
               "[Type 3]Example-3: Auto adjustment for integration time\n"
               "[Type 0]QUIT\n");
        printf("-------------------------------------------------------- \n"
               "PLEASE SELECT: ");
        scanf("%d", &ex_choice);

        switch(ex_choice) {
            case 0:
                printf("Thanks for using.\n");
                return 0;
            case 1:
                example_1_basic_integra(fd, reginfo, color_data);
                break;
            case 2:
                example_2_basic_integra_10x(fd, reginfo, color_data);
                break;
            case 3:
                example_3_auto_adj_inttime(fd, reginfo);
            default:
                printf("Wrong Choice, thanks for using.\n");
                return 0;
        }
    }
    //----- -----

    return 0;
}