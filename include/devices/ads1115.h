#include <i2cfunc.h>

#ifndef ADS1115_H
#define ADS1115_H

#define ADS1115_REGISTER_OUTPUT 0x00
#define ADS1115_REGISTER_CONFIG 0x01
#define ADS1115_REGISTER_THRESH_LO 0x02
#define ADS1115_REGISTER_THRESH_HI 0x03



#define ADS1115_START_CONV 0x80
#define ADS1115_DIFFERENTIAL 0x40

#define ADS1115_FSR_6144 0b0000
#define ADS1115_FSR_4096 0b0010
#define ADS1115_FSR_2048 0b0100
#define ADS1115_FSR_1024 0b0110
#define ADS1115_FSR_0512 0b1000
#define ADS1115_FSR_0256 0b1010

#define ADS1115_CONTINUOUS_CONV 0x00
#define ADS1115_SINGLE_CONV 0x01

#define ADS1115_SPS_8   0x00
#define ADS1115_SPS_16  0x20
#define ADS1115_SPS_32  0x40
#define ADS1115_SPS_64  0x60
#define ADS1115_SPS_128 0x80
#define ADS1115_SPS_250 0xa0
#define ADS1115_SPS_475 0xc0
#define ADS1115_SPS_860 0xe0

/** Configuration Word Layout
 *
 *  | OS[15] | MUX[14..12] | PGA[11..9] | MODE[8] |
 *
 *  | DR[7..5] | COMP_MODE[4] | COMP_POL[3] | COMP_LAT[2] | COMP_QUE[1..0] |
 *
 *  http://www.ti.com/lit/ds/symlink/ads1115.pdf
 */

int ads1115_read_raw(int adapter, int address, short *value);
int ads1115_read(int adapter, int address, float *value);
int ads1115_read_input(int adapter, int address, int pin, float *value);
int ads1115_configure(int adapter, int address, unsigned char pin_mux, unsigned char conv, unsigned char sps);
int ads1115_configure_raw(int adapter, int address, unsigned char conf[2]);

#endif
