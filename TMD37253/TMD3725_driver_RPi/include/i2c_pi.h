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

#ifndef _I2C_PI_H
#define _I2C_PI_H

#include <stdint.h>

#define I2C_SLAVE               0x0703
#define I2C_SMBUS	            0x0720	/* SMBus-level access */
#define I2C_SMBUS_BLOCK_MAX	    32	/* As specified in SMBus standard */

#define I2C_SMBUS_READ	        1
#define I2C_SMBUS_WRITE	        0
#define I2C_SMBUS_BYTE_DATA	    2

union i2c_smbus_data
{
  uint8_t  byte ;
  uint16_t word ;
  uint8_t  block [I2C_SMBUS_BLOCK_MAX + 2] ;	// block [0] is used for length + one more for PEC
} ;

struct i2c_smbus_ioctl_data
{
  char read_write ;
  uint8_t command ;
  int size ;
  union i2c_smbus_data *data ;
} ;

int I2CSetupInterface(const char* device, const int i2cID);
int I2CSetup(const int i2cID);
int i2c_smbus_access(int fd, char rw, uint8_t command, int size, union i2c_smbus_data *data);
int I2CGetreg(int fd, int reg);
int I2CSetreg (int fd, int reg, int value);

#endif