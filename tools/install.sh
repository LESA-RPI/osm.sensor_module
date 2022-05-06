#!/bin/bash
# For installing i2c-tools for easy detection
clear

# Check for git, and purge old version of i2ctools
sudo apt-get update
sudo apt-get purge i2c-tools
sudo apt-get install i2c-tools
hash -r

# Display WiringPi information
echo -e "\n==================================================================="
sudo i2cdetect -y 1
