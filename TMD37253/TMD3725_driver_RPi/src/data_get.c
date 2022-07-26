/*
 * This is the code for fetching data from all the registers of TMD3725. get_data function can be used once at 
 * the initialization in order to keep track of all the register value of the sensor. get_optics_data is used at 
 * every integration cycle to get the raw color values.
 * 
 * Author: You Wu
 * Date: 07/26/2022
 */

#include <stdio.h>
#include "../include/data_get.h"
#include "../include/i2c_pi.h"
#include "../include/registers.h"

int get_data(int fd, int reginfo[]) {

    /*Check if the size of registers info array */
    if (((sizeof(reginfo))/(sizeof(int))) != 35) {
        printf("Register info array has the wrong size.");
        return -1;
    }

    /*Enable to PILT*/
    for (int i=0; i<9; i++) {
        if ((reginfo[i] = I2CGetreg(fd, ENABLE_ADDR+i)) != -1) {
            printf("Error happens when reading register value.");
            return -1;
        }
    }
    /*PIHT*/
    if ((reginfo[9] = I2CGetreg(fd, PIHT_ADDR)) != -1) {printf("Error happens when reading register value."); return -1;}
    /*PERS to PCFG1*/
    for (int i=0; i<4; i++) {
        if ((reginfo[10+i] = I2CGetreg(fd, PERS_ADDR+i)) != -1) {
            printf("Error happens when reading register value.");
            return -1;
        }
    }
    /*CFG1 to PDATA*/
    for (int i=0; i<13; i++) {
        if ((reginfo[14+i] = I2CGetreg(fd, CFG1_ADDR+i)) != -1) {
            printf("Error happens when reading register value.");
            return -1;
        }
    }
    /*CFG2*/
    if ((reginfo[27] = I2CGetreg(fd, CFG2_ADDR)) != -1) {printf("Error happens when reading register value."); return -1;}
    /*CFG3*/
    if ((reginfo[28] = I2CGetreg(fd, CFG3_ADDR)) != -1) {printf("Error happens when reading register value."); return -1;}
    /*POFFSETL*/
    if ((reginfo[29] = I2CGetreg(fd, POFFSETL_ADDR)) != -1) {printf("Error happens when reading register value."); return -1;}
    /*POFFSETH*/
    if ((reginfo[30] = I2CGetreg(fd, POFFSETH_ADDR)) != -1) {printf("Error happens when reading register value."); return -1;}
    /*CALIB*/
    if ((reginfo[31] = I2CGetreg(fd, CALIB_ADDR)) != -1) {printf("Error happens when reading register value."); return -1;}
    /*CALIBCFG*/
    if ((reginfo[32] = I2CGetreg(fd, CALIBCFG_ADDR)) != -1) {printf("Error happens when reading register value."); return -1;}
    /*CALIBSTAT*/
    if ((reginfo[33] = I2CGetreg(fd, CALIBSTAT_ADDR)) != -1) {printf("Error happens when reading register value."); return -1;}
    /*INTENAB*/
    if ((reginfo[34] = I2CGetreg(fd, INTENAB_ADDR)) != -1) {printf("Error happens when reading register value."); return -1;}

    return 0;
}

int get_optics_data(int fd, int color_array[]) {

    /*Check if the size of color array */
    if (((sizeof(color_array))/(sizeof(int))) != 9) {
        printf("Register info array has the wrong size.");
        return -1;
    }

    for (int i=0; i<9; i++) {
        if ((color_array[i] = I2CGetreg(fd, CDATAL_ADDR+i)) != -1) {
            printf("Error happens when reading color value.");
            return -1;
        }
    }

    return 0;
}