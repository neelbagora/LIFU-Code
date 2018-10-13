#include "System.h"

System::System(void)
{
}

//Connection Status Indicator
void System::connected(void)
{
    DigitalOut led1(LED1);
    DigitalOut led3(LED3);
    led1 = 1;
    led3 = 0;
};

//Disconnection Status Indicator
void System::disconnected(void)
{
    DigitalOut led1(LED1);
    DigitalOut led3(LED3);
    led1 = 0;
    led3 = 1;
};
