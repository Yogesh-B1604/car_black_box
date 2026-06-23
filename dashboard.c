#include <xc.h>
#include "main.h"
volatile int sec=30;
int event_count=0;
unsigned char clock_reg[3], speed[3] = {0};
char  *event[ ] = { "ON",  "GN", "G1", "G2", "G3", "G4", "GR", "C "};
int pos = 0,i=0,flag=0,count=3;
unsigned int adc_val;
char password[5]="1100";
char user_password[5];
unsigned long int delay;
int dflag=0;
int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 != '\0' || *s2 != '\0')
    {
        if (*s1 != *s2)
        {
            return 1;   
        }
        s1++;
        s2++;
    }

    return 0;  
}

void dashboard(unsigned char key) {
        dflag = 0;        
        clcd_print(" TIME     EV  SP", LINE1(0));
        
        // display time
        get_time(clock_reg);
        display_time(clock_reg);
        
        // event display ( Gear pos and speed )
        if(key == SW1){
            if(pos == 7){
                pos = 1;
                store_event();
            }
            else if(pos < 6){
                pos++;
                store_event();
            }
        }
        else if(key == SW2){
            if(pos == 7){
                pos = 1;
                store_event();
            }
            if(pos > 1){
                pos--;
                store_event();
            }
        }
        else if(key == SW3){
            pos = 7;
            store_event();
        }
        else if(key == SW4){
            
            password_verification(key);
            
        }
        
        clcd_print("  ",LINE2(8));
        clcd_print(event[pos], LINE2(10));
        clcd_print("  ",LINE2(12));
        adc_val = read_adc(CHANNEL0) / 10.23;
        speed[0]= (adc_val/10)+'0';
        speed[1]= (adc_val%10)+'0';
        speed[2]='\0';
        clcd_print(speed,LINE2(14));
}
void store_event(void){
    static int address = 0x00;
    for(int i=0;i<8;i++){
        if(i==2 || i==5){
            continue;
        }
        write_external_eeprom(address++,time[i]);
    }
    write_external_eeprom(address++,event[pos][0]);
    write_external_eeprom(address++,event[pos][1]);
    
    write_external_eeprom(address++,speed[0]);
    write_external_eeprom(address++,speed[1]);
    if(address == 99){
        address = 0;
    }
    if(event_count < MAX_LOGS)
            event_count++;
}
void password_verification(unsigned char key){
    clcd_print("Enter Password  ",LINE1(0));
    clcd_print("                ",LINE2(0));
    flag=1;

    while(1){
        key = read_digital_keypad(STATE);
        if(i<4){
                    if (key == SW1 )
                    {
                    user_password[i]= '1';
                    clcd_putch('*', LINE2(i));
                    i++;    
                    }
                    else if(key == SW2 )
                    {
                    user_password[i]= '0';
                    clcd_putch('*', LINE2(i));
                    i++;
                    }
        }
        else if(i == 4 && flag == 1){
            
            user_password[i]= '\0';
            
            if(my_strcmp(password,user_password)==0){
                clcd_print("                ",LINE1(0));
                clcd_print("                ",LINE2(0));
                flag=2;
            }
            else{
                 count--;
                 if(count==0){
                    flag=3;           
                 }
                 else{
                    i=0;
                    flag=0;
                    char ch; 
                    ch=count+'0';     
                    clcd_print("Wrong Password ", LINE1(0));
                    clcd_putch(ch,LINE2(0));
                    clcd_print(" Attempts left ", LINE2(1));
                    __delay_ms(900);
                    clcd_print("                ", LINE2(0));
                    flag=1;
                 }  
                }
            }
        
        if(flag == 2){
                main_menu(key);
                if(dflag == 1){
                    i=0;
                    flag=0;
                    count = 3;
                    return;
                }
        }
        else if(flag==3){
            clcd_print("Try After: ", LINE2(0));
            clcd_putch((sec / 10) + '0', LINE2(11));
            clcd_putch((sec % 10) + '0', LINE2(12));
            clcd_print("s  ",LINE2(13));
            if(sec == 0){
                sec = 30;
                clcd_print("                ",LINE1(0));
                clcd_print(" Enter Password ",LINE1(0));
                clcd_print("                ",LINE2(0));
                i = 0;
                count = 3;
                flag = 1;
            }
        }
    }
    }


