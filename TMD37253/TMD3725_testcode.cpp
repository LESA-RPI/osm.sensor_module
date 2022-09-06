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
#define ENABLE_ADDR 0x80	// R/W
#define ATIME_ADDR 0x81		// R/W
#define PTIME_ADDR 0x82		// R/W
#define WTIME_ADDR 0x83		// R/W
#define AILTL_ADDR 0x84		// R/W
#define AILTH_ADDR 0x85		// R/W
#define AIHTL_ADDR 0x86		// R/W
#define AIHTH_ADDR 0x87		// R/W
#define PILT_ADDR 0x88		// R/W
#define PIHT_ADDR 0x8A		// R/W
#define PERS_ADDR 0x8C		// R/W
#define CFG0_ADDR 0x8D		// R/W
#define PCFG0_ADDR 0x8E		// R/W
#define PCFG1_ADDR 0x8F		// R/W
#define CFG1_ADDR 0x90		// R/W
#define REVID_ADDR 0x91		// R
#define ID_ADDR 0x92		// R
#define STATUS_ADDR 0x93	// R/SC
#define CDATAL_ADDR 0x94	// R
#define CDATAH_ADDR 0x95	// R
#define RDATAL_ADDR 0x96	// R
#define RDATAH_ADDR 0x97	// R
#define GDATAL_ADDR 0x98	// R
#define GDATAH_ADDR 0x99	// R
#define BDATAL_ADDR 0x9A	// R
#define BDATAH_ADDR 0x9B	// R
#define PDATA_ADDR 0x9C		// R
#define CFG2_ADDR 0x9F		// R/W
#define CFG3_ADDR 0xAB		// R/W
#define POFFSETL_ADDR 0xC0	// R/W
#define POFFSETH_ADDR 0xC1	// R/W
#define CALIB_ADDR 0xD7		// R/W
#define CALIBCFG_ADDR 0xD9	// R/W
#define CALIBSTAT_ADDR 0xDC	// R/W
#define INTENAB_ADDR 0xDD	// R/W
// notes: 0x98 & 0x99 contains both data from GREEN and IR photodiodes
//----- -----

// // function that read all the color information at the register and put them into a vector for processing
// void readColor(std::vector<int> &color, int fd){
// 	std::vector<int> tempv(2);
// 	int tempnum;
// 	for(int i=0; i<4; i++){
// 		for(int j=0; j<2; j++){
// 			tempv[j] = wiringPiI2CReadReg8(fd, (BDATAH_ADDR-i-j)|CMD);
// 		}
// 		tempnum = tempv[0];
// 		tempnum = tempnum << 8;
// 		tempnum = tempnum + tempv[1];
// 		color[i] = tempnum;
// 	}
// }

// // run readColor for 10 times to return average of 10 readings
// void avgColor(std::vector<int> &color, int fd){
// 	std::vector<int> tempavg(4);
// 	for(int i=0; i<10; i++){
// 		readColor(tempavg, fd);
// 		for(int j=0; j<4; j++){
// 			color[j] += (0.1*tempavg[j]);
// 		}
// 	}
// }

// // function that print out color value
// void printColor(std::vector<int> &color){
// 	std::cout << "C\tR\tG\tB" << std::endl;
// 	for(int i=3; i>-1; i--){
// 		std::cout << color[i] << "\t";
// 	}
// 	std::cout << std::endl;
// }

// main testing code
int main(){
	
	//----- User Settings -----
	const int I2C_ADDR = 0x39;		// i2c address of the sensor can be changed here
	int ENA_SETTING = 0x07;			// Enable register settings can be changed here
	//----- -----

	//----- For initialization -----
	int fd, ID;
	if (!(fd = wiringPiI2CSetup(I2C_ADDR))){	// init i2c sensor and bus
		std::cout << "I2C bus not setup." << std::endl;
		return 1;
	}
	if (!(ID = wiringPiI2CReadReg8(fd,ID_ADDR))){		// try to read the ID of the sensor
		std::cout << "I2C bus not setup." << std::endl;
		return 1;
	}
	else{
		std::cout << "Color sensor (ID:0x" << std::hex << std::uppercase << ID << 
		std::nouppercase << std::dec << ") is initialized." << std::endl;
		std::cout << "The Device revision number is " << wiringPiI2CReadReg8(fd,REVID_ADDR) <<
		"." << std::endl;
	}

	//----- -----

	// //----- Setup the sensor -----
	// if (wiringPiI2CWriteReg8(fd, ENABLE_ADDR|CMD, ENA_SETTING) < 0){
	// 	std::cout << "Error occurs when writing to enable register." << std::endl;
	// }
	// while(!(0x01 & wiringPiI2CReadReg8(fd, STATUS_ADDR|CMD))){}	// Wait until an integration cycle is completed
	// //----- -----

	// //----- Brief Show case -----
	// // Code in this section is subject to changes for user's intention
	// std::vector<int> colors(4);		// [0]->B; [1]->G; [2]->R; [3]->C;
	// avgColor(colors, fd);
	// printColor(colors);
	// //----- -----

	return 0;
}
