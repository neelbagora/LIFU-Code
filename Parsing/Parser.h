#ifndef PARSER_H
#define PARSER_H
#include "mbed.h"
#include <string>
#include "TimerConfig.h"

class Parser
{
public:
    /* CONSTRUCTOR Parser
     * Initializes parsing class with the timer meant to be updated, better 
     * to stick with one timer setting class than deal with a bunch of them
     *
     * Input: TimerConfig* timer
     * Output: void
     */
    Parser(TimerConfig*);
    
    /* FUNCTION updateTime
     * Called by parseString, should directly update timer settings to be in 
     * correlation to desired parameters, no return type necessary
     *
     * TODO
     *
     * Input: TODO
     * Output: TODO
     */
    void updateTime();

    /* FUNCTION updateFreq
     * Called by parseString, should directly update timer settings to be 
     * in correlation to desired parameters, no return type necessary
     *
     * TODO
     *
     * Input: TODO
     * Output: TODO
     */
    void updateFreq();
    
    /* FUNCTION updateDuty
     * Called by parseString, should directly update timer settings to be 
     * in correlation to desired parameters, no return type necessary
     *
     * TODO
     *
     * Input: TODO
     * Output: TODO
     */
    void updateDuty();

    /* FUNCTION parseString
     * Take in char array with encoded message and assigns each variable 
     * based on time unit in front. t for time, f for frequency, d for 
     * duty cycle. 
     *
     * TODO: CONNECT WITH UPDATE FUNCTIONS
     *
     * Input: char* command
     * Output: void
     */
    void parseString(char *command);

private:

    /* TIMERCONFIG* timerConfig
     * Parser will push commands for timer using this pointer.
     *
     * Input: void
     * Output: void
     */
    TimerConfig* timerConfig;
};

#endif
