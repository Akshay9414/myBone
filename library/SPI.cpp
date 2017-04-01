#include "SPI.h"

using namespace std;

SPI::SPI(uint8_t SPIChannel,uint8_t m,uint8_t b,uint32_t s,uint16_t d1){
	
	mode = m ;
	bits = b;
	speed = s;
	delay1 = d1;
	if(SPIChannel != 0 && SPIChannel != 1) pabort("incorrect SPI Channel");
	else{
		if(SPIChannel==0){
			device = "/dev/spidev1.1";
		}
		else{
			device = "/dev/spidev2.1";
		}
	}
	 			
}

char* SPI::transfer(char tx[]){

    int ret=0;
  	
  	fd = open(device, O_RDWR);
  	if (fd < 0)
  	pabort("can't open device");
  	
  	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    if (ret == -1)
    pabort("can't get SPI mode");
  	/*
  	 * bits per word
  	 */
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1)
    pabort("can't set bits per word");
  	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1)
    pabort("can't get bits per word");
    /*
    * max speed hz
    */
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1)
    pabort("can't set max speed hz");
  	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1)
    pabort("can't get max speed hz");
    
    char rx[sizeof(tx) / sizeof((tx)[0])] = {0, };
     struct spi_ioc_transfer tr = {
     tr.tx_buf = (unsigned long)tx,
     tr.rx_buf = (unsigned long)rx,
     tr.len = 8,
     tr.delay_usecs = delay1,
     tr.speed_hz = speed,
     tr.bits_per_word = bits,
    };
    
    ret=0;
    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 1)
    pabort("can't send SPI message");
    close(fd);
    char* y=&rx[0];
    return y;
}

void SPI::pabort(const char *s)
{
 perror(s);
 abort();
}

