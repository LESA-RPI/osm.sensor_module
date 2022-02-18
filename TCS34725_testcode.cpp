/*
This code is to test the usage of color sensor using I2C bus 1 on Pi 0 W
You Wu
*/

//----- Lib used -----
#include <iostream>
#include <fstream>					// for output file
#include <wiringPi.h>				// lib for delay()
#include <wiringPiI2C.h>			// lib for I2C communication
#include <vector>
//----- -----

//----- Register Address -----
#define CMD 0x80			// default command bit for register (write only)

#define ENABLE_ADDR 0x00	// R/W
#define ATIME_ADDR 0x01		// R/W
#define WTIME_ADDR 0x03		// R/W
#define AILTL_ADDR 0x04		// R/W
#define AILTH_ADDR 0x05		// R/W
#define AIHTL_ADDR 0x06		// R/W
#define AIHTH_ADDR 0x07		// R/W
#define PERS_ADDR 0x0C		// R/W
#define CONFIG_ADDR 0x0D	// R/W
#define CONTROL_ADDR 0x0F	// R/W
#define ID_ADDR 0x12		// R
#define STATUS_ADDR 0x13	// R
#define CDATAL_ADDR 0x14	// R
#define CDATAH_ADDR 0x15	// R
#define RDATAL_ADDR 0x16	// R
#define RDATAH_ADDR 0x17	// R
#define GDATAL_ADDR 0x18	// R
#define GDATAH_ADDR 0x19	// R
#define BDATAL_ADDR 0x1A	// R
#define BDATAH_ADDR 0x1B	// R
//----- -----

// function that read all the color information at the register and put them into a vector for processing
void readColor(std::vector<int> &color, int fd){
	std::vector<int> tempv(2);
	int tempnum;
	for(int i=0; i<4; i++){
		for(int j=0; j<2; j++){
			tempv[j] = wiringPiI2CReadReg8(fd, (BDATAH_ADDR-i-j)|CMD);
		}
		tempnum = tempv[0];
		tempnum = tempnum << 8;
		tempnum = tempnum + tempv[1];
		color[i] = tempnum;
	}
}

// run readColor for 10 times to return average of 10 readings
void avgColor(std::vector<int> &color, int fd){
	std::vector<int> tempavg(4);
	for(int i=0; i<10; i++){
		readColor(tempavg, fd);
		for(int j=0; j<4; j++){
			color[j] += (0.1*tempavg[j]);
		}
	}
}

// function that print out color value
void printColor(std::vector<int> &color){
	std::cout << "C\tR\tG\tB" << std::endl;
	for(int i=3; i>-1; i--){
		std::cout << color[i] << "\t";
	}
	std::cout << std::endl;
}

int main(){
	
	//----- User Settings -----
	const int I2C_ADDR = 0x29;		// i2c address of the sensor can be changed here
	int ENA_SETTING = 0x1B;			// Enable register settings can be changed here
	//----- -----

	//----- For initialization -----
	int fd;
	fd = wiringPiI2CSetup(I2C_ADDR);	// init i2c sensor and bus
	if ((wiringPiI2CReadReg8(fd, ID_ADDR|CMD) == 0x44) || (wiringPiI2CReadReg8(fd, ID_ADDR|CMD) == 0x4D)){
		std::cout << "Color sensor (ID:0x" << std::hex << std::uppercase << wiringPiI2CReadReg8(fd, ID_ADDR|CMD) << 
		std::nouppercase << std::dec << ") is initialized." << std::endl;
	}
	else{
		std::cout << "Error occurs when initializing the color sensor at ADDR: 0x" << std::hex << std::uppercase << 
		I2C_ADDR << std::nouppercase << std::dec << "." << std::endl;
	}
	//----- -----

	//----- Setup the sensor -----
	if (wiringPiI2CWriteReg8(fd, ENABLE_ADDR|CMD, ENA_SETTING) < 0){
		std::cout << "Error occurs when writing to enable register." << std::endl;
	}
	while(!(0x01 & wiringPiI2CReadReg8(fd, STATUS_ADDR|CMD))){}	// Wait until an integration cycle is completed
	//----- -----

	//----- Brief Show case -----
	// Code in this section is subject to changes for user's intention
	std::vector<int> colors(4);		// [0]->B; [1]->G; [2]->R; [3]->C;
	avgColor(colors, fd);
	printColor(colors);
	//----- -----

	return 0;
}