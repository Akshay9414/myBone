#ifndef SPI_h
#define SPI_h

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

class SPI{
	
	public:
		const char *device;
		uint8_t mode;
		uint8_t bits;
		uint32_t speed;
		uint16_t delay1;
		int fd;
		SPI(uint8_t SPIChannel,uint8_t m,uint8_t b,uint32_t s,uint16_t d1);
		char* transfer(char tx[]);
		void pabort(const char *s);
};

#endif
