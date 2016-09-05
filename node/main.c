#include        "hardware.h"

int main( void )
{
  iwdg_init(500);
  SYSCFG_RMPCR1 |= 0x10;
  usart_init(9600);
  printf("usart work.\r\n");
  while(1);
  return 0;
}
