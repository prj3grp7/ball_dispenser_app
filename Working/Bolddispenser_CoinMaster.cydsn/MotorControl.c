#include "MotorControl.h"

#define STEPSLEEP 5

int stepCount = 0;
int steppingMode = 0;
bool readyForNextStep = false;
int nextStep = 0;

int stepCount2 = 0;
int steppingMode2 = 0;
bool readyForNextStep2 = false;
int nextStep2 = 0;


/*******************************************************************************
* Function Name: initMotorControl
********************************************************************************
*
* Summary:    This function initialises the timer that is used to control the 
              motor speed. It also i initialises the interrupt receved from 
              said timer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void initMotorControl()
{
    Motor_Timer_Start();
    isr_timer_StartEx(Motor_Timer_I_handler);
    isr_timer_Enable();
};



/*******************************************************************************
* Function Name: CY_ISR
********************************************************************************
*
* Summary:    This function is the default ISR handeler for the timer ISR.
              It sets the readyForNextStep boolian to true which allows the 
              motor to take the next step.
*
* Parameters:
*  ISR_detection_handler spesifies which interrupt to handle
*
*******************************************************************************/
CY_ISR(Motor_Timer_I_handler)
{
    readyForNextStep = true;
    readyForNextStep2 = true;
}

        

/*******************************************************************************
* Function Name: step
********************************************************************************
*
* Summary:    This function is the main control function for the motor.
              It uses a control register to control a stepper motor in the full 
              drive mode. The motor can run in both directions depending on the 
              input.
              It reads the nextStep variable then goes to that part of the
              switch and sets the control register to the appropriate state then 
              changes the nextStep to the next appropriate step.
*
* Parameters:
*     mode:   Controls the motors direction.
*
* Return:
*  None.
*
*******************************************************************************/
void step(int mode)
{

    switch (nextStep)
    {
        case 0 :
        {
            Motor_Reg_1_Write(0b0011);
            if(mode == -1)
            {
                nextStep = 3;
            }
            else
            {
                nextStep += mode;
            }
        }
            break;
        case 1 :
        {
            Motor_Reg_1_Write(0b0110);
            nextStep += mode;
        }
            break;
        case 2 :
        {
            Motor_Reg_1_Write(0b1100);
            nextStep += mode;
        }
            break;
        case 3 :
        {
            Motor_Reg_1_Write(0b1001);
            if(mode == 1)
            {
                nextStep = 0;
            }
            else
            {
                nextStep += mode;
            }
        }
            break;
    }
}



/*******************************************************************************
* Function Name: rotate90
********************************************************************************
*
* Summary:    This function makes the motor rotate 90 clockwise degrees.
              It waits for the readyForNextStep to become true then calls the 
              step function in forward mode. It then sets the readyForNextStep 
              to not true and loops again.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Rotate90()
{
    UART_PutString("Forward\r\n");
    int x = 0;
    while(x < 512)
    {
        while(!readyForNextStep)
        {
        };
        step(Forward);
        CyDelay(STEPSLEEP);
        //UART_PutString("Step\r\n");
        readyForNextStep = false;
        x++;
    }
};



/*******************************************************************************
* Function Name: Rotate180
********************************************************************************
*
* Summary:    This function totates the motor 180 clockwise degrees and works 
              the same way as rotate90
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Rotate180()
{
    int x = 0;
    while(x < 1024)
    {
        while(!readyForNextStep)
        {
        };
        step(Forward);
        CyDelay(STEPSLEEP);
        //UART_PutString("Step\r\n");
        readyForNextStep = false;
        x++;
    }
};



/*******************************************************************************
* Function Name: revRotate90
********************************************************************************
*
* Summary:    This function totates the motor 90 counter clockwise degrees and works 
              the same way as rotate90
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void revRotate90()
{
    int x = 0;
    UART_PutString("Rev\r\n");
    while(x < 512)
    {
        while(!readyForNextStep)
        {
        };
        step(Backward);
        CyDelay(STEPSLEEP);
        //UART_PutString("Step\r\n");
        readyForNextStep = false;
        x++;
    }
};



/*******************************************************************************
* Function Name: revRotate180
********************************************************************************
*
* Summary:    This function totates the motor 180 counter clockwise degrees and works 
              the same way as rotate90
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void revRotate180()
{
    int x = 0;
    while(x < 1024)
    {
        while(!readyForNextStep)
        {
        };
        step(Backward);
        CyDelay(STEPSLEEP);
        //UART_PutString("Step\r\n");
        readyForNextStep = false;
        x++;
    }
};

//----------------------------------------------------------------//


void step2(int mode)
{

    switch (nextStep2)
    {
        case 0 :
        {
            Motor_Reg_2_Write(0b0011);
            if(mode == -1)
            {
                nextStep2 = 3;
            }
            else
            {
                nextStep2 += mode;
            }
        }
            break;
        case 1 :
        {
            Motor_Reg_2_Write(0b0110);
            nextStep2 += mode;
        }
            break;
        case 2 :
        {
            Motor_Reg_2_Write(0b1100);
            nextStep += mode;
        }
            break;
        case 3 :
        {
            Motor_Reg_2_Write(0b1001);
            if(mode == 1)
            {
                nextStep2 = 0;
            }
            else
            {
                nextStep2 += mode;
            }
        }
            break;
    }
}


void Rotate902()
{
    int x = 0;
    while(x < 512)
    {
        while(!readyForNextStep2)
        {
        };
        step2(Forward);
        CyDelay(STEPSLEEP);
        //UART_PutString("Step\r\n");
        readyForNextStep2 = false;
        x++;
    }
};

void Rotate1802()
{
    int x = 0;
    while(x < 1024)
    {
        while(!readyForNextStep2)
        {
        };
        step2(Forward);
        CyDelay(STEPSLEEP);
        //UART_PutString("Step\r\n");
        readyForNextStep2 = false;
        x++;
    }
};



/*******************************************************************************
* Function Name: revRotate90
********************************************************************************
*
* Summary:    This function totates the motor 90 counter clockwise degrees and works 
              the same way as rotate90
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void revRotate902()
{
    int x = 0;
    while(x < 512)
    {
        while(!readyForNextStep2)
        {
        };
        step2(Backward);
        CyDelay(STEPSLEEP);
        //UART_PutString("Step\r\n");
        readyForNextStep2 = false;
        x++;
    }
    UART_PutString("Rev\r\n");
};


void revRotate1802()
{
    int x = 0;
    while(x < 1024)
    {
        while(!readyForNextStep2)
        {
        };
        step2(Backward);
        CyDelay(STEPSLEEP);
        //UART_PutString("Step\r\n");
        readyForNextStep2 = false;
        x++;
    }
};


/* [] END OF FILE */

