#include "Parser.h"

Parser::Parser(TimerConfig * timer)
{
    timerConfig = timer;
}


//TODO
void Parser::updateTime()
{
    //defaultParams.masterPrescaler = 40000;
    //defaultParams.slavePrescaler  = 40000;


}

//TODO
void Parser::updateFreq()
{
    //defaultParams.masterPrescaler = (2.16e+8 / burstFrequency) - 1;
    //defaultParams.slavePrescaler  = (2.16e+8 / pulseFrequency) - 1;
}


//TODO
void Parser::updateDuty()
{

}

void Parser::parseString(char *command)
{
    string word(command, sizeof(command));
    DigitalOut led3(LED2);
    led3 = 1;
    if(word.substr(0,3) == ("set")) {
        timerConfig->status(false);
        timerConfig->set_values(1, 2000, 9, 1, 500, 250, 9, 0);   
    } else if(word.substr(0,3) == ("cat")) {
        timerConfig->status(false);
        timerConfig->set_values(1, 1000, 9, 1, 500, 250, 9, 0);
    }    
    else if(word.substr(0,2) == ("on")) {
        timerConfig->status(true);   
    }    
    else if(word.substr(0,3) == ("off")) 
    {
        timerConfig->status(false);    
    }
    /* 
    else if(word.substr(0,5) == "reset") 
    {
        NVIC_SystemReset();
    }    
    else if(word.substr(0,1) == "t")                                            //time support
    {
        //string manipulation, cut down string to obtain and cast variables
        word = word.substr(word.find(":") + 1, word.size());
        double dose    = atof(word.substr(0, word.find(":")).c_str());

        word = word.substr(word.find(":") + 1, word.size());
        double rest    = atof(word.substr(0, word.find(":")).c_str());

        word = word.substr(word.find(":") + 1, word.size());
        double burst   = atof(word.substr(0, word.find(":")).c_str());

        word = word.substr(word.find(":") + 1, word.size());
        double ontime  = atof(word.substr(0, word.find(":")).c_str());

        word = word.substr(word.find(":") + 1, word.size());
        double offtime = atof(word.substr(0, word.find(":")).c_str());

        //TODO, set new variables to new values

    }
    else if(word.substr(0,1) == "d")                                            //dutycycle support
    {
        //string manipulation, cut down string to obtain and cast variables
        word = word.substr(word.find(":") + 1, word.size());
        double dose        = atof(word.substr(0, word.find(":")).c_str());

        word = word.substr(word.find(":") + 1, word.size());
        double pulseperiod = atof(word.substr(0, word.find(":")).c_str());

        word = word.substr(word.find(":") + 1, word.size());
        double percentage  = atof(word.substr(0, word.find(":")).c_str());

        word = word.substr(word.find(":") + 1, word.size());
        double burstlength = atof(word.substr(0, word.find(":")).c_str());

        word = word.substr(word.find(":") + 1, word.size());
        double restlength  = atof(word.substr(0, word.find(":")).c_str());

        //TODO, set new variables to new values

    }
    else if(word.substr(0,1) == "f")                                            //frequency support
    {
        //string manipulation, cut down string to obtain and cast variables
        word = word.substr(word.find(":") + 1, word.size());
        double dose            = atof(word.substr(0, word.find(":")).c_str());

        word = word.substr(word.find(":") + 1, word.size());
        double pulsefreq       = atof(word.substr(0, word.find(":")).c_str());

        word = word.substr(word.find(":") + 1, word.size());
        double us_pulse_freq   = atof(word.substr(0, word.find(":")).c_str());

        word = word.substr(word.find(":") + 1, word.size());
        double us_pulse_length = atof(word.substr(0, word.find(":")).c_str());

        word = word.substr(word.find(":") + 1, word.size());
        double rest_length     = atof(word.substr(0, word.find(":")).c_str());

        //TODO, set new variables to new values
    } else {
        //Nothing to do!   
    }  */  
}
