# TMD 3725 Driver for Raspberry Pi

## Introduction

## Usage Instruction

## Note:
- This driver is only compatible with certain raspberry pi model that has `/dev/i2c-1`, such as raspberry pi zero w. If the raspberry pi model you are using is using `/dev/i2c-0` as the priority module, please change `RPi_DEVICE_TYPE` in `/scr/i2c_pi.h` to `0`.