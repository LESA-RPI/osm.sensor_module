/*
 * This is the code for processing data from the TMD3725. The main purpose is to correct the raw data from
 * the sensor and convert it into data that human can understand and analyze. Detailed function can be found
 * in the comments below.
 * 
 * Note:
 * - Detailed description for functions are in the source code file.
 * 
 * Author: You Wu
 * Date: 07/27/2022
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>                   // for pow() function
#include "../include/color_alg.h"
#include "../include/data_get.h"

optics_val get_calib_color(int fd, const int reginfo[]) {
    /*
     * FUNCTION: Read color data from sensor and caliberate them to usable data
     * ---------
     * INPUT: fd - the file descriptor of the i2c device
     *        reginfo[35] - current values of all registers
     * RETURN: calibed - return a struct that contains all the caliberated data
     *         empty struct calibed - return empty calibed if errors occur reading from register
     */

    int colorarray[9];
    optics_val calibed;
    int rawr, rawg, rawb, rawc;

    if ((get_optics_data(fd, colorarray)) == -1) {
        return calibed;     // if errors occur when reading from register, return empty calibed
    }

    calibed = calib_color(fd, colorarray, reginfo);     // caliberating ...
    
    return calibed;
}

optics_val calib_color(int fd, const int colorarray[], const int reginfo[]) {
    /*
     * FUNCTION: Caliberate color data
     * ---------
     * INPUT: fd - the file descriptor of the i2c device
     *        colorarray[9] - values read only from color data registers
     *        reginfo[35] - current values of all registers
     * RETURN: calibed - return a struct that contains all the caliberated data
     */

    optics_val calibed;
    int rawr, rawg, rawb, rawc, Again;
    float Atime;

    rawr = combine_color(colorarray, R);
    rawg = combine_color(colorarray, G);
    rawb = combine_color(colorarray, B);
    rawc = combine_color(colorarray, C);

    Atime = 2.81 * (reginfo[1] + 1);            // calculate the integration time in ms
    if (reginfo[11] & 0x02) {
        Atime = Atime * 12;                     // account for wlong case
    }
    Again = pow(2, (reginfo[14] & 0x03) * 2);   // calculate the gain in 1x, 4x, 16x, 64x
    if (!(reginfo[27] & 0x04)) {
        Again = Again/2;                        // account for wider range of gain
    }

    calibed.IR = ((rawr + rawg + rawb) - rawc)/2;
    calibed.CPL = (Again * Atime)/DGF;
    calibed.Lux = ((C_coef * rawc) + (R_coef * rawr) + (G_coef * rawg) + (B_coef * rawb))/calibed.CPL;  // equation for lux

    calibed.red = rawr - calibed.IR;            // caliberated red value
    calibed.green = rawg - calibed.IR;          // caliberated green value
    calibed.blue = rawb - calibed.IR;           // caliberated blue value
    calibed.clear = rawc - calibed.IR;          // caliberated clear value

    calibed.CCT = (CT_coef * (calibed.blue/calibed.red)) + CT_offset;   // equation for color temperature

    return calibed;
}

int combine_color(const int color_array[], int flag) {
    /*
     * FUNCTION: combine the seperate high bit and low bit color data into 2 bytes color data
     * ---------
     * INPUT: color_array[9] - the array that stored color value of registers
     *        flag - choose which color to combined. [options: C - clear, R - red, G - green, B - blue]
     * RETURN: tempcolor - the combined color value
     */

    int tempcolor = 0;

    switch(flag) {
        case 1:
            tempcolor = (color_array[1] << 8) + color_array[0];
            break;
        case 2:
            tempcolor = (color_array[3] << 8) + color_array[2];
            break;
        case 3:
            tempcolor = (color_array[5] << 8) + color_array[4];
            break;
        case 4:
            tempcolor = (color_array[7] << 8) + color_array[6];
            break;
        default:
            tempcolor = -1;
    }

    return tempcolor;
}

void print_color(const optics_val color_data) {
    /*
     * FUNCTION: Print the color from the processed data struct
     * ---------
     * INPUT: color_data - the struct that is storing caliberated color data
     * RETURN: void
     */

    /* formatting the data to left aligned, zero decimal, width of eight floats */
    printf("|CLEAR   |RED     |GREEN   |BLUE    |LUX     |CCT     |\n");
    printf("|%-8.0f|%-8.0f|%-8.0f|%-8.0f|%-8.0f|%-8.0f|\n", color_data.clear, color_data.red, color_data.green, 
                                                            color_data.blue, color_data.Lux, color_data.CCT);

    return;
}