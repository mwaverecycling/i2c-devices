#include <stdio.h>

#include <i2cfunc.h>
#include <devices/pca9555.h>


#define MASK(a,b,c,d,e,f,g,h) ((char)0 | (a) | (b << 1) | (c << 2) | (d << 3) | (e << 4) | (f << 5) | (g << 6) | (h << 7))
#define IO_ADDRESS 0x20

int main(int argc, char const *argv[])
{
	printf("Initializing...\n");
	i2c_init();
	printf("Running...\n");

	char cmd_output[2] = { MASK(1, 0, 1, 0, 0, 0, 1, 1), MASK(0, 0, 1, 0, 0, 0, 0, 1) };
	pca9555_config_output_range(IO_ADDRESS, 0, 16);
	pca9555_write_output(IO_ADDRESS, cmd_output);

	i2c_close();
	printf("Disconneted.\n");
}