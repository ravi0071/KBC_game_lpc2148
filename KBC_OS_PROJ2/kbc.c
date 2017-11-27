#include<stdio.h>
#include<rtl.h>
#include<lpc21xx.h>
#include "buzz.h"
#define PRESCALER 11999
#define DESIRED_COUNT 1000
extern void buzz1(void);
extern void lcd(unsigned int);
extern void delay(unsigned int);
OS_TID tsk1,tsk2,tsk3,tsk4,tsk5,tsk6;
OS_RESULT RE1,RE2,RE3,RE4,RE5,RE6;
unsigned int a,b,c,count=0,i;
__task void job1(void);
__task void job2(void);
__task void job3(void);
__task void job4(void);
__task void job5(void);
__task void job6(void);
char msgcor[]={"Answer is correct "};
char msgcor1[]={"Answer is incorrect "};
char audipoll[]={"**** Audience pole ****** "};
char msg8[]={"Press L for AUDIENCE POLE or F for phone of friend "};
char phonef[]={"************* Calling Friend ************** "};
void init_serial(void);
void init_lcd(void);
void InitTimer(void);
void cmd(unsigned int);
void delay();
char arr[50];
//char pts10[]={"your points:10"};
int main()
{
	 unsigned int i=0;
	unsigned char d;
	 char msg1[]={"Welcome to the quiz "};                   //welcome message
	 char msgstr[]={"Press any button to start "};
	 
	 init_serial();
	 init_lcd();
	 while(msg1[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msg1[i];
		
		 i++;
	 }
	U0THR='\n';
	 i=0;
	 while(msgstr[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgstr[i];
		
		 i++;
	 }
	U0THR='\n';
	 i=0;
	 while(!(U0LSR&0x01));
	 d=U0RBR;
	 U0THR=d;
	 U0THR='\r';
	 U0THR='\n';
	 PINSEL0|=0x00000000;
InitTimer();
init_serial();	
T0TCR=0x01;
	 os_sys_init(job1);
}
void InitTimer(void)
{
T0PR=PRESCALER;
T0MR0=DESIRED_COUNT;
T0MCR=3;
T0TCR=2;
}
void init_serial(void)
{
	PINSEL0|=0X00000005;
	U0LCR=0X83;
	U0DLL=0X61;
	U0LCR=0X03;
}
/////////////////////question 1/////////////////////////////
__task void job1()
{ 
	unsigned int i=0;
	char msg2[]={"Q1: The worlds largest mountain peak is "};
	char msg3[]={"a: Nrupatunga betta"};
	char msg4[]={"b: Mt everest "};
	char msg5[]={"c: Mt shifu "};
	char msg6[]={"d: Mt po "};
	char msg7[]={"a:5%, b:85%, c:7%, d:3% "};
	char msg9[]={"Friend says b or c "};
	init_lcd();
	while(1)	{ 
		 init_serial();
	 while(msg2[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msg2[i];
		 i++;
	 }
	 i=0;
	 U0THR='\r';
	 U0THR='\n';
	  while(msg3[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msg3[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	   while(msg4[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msg4[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	   while(msg5[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msg5[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	
	  while(msg6[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msg6[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 while(msg8[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msg8[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 count=0;
	 while(!(U0LSR&0x01))
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
		lcd(count);
	count++;
	 T0IR=0x01;
			
	}
	else
	{
		count=0;
		while(msgcor1[i]!='\0')
		{
		 while(!(U0LSR&0x20));
		 U0THR=msgcor1[i];
		 i++;
	 }
		U0THR='\r';
	 U0THR='\n';
	 i=0;
	 tsk6=os_tsk_create(job6,1);
	 	os_evt_set(0x0006,tsk6);
	 os_tsk_prio(tsk6,6);
		break;
	}
}
 while(!(U0LSR&0x01));
	 a=0;
	 a=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';

	 switch(a)
	 {
		 case 'b':
			 while(msgcor[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgcor[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 
	 tsk2= os_tsk_create(job2,2);
	 os_evt_set(0x0002,tsk2);
	 os_tsk_prio(tsk2,2);
		break;
   	 
	 case 'l':
			 while(audipoll[i]!='\0')  //audience pole
	 {
		 while(!(U0LSR&0x20));
		 U0THR=audipoll[i];
		 
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	  while(msg7[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msg7[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 while(!(U0LSR&0x01));
	 c=0;
	 c=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';
	 {
		 switch(c)
	 {
		 case 'b':
			 while(msgcor[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgcor[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 tsk2= os_tsk_create(job2,2);
	 os_evt_set(0x0002,tsk2);
	 os_tsk_prio(tsk2,2);
		break;
		 default :
	 while(msgcor1[i]!='\0')
{
while(!(U0LSR&0x20));
U0THR=msgcor1[i];
		 i++;
	 }
		U0THR='\r';
	 U0THR='\n';
	 i=0;
	 tsk6=os_tsk_create(job6,1);
	 	os_evt_set(0x0006,tsk6);
	 os_tsk_prio(tsk6,6);
	 	 }
	 
		break;
	 case 'f':                     //phone a friend
			 while(phonef[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=phonef[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 while(msg9[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msg9[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 while(!(U0LSR&0x01));
	 c=0;
	 c=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';
	 switch(c)
	 {
		 case 'b':
			 while(msgcor[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgcor[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 tsk2= os_tsk_create(job2,2);
	 os_evt_set(0x0002,tsk2);
	 os_tsk_prio(tsk2,2);
		break;
	 	 }
 }
		
		 		default: 
while(msgcor1[i]!='\0')
{
while(!(U0LSR&0x20));
U0THR=msgcor1[i];
		 i++;
	 }
		U0THR='\r';
	 U0THR='\n';
	 i=0;
	 tsk6=os_tsk_create(job6,1);
	 	os_evt_set(0x0006,tsk6);
	 os_tsk_prio(tsk6,6);
			break;
			}
	 os_dly_wait(10);
		
}
	}
/////////////////////question 2/////////////////////////////
 __task void job2()
{ 
	unsigned int i=0;
	
	char msgg2[]={"Q2: The number of continents is "};
	char msgg3[]={"a: Seven "};
	char msgg4[]={"b: Eight "};
	char msgg5[]={"c: Nine "};
	char msgg6[]={"d: Ten "};
	char msg7[]={"a:85%, b:10%, c:7%, d:3% "};
	char msg9[]={"Friend says a or c "};
	while(1)	{ 
		RE2=os_evt_wait_or(0x0002,0x30);
		if(RE2==OS_R_EVT)
		{
		 init_serial();
	 while(msgg2[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgg2[i];
		 i++;
	 }
	 i=0;
	 U0THR='\r';
	 U0THR='\n';
	  while(msgg3[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgg3[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	   while(msgg4[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgg4[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	   while(msgg5[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgg5[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	
	  while(msgg6[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgg6[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 while(msg8[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msg8[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 
	 count=0;
	 while(!(U0LSR&0x01))
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
		lcd(count);
		while(!(T0IR==0x01));	
	count++;
	
	 T0IR=0x01;
	}
	else
	{
		count=0;
		while(msgcor1[i]!='\0')
		{
		 while(!(U0LSR&0x20));
		 U0THR=msgcor1[i];
		 i++;
	 }
		U0THR='\r';
	 U0THR='\n';
	 i=0;
	 tsk6=os_tsk_create(job6,1);
	 	os_evt_set(0x0006,tsk6);
	 os_tsk_prio(tsk6,6);
		break;
	}
}
	 while(!(U0LSR&0x01));
	 c=0;
	 c=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';
	 
	 switch(c)
	 {
		 case 'a':
			 while(msgcor[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgcor[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 tsk3= os_tsk_create(job3,2);
	 os_evt_set(0x0002,tsk3);
	 os_tsk_prio(tsk3,2);
		break;
 
	 
	 case 'l':
			 while(audipoll[i]!='\0')  //audience pole
	 {
		 while(!(U0LSR&0x20));
		 U0THR=audipoll[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	  while(msg7[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msg7[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 while(!(U0LSR&0x01));
	 c=0;
	 c=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';
	 {
		 switch(c)
	 {
		 case 'a':
			 while(msgcor[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgcor[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 tsk3= os_tsk_create(job3,2);
	 os_evt_set(0x0002,tsk3);
	 os_tsk_prio(tsk3,2);
		break;
		 default :
	 while(msgcor1[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgcor1[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	  	tsk6=  os_tsk_create(job6,6);
	 	os_evt_set(0x0006,tsk6);
	 	 }
	 	break;
	 case 'f':                     //phone a friend
			 while(phonef[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=phonef[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 while(msg9[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msg9[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 while(!(U0LSR&0x01));
	 c=0;
	 c=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';
	 switch(c)
	 {
		 case 'a':
			 while(msgcor[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgcor[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 tsk3= os_tsk_create(job3,2);
	 os_evt_set(0x0002,tsk3);
	 os_tsk_prio(tsk3,2);
		break;
	 	 }
 
	
	 }
	 tsk3= os_tsk_create(job3,1);
	 os_evt_set(0x0003,tsk3);
	 os_tsk_prio(tsk3,3);
		
		default:
			 while(msgcor1[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgcor1[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	  	tsk6=  os_tsk_create(job6,6);
	 	os_evt_set(0x0006,tsk6);
	 break;

 }                                           
			}
		}	 
}
	
//////////////////////////////question 3////////////////////////////////
__task void job3()
{ 
	unsigned int i=0;
	
	char msggg2[]={"Q3: The number of oceans is "};
	char msggg3[]={"a: Two "};
	char msggg4[]={"b: Three "};
	char msggg5[]={"c: Four "};
	char msggg6[]={"d: Five "};
	
	while(1)	{
 RE3=os_evt_wait_or(0x0003,0x30);
		if(RE3==OS_R_EVT)
		{		
		 init_serial();
	 while(msggg2[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msggg2[i];
		 i++;
	 }
	 i=0;
	 U0THR='\r';
	 U0THR='\n';
	  while(msggg3[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msggg3[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	   while(msggg4[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msggg4[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	   while(msggg5[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msggg5[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	
	  while(msggg6[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msggg6[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 count=0;
	 while(!(U0LSR&0x01))
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
		lcd(count);
		while(!(T0IR==0x01));	
	count++;
	
	 T0IR=0x01;
	}
	else
	{
		count=0;
		while(msgcor1[i]!='\0')
		{
		 while(!(U0LSR&0x20));
		 U0THR=msgcor1[i];
		 i++;
	 }
		U0THR='\r';
	 U0THR='\n';
	 i=0;
	 tsk6=os_tsk_create(job6,1);
	 	os_evt_set(0x0006,tsk6);
	 os_tsk_prio(tsk6,6);
		break;
	}
}
	 while(!(U0LSR&0x01));
	 a=0;
	 a=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';
	 
	 switch(a)
	 {
		 case 'c':
			 while(msgcor[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgcor[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	  
	tsk4=os_tsk_create(job4,1);
	 os_evt_set(0x0004,tsk4);
	 os_tsk_prio(tsk4,4);
		break;
		default:
			 while(msgcor1[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgcor1[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	  	tsk6=  os_tsk_create(job6,6);
	 	os_evt_set(0x0006,tsk6);
	 break;
			}
		}	 
}
	}
/////////////////////////////////question 4//////////////////////////////////////////
__task void job4()
{ 
	unsigned int i=0;
	
	char msggg[]={"Q4: The number of planets is "};
	char msggg1[]={"a: Two "};
	char msggg2[]={"b: Three "};
	char msggg3[]={"c: Nine "};
	char msggg4[]={"d: Five "};
	
	while(1)	{ 
		RE4=os_evt_wait_or(0x0004,0x30);
		if(RE4==OS_R_EVT)
		{
		 init_serial();
	 while(msggg[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msggg[i];
		 i++;
	 }
	 i=0;
	 U0THR='\r';
	 U0THR='\n';
	  while(msggg1[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msggg1[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	   while(msggg2[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msggg2[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	   while(msggg3[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msggg3[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	
	  while(msggg4[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msggg4[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 count=0;
	 while(!(U0LSR&0x01))
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
		lcd(count);
		while(!(T0IR==0x01));	
	count++;
	
	 T0IR=0x01;
	}
	else
	{
		count=0;
		while(msgcor1[i]!='\0')
		{
		 while(!(U0LSR&0x20));
		 U0THR=msgcor1[i];
		 i++;
	 }
		U0THR='\r';
	 U0THR='\n';
	 i=0;
	 tsk6=os_tsk_create(job6,1);
	 	os_evt_set(0x0006,tsk6);
	 os_tsk_prio(tsk6,6);
		break;
	}
}
	 while(!(U0LSR&0x01));
	 a=0;
	 a=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';
	 switch(a)
	 {
		 case 'c':
			 while(msgcor[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgcor[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	tsk5=os_tsk_create(job5,1);
	 os_evt_set(0x0005,tsk5);
	 os_tsk_prio(tsk5,5);
		break;
		default:
			 while(msgcor1[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgcor1[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	  	tsk6=  os_tsk_create(job6,6);
	 	os_evt_set(0x0006,tsk6);
	 break;
			}
		}	 
}
	}
////////////////////////////////////////question 5//////////////////////////////
__task void job5()
{ 
	unsigned int i=0;
	
	char msggg[]={"Q5: Our galaxy is "};
	char msgg11[]={"a: Andromeda "};
	char msgg22[]={"b: Asgard "};
	char msgg33[]={"c: Milky Way "};
	char msgg44[]={"d: None of the above "};
	
	while(1)	{ 
		RE5=os_evt_wait_or(0x0005,0x30);
		if(RE5==OS_R_EVT)
		{
		 init_serial();
	 while(msggg[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msggg[i];
		 i++;
	 }
	 i=0;
	 U0THR='\r';
	 U0THR='\n';
	  while(msgg11[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgg11[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	   while(msgg22[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgg22[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	   while(msgg33[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgg33[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	
	  while(msgg44[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgg44[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 count=0;
	 while(!(U0LSR&0x01))
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
		lcd(count);
		while(!(T0IR==0x01));	
	count++;
	
	 T0IR=0x01;
	}
	else
	{
		count=0;
		while(msgcor1[i]!='\0')
		{
		 while(!(U0LSR&0x20));
		 U0THR=msgcor1[i];
		 i++;
	 }
		U0THR='\r';
	 U0THR='\n';
	 i=0;
	 tsk6=os_tsk_create(job6,1);
	 	os_evt_set(0x0006,tsk6);
	 os_tsk_prio(tsk6,6);
		break;
	}
}
	 while(!(U0LSR&0x01));
	 a=0;
	 a=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';
	 
	 switch(a)
	 {
		 case 'c':
			 while(msgcor[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgcor[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 
	while(1)
	{
		char winmsg[]={"You won!!!!!!!!!! "};
		while(winmsg[i]!='\0')
		{
		while(!(U0LSR&0x20));
		U0THR=winmsg[i];
		i++;
		}
		U0THR='\r';
		U0THR='\n';
		i=0;
	}
		
		default:
			 while(msgcor1[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msgcor1[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
	 tsk6=os_tsk_create(job6,6);
	 os_evt_set(0x0006,tsk6);
	 break;
			}
		}	 
}
	}
__task void job6()
{ 
	while(1)
	{
		 unsigned int i;
		char msg7[]={"Aaap har gaye !!!!!!! hot seat se utarjao "};

	RE6=os_evt_wait_or(0x0006,0x0030);
		if(RE6==OS_R_EVT)
{
	while(1)
	{buzz1();
 	  while(msg7[i]!='\0')
	 {
		 while(!(U0LSR&0x20));
		 U0THR=msg7[i];
		 i++;
	 }
	 U0THR='\r';
	 U0THR='\n';
	 i=0;
}
	}
	
}
}
void init_lcd(void)
  {
		int c1[]={0x30,0x30,0x38,0x20,0x20,0x28,0x01,0x06,0x0e,0x80};
	 unsigned char i;
	 PINSEL0|=0x00000000;
	 IODIR0=0x000000fc;
	 IOCLR0=0x000000fc;
	 for(i=0;i<9;i++)
	 {
	 	cmd(c1[i]);
		delay(10000);
	 }
	 cmd(0x80);
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


