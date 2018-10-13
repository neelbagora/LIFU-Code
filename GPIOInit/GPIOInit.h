#ifndef GPIOINIT_H
#define GPIOINIT_H

#include "mbed.h"

class GPIOInit 
{
public:
    /* CONSTRUCTOR GPIOInit
     * Initializes GPIOInit constructor, controls hardware
     *
     * Input: void
     * Output: void
     */
    GPIOInit();
    
    /* FUNCTION MX_GPIO_Init
     * Initialize GPIO Pins
     *
     * TODO: add TIM8 CH1 N GPIO Initialization and 4 GPIOS for LEDs, 4 GPIOs 
     * for Debugging.
     *
     * Input: TODO
     * Output: TODO
     */
    void MX_GPIO_Init(void);
    
    /* FUNCTION MX_GPIO_Init
     * DeInitializes GPIO Pins, do not use HAL_DeInit(). 
     * Deinitialization is for signal cutoff
     *
     * Input: void
     * Output: void
     */
    void MX_GPIO_DeInit(void);
};
#endif
