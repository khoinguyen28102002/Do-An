#include "traffic.h"
#include "../global/global.h"
#include "../button_matrix/button.h"
#include "../lcd/lcd.h"
#include "../output/output.h"

void AppTrafficLight()
{
    
    cntOfLight = (cntOfLight + 1)%20;
    if (cntOfLight == 0){ 
        set_flag=1;
    }
    switch (statusSystem)
    {
        case INIT:
            clear_screen(2);
            setLedPhase1();
            setLedPhase2();
            Init_enter_password();
            if (isConfirmButtonPressed())
            {
                indexOfNumber = 0;
                timeDelay = 0;
                statusSystem = ENTER_PASSWORD;
                previousStatus = INIT;
            }
            break;
        case ENTER_PASSWORD:
            clear_screen(0);            
            LcdPrintStringS(0,0,"ENTER PASSWORD");
            if (indexOfNumber==0 ) {
                clear_screen(1);
                LcdPrintStringS(1,12,"____"); 
            }
            if (indexOfNumber==1) {
                clear_screen(1);            
                LcdPrintStringS(1,12,"*");
                LcdPrintStringS(1,13,"___");
            }
            if (indexOfNumber==2) {
                clear_screen(1);            
                LcdPrintStringS(1,12,"**");
                LcdPrintStringS(1,14,"__");
            }
            if (indexOfNumber==3) {
                clear_screen(1);            
                LcdPrintStringS(1,12,"***");
                LcdPrintStringS(1,15,"_");
            }
            
            if(indexOfNumber == 4){
                clear_screen(1);            
                LcdPrintStringS(1,12,"****");
            }
//            if (isButtonNumber()) {
//                int temp = indexOfNumber+1;
//                if (temp<3) {
//                    LcdPrintNumS(1,indexOfNumber+14,numberValue);
//                arrayInput[indexOfNumber]=numberValue;
//                }
//                indexOfNumber++;
//            }
            timeDelay ++;
            if (isButtonNumber() && !isDelButtonPressed())
            {
                if(indexOfNumber < 4){
                    LcdPrintStringS(1,indexOfNumber+12,"*");
                    arrayPassword[indexOfNumber] = numberValue;
                }
                indexOfNumber ++;
                timeDelay = 0;
            }
            if(isDelButtonPressed()){
                indexOfNumber = 0;
                timeDelay = 0;
                clear_screen(1);
            }
            if (isConfirmButtonPressed()){
//                checkPass = CheckPassword();
//                LcdPrintNumS(1,6, checkPass);
                statusSystem = CHECK_PASSWORD;
                clear_screen(2);
            }
            if (timeDelay >= 200){
                statusSystem = previousStatus;
                timeDelay = 0;
                indexOfNumber = 0;
            }
            break;
        case CHECK_PASSWORD:
            timeDelay = 0;
            for (index1 = 0; index1 < 5; index1++){
                for (index2 = 0; index2 <4 ; index2++){
                    if (arrayPassword[index2] != arrayMapOfPassword[index1][index2]){
                        result = 0;
                        break;
                    }
                }
                if (index2 == 4){
                    result = 1;
                    break;
                }
            }
            if (result){
                if(nextStatus == 0){
                    statusSystem  = INIT_SYSTEM;
                }
                else if(nextStatus == SET_TIME){
                    statusSystem = SET_TIME;
                }
                else if(nextStatus == SLOW_MODE){
                    statusSystem = SLOW_MODE;
                }
                else{
                    statusSystem = MANUAL_MODE;
                }
                password_flag = 1;
                indexOfNumber = 0;
            }
            else{
                statusSystem = WRONG_PASSWORD;
            }
            break;
        case WRONG_PASSWORD:
            timeDelay ++;
            clear_screen(2);
            LcdPrintStringS(0,0,"PASSWORD WRONG");
            LcdPrintStringS(1,0,"PRESS #");
            if (isConfirmButtonPressed())
            {
                indexOfNumber = 0;
                timeDelay = 0;
                statusSystem = ENTER_PASSWORD;
                clear_screen(2);
            }
            // con thieu dieu kien chuyen trang thai
            break;
        case INIT_SYSTEM:
            clear_screen(2);
            setLedPhase1();
            setLedPhase2();
            Init_flag();
            if (isSetTimeButtonPressed()) {
                statusSystem = SET_TIME;
            }
            if(isManualButtonPressed()){
                statusSystem = MANUAL_MODE;
                previousStatus = INIT_SYSTEM;
            }
            if(isSlowButtonPressed()){
                statusSystem = SLOW_MODE;
                previousStatus = INIT_SYSTEM;
            }
            if (isConfirmButtonPressed()) {
                statusSystem = START;
            }
            break;
        case SET_TIME:
            setLedPhase1();
            setLedPhase2();
            statusSystem = SET_PHASE1_GREEN;
            indexOfNumber = 0;
            clear_screen(2);
            break;
        case SET_PHASE1_GREEN:
            LcdPrintStringS(0,0,"PHASE1_GREEN:");
            timeDelay++;
            if (indexOfNumber==0 ) {
                clear_screen(1);
                LcdPrintStringS(1,0,"(10-90)");
                LcdPrintStringS(1,14,"__"); 
            }
            if (indexOfNumber==1) {
                clear_screen(1);
                LcdPrintStringS(1,0,"(10-90)");
                LcdPrintNumS(1,14,arrayInput[0]);
                LcdPrintStringS(1,15,"_");
            }
            if (isButtonNumber()) {
                int temp = indexOfNumber+1;
                if (temp<3) {
                    LcdPrintNumS(1,indexOfNumber+14,numberValue);
                arrayInput[indexOfNumber]=numberValue;
                }
                indexOfNumber++;
            }
            if(isDelButtonPressed()){
                indexOfNumber = 0;
                statusSystem = SET_PHASE1_GREEN;
                clear_screen(2);
            }
            if (isConfirmButtonPressed()) {
                if (indexOfNumber == 1) timeOfGreenPhase1 = 10;
                else timeOfGreenPhase1=arrayInput[0]*10 + arrayInput[1];
                if (timeOfGreenPhase1 > 90) timeOfGreenPhase1 = 90;
                setTimeOfGreenPhase1 = timeOfGreenPhase1;
                indexOfNumber = 0;
                statusSystem = SET_PHASE1_YELLOW;
                clear_screen(2);   
            }
            if(isSetTimeButtonPressed()){
                clear_screen(2);
                setLedPhase1();
                setLedPhase2();
                statusSystem = SET_TIME;
            }
            if(timeDelay > 1000){
                statusSystem = INIT_SYSTEM;
                timeDelay = 0;
            }
            break;
        case SET_PHASE1_YELLOW:
            LcdPrintStringS(0,0,"PHASE1_YELLOW:");
            timeDelay++;
            if (indexOfNumber==0) {
                clear_screen(1);
                LcdPrintStringS(1,0,"(1-9)");
                LcdPrintCharS(1,15,'_');
            }
            if (isButtonNumber()) {
                int temp = indexOfNumber+1;
                if (temp<2) {
                    LcdPrintNumS(1,indexOfNumber+15,numberValue);
                    arrayInput[indexOfNumber]=numberValue;
                } 
                indexOfNumber++;
                timeDelay=0;
            }
            if(isDelButtonPressed()){
                clear_screen(2);
                indexOfNumber = 0;
                statusSystem = SET_PHASE1_YELLOW;
            }
            if (isConfirmButtonPressed()) {
                clear_screen(2);
                indexOfNumber = 0;
                timeOfYellowPhase1 = arrayInput[0];
                setTimeOfYellowPhase1 = timeOfYellowPhase1;
                timeOfRedPhase2 = timeOfGreenPhase1+timeOfYellowPhase1;
                setTimeOfRedPhase2 = timeOfRedPhase2;
                statusSystem = SET_PHASE2_GREEN;
            }
            if(isSetTimeButtonPressed()){
                clear_screen(2);
                setLedPhase1();
                setLedPhase2();
                statusSystem = SET_TIME;
            }
            if(timeDelay > 1000){
                statusSystem = INIT_SYSTEM;
                timeDelay = 0;
            }
            break;
        case SET_PHASE2_GREEN:
            LcdPrintStringS(0,0,"PHASE2_GREEN:");
            timeDelay++;
            if (indexOfNumber==0) {
                clear_screen(1);
                LcdPrintStringS(1,0,"(10-90)");
                LcdPrintStringS(1,14,"__");
            }
            if (indexOfNumber==1) {
                clear_screen(1);
                LcdPrintStringS(1,0,"(10-90)");
                LcdPrintNumS(1,14,arrayInput[0]);
                LcdPrintStringS(1,15,"_");
            }
            if (isButtonNumber()) {
                int temp = indexOfNumber+1;
                if (temp<3) {
                    LcdPrintNumS(1,indexOfNumber+14,numberValue);
                    arrayInput[indexOfNumber]=numberValue;
                }
                
                indexOfNumber++;
            }
            if(isDelButtonPressed()){
                clear_screen(2);
                indexOfNumber = 0;
                statusSystem = SET_PHASE2_GREEN;
            }
            if (isConfirmButtonPressed()) {
                if(indexOfNumber == 1)  timeOfGreenPhase2 = 10;
                else timeOfGreenPhase2 = arrayInput[0]*10 + arrayInput[1];
                if(timeOfGreenPhase2 > 90) timeOfGreenPhase2 = 90;
                setTimeOfGreenPhase2 = timeOfGreenPhase2;
                statusSystem = SET_PHASE2_YELLOW;
                indexOfNumber=0;    
                clear_screen(2);              
            }
            if(isSetTimeButtonPressed()){
                clear_screen(2);
                setLedPhase1();
                setLedPhase2();
                statusSystem = SET_TIME;
            }
            if(timeDelay > 1000){
                statusSystem = INIT_SYSTEM;
                timeDelay = 0;
            }
            break;
        case SET_PHASE2_YELLOW:
            LcdPrintStringS(0,0,"PHASE2_YELLOW:");
            timeDelay++;
            if (indexOfNumber==0) {
                clear_screen(1);
                LcdPrintStringS(1,0,"(1-9)");
                LcdPrintCharS(1,15,'_');
            }
            if (isButtonNumber()) {
                int temp = indexOfNumber+1;
                if (temp<2) {
                    LcdPrintNumS(1,indexOfNumber+15,numberValue);
                arrayInput[indexOfNumber]=numberValue;
                }
                indexOfNumber++;
                timeDelay=0;
            }                
            if(isDelButtonPressed()){
                indexOfNumber = 0;
                statusSystem = SET_PHASE2_YELLOW;
                clear_screen(2);
            }
            if (isConfirmButtonPressed()) {
                clear_screen(2);
                indexOfNumber=0;
                timeOfYellowPhase2 = arrayInput[0];
                setTimeOfYellowPhase2 = timeOfYellowPhase2;
                timeOfRedPhase1 = timeOfGreenPhase2+timeOfYellowPhase2;
                setTimeOfRedPhase1 = timeOfRedPhase1;
                isSetTime = 1;
                statusSystem = INIT_SYSTEM;
            }
            if(isSetTimeButtonPressed()){
                clear_screen(2);
                setLedPhase1();
                setLedPhase2();
                statusSystem = SET_TIME;
            }
            if(timeDelay > 1000){
                statusSystem = INIT_SYSTEM;
                timeDelay = 0;
            }
            break; 
        case START:
            if (isSetTime==0) {
                clear_screen(2);
                LcdPrintStringS(0,0,"TIME NOT ALREADY");
                LcdPrintStringS(1,0,"PRESS #");
                if (isConfirmButtonPressed()) {
                    statusSystem = INIT_SYSTEM;
                }
            }
            else {
                password_flag = 0;
                statusSystem = GREEN1_RED2;
                indexOfNumber = 0;
            }
            break;
        case GREEN1_RED2:
            clear_screen(2);
            Phase1_GreenOn();
            Phase2_RedOn();
            timeOfPhase1 = timeOfGreenPhase1;
            timeOfPhase2 = timeOfRedPhase2;
            showLedPhase1();
            showLedPhase2();
            LcdPrintStringS(0,0,"PHASE1: GREEN");
            if (timeOfGreenPhase1>=10) {
                LcdPrintNumS(0,14,timeOfGreenPhase1);
            }
            else {
                LcdPrintNumS(0,15,timeOfGreenPhase1);
            }
            LcdPrintStringS(1,0,"PHASE2: RED");
            if (timeOfRedPhase2>=10) {
                LcdPrintNumS(1,14,timeOfRedPhase2);
            }
            else {
                LcdPrintNumS(1,15,timeOfRedPhase2);
            }
            if (set_flag) {
                timeOfGreenPhase1--;
                timeOfRedPhase2--;
                set_flag = 0;
            }
            if (isSetTimeButtonPressed()) {
                previousStatus = GREEN1_RED2;
                Phase1_GreenOff();
                Phase2_RedOff();
                clear_screen(2);
                statusSystem = ENTER_PASSWORD;
                nextStatus = SET_TIME;
            }
            if (isManualButtonPressed()) {
                previousStatus = GREEN1_RED2;
                setLedPhase1();
                setLedPhase2();
                Phase1_GreenOff();
                Phase2_RedOff();
                clear_screen(2);
                statusSystem = ENTER_PASSWORD;
                nextStatus = MANUAL_MODE;
                manualStatus = MANUAL_0;
            }
            if (isSlowButtonPressed() || ( 0 <= hour && hour <= 4) || hour == 23) {
                if(slowModeStatus != SLOW_I2C_EXIT){
                    previousStatus = GREEN1_RED2;
                    setLedPhase1();
                    setLedPhase2();
                    Phase1_RedOff();
                    Phase2_GreenOff();
                    clear_screen(2);
                    if(isSlowButtonPressed()){
                        statusSystem = ENTER_PASSWORD;
                        nextStatus = SLOW_MODE;
                    }
                    else{
                        statusSystem = SLOW_MODE;
                    }
                    slowModeStatus = SLOW_0;
                }
            }
            if(slowModeStatus == SLOW_I2C_EXIT && isDelButtonPressed()){
                previousStatus = GREEN1_RED2;
                setLedPhase1();
                setLedPhase2();
                Phase1_RedOff();
                Phase2_GreenOff();
                clear_screen(2);
                statusSystem = ENTER_PASSWORD;
                nextStatus = SLOW_MODE;
                slowModeStatus = SLOW_I2C;
            }
            if (isPedesButtonPressed1()){
                previousStatus = GREEN1_RED2;
                Phase1_GreenOff();
                Phase2_RedOff();               
                statusSystem = PEDESTRIAN;
                pedestrianStatus = PEDES_0;
            }
            if (timeOfGreenPhase1==0) {
                clear_screen(2);
                Phase1_GreenOff();
                statusSystem = YELLOW1_RED2;
            }
            break;
        case YELLOW1_RED2:
            clear_screen(2);
            Phase1_YellowOn();
            Phase2_RedOn();
            timeOfPhase1 = timeOfYellowPhase1;
            timeOfPhase2 = timeOfRedPhase2;
            showLedPhase1();
            showLedPhase2();
            LcdPrintStringS(0,0,"PHASE1: YELLOW");
            if (timeOfYellowPhase1>=10) {
                LcdPrintNumS(0,14,timeOfYellowPhase1);
            }
            else {
                LcdPrintNumS(0,15,timeOfYellowPhase1);
            }
            LcdPrintStringS(1,0,"PHASE2: RED");
            if (timeOfRedPhase2>=10) {
                LcdPrintNumS(1,14,timeOfRedPhase2);
            }
            else {
                LcdPrintNumS(1,15,timeOfRedPhase2);
            }
            
            if (set_flag) {
                timeOfYellowPhase1--;
                timeOfRedPhase2--;
                set_flag = 0;
            }
            if (isSetTimeButtonPressed()) {
                previousStatus = YELLOW1_RED2;
                Phase1_YellowOff();
                Phase2_RedOff();
                clear_screen(2);
                statusSystem = ENTER_PASSWORD;
                nextStatus = SET_TIME;
            }
            if (isManualButtonPressed()) {
                previousStatus = YELLOW1_RED2;
                setLedPhase1();
                setLedPhase2();
                Phase1_YellowOff();
                Phase2_RedOff();
                clear_screen(2);
                statusSystem = ENTER_PASSWORD;
                nextStatus = MANUAL_MODE;
                manualStatus = MANUAL_0;
            }
            if (isSlowButtonPressed() || ( 0 <= hour && hour <= 4) || hour == 23) {
                if(slowModeStatus != SLOW_I2C_EXIT){
                    previousStatus = YELLOW1_RED2;
                    setLedPhase1();
                    setLedPhase2();
                    Phase1_RedOff();
                    Phase2_GreenOff();
                    clear_screen(2);
                    if(isSlowButtonPressed()){
                        statusSystem = ENTER_PASSWORD;
                        nextStatus = SLOW_MODE;
                    }
                    else{
                        statusSystem = SLOW_MODE;
                    }
                    nextStatus = SLOW_MODE;
                    slowModeStatus = SLOW_0;
                }
            }
            if(slowModeStatus == SLOW_I2C_EXIT && isDelButtonPressed()){
                previousStatus = YELLOW1_RED2;
                setLedPhase1();
                setLedPhase2();
                Phase1_RedOff();
                Phase2_GreenOff();
                clear_screen(2);
                statusSystem = ENTER_PASSWORD;
                nextStatus = SLOW_MODE;
                slowModeStatus = SLOW_I2C;
            }
            if (timeOfYellowPhase1 == 0 || timeOfRedPhase2==0) {
                clear_screen(2);
                timeOfGreenPhase1 = setTimeOfGreenPhase1;
                timeOfYellowPhase1 = setTimeOfYellowPhase1;
                timeOfRedPhase2 = setTimeOfRedPhase2;
                Phase1_YellowOff();
                Phase2_RedOff();
                statusSystem = RED1_GREEN2;
            }
            break;
        case RED1_GREEN2:
            clear_screen(2);
            Phase1_RedOn();
            Phase2_GreenOn();
            timeOfPhase1 = timeOfRedPhase1;
            timeOfPhase2 = timeOfGreenPhase2;
            showLedPhase1();
            showLedPhase2();
            LcdPrintStringS(0,0,"PHASE1: RED");
            if (timeOfRedPhase1>=10) {
                LcdPrintNumS(0,14,timeOfRedPhase1);
            }
            else {
                LcdPrintNumS(0,15,timeOfRedPhase1);
            }
            LcdPrintStringS(1,0,"PHASE2: GREEN");
            if (timeOfGreenPhase2>=10) {
                LcdPrintNumS(1,14,timeOfGreenPhase2);
            }
            else {
                LcdPrintNumS(1,15,timeOfGreenPhase2);
            }
            if (set_flag) {
                timeOfRedPhase1--;
                timeOfGreenPhase2--;
                set_flag = 0;
            }
            if (isSetTimeButtonPressed()) {
                timeOfPhase1 = timeOfPhase2 = 0;
                Phase1_RedOff();
                Phase2_GreenOff();
                clear_screen(2);
                statusSystem = ENTER_PASSWORD;
                nextStatus = SET_TIME;
            }
            if (isManualButtonPressed()) {
                previousStatus = RED1_GREEN2;
                setLedPhase1();
                setLedPhase2();
                Phase1_RedOff();
                Phase2_GreenOff();
                clear_screen(2);
                statusSystem = ENTER_PASSWORD;
                nextStatus = MANUAL_MODE;
                manualStatus = MANUAL_0;
            }
            
            if (isSlowButtonPressed() || ( 0 <= hour && hour <= 4) || hour == 23) {
                if(slowModeStatus != SLOW_I2C_EXIT){
                    previousStatus = RED1_GREEN2;
                    setLedPhase1();
                    setLedPhase2();
                    Phase1_RedOff();
                    Phase2_GreenOff();
                    clear_screen(2);
                    if(isSlowButtonPressed()){
                        statusSystem = ENTER_PASSWORD;
                        nextStatus = SLOW_MODE;
                    }
                    else{
                        statusSystem = SLOW_MODE;
                    }
                    nextStatus = SLOW_MODE;
                    slowModeStatus = SLOW_0;
                }
            }
            if(slowModeStatus == SLOW_I2C_EXIT && isDelButtonPressed()){
                previousStatus = RED1_GREEN2;
                setLedPhase1();
                setLedPhase2();
                Phase1_RedOff();
                Phase2_GreenOff();
                clear_screen(2);
                statusSystem = ENTER_PASSWORD;
                nextStatus = SLOW_MODE;
                slowModeStatus = SLOW_I2C;
            }
            if (isPedesButtonPressed2()){
                previousStatus = RED1_GREEN2;
                Phase2_GreenOff();
                Phase1_RedOff();               
                statusSystem = PEDESTRIAN;
                pedestrianStatus = PEDES_0;
            }
            if (timeOfGreenPhase2==0) {
                clear_screen(2);
                Phase2_GreenOff();
                statusSystem = RED1_YELLOW2;
            }
            break;
        case RED1_YELLOW2:
            clear_screen(2);
            Phase1_RedOn();
            Phase2_YellowOn();
            timeOfPhase1 = timeOfRedPhase1;
            timeOfPhase2 = timeOfYellowPhase2;
            showLedPhase1();
            showLedPhase2();
            LcdPrintStringS(0,0,"PHASE1: RED");
            if (timeOfRedPhase1>=10) {
                LcdPrintNumS(0,14,timeOfRedPhase1);
            }
            else {
                LcdPrintNumS(0,15,timeOfRedPhase1);
            }
            LcdPrintStringS(1,0,"PHASE2: YELLOW");
            if (timeOfYellowPhase2>=10) {
                LcdPrintNumS(1,14,timeOfYellowPhase2);
            }
            else {
                LcdPrintNumS(1,15,timeOfYellowPhase2);
            }
            if (set_flag) {
                timeOfRedPhase1--;
                timeOfYellowPhase2--;
                set_flag = 0;
            }
            if (isSlowButtonPressed() || ( 0 <= hour && hour <= 4) || hour == 23) {
                if(slowModeStatus != SLOW_I2C_EXIT){
                    previousStatus = RED1_YELLOW2;
                    setLedPhase1();
                    setLedPhase2();
                    Phase1_RedOff();
                    Phase2_GreenOff();
                    clear_screen(2);
                    if(isSlowButtonPressed()){
                        statusSystem = ENTER_PASSWORD;
                        nextStatus = SLOW_MODE;
                    }
                    else{
                        statusSystem = SLOW_MODE;
                    }
                    nextStatus = SLOW_MODE;
                    slowModeStatus = SLOW_0;
                }
            }
            if(slowModeStatus == SLOW_I2C_EXIT && isDelButtonPressed()){
                previousStatus = RED1_YELLOW2;
                setLedPhase1();
                setLedPhase2();
                Phase1_RedOff();
                Phase2_GreenOff();
                clear_screen(2);
                statusSystem = ENTER_PASSWORD;
                nextStatus = SLOW_MODE;
                slowModeStatus = SLOW_I2C;
            }
            if (isSetTimeButtonPressed()) {
                timeOfPhase1 = timeOfPhase2 = 0;
                Phase1_RedOff();
                Phase2_YellowOff();
                clear_screen(2);
                statusSystem = ENTER_PASSWORD;
                nextStatus = SET_TIME;
            }
            if (isManualButtonPressed()) {
                previousStatus = RED1_YELLOW2;
                setLedPhase1();
                setLedPhase2();
                Phase1_RedOff();
                Phase2_YellowOff();
                clear_screen(2);
                statusSystem = ENTER_PASSWORD;
                nextStatus = MANUAL_MODE;
                manualStatus = MANUAL_0;
            }
            if (timeOfYellowPhase2 == 0 || timeOfRedPhase1==0) {
                clear_screen(2);
                timeOfGreenPhase2 = setTimeOfGreenPhase2;
                timeOfYellowPhase2 = setTimeOfYellowPhase2;
                timeOfRedPhase1 = setTimeOfRedPhase1;
                Phase1_RedOff();
                Phase2_YellowOff();
                statusSystem = START;
            }
            break;
        case SLOW_MODE:
            clear_screen(2);
            showLedPhase1();
            showLedPhase2();
//            Phase1_GreenOff();
//            Phase1_RedOff();
//            Phase2_GreenOff();
//            Phase2_RedOff();
            LcdPrintStringS(0,3,"SLOW DOWN");
            DisplayTime();
            if(slowModeStatus == SLOW_0){
                if(( 0 <= hour && hour <= 4) || hour == 23){
                    slowModeStatus = SLOW_I2C;
                }
                else{
                    slowModeStatus = SLOW_BUTTON;
                }
            }
            if (set_flag) {
                if(slowCnt%2 == 0){
                    Phase1_YellowOff();
                    Phase2_YellowOn();
                    slowCnt = 1;
                }
                else{                    
                    Phase2_YellowOff();
                    Phase1_YellowOn();
                    slowCnt = 0;
                }
                set_flag = 0;
            }
            if(isSetTimeButtonPressed()){
                Phase1_YellowOff();
                Phase2_YellowOff();
                statusSystem = SET_TIME;
                if(slowModeStatus == SLOW_I2C){
                    slowModeStatus = SLOW_I2C_EXIT;
                }
                else{
                    slowModeStatus = SLOW_0;
                }
            }
            if (isConfirmButtonPressed()) {
                Phase1_YellowOff();
                Phase2_YellowOff();
                statusSystem = previousStatus;
                timeOfPhase1 = pretimeOfPhase1;
                timeOfPhase2 = pretimeOfPhase2;
                if(slowModeStatus == SLOW_I2C){
                    slowModeStatus = SLOW_I2C_EXIT;
                }
                else{
                    slowModeStatus = SLOW_0;
                }
                if(statusSystem != INIT_SYSTEM){
                    password_flag = 0;                    
                }
            }
            break;
        case MANUAL_MODE:
            clear_screen(2);
            showLedPhase1();
            showLedPhase2();
            if (manualStatus == MANUAL_0) {
                if(previousStatus == RED1_GREEN2){
                    manualStatus = MANUAL_3;
                }
                else if(previousStatus == RED1_YELLOW2){
                    manualStatus = MANUAL_4;
                }
                else if(previousStatus == GREEN1_RED2 || previousStatus == INIT_SYSTEM){
                    manualStatus = MANUAL_1;
                }
                else if(previousStatus == YELLOW1_RED2){
                    manualStatus = MANUAL_2;
                }
            }
            if(manualStatus == MANUAL_1){            
                LcdPrintStringS(0,0,"PHASE1: GREEN");
                LcdPrintStringS(1,0,"PHASE2: RED");
                Phase1_GreenOn();
                Phase2_RedOn();
                if (isManualButtonPressed()) {
                    Phase1_GreenOff();
                    manualStatus = MANUAL_2;
                }
            }
            else if (manualStatus == MANUAL_2){             
                LcdPrintStringS(0,0,"PHASE1: YELLOW");
                LcdPrintStringS(1,0,"PHASE2: RED");
                Phase1_YellowOn();
                Phase2_RedOn();
                if (isManualButtonPressed()) {
                    Phase1_YellowOff();
                    Phase2_RedOff();
                    manualStatus = MANUAL_3;
                }
            }
            else if (manualStatus == MANUAL_3){             
                LcdPrintStringS(0,0,"PHASE1: RED");
                LcdPrintStringS(1,0,"PHASE2: GREEN");
                Phase1_RedOn();
                Phase2_GreenOn();
                if (isManualButtonPressed()) {
                    Phase1_RedOff();
                    Phase2_GreenOff();
                    manualStatus = MANUAL_4;
                }
            }
            else {                 
                LcdPrintStringS(0,0,"PHASE1: RED");               
                LcdPrintStringS(1,0,"PHASE2: YELLOW");
                Phase2_YellowOn();
                Phase1_RedOn();
                if (isManualButtonPressed()) {
                    Phase2_YellowOff();
                    Phase1_RedOff();
                    manualStatus = MANUAL_1;
                }
            }
            if (isConfirmButtonPressed()) {
                Phase1_GreenOff();
                Phase1_RedOff();
                Phase1_YellowOff();
                Phase2_GreenOff();
                Phase2_RedOff();
                Phase2_YellowOff();
                manualStatus = MANUAL_0;
                statusSystem = previousStatus;
                if(statusSystem != INIT_SYSTEM){
                    password_flag = 0;                    
                }
            }
            break;
        case PEDESTRIAN:
            clear_screen(2);
            LcdPrintStringS(0,0,"PEDESTRIAN MODE");
            if(pedestrianStatus == PEDES_0){
                if(previousStatus == RED1_GREEN2){
                    pedestrianStatus = PEDES_4;
                    timeOfYellowPhase2 = 10;
                }
                else if(previousStatus == GREEN1_RED2){
                    pedestrianStatus = PEDES_1;
                    timeOfYellowPhase1 = 10;
                }
            }
            if (pedestrianStatus == PEDES_1){
                Phase1_YellowOn();
                Phase2_RedOn();
                timeOfPhase1 = timeOfYellowPhase1;
                timeOfPhase2 = timeOfYellowPhase1;
                showLedPhase1();
                showLedPhase2();
                if (set_flag) {
                    timeOfYellowPhase1--;
                    set_flag=0; 
                }
                if (timeOfYellowPhase1==0) {
                    Phase1_YellowOff();
                    Phase2_RedOff();
                    timeOfYellowPhase1 = setTimeOfYellowPhase1;
                    pedestrianStatus = PEDES_2;
                }
            }
            else if (pedestrianStatus == PEDES_2){
                Phase1_RedOn();
                Phase2_GreenOn();
                timeOfPhase1 = timeOfRedPhase1;
                timeOfPhase2 = timeOfGreenPhase2;
                showLedPhase1();
                showLedPhase2();
                if (set_flag==1) {
                    timeOfRedPhase1--;
                    timeOfGreenPhase2--;
                    set_flag=0;
                }
                if (timeOfGreenPhase2==0) {
                    Phase2_GreenOff();
                    pedestrianStatus = PEDES_3;
                    timeOfGreenPhase2 = setTimeOfGreenPhase2;
                }
            }
            else if(pedestrianStatus == PEDES_3){
                Phase1_RedOn();
                Phase2_YellowOn();
                timeOfPhase1 = timeOfRedPhase1;
                timeOfPhase2 = timeOfYellowPhase2;
                showLedPhase1();
                showLedPhase2();
                if (set_flag==1) {
                    timeOfRedPhase1--;
                    timeOfYellowPhase2--;
                    set_flag=0;
                }
                if (timeOfYellowPhase2==0 || timeOfRedPhase1 == 0) {
                    Phase2_YellowOff();
                    Phase1_RedOff();
                    pedestrianStatus = PEDES_0;
                    timeOfYellowPhase2 = setTimeOfYellowPhase2;
                    timeOfRedPhase1 = setTimeOfRedPhase1;
                    timeOfRedPhase2 = setTimeOfRedPhase2;
                    timeOfGreenPhase1 = setTimeOfGreenPhase1;
                    statusSystem = GREEN1_RED2;
                }                
            }
            if (pedestrianStatus == PEDES_4){
                Phase2_YellowOn();
                Phase1_RedOn();
                timeOfPhase2 = timeOfYellowPhase2;
                timeOfPhase1 = timeOfYellowPhase2;
                showLedPhase1();
                showLedPhase2();
                if (set_flag==1) {
                    timeOfYellowPhase2--;
                    set_flag=0;
                }
                if (timeOfYellowPhase2==0) {
                    Phase2_YellowOff();
                    Phase1_RedOff();
                    timeOfYellowPhase2 = setTimeOfYellowPhase2;
                    pedestrianStatus = PEDES_5;
                }
            }
            else if (pedestrianStatus == PEDES_5){
                Phase2_RedOn();
                Phase1_GreenOn();
                timeOfPhase2 = timeOfRedPhase2;
                timeOfPhase1 = timeOfGreenPhase1;
                showLedPhase1();
                showLedPhase2();
                if (set_flag==1) {
                    timeOfRedPhase2--;
                    timeOfGreenPhase1--;
                    set_flag=0;
                }
                if (timeOfGreenPhase1==0) {
                    Phase1_GreenOff();
                    pedestrianStatus = PEDES_6;
                    timeOfGreenPhase1 = setTimeOfGreenPhase1;
                }
            }
            else if (pedestrianStatus == PEDES_6){
                Phase2_RedOn();
                Phase1_YellowOn();
                timeOfPhase2 = timeOfRedPhase2;
                timeOfPhase1 = timeOfYellowPhase1;
                showLedPhase1();
                showLedPhase2();
                if (set_flag==1) {
                    timeOfRedPhase2--;
                    timeOfYellowPhase1--;
                    set_flag=0;
                }
                if (timeOfRedPhase2 == 0 ||timeOfYellowPhase1 == 0) {
                    Phase2_RedOff();
                    Phase1_YellowOff();
                    pedestrianStatus = PEDES_0;
                    timeOfRedPhase2 = setTimeOfRedPhase2;
                    timeOfYellowPhase1 = setTimeOfYellowPhase1;
                    timeOfRedPhase1 = setTimeOfRedPhase1;
                    timeOfGreenPhase2 = setTimeOfGreenPhase2;
                    statusSystem = RED1_GREEN2;
                }
            }
            break;
        default:
            break;                   
    }
}