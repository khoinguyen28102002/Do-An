#include "global.h"

// CAC BIEN LUU THOI GIAN HIEN THI TREN 2 LED 7 DOAN
unsigned char timeOfPhase1 = 0;
unsigned char timeOfPhase2 = 0;
unsigned char pretimeOfPhase1 = 0;
unsigned char pretimeOfPhase2 = 0;

//CAC BIEN PHU
unsigned char set_flag = 0; // flag for timer
unsigned char cntOfLight = 0;
unsigned char indexOfNumber = 0;
unsigned char timeDelay = 0;
unsigned char arrayInput[2];
unsigned char numberValue = 0;
unsigned char slowCnt = 0;
unsigned char isSetTime=0;

// CAC BIEN LUU CAC TRANG THAI
unsigned char statusSystem = INIT;
unsigned char previousStatus = 0;
unsigned char nextStatus = 0;
unsigned char setTimeStatus = 0;
unsigned char autoStatus = 0;
unsigned char slowModeStatus = SLOW_0;
unsigned char manualStatus = 0;
unsigned char pedestrianStatus = 0;

// CAC BIEN LUU THOI GIAN DEM NGUOC TUYEN 1
unsigned char timeOfGreenPhase1 = 0;
unsigned char timeOfYellowPhase1 = 0;
unsigned char timeOfRedPhase1 = 0;

// CAC BIEN LUU THOI GIAN DEM NGUOC TUYEN 2
unsigned char timeOfGreenPhase2 = 0;
unsigned char timeOfYellowPhase2 = 0;
unsigned char timeOfRedPhase2 = 0;

// CAC BIEN LUU THOI GIAN DUOC SET TUYEN 1
unsigned char setTimeOfGreenPhase1 = 0;
unsigned char setTimeOfYellowPhase1 = 0;
unsigned char setTimeOfRedPhase1 = 0;

// CAC BIEN LUU THOI GIAN DUOC SET TUYEN 2
unsigned char setTimeOfGreenPhase2 = 0;
unsigned char setTimeOfYellowPhase2 = 0;
unsigned char setTimeOfRedPhase2 = 0;

// CAC BIEN LUU THOI GIAN THUC
char second = 0,minute = 0,hour = 0;
char day = 0;
char date = 0,month = 0,year = 0;
unsigned char count = 0;

// CAC BIEN KIEM TRA MAT KHAU
unsigned char arrayMapOfPassword[5][4]= {
  {1,2,3,4},
  {2,7,8,9},
  {3,3,3,3},
  {4,8,6,8},
  {5,'A','B','C'},
};
unsigned char arrayPassword[4];
unsigned char password_flag = 0;
unsigned char index1, index2;
unsigned char result = 0;