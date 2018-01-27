#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include "i2cfunc.h"



char* i2c_file = "/dev/i2c-2";
int i2c_adapter;
int curr_reg;


void i2c_init()
{
    i2c_adapter = open(i2c_file, O_RDWR);
    if(i2c_adapter < 0)
    {
        perror("i2c_init error:");
        exit(1);
    }
}
void i2c_init_file(char* filename)
{
    i2c_adapter = open(filename, O_RDWR);
    if(i2c_adapter < 0)
    {
        perror("i2c_init error:");
        exit(1);
    }
}

void _i2c_set_addr(int addr)
{
    if(addr != curr_reg) {
        if(ioctl(i2c_adapter, I2C_SLAVE, addr) < 0) {
            perror("_i2c_change_reg error:");
            curr_reg = -1;
        } else {
            curr_reg = addr;
        }
    }
}



int i2c_write(int address, unsigned char* buffer, unsigned int length)
{
    _i2c_set_addr(address);

    if(write(i2c_adapter, buffer, length) != length)
    {
        perror("i2c_write error:");
        return -1;
    }
    return length;
}

int i2c_read(int address, unsigned char* buffer, unsigned int length)
{
    _i2c_set_addr(address);

    if(read(i2c_adapter, buffer, length) != length)
    {
        perror("i2c_read error:");
        return -1;
    }
    return length;
}

int i2c_close()
{
    if ((close(i2c_adapter)) != 0)
    {
        perror("i2c_close error:");
        return -1;
    }
    return 0;
}