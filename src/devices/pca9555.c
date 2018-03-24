#include <i2cfunc.h>
#include <devices/pca9555.h>

tI2C_Status pca9555_read_input(int adapter, int address, unsigned char data[2])
{
	static unsigned char read_cmd[1] = { PCA9555_REGISTER_INPUT };
	i2c_write(adapter, address, read_cmd, 1);
	return i2c_read(adapter, address, data, 2);
}
int pca9555_read_pin(int adapter, int address, int pin)
{
	unsigned char buffer[2];
	pca9555_read_input(adapter, address, buffer);
	return (buffer[pin >= 8] & (1 << (pin % 8))) > 0;
}

tI2C_Status pca9555_write_output(int adapter, int address, unsigned char data[2])
{
	unsigned char cmd_buf[3] = { PCA9555_REGISTER_OUTPUT, data[0], data[1] };
	return i2c_write(adapter, address, cmd_buf, 3);
}
tI2C_Status pca9555_write_output_range(int adapter, int address, int start_pin, int end_pin, unsigned char *values)
{
	unsigned char data[2];
	tI2C_Status status = pca9555_read_input(adapter, address, data);
	if(status != 2) { return status; }

	for(int pin = start_pin; pin < end_pin; pin++) {
		if((values[(pin - start_pin) >> 3] & (1 << ((pin - start_pin) & 0b111))) > 0) {
			data[pin >> 3] |= (1 << (pin & 0b111));
		} else {
			data[pin >> 3] &= ~(1 << (pin & 0b111));
		}
	}
	return pca9555_write_output(adapter, address, data);
}
tI2C_Status pca9555_write_pin(int adapter, int address, int pin, int value)
{
	return pca9555_write_output_range(adapter, address, pin, pin + 1, (unsigned char[1]){ value & 0x1 });
}

//void pca9555_write_polarity(int address);
//void pca9555_read_polarity(int address, int pin);

tI2C_Status pca9555_config_read(int adapter, int address, unsigned char data[2])
{
	static unsigned char read_cmd[1] = { PCA9555_REGISTER_CONFIGURE };
	i2c_write(adapter, address, read_cmd, 1);
	return i2c_read(adapter, address, data, 2);
}
tI2C_Status pca9555_config_write(int adapter, int address, unsigned char data[2])
{
	char unsigned cmd_buf[3] = { PCA9555_REGISTER_CONFIGURE, data[0], data[1] };
	return i2c_write(adapter, address, cmd_buf, 3);
}

/** Configures pins [start_pin, end_pin) as output, and the rest as input */
tI2C_Status pca9555_config_output_range(int adapter, int address, int start_pin, int end_pin)
{
	char unsigned data[2] = { 0xff, 0xff };
	for(int pin = start_pin; pin < end_pin; pin++) {
		data[pin >= 8] &= ~(1 << (pin % 8));
	}
	return pca9555_config_write(adapter, address, data);
}
/** Configures pins [start_pin, end_pin) as intput, and the rest as output */
tI2C_Status pca9555_config_intut_range(int adapter, int address, int start_pin, int end_pin)
{
	char unsigned data[2] = { 0x00, 0x00 };
	for(int pin = start_pin; pin < end_pin; pin++) {
		data[pin >= 8] |= (1 << (pin % 8));
	}
	return pca9555_config_write(adapter, address, data);
}