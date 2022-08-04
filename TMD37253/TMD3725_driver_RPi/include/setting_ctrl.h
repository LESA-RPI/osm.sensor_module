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

#ifndef _SETTING_CTRL_H
#define _SETTING_CTRL_H

#include <stdio.h>
#include "../include/color_alg.h"

#define AUTOINTTIMETEST_FLAG 1      //flag for test prints

// Gain setting
#define x1 1
#define x4 4
#define x16 16
#define x64 64

void auto_inttime_adj(int fd, int reginfo[]);
int enable_sensor(int fd, int reginfo[], int wait_flag, int prox_flag, int als_flag);
int set_atime(int fd, int reginfo[], int cycle_No);
int set_cfg1(int fd, int reginfo[], int IRtoG_flag, int again_flag);

#endif  