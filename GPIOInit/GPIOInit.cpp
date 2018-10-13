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
    GPIO.Mode      = GPIO_MODE_AF_PP;                                           //Mode- Push Pull
    GPIO.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;                                 //Frequency-Very High
    GPIO.Pull      = GPIO_NOPULL;                                               //DeToggle pull
    GPIO.Alternate = GPIO_AF1_TIM1;                                             //AlternateFunction3- Timer 1
    HAL_GPIO_Init(GPIOA, &GPIO);                                                //Init
    
    //Positive PWM Output                                                       
    GPIO.Pin                     = GPIO_PIN_6;                                  //PC6
    GPIO.Mode                    = GPIO_MODE_AF_PP;                             //Mode- Push Pull
    GPIO.Speed                   = GPIO_SPEED_FREQ_VERY_HIGH;                   //Frequency-Very High
    GPIO.Pull                    = GPIO_NOPULL;                                 //DeToggle pull
    GPIO.Alternate               = GPIO_AF3_TIM8;                               //AlternateFunction3- Timer 8
    HAL_GPIO_Init(GPIOC, &GPIO);                                                //Init
    
    //NEGATIVE GPIO CONFIG FIXED
    GPIO.Pin       = GPIO_PIN_7;                                                //PA7
    GPIO.Mode      = GPIO_MODE_AF_PP;                                           //Mode- Push Pull
    GPIO.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;                                 //Frequency-Very High
    GPIO.Pull      = GPIO_NOPULL;                                               //DeToggle pull
    GPIO.Alternate = GPIO_AF3_TIM8;                                             //AlternateFunction3- Timer 8
    HAL_GPIO_Init(GPIOA, &GPIO);                                                //Init
}

void GPIOInit::MX_GPIO_DeInit() {                                               //DeInit
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6);                                         //PC6
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_7);                                         //PC7
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9);                                         //PC9
}
