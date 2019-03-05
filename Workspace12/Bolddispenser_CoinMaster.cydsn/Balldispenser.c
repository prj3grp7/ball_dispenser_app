#include "Balldispenser.h"

#define NUMBER_OF_BALLS 2

static uint8 ball_count;
static uint16 V_Sample;

/*******************************************************************************
* Function Name: initBallDispenser
********************************************************************************
*
* Summary:     
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void initBallDispenser()
{
    UART_PutString("Ball Dispenser INIT\r\n");
    PWM_1_Start();
    Sample_Hold_1_Start();
    ADC_DelSig_1_Start();
    countBalls();
}

void DispenseBalls()
{
    uint8 count = 0;
    while(count++<(NUMBER_OF_BALLS))
    {
    UART_PutString("Ball Dispensing\r\n");
    Rotate360();
    UART_PutString("Ball Dispensed\r\n");
    }
}

int countBalls()
{
    ADC_DelSig_1_StartConvert();
    V_Sample = ADC_DelSig_1_GetResult16();
    if(V_Sample>1 && V_Sample<400)
    {
        ball_count = 4;
    }
    else if(V_Sample>30000 && V_Sample<40000)
    {
        ball_count = 3;
    }
    else if(V_Sample>15000 && V_Sample<30000)
    {
        ball_count = 2;
    }
    else if(V_Sample>1000 && V_Sample<15000)
    {
        ball_count = 1;
        //dispenserEmpty();
    }
    else
    {
        
    }
        UpdateStatusLEDS();
        return ball_count;
}

void UpdateStatusLEDS()
{
    if(ball_count==4){
        pin_full_Write(1); 
        pin_empty_Write(0);
    }
    else if(ball_count==3)
    {
        pin_full_Write(0); 
        pin_empty_Write(0);
    }
     else if(ball_count<3)
    {
        pin_full_Write(0); 
        pin_empty_Write(1);
    }
    
}