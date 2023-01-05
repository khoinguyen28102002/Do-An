#include "output.h"
#include "../global/global.h"

unsigned char arrayMapOfOutput [8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
unsigned char array_led7seg [10] = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09};

void delay_ms(int value)
{
	int i,j;
	for(i=0;i<value;i++)
		for(j=0;j<238;j++);
}
void init_output(void)
{
   TRISD_OUT = 0x00;
   PORTD_OUT = 0x00;
   TRISA_OUT = 0x00;
   PORTA_OUT = 0x00;
   TRISE_OUT = 0x00;
   PORTE_OUT = 0x00;
}
void OpenOutputA(int index)
{
	if (index >= 0 && index <= 7)
	{
		PORTA_OUT = PORTA_OUT | arrayMapOfOutput[index];
	}
}

void OpenOutputE(int index)
{
	if (index >= 0 && index <= 3)
	{
		PORTE_OUT = PORTE_OUT | arrayMapOfOutput[index];
	}
}

void OpenOutput(int index)
{
	if (index >= 0 && index <= 7)
	{
		PORTD_OUT = PORTD_OUT | arrayMapOfOutput[index];
	}
}

void CloseOutput(int index)
{
	if (index >= 0 && index <= 7)
	{
		PORTD_OUT = PORTD_OUT & ~arrayMapOfOutput[index];
	}
}

void CloseOutputA(int index) 
{
    if (index >= 0 && index <= 7) {
        PORTA_OUT = PORTA_OUT & ~arrayMapOfOutput[index];
    }
}

void CloseOutputE(int index) 
{
    if (index >= 0 && index <= 3) {
        PORTE_OUT = PORTE_OUT & ~arrayMapOfOutput[index];
    }
}
void TestOutput(void)
{
	int k;
	for (k=0;k<14 ;k++ )
	{
		OpenOutput(k);
		delay_ms(500);
		CloseOutput(k);
		delay_ms(500);
	}
}
// CAC HAM BAT TAT DEN
void Phase1_GreenOn()
{
    OpenOutputE(0);
}
void Phase1_GreenOff()
{
    CloseOutputE(0);
}

void Phase1_YellowOn()
{
    OpenOutputA(2);
}
void Phase1_YellowOff()
{
    CloseOutputA(2);
}

void Phase1_RedOn()
{
    OpenOutput(7);
}
void Phase1_RedOff()
{
    CloseOutput(7);
}

void Phase2_GreenOn()
{
    OpenOutputA(1);
}
void Phase2_GreenOff()
{
    CloseOutputA(1);
}

void Phase2_YellowOn()
{
    OpenOutputA(3);
}
void Phase2_YellowOff()
{
    CloseOutputA(3);
}
void Phase2_RedOn()
{
    OpenOutput(6);
}
void Phase2_RedOff()
{
    CloseOutput(6);
}
//CAC HAM HO TRO HIEN THOI GIAN TREN 2 LED 7 DOAN TUYEN 1
void shiftOutLed1(unsigned char number)
{
    int i, temp;
    for (i=0; i<8; i++) {
        temp = (number &(1 << i));
        if (temp) 
            OpenOutput(0);
        else 
            CloseOutput(0);
        CloseOutput(1);
        OpenOutput(1);
    }
}
void showLedPhase1() 
{
    shiftOutLed1(array_led7seg[timeOfPhase1%10]);
    shiftOutLed1(array_led7seg[timeOfPhase1/10]);
    CloseOutput(2);
    OpenOutput(2);
}
void setLedPhase1() 
{
    pretimeOfPhase1 = timeOfPhase1;
    timeOfPhase1 = 0;
}
// HAM HO TRO HIEN THI THOI GIAN TREN LED 7 DOAN PHASE 2
void shiftOutLed2(unsigned char number)
{
    int i, temp;
    for (i=0; i<8; i++) {
        temp = (number &(1 << i));
        if (temp) 
            OpenOutput(3);
        else 
            CloseOutput(3);
        CloseOutput(4);
        OpenOutput(4);
    }
}

void showLedPhase2() {
    shiftOutLed2(array_led7seg[timeOfPhase2%10]);
    shiftOutLed2(array_led7seg[timeOfPhase2/10]);
    CloseOutput(5);
    OpenOutput(5);
}

void setLedPhase2() {
    pretimeOfPhase2 = timeOfPhase2;
    timeOfPhase2 = 0;
}