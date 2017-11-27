#include<lpc21xx.h>
#include<stdio.h>
#include<rtl.h>
unsigned int q;
void buzz1(void)
{
PINSEL0|=0x00000000;
IODIR0=0x00010000;
	for(q=0;q<1000000;q++);
IOSET0=0x00010000;
for(q=0;q<1000000;q++);	
IOCLR0=0x00010000;
}
