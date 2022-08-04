# OSM.sensor_module

## Introduction

## File Structure
__*TCS34725*__
    Folder for information of TCS34725 color sensor  
__*TMD37253*__
    Folder for information of TMD37253 color sensor  
__*tools*__
    Folder for some helpful tools used in development  

### Color Sensor `TMD37253`
*-include in folder TMD37253*

#### Introduction

#### Implementation Guides

#### Modification Note

### Color Sensor `TCS34725`
*-include in folder TCS34725*

#### Introduction
This is a section for implementation codes for color sensor `TCS34725`  
The code is fully `C++` and uses `WiringPi` for I2C interface access

#### Implementation Guides
Following is the process of how to use the codes in this section:
- Download the whole repository to the system.
- Use command `chmod +x install.sh` to make shell file executable.
- Run `install.sh` to setup `WiringPi` on the system, the output on the terminal should be the version of `WiringPi` and the pins map of current board if everything goes right.
- Compile `TCS34725_testcode.cpp` using command `g++ TCS34725_testcode.cpp -o TCS34725_show.exe -l wiringPi`
- Run `TCS34725_show.exe`

#### Modification Note
Inside the main function of `TCS34725_testcode.cpp`:
- I2C address and enbale register settings can be changed in the `User Settings` section
- Any changes for register data could be add to `Setup the sensor` section
- How to read, process, and output color data codes will be added to `Brief Show case` section
