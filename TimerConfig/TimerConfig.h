#ifndef HEADERGUARD_H
#define HEADERGUARD_H
#include "mbed.h"
#include "Variables.h"
#include "GPIOInit.h"

class TimerConfig
{
public:
    
    /* CONSTRUCTOR TimerConfig
     * Constructor to instantiate timer with pre set values, can be changed in every initialization
     *
     * Input: double masterPrescaler,double masterPeriod,double masterReps,double slavePrescaler;double slavePeriod,double slavePulse,double slaveReps;
     * Output: void
     */
    TimerConfig(double mPrescaler, double mPeriod, double mReps, double sPresaler, double sPeriod, double sPulse, double sReps);
    
    /* FUNCTION set_values
     * Function used to dynamically change the values of an instance. 
     *
     * Input: double masterPrescaler,double masterPeriod,double masterReps,double slavePrescaler;double slavePeriod,double slavePulse,double slaveReps;
     * Output: void
     */
    void set_values(double mPrescaler, double mPeriod, double mReps, double sPresaler, double sPeriod, double sPulse, double sReps, double dose);
    
    /* FUNCTION status
     * Function used to change the status of the timer, this is not instance dependent. It can shut off any instance as it controls hardware
     *
     * Input: bool;
     * Output: void
     */
    void status(bool on);
    
    /* FUNCTION MX_TIM1_Init
     * Function used to initialize TIMER 1 CH 2. Controls Hardware 
     *
     * Input: void
     * Output: void
     */
    void MX_TIM1_Init(void);
    
    /* FUNCTION MX_TIM8_Init
     * Function used to initialize TIMER 8 CH 1. Controls Hardware
     *
     * Input: void
     * Output: void
     */
    void MX_TIM8_Init(void);
    
    /* FUNCTION getDosage
     * Timer.read_ms() <= dosage ? true : false; if false, main function can turn off timer
     *
     * Input: void
     * Output: bool
     */
    bool getDosage();
    
    /* FUNCTION setDosage
     * Set required dosage, is a user value so requires an external function separate from the timer values
     * NOTE: To remove dosage, set as 0!!!
     *
     * Input: double dose
     * Output: void
     */
    void setDosage(double dose);
    
    /* FUNCTION getStatus
     * return if timer on or off
     *
     * Input: void
     * Output: bool
     */
    bool getStatus();
    
private:
    /* Timer timer
     * Checks dosage, starts when timer status(true) called and reset when status(false)
     *
     * Input: void
     * Output: void
     */
    Timer timer;
    
    /* STRUCTURE timerInput systemParams
     * Definition found in variables.h, contains generic timer settings in hardware units. (Prescaler, period, etc.)
     *
     * Input: void
     * Output: void
     */
    struct timerInput systemParams;
    
    /* DOUBLE dosage
     * Length of electric output
     *
     * Input: void
     * Output: void
     */
    double dosage;
    
    /* BOOL systemStatus
     * Status of device output
     *
     * Input: void
     * Output: void
     */
    bool systemStatus;
    
    /* TIM_HANDLETYPEDEF htim1
     * Hardware timer data type. Reference: 
     *   https://www.st.com/content/ccc/resource/technical/document/user_manual/45/27/9c/32/76/57/48/b9/DM00189702.pdf/files/DM00189702.pdf/jcr:content/translations/en.DM00189702.pdf
     *  
     *  Page:924, you'll need it if you program these timers...
     *
     * Input: void
     * Output: void
     */
    TIM_HandleTypeDef htim1;
    
    /* TIM_HANDLETYPEDEF htim8
     * Hardware timer data type. Reference: 
     *  https://www.st.com/content/ccc/resource/technical/document/user_manual/45/27/9c/32/76/57/48/b9/DM00189702.pdf/files/DM00189702.pdf/jcr:content/translations/en.DM00189702.pdf
     *  
     *  Page:924
     *
     * Input: void
     * Output: void
     */
    TIM_HandleTypeDef htim8;

};
#endif
