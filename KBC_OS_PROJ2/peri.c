#include<lpc21xx.h>
#include "buzz.h"
void delay(unsigned int x)
{
unsigned int del;
for(del=0;del<x;del++);
}
void lcd(unsigned char dat)
{
	unsigned int y;
	y=dat;
	y=y&0xf0;
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
void cmd(unsigned int value)
{ 
	unsigned int y;
	y=value;
	y=y &0xf0;
	IOCLR0=0x000000fc;
	IOCLR0=0x00000004;
	IOSET0=y;
	IOSET0=0x00000008;
	delay(10);
	IOCLR0=0x00000008;
	y=value;
	y=y&0x0f;
	y=y<<4;
	IOCLR0=0x000000fc;
	IOCLR0=0x00000004;
	IOSET0=y;
	IOSET0=0x00000008;
	delay(10);
	IOCLR0=0x00000008;
}
void serial_disp(unsigned char *msg)
{
	unsigned int i=0;
while(msg[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msg[i];
		 i++;
	 }
	 i=0;
	 U0THR='\r';
	 U0THR='\n';
}
