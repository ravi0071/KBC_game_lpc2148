#ifndef __buzz1_h
#define __buzz1_h
extern void buzz1(void);
#endif
#ifdef __lcd_h
#define __lcd_h
extern void lcd(int);
#endif
#ifdef __delay_h
#define __delay_h
extern void delay(int);
#endif
#ifdef __data_h
#define __data_h
extern void data(unsigned int);
#endif
#ifdef __uart_h
#define __uart_h
extern void serial_disp(char *);
#endif
