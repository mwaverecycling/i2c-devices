#include <i2cfunc.h>
#include <devices/pca9555.h>

void pca9555_read_input(int address, char data[2])
{
	static char read_cmd[1] = { PCA9555_REGISTER_INPUT };
	i2c_write(address, read_cmd, 1);
	i2c_read(address, data, 2);
}
int pca9555_read_pin(int address, int pin)
{
	char buffer[2];
	pca9555_read_input(address, buffer);
	return (buffer[pin >= 8] & (1 << (pin % 8))) > 0;
}

void pca9555_write_output(int address, char data[2])
{
	char cmd_buf[3] = { PCA9555_REGISTER_OUTPUT, data[0], data[1] };
	i2c_write(address, cmd_buf, 3);
}
void pca9555_write_pin(int address, int pin, int value)
{
	char buffer[2];
	pca9555_read_input(address, buffer);
	if(value) {
		buffer[pin >= 8] |= (1 << (pin % 8));
	} else {
		buffer[pin >= 8] &= ~(1 << (pin % 8));
	}
}

//void pca9555_write_polarity(int address);
//void pca9555_read_polarity(int address, int pin);

void pca9555_read_config(int address, char data[2])
{
	static char read_cmd[1] = { PCA9555_REGISTER_CONFIGURE };
	i2c_write(address, read_cmd, 1);
	i2c_read(address, data, 2);
}
void pca9555_write_config(int address, char data[2])
{
	char cmd_buf[3] = { PCA9555_REGISTER_CONFIGURE, data[0], data[1] };
	i2c_write(address, cmd_buf, 3);
}