#include <xc.h>
#include "main.h"

void init_digital_keypad(void)
{
    /* Set Keypad Port as input */
    KEYPAD_PORT_DDR = KEYPAD_PORT_DDR | INPUT_LINES;
}

unsigned char read_digital_keypad(unsigned char mode)
{
    static unsigned char once = 1;
    unsigned char key = KEYPAD_PORT & INPUT_LINES;

    if (mode == LEVEL_DETECTION)
    {
        return key;
    }

    // STATE DETECTION with DEBOUNCE
    if (key != ALL_RELEASED && once)
    {
        __delay_ms(20);  

        key = KEYPAD_PORT & INPUT_LINES; 

        if (key != ALL_RELEASED)
        {
            once = 0;
            return key;
        }
    }
    else if (key == ALL_RELEASED)
    {
        once = 1;
    }

    return ALL_RELEASED;
}
