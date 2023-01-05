#ifndef GLOBAL_H
#define	GLOBAL_H
#include <p18f4620.h>

// CAC TRANG THAI CHUNG CUA HE THONG
#define     INIT_SYSTEM         255
#define     SET_TIME            254
#define     SLOW_MODE           253
#define     MANUAL_MODE         252
#define     PEDESTRIAN          251
#define     START               250

// CAC TRANG THAI KIEM TRA MAT KHAU
#define     INIT                50
#define     ENTER_PASSWORD      51
#define     CHECK_PASSWORD      52
#define     WRONG_PASSWORD      54

// CAC TRANG THAI CHE DO SET TIME
#define     SET_PHASE1_GREEN    5
#define     SET_PHASE1_YELLOW   6
#define     SET_PHASE2_GREEN    7
#define     SET_PHASE2_YELLOW   8

// CAC TRANG THAI CHE DO AUTOMATIC
#define     GREEN1_RED2         10
#define     YELLOW1_RED2        11
#define     RED1_GREEN2         12
#define     RED1_YELLOW2        13

//CAC TRANG THAI CHE DO MANUAL
#define     MANUAL_0            20
#define     MANUAL_1            21
#define     MANUAL_2            22
#define     MANUAL_3            23
#define     MANUAL_4            24

//CAC TRANG THAI CHE DO PEDESTRIAN
#define     PEDES_0             30
#define     PEDES_1             31
#define     PEDES_2             32
#define     PEDES_3             33
#define     PEDES_4             34
#define     PEDES_5             35
#define     PEDES_6             36

//CAC TRANG THAI CHE DO SLOW
#define     SLOW_0              40
#define     SLOW_I2C            41
#define     SLOW_BUTTON         42
#define     SLOW_I2C_EXIT       43

// CAC BIEN LUU THOI GIAN HIEN THI TREN 2 LED 7 DOAN
extern unsigned char timeOfPhase1 ;
extern unsigned char timeOfPhase2 ;
extern unsigned char pretimeOfPhase1;
extern unsigned char pretimeOfPhase2 ;

//CAC BIEN PHU
extern unsigned char set_flag ; // flag for timer
extern unsigned char cntOfLight;
extern unsigned char indexOfNumber;
extern unsigned char timeDelay;
extern unsigned char arrayInput[2];
extern unsigned char numberValue ;
extern unsigned char slowCnt;
extern unsigned char isSetTime;

// CAC BIEN LUU CAC TRANG THAI
extern unsigned char statusSystem;
extern unsigned char previousStatus;
extern unsigned char nextStatus;
extern unsigned char setTimeStatus;
extern unsigned char autoStatus;
extern unsigned char slowModeStatus;
extern unsigned char manualStatus ;
extern unsigned char pedestrianStatus;

// CAC BIEN LUU THOI GIAN DEM NGUOC TUYEN 1
extern unsigned char timeOfGreenPhase1 ;
extern unsigned char timeOfYellowPhase1;
extern unsigned char timeOfRedPhase1 ;

// CAC BIEN LUU THOI GIAN DEM NGUOC TUYEN 2
extern unsigned char timeOfGreenPhase2;
extern unsigned char timeOfYellowPhase2 ;
extern unsigned char timeOfRedPhase2;

// CAC BIEN LUU THOI GIAN DUOC SET TUYEN 1
extern unsigned char setTimeOfGreenPhase1;
extern unsigned char setTimeOfYellowPhase1;
extern unsigned char setTimeOfRedPhase1 ;

// CAC BIEN LUU THOI GIAN DUOC SET TUYEN 2
extern unsigned char setTimeOfGreenPhase2 ;
extern unsigned char setTimeOfYellowPhase2;
extern unsigned char setTimeOfRedPhase2;

// CAC BIEN LUU THOI GIAN THUC
extern char second,minute ,hour;
extern char day;
extern char date ,month,year ;
extern unsigned char count;

// CAC BIEN KIEM TRA MAT KHAU
extern unsigned char arrayMapOfPassword [5][4];
extern unsigned char arrayPassword[4];
extern unsigned char password_flag;
extern unsigned char checkPass;             
extern unsigned char index1, index2;
extern unsigned char result;
#endif	/* GLOBAL_H */

