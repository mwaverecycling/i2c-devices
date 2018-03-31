#include <i2cfunc.h>
#include <devices/ads1115.h>

static unsigned char curr_conf[2];

static float getVoltage(short raw_value)
{
	float big_short = (float)((int)1 << 15);
	switch(curr_conf[0] & 0b1110)
	{
		case ADS1115_FSR_6144: return ((float)raw_value * 6.144f) / big_short;
		case ADS1115_FSR_4096: return ((float)raw_value * 4.049f) / big_short;
		case ADS1115_FSR_2048: return ((float)raw_value * 2.048f) / big_short;
		case ADS1115_FSR_1024: return ((float)raw_value * 1.024f) / big_short;
		case ADS1115_FSR_0512: return ((float)raw_value * 0.512f) / big_short;
		case ADS1115_FSR_0256: return ((float)raw_value * 0.256f) / big_short;
	}
}

int ads1115_read_raw(int adapter, int address, short *value)
{
	unsigned char buffer[2] = { ADS1115_REGISTER_OUTPUT, 0 };
	int status = i2c_write(adapter, address, buffer, 1);
	if(status < 0) { return status; }

	status = i2c_read(adapter, address, buffer, 2);
	if(status < 0) { return status; }

	value[0] = ((short)buffer[0] << 8) | buffer[1];
	return status;
}
int ads1115_read(int adapter, int address, float *value)
{
	short raw_value;
	int status = ads1115_read_raw(adapter, address, &raw_value);
	if(status < 0) { return status; }

	value[0] = getVoltage(raw_value);
	return status;
}
int ads1115_read_input(int adapter, int address, int pin, float *value)
{
	curr_conf[0] &= ~(0x70);
	curr_conf[0] |= (pin << 4);
	int status = ads1115_configure_raw(adapter, address, curr_conf);
	if(status < 0) { return status; }
	return ads1115_read(adapter, address, value);
}

int ads1115_configure(int adapter, int address, unsigned char pin_mux, unsigned char conv, unsigned char sps)
{
	curr_conf[0] = (pin_mux << 4) | conv;
	curr_conf[1] = sps | 0b11;
	return ads1115_configure_raw(adapter, address, curr_conf);
}
int ads1115_configure_raw(int adapter, int address, unsigned char conf[2])
{
	char unsigned cmd_buf[3] = { ADS1115_REGISTER_CONFIG, conf[0], conf[1] };
	int status = i2c_write(adapter, address, cmd_buf, 3);
	if(curr_conf[0] & ADS1115_SINGLE_CONV) { curr_conf[0] |= ADS1115_START_CONV; }
	return status;
}