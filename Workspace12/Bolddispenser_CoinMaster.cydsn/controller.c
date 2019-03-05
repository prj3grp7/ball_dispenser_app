#include "controller.h"

#define DISPENSE_OFF 0x15
#define DISPENSE_ON 0x14
#define COIN_DETECTED 0x1E
#define DISPENSER_EMPTY 0x1F
#define DISPENSER_NOT_EMPTY 0x20

int n;



uint8_t readBuffer[256];
uint8_t writeBuffer[256];




/*******************************************************************************
* Function Name: RPI_IF_init
********************************************************************************
*
* Summary:    This function initialises the I2C communication between the PSoC
              and the GameController
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void initI2C()
{
    I2C_Start();
    I2C_EnableInt();
    
    I2C_SlaveInitReadBuf((uint8_t*)readBuffer,255);
    I2C_SlaveInitWriteBuf((uint8_t*)writeBuffer,255);
    
    resetReadBuffer();

}



/*******************************************************************************
* Function Name: resetReadBuffer
********************************************************************************
*
* Summary:    This function clears the I2C readbuffer during initialisation
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void resetReadBuffer()
{
    for(int i = 0; i < 255; i++)
    {
        readBuffer[i] = 0xFF;
    }
 
}



/*******************************************************************************
* Function Name: coinInserted()
********************************************************************************
*
* Summary:    This function is called when the system detects that a coin has
*             entered the system. It then calls the appropriate functions to 
*             handle the coin itself as well as dispense balls and message the
*             RPi.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void coinInserted()
{
    handleCoinDetection();
    if(countBalls() <= 2)
        {
            disableDispenser();
            sendDispenserStatus();
        }
    sendCoinDetected();
    DispenseBalls();
    resetDetectionISR();
}



/*******************************************************************************
* Function Name: dispenserStatus
********************************************************************************
*
* Summary:    Sends the coin detected message to the RPi.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void sendCoinDetected()
{
    SendToRPi(COIN_DETECTED); 
}



/*******************************************************************************
* Function Name: dispenserStatus
********************************************************************************
*
* Summary:    Sends the current ballDispenser status to the RPi.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void sendDispenserStatus()
{
    if(countBalls() == 4)
    {
        SendToRPi(DISPENSER_NOT_EMPTY);
    }
    else if(countBalls() < 2)
    {
        SendToRPi(DISPENSER_EMPTY);
    }
}



/*******************************************************************************
* Function Name: SendToRPi
********************************************************************************
*
* Summary:    This function sends a message to the Rpi using the I2C protocol.
*
* Parameters:
*             uint8_t message: The message to be sendt to the Rpi.
*
* Return:
*  None.
*
*******************************************************************************/
void SendToRPi(uint8_t message)
{
    resetReadBuffer();
    readBuffer[0] = message;
    I2C_SlaveClearReadBuf();
    CyDelay(1);
    Interrupt_Write(0);
    CyDelay(15);
    Interrupt_Write(1);
}



/*******************************************************************************
* Function Name: handleI2CData
********************************************************************************
*
* Summary:    This function reads the write buffer and calls the correct 
              function depending on the contents of the buffer
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void handleI2CData()
{
    if(I2C_SlaveClearWriteStatus() & I2C_SSTAT_WR_CMPLT)
    {
        
        int writeSize = I2C_SlaveGetWriteBufSize();
        for(int i = 0; i < writeSize; i++)
        {
            switch (writeBuffer[i])
            {
                case DISPENSE_ON:{
                    UART_PutString("Enable\r\n");
                    enableDispenser();
                    break;}
                case DISPENSE_OFF:{
                    UART_PutString("Disable\r\n");
                    disableDispenser();
                    break;} 
            }
        }
    }
}
