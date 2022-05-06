#!/bin/bash
# For installing WiringPi for the I2C interface
clear

# Check for git, and purge old version of wiringpi
sudo apt-get install git-core
sudo apt-get purge wiringpi
hash -r

# Install at desktop for easy access
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
git pull origin
./build

# Display WiringPi information
echo -e "\n==================================================================="
gpio -v
echo -e "\n==================================================================="
gpio readall
