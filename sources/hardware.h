#ifndef         __HARDWARE_H__
#define         __HARDWARE_H__

#include        <iostm8l051f3.h>
#include        <stdint.h>
#include        <stdio.h>


#define         get_hsi()               16000000
#define         get_hse()               8000000
#define         get_lsi()               38000

#define         iwdg_refresh()          {IWDG_KR = 0xAA}




void iwdg_init(uint16_t nms);
uint32_t get_sysclk(void);
void usart_init(uint32_t baudrate);
int putchar(int c);


#endif          //__HARDWARE_H__
