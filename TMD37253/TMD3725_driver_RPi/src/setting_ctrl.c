/*
 * This is the code for setting some of the control parameters we usually setup before 
 * integration, such as gain and integration time. More functions will be added to this
 * file to account for more advanced settings. 
 * 
 * Note:
 * - the integration adjustment algorithm implements a bound to bound control method 
 *   instead of PID control, since we don't have a strictly desired integration time
 * 
 * Author: You Wu
 * Date: 08/02/2022
 */

#include <stdlib.h>
#include "../include/data_get.h"
#include "../include/setting_ctrl.h"
#include "../include/i2c_pi.h"
#include "../include/registers.h"

void auto_inttime_adj(int fd, int reginfo[]) {
    /*
     * FUNCTION: Adjust the integration time automatically once started in a thread
     * ---------
     * INPUT: fd - the file descriptor of the i2c device
     *        reginfo[35] - current values of all registers
     * RETURN: void
     */
    
    int* max_als_limit = calloc(1, sizeof(int));
    int* uplimit = calloc(1, sizeof(int));
    int* lowlimit = calloc(1, sizeof(int));
    optics_val testread;

    while (1) {
        *max_als_limit = (reginfo[1] * 1024)-1;     // read the current integration time and set the 
        *uplimit = 0.9*(*max_als_limit);            // limit for checking integration time dynamically
        *lowlimit = 0.1*(*max_als_limit);

        if (AUTOINTTIMETEST_FLAG) {                     // some testing print for this function, in read application
            testread = get_calib_color(fd, reginfo);    // the flag can be change to 0 to stop the printing, the flag
            print_color(testread);                      // is in header file
            printf("Current ALS max is: %u", *max_als_limit);
        }

        if ((get_raw_clear > *uplimit) && (get_raw_clear < *max_als_limit)) {   // if value is on the upper bound, then decrease integration time
            reginfo[1] = reginfo[1] - 10;
            I2CSetreg(fd, ATIME_ADDR, reginfo[1]);
        }
        else if ((get_raw_clear < *lowlimit) && (get_raw_clear > 0)) {          // if value is on the lower bound, then increase integration time
            reginfo[1] = reginfo[1] + 10;
            I2CSetreg(fd, ATIME_ADDR, reginfo[1]);
        }
    }
    
    return;
}

int enable_sensor(int fd, int reginfo[], int wait_flag, int prox_flag, int als_flag) {
    /*
     * FUNCTION: Change the enable register settings
     * ---------
     * INPUT: fd - the file descriptor of the i2c device
     *        reginfo[35] - current values of all registers
     *        wait_flag - 1 to enable wait feature, 0 to disable wait feature
     *        prox_flag - 1 to enable proximity feature, 0 to disable wait feature
     *        als_flag - 1 to enable als feature, 0 to disable wait feature
     * RETURN: 0 - success
     *         -1 - error
     */

    if (wait_flag) { reginfo[0] = reginfo[0] | 0x08; }
    else { reginfo[0] = reginfo[0] & 0xF7; }

    if (prox_flag) { reginfo[0] = reginfo[0] | 0x04; }
    else { reginfo[0] = reginfo[0] & 0xFB; }

    if (als_flag) { reginfo[0] = reginfo[0] | 0x03; }
    else { reginfo[0] = reginfo[0] & 0xFC; }

    return I2CSetreg(fd, ENABLE_ADDR, reginfo[0]);
}

int set_atime(int fd, int reginfo[], int cycle_No) {
    /*
     * FUNCTION: Change the integration time
     * ---------
     * INPUT: fd - the file descriptor of the i2c device
     *        reginfo[35] - current values of all registers
     *        cycle_No - integration cycle numbers, must be between 1-256
     * RETURN: 0 - success
     *         -1 - error
     */

    if ( (cycle_No <= 256) && (cycle_No >= 1) ) {
        reginfo[1] = cycle_No - 1;
    }
    else{ return -1; }

    return I2CSetreg(fd, ATIME_ADDR, reginfo[1]);
}

int set_cfg1(int fd, int reginfo[], int IRtoG_flag, int again_flag) {
    /*
     * FUNCTION: Change the gain and ir to green setting
     * ---------
     * INPUT: fd - the file descriptor of the i2c device
     *        reginfo[35] - current values of all registers
     *        IRtoG_flag - 1 to enable ir to green, 0 to disable ir to green
     *        again_flag - [x1 - gain of 1, x4 - gain of 4, x16 - gain of 16, x64 - gain of 64]
     * RETURN: 0 - success
     *         -1 - error
     */

    if (IRtoG_flag) { reginfo[14] = reginfo[14] | 0x08; }
    else { reginfo[14] = reginfo[14] & 0xF7; }

    switch (again_flag) {
        case 1:
            reginfo[14] = reginfo[14] & 0xFC;
            break;
        case 4:
            reginfo[14] = reginfo[14] & 0xFD;
            reginfo[14] = reginfo[14] | 0x01;
            break;
        case 16:
            reginfo[14] = reginfo[14] & 0xFE;
            reginfo[14] = reginfo[14] | 0x02;
            break;
        case 64:
            reginfo[14] = reginfo[14] | 0x03;
            break;
        default:
            reginfo[14] = reginfo[14] & 0xFD;
            reginfo[14] = reginfo[14] | 0x01;
    }

    return I2CSetreg(fd, CFG1_ADDR, reginfo[14]);
}