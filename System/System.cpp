#include "System.h"

System::System(void)
{
}

void System::connected(void)
{
    DigitalOut led1(LED1);
    DigitalOut led3(LED3);
    led1 = 1;
    led3 = 0;
};

void System::disconnected(void)
{
    DigitalOut led1(LED1);
    DigitalOut led3(LED3);
    led1 = 0;
    led3 = 1;
};
