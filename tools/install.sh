#!/bin/bash
# For installing i2c-tools for easy detection
clear

# Check for git, and purge old version of i2ctools
sudo apt-get install git-core
sudo apt-get purge wiringpi
sudo apt-get update
sudo apt-get purge i2c-tools
sudo apt-get install i2c-tools
hash -r

# Install at desktop for easy access
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
git pull origin
./build

# Display i2c information
echo -e "Installed successfully."
echo -e "\n==================================================================="
sudo i2cdetect -y 1

# Display WiringPi information
echo -e "\n==================================================================="
gpio -v
echo -e "\n==================================================================="
gpio readall
