/*
 * This is the file that has all the register addresses for TMD3725 color sensor.
 *
 * Note:
 * - The read and write ability of the register is commented
 * - Details about registers can be checked at the datasheet
 *
 * Author: You Wu
 * Date: 07/26/2022
 */

#ifndef _REGISTERS_H
#define _REGISTERS_H

#define ENABLE_ADDR     0x80	// R/W
#define ATIME_ADDR      0x81	// R/W
#define PTIME_ADDR      0x82	// R/W
#define WTIME_ADDR      0x83	// R/W
#define AILTL_ADDR      0x84	// R/W
#define AILTH_ADDR      0x85	// R/W
#define AIHTL_ADDR      0x86	// R/W
#define AIHTH_ADDR      0x87	// R/W
#define PILT_ADDR       0x88	// R/W
#define PIHT_ADDR       0x8A	// R/W
#define PERS_ADDR       0x8C	// R/W
#define CFG0_ADDR       0x8D	// R/W
#define PCFG0_ADDR      0x8E	// R/W
#define PCFG1_ADDR      0x8F	// R/W
#define CFG1_ADDR       0x90	// R/W
#define REVID_ADDR      0x91	// R
#define ID_ADDR         0x92	// R
#define STATUS_ADDR     0x93	// R/SC
#define CDATAL_ADDR     0x94	// R
#define CDATAH_ADDR     0x95	// R
#define RDATAL_ADDR     0x96	// R
#define RDATAH_ADDR     0x97	// R
#define GDATAL_ADDR     0x98	// R
#define GDATAH_ADDR     0x99	// R
#define BDATAL_ADDR     0x9A	// R
#define BDATAH_ADDR     0x9B	// R
#define PDATA_ADDR      0x9C	// R
#define CFG2_ADDR       0x9F	// R/W
#define CFG3_ADDR       0xAB	// R/W
#define POFFSETL_ADDR   0xC0	// R/W
#define POFFSETH_ADDR   0xC1	// R/W
#define CALIB_ADDR      0xD7	// R/W
#define CALIBCFG_ADDR   0xD9	// R/W
#define CALIBSTAT_ADDR  0xDC	// R/W
#define INTENAB_ADDR    0xDD	// R/W

#endif