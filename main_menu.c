/*
 * File:   main_menu.c
 * Author: yogesh_B
 *
 * Created on June 19, 2026, 6:25 AM
 */


#include <xc.h>
#include "main.h"
int menu_index = 0;
int star_pos = 0;
int selected;
char data[17];
extern int event_count;
int hh,mm,ss;
extern char time[9];
int field = 0;
extern int dflag;
volatile unsigned char blink_flag;
extern char password[5];
extern int i, flag;

void my_strcpy(char *dest, const char *src, int size)
{
    for(int i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
}

void main_menu (unsigned char key){
    char *menu[]={"View Log       ","clear Log      ","Download Log   ","Set Time        ","Change Password"};
    clcd_print(menu[menu_index], LINE1(1));

    if(menu_index < MENU_COUNT - 1)
        clcd_print(menu[menu_index + 1], LINE2(1));
    if(star_pos == 0){
        clcd_putch('*', LINE1(0));
        clcd_putch(' ', LINE2(0));
    }
    else{
        clcd_putch('*', LINE2(0));
        clcd_putch(' ', LINE1(0));
    }
    
    if(key == SW1)
    {
        if(star_pos == 1)
            star_pos = 0;
        else
        {
            if(menu_index > 0)
                menu_index--;
        }
    }
    else if(key == SW2)
    {
        if(star_pos == 0)
            star_pos = 1;
        else
        {
            if(menu_index < 3)
                menu_index++;
        }
    }
    else if(key == SW4){
        selected = menu_index + star_pos;
        switch(selected)
        {
            case 0: view_log(key);
                    break;

            case 1: clear_log(key);
                    break;

            case 2: download_log(key);
                    break;

            case 3: set_time(key);
                    break;

            case 4: change_password(key);
                    break;
            }
        }
}
void read_data(int addr)
{
    for(int j = 0; j < 16; j++)
    {
        if(j == 2 || j == 5)
        {
            data[j] = ':';   
        }
        else if(j == 8 || j == 11)
        {
            data[j] = ' ';   
        }
        else
        {
            data[j] = read_external_eeprom(addr++);
        }
    }
    data[16] = '\0';   
}
void view_log(unsigned char key){
    static int addr = 0;
    static int index = 0;
    if(event_count == 0)
        {
                clcd_print("    No  Logs    ", LINE1(0));
                clcd_print("     Found      ", LINE2(0));
                __delay_ms(1000);
                return;
            }
    while(key != SW5){
    key = read_digital_keypad(STATE);
        if(key == SW1)  
        {
        index++;
        if(index >= event_count)
            index = 0;
        }
    else if(key == SW2) 
        {
        if(index == 0)
            index = event_count - 1;
        else
            index--;
        }
    else if(key == SW5)
        {
            index = 0;
            return;
        }
        addr = index * LOG_SIZE;
        clcd_putch(index + '0', LINE2(0));
        //display_data(addr);
        read_data(addr);
        clcd_print("#   TIME   EV SP", LINE1(0));
        clcd_putch(' ',LINE2(1));
        clcd_print(data, LINE2(2));
    }
}

void clear_log(unsigned char key){
    if(event_count == 0)
        {
                clcd_print("     No Logs    ", LINE1(0));
                clcd_print(" Found to clear ", LINE2(0));
                __delay_ms(1000);
                return;
        }
    else{
                event_count = 0;
                clcd_print("    Clearing    ", LINE1(0));
                clcd_print("     Logs...    ", LINE2(0));
                __delay_ms(1000);
                return;
            }
    }


void download_log(unsigned char key){
    if(event_count == 0){
        puts("NO Logs Present To Download");
        puts("\r\n");
        clcd_print("NO LOGS PRESENT ", LINE1(0));
        clcd_print("  TO  DOWNLOAD  ", LINE2(0));
        __delay_ms(1000);
        return;
    }
    else{
    
    clcd_print("  Downloading   ", LINE1(0));
    clcd_print("     Logs...    ", LINE2(0));
    puts("#   TIME    EV SP");
    puts("\r\n");
    puts("--------------------------------\r\n");
    for(int i=0; i<event_count;i++){
        putchar(i+'0');
        puts("  ");
        read_data(i*10);
        puts(data);
        puts("\r\n");
    }
    }
    puts("--------------------------------\r\n");
    __delay_ms(1000);
    return;
    }

void set_time(unsigned char key){
    hh = (time[0]-'0')*10 + (time[1]-'0'); 
    mm = (time[3]-'0')*10 + (time[4]-'0');
    ss = (time[6]-'0')*10 + (time[7]-'0');
    
        
    while(1){
        key = read_digital_keypad(STATE);
        if(key == SW1){
            if(field == 0){
                if(hh >= 23)
                    hh = 0;
                else
                    hh++;
            }
            else if(field == 1){
                if(mm >= 59)
                    mm = 0;
                else
                    mm++;
            }
            else if(field == 2){
                if(ss >= 59)
                    ss = 0;
                else
                    ss++;
            }
        }
        if(key == SW2){
            field++;
            if(field > 2)
                field = 0;
        }
        else if(key == SW4){
            write_ds1307(HOUR_ADDR,((hh/10)<<4)|(hh%10));
            write_ds1307(MIN_ADDR,((mm/10)<<4)|(mm%10));
            write_ds1307(SEC_ADDR,((ss/10)<<4)|(ss%10));
            dflag=1;
            return;
        }
        else if(key == SW5)
            return;
        
        clcd_print("    HH:MM:SS    ", LINE1(0));
        clcd_print("    ",LINE2(0));
        if(field == 0 && blink_flag)
        {
            clcd_putch(' ', LINE2(4));
            clcd_putch(' ', LINE2(5));
        }
        else
        {
            clcd_putch((hh/10)+'0', LINE2(4));
            clcd_putch((hh%10)+'0', LINE2(5));
        }
        
        clcd_putch(':', LINE2(6));
        
        if(field == 1 && blink_flag)
        {
            clcd_putch(' ', LINE2(7));
            clcd_putch(' ', LINE2(8));
        }
        else
        {
            clcd_putch((mm/10)+'0', LINE2(7));
            clcd_putch((mm%10)+'0', LINE2(8));
        }
        clcd_putch(':', LINE2(9));
        if(field == 2 && blink_flag)
        {
            clcd_putch(' ', LINE2(10));
            clcd_putch(' ', LINE2(11));
        }
        else
        {
            clcd_putch((ss/10)+'0', LINE2(10));
            clcd_putch((ss%10)+'0', LINE2(11));
        }
        clcd_print("    ",LINE2(12));
        }

}

void change_password(unsigned char key){
    char temp[5],temp1[5];
    i=0;
    flag=1;
    clcd_print("EnterNewPassword", LINE1(0));
    clcd_print("                ", LINE2(0));
    while(1){
        
        key = read_digital_keypad(STATE);
        if(i<4){
        if(key == SW1){
            temp[i]='1';
            clcd_putch('*',LINE2(i));
            i++;
        }
        else if(key == SW2){
            temp[i]='0';
            clcd_putch('*',LINE2(i));
            i++;
        }
        }
        else if(i==4 && flag == 1){
            temp[i]='\0';
            i=0;
            clcd_print("ReEnter New Pass", LINE1(0));
            clcd_print("                ", LINE2(0));
            while(1){
                key = read_digital_keypad(STATE);
                if(i<4){
                if(key == SW1){
                    temp1[i]='1';
                    clcd_putch('*',LINE2(i));
                    i++;
                }
                else if(key == SW2){
                    temp1[i]='0';
                    clcd_putch('*',LINE2(i));
                    i++;
                }
                }
                else if(i==4 && flag == 1){
                    temp1[i]='\0';
                    if(my_strcmp(temp,temp1)== 0){
                        my_strcpy(password,temp,4);
                        flag=2;
                        clcd_print("Password Changed",LINE1(0));
                        clcd_print("  Successfully  ",LINE2(0));
                        __delay_ms(1000);
                        return;
                    }
                    else{
                        flag=2;
                        clcd_print(" ReEntered Pass ",LINE1(0));
                        clcd_print("  Doesn't Match ",LINE2(0));
                        __delay_ms(1000);
                        return;
                    }
                }
            }
        }
    }
}


