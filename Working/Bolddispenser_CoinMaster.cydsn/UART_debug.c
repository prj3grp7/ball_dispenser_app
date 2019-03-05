#include "UART_debug.h"

void handleCommand(char cmd)
{
    switch(cmd)
    {
        
        case '1' :
        {
            DispenseBalls(1);
        }
            break;
        
        case '2' :
        {
            DispenseBalls(2);
        }
            break;
        
        case 'r' :
        {
            rejectCoin();
        }
            break;

        case 'a' :
        {
            acceptCoin();
        }
            break;

        case 'l' :
        {
            resetDetectorISR();
        }
            break;
        case 't' :
        {
            SendToRPi(0x1E);
        }
            break;
        case 'y' :
        {
            SendToRPi(0x1f);
        }
            break;
        case 'u' :
        {
            SendToRPi(0x20);
        }
            break;

        default :
        {
            // nothing
        }
            break;
    }
};

void handleUART()
{
    char cmdchar = UART_GetChar();
    if (cmdchar)
    {
        UART_PutChar(cmdchar); // echo back
        UART_PutString("\r\n");
        handleCommand(cmdchar);
    }
};

CY_ISR(ISR_UART_rx_handler)
        {
                handleUART();
        }

void initUART()
{
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    UART_Start();
    UART_PutString("Coinmaster 2000 ready for service\r\n");
    UART_PutString("r: Reject Coin\r\n");
    UART_PutString("a: Accept Coin\r\n");
    UART_PutString("R: Reset Detector ISR");
};
