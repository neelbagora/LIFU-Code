#include "GPIOInit.h"

GPIOInit::GPIOInit()
{
}

void GPIOInit::MX_GPIO_Init(void)
{
    __GPIOA_CLK_ENABLE();
    __GPIOC_CLK_ENABLE();
    
    //Master Timer Output
    GPIO_InitTypeDef GPIO;
    GPIO.Pin       = GPIO_PIN_9;                                                //PA9
    GPIO.Mode      = GPIO_MODE_AF_PP;
    GPIO.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO.Pull      = GPIO_NOPULL;
    GPIO.Alternate = GPIO_AF1_TIM1;
    HAL_GPIO_Init(GPIOA, &GPIO); 
    
    //Positive PWM Output                                                       //PC6
    GPIO.Pin                     = GPIO_PIN_6;
    GPIO.Mode                    = GPIO_MODE_AF_PP;
    GPIO.Speed                   = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO.Pull                    = GPIO_NOPULL;
    GPIO.Alternate               = GPIO_AF3_TIM8;
    HAL_GPIO_Init(GPIOC, &GPIO);
    
    //NEGATIVE GPIO CONFIG CAUSES PROGRAM HANG, NEEDS TO BE FIXED
    GPIO.Pin       = GPIO_PIN_7;                                                //PA7
    GPIO.Mode      = GPIO_MODE_AF_PP;
    GPIO.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO.Pull      = GPIO_NOPULL;
    GPIO.Alternate = GPIO_AF3_TIM8;
    HAL_GPIO_Init(GPIOA, &GPIO);
}

void GPIOInit::MX_GPIO_DeInit() {
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6);
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_7);
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9);
}