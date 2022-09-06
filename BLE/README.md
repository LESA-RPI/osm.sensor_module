## Before Starting
- install BlueZ (it is usually pre-installed)
- download header files for bluetooth: `https://stackoverflow.com/questions/23436909/where-is-the-bluetooth-bluetooth-h-located-in-linux`
- `https://raspberrypi.stackexchange.com/questions/14598/making-raspberry-pi-bluetooth-slave/19865#19865` for activating discoverable mode

## Compiling
Use command `gcc *.c -o *.o -lbluetooth`, replace `*` with document names

## Files
- `simplescan.c` is for scanning through the current environment for available BLE devices
- `rfcomm_client.c` and `rfcomm_server.c` are for point to point 

### Note
- Useful tool: `sudo hciconfig -h` for hciconfig help
