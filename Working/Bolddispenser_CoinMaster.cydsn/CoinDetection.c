#include "CoinDetection.h"
#define ISRENABLEDELAY 50

bool dispencerEnabled = true;

/*******************************************************************************
* Function Name: handleCoinDetection
********************************************************************************
*
* Summary:    This function is called from the detection handeler
*             It sends a message to the game controller that a coin has been
*             detected then checks if the dispencer is enabled and calls the
              appropriate function. Finnaly it reenables the detection ISR to 
              make the system ready for a new coin.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void handleCoinDetection()
{
    UART_PutString("Coin Detected\r\n");

    if(dispencerEnabled)
    {
        dispenserStatus();
        coinInserted();
        acceptCoin();
        if(countBalls() <= 2)
            disableDispenser();
        //DispenseBalls();
    }
    else
    {
        rejectCoin();
    }
    CyDelay(ISRENABLEDELAY);
    isr_detection_Enable();
    isr_detection_ClearPending();
    CyDelay(ISRENABLEDELAY);
};

/*******************************************************************************
* Function Name: initCoinDetector
********************************************************************************
*
* Summary:    This function initialises the detection ISR.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void initCoinDetector()
{
    isr_detection_StartEx(ISR_detection_handler);
};



/*******************************************************************************
* Function Name: CY_ISR
********************************************************************************
*
* Summary:    This function is the default ISR handeler for the detection ISR.
              It disables the ISR to prevent multiple coin detections then calls
              the handleCoinDetection function. 
*
* Parameters:
*  ISR_detection_handler spesifies which interrupt to handle
*
*******************************************************************************/
CY_ISR(ISR_detection_handler)
{
    isr_detection_Disable();
    UART_PutString("DetectionISR\r\n");
    handleCoinDetection();
}



/*******************************************************************************
* Function Name: rejectCoin
********************************************************************************
*
* Summary:    This function is responcible for coin rejection, it calles the 
              motor control functions required to reject a coin from the system.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void rejectCoin()
{
    Rotate90();
    revRotate90();
};



/*******************************************************************************
* Function Name: acceptCoin
********************************************************************************
*
* Summary:    This function is responcible for accepting a coin into the system, 
              it calles the motor control functions required to accept a coin
              then reenables the detection ISR to make the system ready for a 
              new coin.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void acceptCoin()
{
    revRotate90();
    Rotate90();
};



/*******************************************************************************
* Function Name: disableDispencer
********************************************************************************
*
* Summary:    This function disables the dispenser, this function is called from
              the I2C handler when it recives a message from the game controller 
              that the game is active.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void disableDispenser()
{
    dispencerEnabled = false;
    UART_PutString("Coinmaster 2000 disabled\r\n");
};



/*******************************************************************************
* Function Name: enableDispencer
********************************************************************************
*
* Summary:    This function enables the dispenser, this function is called from
              the I2C handler when it recives a message from the game controller 
              that the game is idle.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void enableDispenser()
{
    dispencerEnabled = true;
    UART_PutString("Coinmaster 2000 enabled\r\n");
};



/*******************************************************************************
* Function Name: resetDetectorISR
********************************************************************************
*
* Summary:    Debugging function used to reenable the detection ISR.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void resetDetectorISR()
{
    isr_detection_Enable();
    UART_PutString("Interupt Reset\r\n");
};

