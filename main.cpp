#include "Parser.h"
#include "TimerConfig.h"
#include "mbed.h"
#include "EthernetInterface.h"
#include "Websocket.h"
#include "System.h"

#define MAX_LEN 512

int main() {
    char str[MAX_LEN];
    
    //Device Utilities    
    TimerConfig *timerConfig                 = new TimerConfig(1, 1000, 9, 1, 500, 250, 9); //default values, can be changed
    System *newSystem                        = new System();                    //system instance to control system LEDs
    Parser *parser                           = new Parser(timerConfig);//Parser class, pushes commands to timerConfig pointer
    
    EthernetInterface eth;                                                      //Ethernet Interface 
    eth.set_dhcp(true);                                                         //set ethernet connection as dhcp
    newSystem->disconnected(); 
    while(!eth.connect());                                                                    
    
    //Websocket must be initialized after the ethernet is connected. src of the websocket client is written that way.
    
    Websocket ws("ws://10.0.1.17:8000/ws", &eth);                               //Websocket Instance created, stuck in loop if not conncted

    while(!ws.connect());
    ws.send("STM");
    
    
    while (1) { 
        newSystem->connected();
        while(ws.checkConnection()) {                                           //check for internet connection
            newSystem->connected();                                             //LED indication of websocket connection
            if(ws.read(str)) {
                parser->parseString(str);
            }
            
        }
        newSystem->disconnected();
        //TODO LISTEN FOR PHYSICAL BUTTON SIGNALS                                            
    } 
}   
