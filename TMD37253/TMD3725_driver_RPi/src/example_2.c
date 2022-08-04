#include "../include/example_1.h"
#include "../include/example_2.h"

int example_2_basic_integra_10x(int fd, int reginfo[], optics_val colordata) {
    
    for (int i=0; i<10; i++) {
        example_1_basic_integra(fd, reginfo, colordata);
    }

    return 0;
}