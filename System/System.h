#ifndef SYSTEMGUARD_H
#define SYSTEMGUARD_H

#include "mbed.h"

class System
{
public:
    //TODO, add more system functions. LEDs are not worth an entire class ..xD

    /* CONSTRUCTOR System
     * Initializes System class for access to system functions. 
     *
     * Input: void
     * Output: void
     */
    System(void);

    /* FUNCTION connected
     * LED function for wifi connection
     *
     * Input: void
     * Output: void
     */
    void connected(void);
    
    /* FUNCTION disconnected
     * LED function for wifi disconnection
     *
     * Input: void
     * Output: void
     */
    void disconnected(void);

};
#endif
