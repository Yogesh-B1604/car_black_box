#ifndef MAIN_H
#define	MAIN_H
#include "adc.h"
#include "digital_keypad.h"
#include "external_eeprom.h"
#include "clcd.h"
#include "i2c.h"
#include "ds1307.h"
#include "uart.h"
#include "timers.h"
#define MENU_COUNT 5
#define MAX_LOGS 10
#define LOG_SIZE 10 
#define MAIN_MENU        0
#define VIEW_LOG_MODE    1
#define CLEAR_LOG_MODE   2
#define DOWNLOAD_MODE    3
#define SET_TIME_MODE    4
#define CHANGE_PASS_MODE 5

void dashboard(unsigned char key);

void store_event(void);

void password_verification(unsigned char key);

void main_menu (unsigned char key);

void my_strcpy(char *dest, const char *src, int size);

int my_strcmp(const char *s1, const char *s2);

void read_log(int addr);

void view_log(unsigned char key);

void clear_log(unsigned char key);

void download_log(unsigned char key);

void set_time(unsigned char key);

void change_password(unsigned char key);

#endif	/* MAIN_H */

