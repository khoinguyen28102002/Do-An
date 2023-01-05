
#ifndef OUTPUT_H
#define	OUTPUT_H
#include <p18f4620.h>

#define PORTD_OUT   PORTD
#define TRISD_OUT   TRISD

#define PORTA_OUT   PORTA
#define TRISA_OUT   TRISA

#define PORTB_OUT   PORTB
#define TRISB_OUT   TRISB

#define PORTE_OUT   PORTE
#define TRISE_OUT   TRISE

extern unsigned char arrayMapOfOutput [8];
extern unsigned char array_led7seg [10] ;

void delay_ms(int value);
void init_output(void);
void OpenOutputA(int index);

void OpenOutputE(int index);
void OpenOutput(int index);
void CloseOutput(int index);
void CloseOutputA(int index);
void CloseOutputE(int index) ;
void TestOutput(void);

// CAC HAM BAT TAT DEN
void Phase1_GreenOn();
void Phase1_GreenOff();
void Phase1_YellowOn();
void Phase1_YellowOff();
void Phase1_RedOn();
void Phase1_RedOff();

void Phase2_GreenOn();
void Phase2_GreenOff();
void Phase2_YellowOn();
void Phase2_YellowOff();
void Phase2_RedOn();
void Phase2_RedOff();

//CAC HAM HO TRO HIEN THOI GIAN TREN 2 LED 7 DOAN TUYEN 1
void shiftOutLed1(unsigned char number);
void showLedPhase1();
void setLedPhase1();
// HAM HO TRO HIEN THI THOI GIAN TREN LED 7 DOAN PHASE 2
void shiftOutLed2(unsigned char number);
void showLedPhase2();
void setLedPhase2();

#endif	/* OUTPUT_H */

