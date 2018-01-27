

#ifndef PCA9555
#define PCA9555

#define PCA9555_REGISTER_INPUT 0x00
#define PCA9555_REGISTER_OUTPUT 0x02
#define PCA9555_REGISTER_POLARITY 0x04
#define PCA9555_REGISTER_CONFIGURE 0x06

void pca9555_read_input(int address, char data[2]);
int pca9555_read_pin(int address, int pin);

void pca9555_write_output(int address, char data[2]);
void pca9555_write_pin(int address, int pin, int value);

//void pca9555_write_polarity(int address);
//void pca9555_read_polarity(int address, int pin);

void pca9555_read_config(int address, char data[2]);
void pca9555_write_config(int address, char data[2]);

#endif