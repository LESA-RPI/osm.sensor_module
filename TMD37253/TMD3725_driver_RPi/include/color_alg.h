#ifndef _COLOR_ALG_H
#define _COLOR_ALG_H

#define C_coef      0.16    // clear
#define R_coef      -0.04   
#define G_coef      0.16
#define B_coef      -0.29
#define DGF         682.85
#define CT_coef     4520    // color temperature coefficient
#define CT_offset   1804    // color temperature offset

typedef struct optics_val {
    // struct that stored the processed data that can be used in later analysis
    int red;
    int green;
    int blue;
    int IR;
    int CPL;
    int Lux;
    int CCT;
} optics_val;

#endif