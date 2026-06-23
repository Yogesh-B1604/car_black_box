#include <xc.h>
#include "main.h"
extern volatile int sec;
extern int flag;
extern int i;
extern volatile unsigned char blink_flag;
int f=0;
void __interrupt() isr(void)
{
    static unsigned int count = 0;
    
    if (TMR0IF == 1)
    {
        /* TMR0 Register valur + 6 (offset count to get 250 ticks) + 2 Inst Cycle */
        TMR0 = TMR0 + 6 + 2;
        
        if (++count == 20000)
        {
            count = 0;
            if(flag == 3){
            if(sec > 0)
                sec--;
            }
            if(flag == 1){
            if(f==0){
                clcd_putch('_', LINE2(i));
                f=1;
            }
            else if(f==1){
                clcd_putch(' ', LINE2(i));
                f=0;
            }
            }
            blink_flag = !blink_flag;
        }
        
        TMR0IF = 0;
    }
}