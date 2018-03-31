#include <stdio.h>
#include <string.h>

#include <i2cfunc.h>
#include <devices/pca9555.h>


#define MASK(a,b,c,d,e,f,g,h) ((unsigned char)0 | (a) | (b << 1) | (c << 2) | (d << 3) | (e << 4) | (f << 5) | (g << 6) | (h << 7))
#define IO_ADDRESS 0x20
#define ADC_ADDRESS 0x48

int main(int argc, char const *argv[])
{
	printf("Initializing...\n");
	int i2cd = i2c_init();
	printf("Running...\n");

	//char unsigned cmd_output[2] = { MASK(1, 0, 1, 0, 0, 0, 1, 1), MASK(0, 0, 1, 0, 0, 0, 0, 1) };
	//pca9555_config_output_range(i2cd, IO_ADDRESS, 0, 16);
	//pca9555_write_output(i2cd, IO_ADDRESS, cmd_output);
	ads1115_configure(i2cd, ADC_ADDRESS, 4 | 0, ADS1115_FSR_1024 | ADS1115_CONTINUOUS_CONV, ADS1115_SPS_8);
	float voltage;
	int status;
	for(int i = 0; i < 10; i++)
	{
		status = ads1115_read(i2cd, ADC_ADDRESS, &voltage);
		if(status < 0) { perror("  Error: "); }
		float temp = voltage * 100;
		printf("  Success! %f V => %f C\n", voltage, temp);
	}

	int status = i2c_close(i2cd);
	printf("Disconneted. %d\n", status);
}