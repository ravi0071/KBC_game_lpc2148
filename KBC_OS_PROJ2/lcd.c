#include<lpc21xx.h>
void lcd(unsigned int dat)
{
	unsigned int y;
	y=dat;
	y=y & 0xf0;
	IOCLR0=0x000000fc;
	IOSET0=0x00000004;
	IOSET0=y;
	IOSET0=0x00000008;
	delay(10);
	IOCLR0=0x00000008;
	y=dat;
	y=y&0x0f;
	y=y<<4;
	IOCLR0=0x000000fc;
	IOSET0=0x00000004;
	IOSET0=y;
	IOSET0=0x00000008;
	delay(10);
	IOCLR0=0x00000008;			
}

