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
int curr_reg;


int i2c_init()
{
    int fd = open(i2c_file, O_RDWR);
    if(fd < 0)
    {
        perror("i2c_init error:");
        exit(1);
    }
    return fd;
}
int i2c_init_file(char* filename)
{
    int fd = open(filename, O_RDWR);
    if(fd < 0)
    {
        perror("i2c_init error:");
        exit(1);
    }
    return fd;
}

void _i2c_set_addr(int adapter, int addr)
{
    if(addr != curr_reg) {
        if(ioctl(adapter, I2C_SLAVE, addr) < 0) {
            perror("_i2c_change_reg error:");
            curr_reg = -1;
        } else {
            curr_reg = addr;
        }
    }
}



int i2c_write(int adapter, int address, unsigned char* buffer, unsigned int length)
{
    _i2c_set_addr(adapter, address);

    if(write(adapter, buffer, length) != length)
    {
        perror("i2c_write error:");
        return -1;
    }
    return length;
}

int i2c_read(int adapter, int address, unsigned char* buffer, unsigned int length)
{
    _i2c_set_addr(adapter, address);

    if(read(adapter, buffer, length) != length)
    {
        perror("i2c_read error:");
        return -1;
    }
    return length;
}



int i2c_close(int adapter)
{
    if ((close(adapter)) != 0)
    {
        perror("i2c_close error:");
        return -1;
    }
    return 0;
}