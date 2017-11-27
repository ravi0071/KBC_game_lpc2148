#include<lpc21xx.h>
#include<stdio.h>
#define DESIRED_COUNT 100
#define PRESCALER 11999
int count=0,i;
char arr[];
void init_serial(void);
void InitTimer(void);
int time(void)
{
PINSEL0=0x00000000;
InitTimer();
init_serial();	
T0TCR=0x01;
while(1)
{
	if(count!=10)
	{
	  sprintf(arr,"count:%d",count);
	while(arr[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=arr[i];
		 i++;
    }
	   U0THR='\r';
	 U0THR='\n';
		
	 i=0; 
	 while(!(T0IR==0x01));	
	 count++;
	
	 T0IR=0x01;
	}
	else
	{
		count=0;
		break;
	}
}
}

