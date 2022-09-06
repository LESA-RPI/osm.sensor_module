# TMD 3725 Driver for Raspberry Pi

## Introduction
The driver is developed for AMS color sensor TMD3725 specifically for LESA usage, becasue AMS doesn't have driver for TMD3725 under raspberry pi developing environment. This driver library is possible to be modified and used in other projects. 

## Usage Instruction
- Download the folder `TMD3725_driver_RPi` to the raspberry pi.
- Write the code that will use this driver, and put the code under `src` folder; or you can directly use the example code already exist in `src` folder.
- If you are using the example code, just go to the `src` directory and use `make` command to compile; if you are using your own code, `Makefile` under `src` folder needs to be edited first, detailed editing notes are given in the Implementation Note section below.
- Or you can copy the the header files in include folder and src codes in src folder and implement else where.
- Enjoy sensing colors.

## Implementation Note
- Editing `Makefile` for customized usage:
    - For the `SRCS` variable, add your code, then delete the examples code files:
    ```
    SRCS = ... mycode.c
    ```
    - For the `TARGET` variable, you can customized the excutable file name:
    ```
    TARGET = Myprogram
    ```
- This driver is only compatible with certain raspberry pi model that has `/dev/i2c-1`, such as raspberry pi zero w. If the raspberry pi model you are using is using `/dev/i2c-0` as the priority module, please change `RPi_DEVICE_TYPE` in `/scr/i2c_pi.h` to `0`.

## Development Note:
- Some functions are taken from WiringPi library that is also availble on Github.
- Information about registers and other device related data are from the official data sheet, which is available on AMS official website.
- Developed by: You Wu
