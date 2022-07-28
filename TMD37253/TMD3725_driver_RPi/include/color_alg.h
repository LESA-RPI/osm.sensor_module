/*
 * This is the code for processing data from the TMD3725. The main purpose is to correct the raw data from
 * the sensor and convert it into data that human can understand and analyze. Detailed function can be found
 * in the comment below.
 * 
 * Note:
 * - Detailed description for functions are in the source code file.
 * 
 * Author: You Wu
 * Date: 07/27/2022
 */

#ifndef _COLOR_ALG_H
#define _COLOR_ALG_H

#define C_coef      0.16    // clear channel coefficient
#define R_coef      -0.04   
#define G_coef      0.16
#define B_coef      -0.29
#define DGF         682.85
#define CT_coef     4520    // color temperature coefficient
#define CT_offset   1804    // color temperature offset

/*combine color flag*/
#define C           1
#define R           2
#define G           3
#define B           4

typedef struct optics_val {
    // struct that stored the processed data that can be used in later analysis
    float red;
    float green;
    float blue;
    float clear;
    float IR;
    float CPL;
    float Lux;
    float CCT;
} optics_val;

optics_val get_calib_color(int fd, const int reginfo[]);
optics_val calib_color(int fd, const int colorarray[], const int reginfo[]);
int combine_color(const int color_array[], int flag);
void print_color(optics_val color_data);    // From what I learned, const non pointer variable don't need const to init the function

#endif