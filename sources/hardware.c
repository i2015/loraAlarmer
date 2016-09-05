#include        "hardware.h"

void iwdg_init(uint16_t nms) {
uint8_t pr, rlr;
    
    for(pr=2; pr<=8; pr++) {
        if(((get_lsi()/1000*nms)>>pr) < 0x100)
          break;
    }
    rlr = get_lsi()/1000*nms>>pr;
    pr -= 2;
    
    IWDG_KR = 0xCC;
    IWDG_KR = 0x55;  
    IWDG_PR = pr;
    IWDG_RLR = rlr;
    IWDG_KR = 0xAA;
}

uint32_t get_sysclk(void) {
uint32_t clk;
	switch(CLK_SCSR) {
	case 0x01:
		clk = get_hsi();
		break;
	case 0x02:
		clk = get_lsi();
		break;
	case 0x04:
		clk = get_hse();
		break;
	default:
		break;
	}
	
	clk >>= (CLK_CKDIVR);
	return clk;
}

void usart_init(uint32_t baudrate) {
uint16_t brr;

	CLK_PCKENR1 |= 0x20;
	brr = get_sysclk()/baudrate;
	if((get_sysclk()-brr*baudrate) >= (baudrate>>1)) {
		brr += 1;
	}
	USART1_BRR2 = ((brr>>8)&0xF0)|(brr&0x0F);
	USART1_BRR1 = (brr>>4)&0xFF;
	USART1_CR1 = 0x00;
	USART1_CR2 = 0x2c;
	USART1_CR3 = 0x00;	
}

int putchar(int c) {
	while(!USART1_SR_TXE);
	USART1_DR = c;
	return c;
}
