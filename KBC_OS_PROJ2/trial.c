#include<stdio.h>
#include<rtl.h>
#include<lpc21xx.h>
#include "buzz.h"
#define PRESCALER 11999
#define DESIRED_COUNT 1000
extern void buzz1(void);
extern void lcd(unsigned char);
extern void delay(unsigned int);
extern void cmd(unsigned int);
extern void serial_disp(char *);
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
char arr[50];
int main()
{
	 unsigned int i=0;
	unsigned char d;
	 char msg1[]={"Welcome to the kbc "};                   //welcome message
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
__task void job1()/////////////////////question 1/////////////////////////////
{ 
	unsigned int i=0;
	char money1[]={" AMT: 1,00,000"};
	char msg2[]={"Q1: The worlds largest mountain peak is "};
	char msg3[]={"a: Nrupatunga betta"};
	char msg4[]={"b: Mt everest "};
	char msg5[]={"c: Mt shifu "};
	char msg6[]={"d: Mt po "};
	char msg7[]={"a:5%, b:85%, c:7%, d:3% "};
	char msg9[]={"Friend says b or c "};
	while(1)	
		{ 
		 init_serial();
			T0TCR=0x01;
			init_lcd();
	while(money1[i]!='\0')
			{
			lcd(money1[i]);
				i++;
				delay(500);
			} 
			i=0;
	 serial_disp(msg2);
	 serial_disp(msg3);
	 serial_disp(msg4);
	 serial_disp(msg5);
	 serial_disp(msg6);
	 serial_disp(msg8);
	 count=15;
	 while(!(U0LSR&0x01))
{
if(count!=0)
	{
	  sprintf(arr,"seconds:%d",count);
	serial_disp(arr);
		while(!(T0IR==0x01));	
	count--;
	T0IR=0x01;		
	}
	else
	{
		serial_disp(msgcor1);
	 tsk6=os_tsk_create(job6,1);
	 	os_evt_set(0x0006,tsk6);
	 os_tsk_prio(tsk6,6);
		break;
	}
}
	 a=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';
 switch(a)
	 {
		 case 'b':
			serial_disp(msgcor);
	 tsk2= os_tsk_create(job2,2);
	 os_evt_set(0x0002,tsk2);
	 os_tsk_prio(tsk2,2);
		break;
   	case 'l':
			serial_disp(audipoll);
	 serial_disp(msg7);
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
			serial_disp(msgcor);
	 tsk2= os_tsk_create(job2,2);
	 os_evt_set(0x0002,tsk2);
	 os_tsk_prio(tsk2,2);
		break;
		 default :
	serial_disp(msgcor1);
	 tsk6=os_tsk_create(job6,1);
	 	os_evt_set(0x0006,tsk6);
	 os_tsk_prio(tsk6,6);
	 	 }
	 break;
	 case 'f':                     //phone a friend
			serial_disp(phonef);
	serial_disp(msg9);
	 while(!(U0LSR&0x01));
	 c=0;
	 c=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';
	 switch(c)
	 {
		 case 'b':
			serial_disp(msgcor);
	 tsk2= os_tsk_create(job2,2);
	 os_evt_set(0x0002,tsk2);
	 os_tsk_prio(tsk2,2);
		break;
	 	 }
 }
		default: 
    serial_disp(msgcor1);
	 tsk6=os_tsk_create(job6,1);
	 	os_evt_set(0x0006,tsk6);
	 os_tsk_prio(tsk6,6);
			break;
			}
	 os_dly_wait(10);
	}
	}
 __task void job2()/////////////////////question 2/////////////////////////////
{ 
	unsigned int i=0;
	char money2[]={" AMT:12,50,000"};
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
			init_lcd();
	while(money2[i]!='\0')
			{
			lcd(money2[i]);
				i++;
				delay(500);
			} 
			i=0;
	 serial_disp(msgg2);
	 serial_disp(msgg3);
	 serial_disp(msgg4);
	 serial_disp(msgg5);
	 serial_disp(msgg6);
   serial_disp(msg8);
	 count=15;
	 while(!(U0LSR&0x01))
{
	if(count!=0)
	{
	sprintf(arr,"seconds:%d",count);
	serial_disp(arr);
	while(!(T0IR==0x01));	
	count--;
	T0IR=0x01;
	}
	else
	{
		count=0;
		serial_disp(msgcor1);
	 tsk6=os_tsk_create(job6,1);
	 	os_evt_set(0x0006,tsk6);
	 os_tsk_prio(tsk6,6);
		break;
	}
}
	 c=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';
	 switch(c)
	 {
		 case 'a':
	serial_disp(msgcor);
	 tsk3= os_tsk_create(job3,2);
	 os_evt_set(0x0002,tsk3);
	 os_tsk_prio(tsk3,2);
		break;
  case 'l':
	serial_disp(audipoll);
	 serial_disp(msg7);
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
	serial_disp(msgcor);
	 tsk3= os_tsk_create(job3,2);
	 os_evt_set(0x0002,tsk3);
	 os_tsk_prio(tsk3,2);
		break;
		 default :
	  serial_disp(msgcor1);
	  tsk6=  os_tsk_create(job6,6);
	 	os_evt_set(0x0006,tsk6);
	 	 }
	 	break;
	 case 'f':                     //phone a friend
		serial_disp(phonef);
	serial_disp(msg9);
	 while(!(U0LSR&0x01));
	 c=0;
	 c=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';
	 switch(c)
	 {
		 case 'a':
		serial_disp(msgcor);
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
	 serial_disp(msgcor1);
	  tsk6=  os_tsk_create(job6,6);
	 	os_evt_set(0x0006,tsk6);
	 break;
}                                           
			}
		}	 
}
__task void job3()//////////////////////////////question 3////////////////////////////////
{ 
	unsigned int i=0;
	char money3[]={" AMT:25,00,000"};
	char msggg2[]={"Q3: The number of oceans is "};
	char msggg3[]={"a: Two "};
	char msggg4[]={"b: Three "};
	char msggg5[]={"c: Four "};
	char msggg6[]={"d: Five "};
	while(1)	{
		init_lcd();
	while(money3[i]!='\0')
			{
			lcd(money3[i]);
				i++;
				delay(500);
			} 
			i=0;
 RE3=os_evt_wait_or(0x0003,0x30);
		if(RE3==OS_R_EVT)
		{		
		 init_serial();
	serial_disp(msggg2);
	serial_disp(msggg3);
	 serial_disp(msggg4);
	 serial_disp(msggg5);
	serial_disp(msggg6);
	 count=15;
	 while(!(U0LSR&0x01))
{
 if(count!=0)
	{
	  sprintf(arr,"seconds:%d",count);
   serial_disp(arr);
		while(!(T0IR==0x01));	
	count--;
	T0IR=0x01;
	}
	else
	{
		count=0;
	serial_disp(msgcor1);
	 tsk6=os_tsk_create(job6,1);
	 	os_evt_set(0x0006,tsk6);
	 os_tsk_prio(tsk6,6);
		break;
	}
}
	 a=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';
	 switch(a)
	 {
		 case 'c':
		serial_disp(msgcor);
	tsk4=os_tsk_create(job4,1);
	 os_evt_set(0x0004,tsk4);
	 os_tsk_prio(tsk4,4);
		break;
		default:
		serial_disp(msgcor1);
	  	tsk6=  os_tsk_create(job6,6);
	 	os_evt_set(0x0006,tsk6);
	 break;
			}
		}	 
}
	}
__task void job4()/////////////////////////////////question 4//////////////////////////////////////////
{ 
	unsigned int i=0;
	char money4[]={" AMT:50,00,000"};
	char msggg[]={"Q4: The number of planets is "};
	char msggg1[]={"a: Two "};
	char msggg2[]={"b: Three "};
	char msggg3[]={"c: Nine "};
	char msggg4[]={"d: Five "};
	while(1)	{ 
		init_lcd();
	while(money4[i]!='\0')
			{
			lcd(money4[i]);
				i++;
				delay(500);
			} 
			i=0;
		RE4=os_evt_wait_or(0x0004,0x30);
		if(RE4==OS_R_EVT)
		{
		 init_serial();
	 serial_disp(msggg);
	 serial_disp(msggg1);
	 serial_disp(msggg2);
	 serial_disp(msggg3);
	 serial_disp(msggg4);
	 count=15;
	 while(!(U0LSR&0x01))
{
 if(count!=0)
	{
	  sprintf(arr,"seconds:%d",count);
	serial_disp(arr);
		while(!(T0IR==0x01));	
	count++;
	T0IR=0x01;
	}
	else
	{
		count=0;
   serial_disp(msgcor1);
	 tsk6=os_tsk_create(job6,1);
	 	os_evt_set(0x0006,tsk6);
	 os_tsk_prio(tsk6,6);
		break;
	}
}
	 a=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';
	 switch(a)
	 {
		 case 'c':
			serial_disp(msgcor);
	tsk5=os_tsk_create(job5,1);
	 os_evt_set(0x0005,tsk5);
	 os_tsk_prio(tsk5,5);
		break;
		default:
		serial_disp(msgcor1);
	  	tsk6=  os_tsk_create(job6,6);
	 	os_evt_set(0x0006,tsk6);
	 break;
			}
		}	 
}
	}
__task void job5()////////////////////////////////////////question 5//////////////////////////////
{ 
	unsigned int i=0;
	char money4[]={" AMT:1 CRORE!!!"};
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
	serial_disp(msggg);
	serial_disp(msgg11);
	serial_disp(msgg22);
	 serial_disp(msgg33);
	 serial_disp(msgg44);
	 count=15;
	 while(!(U0LSR&0x01))
{ 
	if(count!=0)
	{
	  sprintf(arr,"seconds:%d",count);
	serial_disp(arr);
		while(!(T0IR==0x01));	
	count--;
	T0IR=0x01;
	}
	else
	{
		count=0;
		serial_disp(msgcor1);
	 tsk6=os_tsk_create(job6,1);
	 	os_evt_set(0x0006,tsk6);
	 os_tsk_prio(tsk6,6);
		break;
	}
}
	 a=U0RBR;
	 U0THR=a;
	 U0THR='\r';
	 U0THR='\n';
	 
	 switch(a)
	 {
		 case 'c':
		serial_disp(msgcor);
	 while(1)
	{
		char winmsg[]={"Aap jeet gaye!!!!!!!!!! "};
		init_lcd();
	while(money4[i]!='\0')
			{
			lcd(money4[i]);
				i++;
				delay(500);
			} 
			i=0;
	serial_disp(winmsg);
	}
		default:
		serial_disp(msgcor1);
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
		char msg7[]={"Aaap har gaye !!!!!!! hot seat se utarjao "};
 RE6=os_evt_wait_or(0x0006,0x0030);
		if(RE6==OS_R_EVT)
{
	while(1)
	{buzz1();
 	 serial_disp(msg7);
}
	}
	}
}
void init_lcd(void)
  {
		int c1[]={0x30,0x30,0x38,0x20,0x20,0x28,0x01,0x06,0x0e,0x80};
	 unsigned int i=0;
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

