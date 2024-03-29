# OSM.sensor_module

## Introduction
Codes for the occupancy sensing module that utilizes ToF and color sensor.

## File Structure
__*BLE*__
    Folder for BLE communication on RPi  
__*TCS34725*__
    Folder for information of TCS34725 color sensor  
__*TMD37253*__
    Folder for information of TMD37253 color sensor  
__*tools*__
    Folder for some helpful tools used in development

---

### Bluetooth communication
*-include in folder BLE*

#### Introduction
This is the section for simple bluetooth communication implementation on RPi, there is only point to point communication at this point

---

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

---

### Color Sensor `TMD37253`
*-include in folder TMD37253*

#### Introduction
This is a section for implementation codes for color sensor `TMD37253`
The code is fully `c` and uses modified `WiringPi` methods for I2C interface access

#### Implementation Guides
For this part:
- `TMD3725_driver_RPi` is the folder that holds a `c` driver that can enable TMD3725 on RPi
- `TMD3725_testcode.cpp` has a brief example that uses `WiringPi` for TMD3725 implementation, for test purpose

#### Modification Note
- Detailed notes are in the `README.md` in `TMD3725_driver_RPi`
