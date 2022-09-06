## Before Starting
- install BlueZ (it is usually pre-installed)
- download header files for bluetooth: `https://stackoverflow.com/questions/23436909/where-is-the-bluetooth-bluetooth-h-located-in-linux`
- `https://raspberrypi.stackexchange.com/questions/14598/making-raspberry-pi-bluetooth-slave/19865#19865` for activating discoverable mode

## Compiling
Use command `gcc *.c -o *.o -lbluetooth -lpthread`, replace `*` with document names

## Files
- `simplescan.c` is for scanning through the current environment for available BLE devices
- `rfcomm_client.c` and `rfcomm_server.c` are for point to point communication and server is only for receiving while client is only for sending
- `rf_client_bi_dir.c` and `rf_server_bi_dir.c` are also for point to pint communication, but they utilize multi-threading so that both of them can send and receive at the same time 

### Note
- Useful tool: `sudo hciconfig -h` for hciconfig help
- The codes here utilize socket communication, not the GATT type that BLE mostly used today
