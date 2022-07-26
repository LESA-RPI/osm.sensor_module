/*
 * This is the library for i2c communication for device on raspberry pi zero w. All the codes are based on the work of
 * WiringPi library, and for the convenience of using, only the i2c interface section is implemented here. 
 *
 * Usage Instructions:
 * 1. Make sure that i2c device is connected onto the i2c-1 bus of the pi, if it's connected to i2c-2, please refer to
 * the note section of README file for code modification.
 * 2. Include the header into main code, and use I2CSetup() to get the file descriptor of the device.
 * 3. If the return value of I2CSetup() is not -1, then go ahead to use I2CGetreg() and I2CSetreg() to play with the 
 * registers on the device.
 *
 * Note:
 * - For this specific driver, this i2c module only support read and write byte from and to the register.
 *
 * Original work: WiringPi
 * Modified by: You Wu
 * Date: 07/25/2022
 */

#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>                  // include open()
#include <sys/ioctl.h>              // include the ioctl() for selecting i2c device
#include "../include/i2c_pi.h"      // include the header

int i2c_smbus_access(int fd, char rw, uint8_t command, int size, union i2c_smbus_data *data) {
    
    struct i2c_smbus_ioctl_data args;

    args.read_write = rw;
    args.command    = command;
    args.size       = size;
    args.data       = data;

    return ioctl (fd, I2C_SMBUS, &args);
}

/* helper function for I2CSetup() */
int I2CSetupInterface(const char* device, const int i2cID) {
    
    int fd;

    if ((fd = open(device, O_RDWR)) < 0) {
        printf("Unable to open I2C device.");
        return -1;
    }

    if (ioctl(fd, I2C_SLAVE, i2cID) < 0) {
        printf("Unable to select I2C device.");
        return -1;
    }

    return fd;
}

/* return the file descriptor that i2c communication used */
int I2CSetup(const int i2cID) {

    const char* device;
    device = "/dev/i2c-1";          // Here specify the i2c module that Rpi used, can be modified

    return I2CSetupInterface(device, i2cID);
}

int I2CGetreg(int fd, int reg) {

    union i2c_smbus_data data;

    if (i2c_smbus_access (fd, I2C_SMBUS_READ, reg, I2C_SMBUS_BYTE_DATA, &data))
        return -1;
    else
        return data.byte & 0xFF;
}

int I2CSetreg (int fd, int reg, int value) {
  
    union i2c_smbus_data data;

    data.byte = value;
    return i2c_smbus_access (fd, I2C_SMBUS_WRITE, reg, I2C_SMBUS_BYTE_DATA, &data);
}