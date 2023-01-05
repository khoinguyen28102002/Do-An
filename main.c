#include "main.h"
// Noi khai bao hang so
#define     LED     PORTD
#define     ON      1
#define     OFF     0

#define     ADDRESS_SECOND  0x00
#define     ADDRESS_MINUTE  0x01
#define     ADDRESS_HOUR    0x02
#define     ADDRESS_DAY     0x03
#define     ADDRESS_DATE    0x04
#define     ADDRESS_MONTH   0x05
#define     ADDRESS_YEAR    0x06


// Khai bao cac ham co ban IO
//void init_output(void);
void init_system(void);
//void delay_ms(int value);
//void OpenOutput(int index);
//void CloseOutput(int index);
//void TestOutput(void);
//void ReverseOutput(int index);
//void Test_KeyMatrix();

// CAC HAM BAT TAT DEN GIAO THONG TUYEN 1
//void Phase1_GreenOn();
//void Phase1_GreenOff();
//void Phase1_YellowOn();
//void Phase1_YellowOff();
//void Phase1_RedOn();
//void Phase1_RedOff();

// CAC HAM BAT TAT DEN GIAO THONG TUYEN 2
//void Phase2_GreenOn();
//void Phase2_GreenOff();
//void Phase2_YellowOn();
//void Phase2_YellowOff();
//void Phase2_RedOn();
//void Phase2_RedOff();

// CAC HAM CAN CHO HE THONG
//void AppTrafficLight();
//void shiftOutLed1(unsigned char number);
//void shiftOutLed2(unsigned char number);
//void showLedPhase1();
//void showLedPhase2();
//void setLedPhase1();
//void setLedPhase2();
//unsigned char arrayMapOfPassword[5][4]= {
//  {1,2,3,4},
//  {2,7,8,9},
//  {3,3,3,3},
//  {4,8,6,8},
//  {5,'A','B','C'},
//};
//unsigned char arrayPassword[4];
//unsigned char password_flag = 0;
void SetupTimeForRealTime();
void BaiTap_I2C();
void DisplayTime();
unsigned char CheckPassword();

void main(void)
{
	unsigned int k = 0;
	init_system();
    delay_ms(1000);
//    SetupTimeForRealTime();
	while (1)
	{
        while (!flag_timer3);
        flag_timer3 = 0;
        scan_key_matrix(); // 8 button
        BaiTap_I2C();
        AppTrafficLight();
        showLedPhase1();
        showLedPhase2();
        DisplayLcdScreenOld(); //Output process 14ms vs 10ms with no timer
            
	}
}

void init_system(void)
{
    init_output();
    lcd_init();
    init_key_matrix();
    init_interrupt();
    lcd_clear();
    LcdClearS();
    delay_ms(500);
    init_timer0(4695);      //dinh thoi 1ms sai so 1%
    init_timer3(46950);     //dinh thoi 10ms
    SetTimer0_ms(2);
    SetTimer3_ms(50);       //Chu ky thuc hien viec xu ly input,proccess,output
    init_i2c();
    //PORTAbits.RA0 = 1;
}

void SetupTimeForRealTime()
{
    second = 20;
    minute = 13;
    hour = 23;
    day = 3;
    date = 3;
    month = 1;
    year = 23;
    write_ds1307(ADDRESS_SECOND, second);
    write_ds1307(ADDRESS_MINUTE, minute);
    write_ds1307(ADDRESS_HOUR, hour);
    write_ds1307(ADDRESS_DAY, day);
    write_ds1307(ADDRESS_DATE, date);
    write_ds1307(ADDRESS_MONTH, month);
    write_ds1307(ADDRESS_YEAR, year);
}
void DisplayTime(){
    LcdPrintNumS(1,0,date/10);
    LcdPrintNumS(1,1,date%10);
    LcdPrintStringS(1,2,"/");
    LcdPrintNumS(1,3,month/10);
    LcdPrintNumS(1,4,month%10);
    LcdPrintStringS(1,5,"/");
    LcdPrintNumS(1,6,year/10);
    LcdPrintNumS(1,7,year%10);
    
    LcdPrintNumS(1,11,hour/10);
    LcdPrintNumS(1,12,hour%10);
    LcdPrintStringS(1,13,":");
    LcdPrintNumS(1,14,minute/10);
    LcdPrintNumS(1,15,minute%10);
}
void BaiTap_I2C()
{
    second = read_ds1307(ADDRESS_SECOND);
    minute = read_ds1307(ADDRESS_MINUTE);
    hour = read_ds1307(ADDRESS_HOUR);
    day = read_ds1307(ADDRESS_DAY);
    date = read_ds1307(ADDRESS_DATE);
    month = read_ds1307(ADDRESS_MONTH);
    year = read_ds1307(ADDRESS_YEAR);
}
unsigned char CheckPassword()
{
    unsigned char i,j;
    unsigned char result = 0;
    for (i=0;i<5;i++)
    {
        result = 1;
        for (j=0;j<4;j++)
        {
            if (arrayPassword[j] != arrayMapOfPassword[i][j])
                result = 0;
        }
        if (result == 1){
            return (i+1);
        }
    }
    return result;
}

