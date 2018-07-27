#include "mbed.h"
 
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim8;
 
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM8_Init(void);
 
int main(void)
{
    HAL_Init();
    
    MX_GPIO_Init();         //GPIO Port Iniitalization
    MX_TIM2_Init();         //Timer 1 Initialization
    MX_TIM8_Init();         //Timer 8 Initialization
    
    while (1)
    {
    }
 
}
 
static void MX_TIM2_Init(void)
{
    __TIM2_CLK_ENABLE();
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;
    
    htim2.Instance               = TIM2;
    htim2.Channel                = HAL_TIM_ACTIVE_CHANNEL_2;
    htim2.Init.Prescaler         = 1;
    htim2.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim2.Init.Period            = 9000;
    htim2.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim2);
    
    HAL_TIM_PWM_Init(&htim2);
    
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);
    
    sConfigOC.OCMode       = TIM_OCMODE_PWM1;                                     //OCPulse has no effect on the wave, removed to minimize confusion
    sConfigOC.OCPolarity   = TIM_OCPOLARITY_LOW;
    sConfigOC.OCNPolarity  = TIM_OCNPOLARITY_LOW;
    sConfigOC.OCFastMode   = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState  = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}
 
static void MX_TIM8_Init(void)
{
    __TIM8_CLK_ENABLE();
    TIM_SlaveConfigTypeDef sSlaveConfig;
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;
    
    htim8.Instance               = TIM8;
    htim8.Channel                = HAL_TIM_ACTIVE_CHANNEL_1;
    htim8.Init.Prescaler         = 1;                                 
    htim8.Init.CounterMode       = TIM_COUNTERMODE_UP;                            //Rising edge mode
    htim8.Init.Period            = 500;
    htim8.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    htim8.Init.RepetitionCounter = 9;                                             //Starts at zero, will do rcr + 1 cycles
    HAL_TIM_Base_Init(&htim8);
    
    HAL_TIM_OnePulse_Init(&htim8, TIM_OPMODE_SINGLE);                             //Single Mode
    
    sSlaveConfig.SlaveMode    = TIM_SLAVEMODE_TRIGGER;                            //Slave will listen for trigger from ITR0
    sSlaveConfig.InputTrigger = TIM_TS_ITR1;
    HAL_TIM_SlaveConfigSynchronization(&htim8, &sSlaveConfig);
    
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;                           //Not applicable
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig);
    
    sConfigOC.OCMode       = TIM_OCMODE_PWM1;                                     //PWM2 flips the output where the square wave will be 0V and the non-square wave will be 3.3V
    sConfigOC.Pulse        = 250;
    sConfigOC.OCPolarity   = TIM_OCPOLARITY_LOW;                                  //Leave Polarity as Low so positive reads positive and negative reads negative
    sConfigOC.OCNPolarity  = TIM_OCNPOLARITY_LOW;
    sConfigOC.OCFastMode   = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState  = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    
    HAL_TIM_PWM_Init(&htim8);
    HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1);
    
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(&htim8, TIM_CHANNEL_1);
    HAL_TIM_OnePulse_Start(&htim8, TIM_CHANNEL_1);
}
 
static void MX_GPIO_Init(void)
{
    __GPIOA_CLK_ENABLE();
    __GPIOB_CLK_ENABLE();
    __GPIOC_CLK_ENABLE();
 
    //Master Timer Output
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin       = GPIO_PIN_3;
    GPIO_InitStructure.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStructure.Pull      = GPIO_NOPULL;
    GPIO_InitStructure.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    //Negative complement
    GPIO_InitStructure.Pin       = GPIO_PIN_7;
    GPIO_InitStructure.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStructure.Pull      = GPIO_NOPULL;
    GPIO_InitStructure.Alternate = GPIO_AF3_TIM8;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    //Output for positive output
    GPIO_InitTypeDef GPIO;
    GPIO.Pin       = GPIO_PIN_6;
    GPIO.Mode      = GPIO_MODE_AF_PP;
    GPIO.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO.Pull      = GPIO_NOPULL;
    GPIO.Alternate = GPIO_AF3_TIM8;
    HAL_GPIO_Init(GPIOC, &GPIO);
 
}