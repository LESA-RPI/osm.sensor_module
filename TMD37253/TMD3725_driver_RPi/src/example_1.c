#include "../include/example_1.h"

int example_1_basic_integra(int fd, int reginfo[], optics_val colordata) {
    
    colordata = get_calib_color(fd, reginfo);
    print_color(colordata);
    
    return 0;
}