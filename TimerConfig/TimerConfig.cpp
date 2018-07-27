#include "TimerConfig.h"
struct timerInput *userInput;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim8;    


TimerConfig::TimerConfig(double mPrescaler, double mPeriod, double mReps, double sPresaler, double sPeriod, double sPulse, double sReps) 
{
    systemStatus = false;
    systemParams.masterPrescaler = mPrescaler;
    systemParams.masterPeriod = mPeriod;
    systemParams.masterReps = mReps;

    systemParams.slavePrescaler = sPresaler;
    systemParams.slavePeriod = sPeriod;
    systemParams.slavePulse = sPulse;
    systemParams.slaveReps = sReps;
    
};


void TimerConfig::status(bool on)
{
    GPIOInit* gpio = new GPIOInit();
    DigitalOut led2(LED2);
    if(!on)
    {
        gpio->MX_GPIO_DeInit();
        //not outputting
        led2 = 0;
        
        HAL_TIMEx_PWMN_Stop(&htim8, TIM_CHANNEL_1);
        HAL_TIM_OnePulse_Stop(&htim8, TIM_CHANNEL_1);
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
        __TIM8_CLK_DISABLE();
        __TIM1_CLK_DISABLE();
        timer.stop();
        timer.reset();
    }
    else if(on)
    {   
        gpio->MX_GPIO_Init();
        //outputting signal
        led2 = 1;

        MX_TIM1_Init();                                                         //Timer 1 Initialization
        MX_TIM8_Init();                                                         //Timer 8 Initialization

        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
        HAL_TIM_OnePulse_Start(&htim8, TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Start(&htim8, TIM_CHANNEL_1);   
        timer.start();
        systemStatus = true;
    }
} 

bool TimerConfig::getStatus() {
    return systemStatus;   
}     

void TimerConfig::set_values(double mPrescaler, double mPeriod, double mReps, double sPresaler, double sPeriod, double sPulse, double sReps, double dose) {
    systemParams.masterPrescaler = mPrescaler;
    systemParams.masterPeriod = mPeriod;
    systemParams.masterReps = mReps;

    systemParams.slavePrescaler = sPresaler;
    systemParams.slavePeriod = sPeriod;
    systemParams.slavePulse = sPulse;
    systemParams.slaveReps = sReps;
    
    if(dose != 0) {
        dosage = dose;
    }        
}

void TimerConfig::MX_TIM1_Init(void)
{
    __TIM1_CLK_ENABLE();
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;

    htim1.Instance               = TIM1;
    htim1.Channel                = HAL_TIM_ACTIVE_CHANNEL_2;
    htim1.Init.Prescaler         = systemParams.masterPrescaler;
    htim1.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim1.Init.Period            = systemParams.masterPeriod - 1;
    htim1.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = systemParams.masterReps - 1;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim1);

    HAL_TIM_PWM_Init(&htim1);

    sMasterConfig.MasterOutputTrigger     = TIM_TRGO_UPDATE;
    sMasterConfig.MasterSlaveMode         = TIM_MASTERSLAVEMODE_ENABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig);

    sConfigOC.OCMode            = TIM_OCMODE_PWM1;
    sConfigOC.OCPolarity        = TIM_OCPOLARITY_LOW;
    sConfigOC.OCNPolarity       = TIM_OCNPOLARITY_LOW;
    sConfigOC.OCFastMode        = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState       = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState      = TIM_OCNIDLESTATE_RESET;

    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
}

void TimerConfig::MX_TIM8_Init(void)
{
    __TIM8_CLK_ENABLE();
    TIM_SlaveConfigTypeDef sSlaveConfig;
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;

    htim8.Instance               = TIM8;
    htim8.Channel                = HAL_TIM_ACTIVE_CHANNEL_1;
    htim8.Init.Prescaler         = systemParams.slavePrescaler;
    htim8.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim8.Init.Period            = systemParams.slavePeriod - 1;
    htim8.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    htim8.Init.RepetitionCounter = systemParams.slaveReps - 1;
    HAL_TIM_Base_Init(&htim8);

    HAL_TIM_OnePulse_Init(&htim8, TIM_OPMODE_SINGLE);

    sSlaveConfig.SlaveMode       = TIM_SLAVEMODE_TRIGGER;
    sSlaveConfig.InputTrigger    = TIM_TS_ITR0;
    HAL_TIM_SlaveConfigSynchronization(&htim8, &sSlaveConfig);

    sMasterConfig.MasterOutputTrigger     = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode         = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig);

    sConfigOC.OCMode            = TIM_OCMODE_PWM1;
    sConfigOC.Pulse             = systemParams.slavePulse;
    sConfigOC.OCPolarity        = TIM_OCPOLARITY_LOW;
    sConfigOC.OCNPolarity       = TIM_OCNPOLARITY_LOW;
    sConfigOC.OCFastMode        = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState       = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState      = TIM_OCNIDLESTATE_RESET;

    //PWM Configuration
    HAL_TIM_PWM_Init(&htim8);
    HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1);
}

bool TimerConfig::getDosage(void) {
    if(dosage != 0) {
        return timer.read_ms() <= (dosage * 1000);
    } else {
        return true;   
    }           
}

void TimerConfig::setDosage(double newValue) {
    dosage = newValue;      
}           
