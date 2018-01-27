#include <stdio.h>

#include <i2cfunc.h>
#include <devices/pca9555.h>


int main(int argc, char const *argv[])
{
	i2c_init();
	i2c_close();
	printf("Disconneted.\n");
}