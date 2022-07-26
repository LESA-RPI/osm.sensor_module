#include <stdio.h>
#include "../include/i2c_pi.h"
#include "../include/registers.h"

int main() {

    int fd, ID;
    const int I2C_ADDR = 0x39;

    if ((fd = I2CSetup(I2C_ADDR)) < 0) {
        printf("failed.");
    }

    if ((ID = I2CGetreg(fd, ID_ADDR)) < 0) {		// try to read the ID of the sensor
		printf("I2C bus not setup");
		return 1;
	}

    printf("\nFinished. ID: 0x%X\n", ID);

    return 0;
}