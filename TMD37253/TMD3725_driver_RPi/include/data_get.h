/*
 * This is the code for fetching data from all the registers of TMD3725. get_data function can be used once at 
 * the initialization in order to keep track of all the register value of the sensor. get_optics_data is used at 
 * every integration cycle to get the raw color values.
 * 
 * Note:
 * - Detailed description for functions are in the source code file.
 * 
 * Author: You Wu
 * Date: 07/26/2022
 */

#ifndef _DATA_GET
#define _DATA_GET

int get_data(int fd, int reginfo[]);
int get_optics_data(int fd, int color_array[]);
int get_raw_clear(int fd);

#endif