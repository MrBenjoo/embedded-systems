/*
 * WTDTimer.c
 *
 * Created: 2017-01-13 14:12:57
 *  Author: George Albert Florea & Benjamin Sejdic 
 */ 

#include <inttypes.h>

#define WDT_KEY (0xA5 << 24) 
#define WDT_WDRSTT (1 << 0) /* shifts each bit in left-hand operand to the left by the number of positions indicated by the right-hand operand */

uint32_t *const p_WDT_CR = (uint32_t*) 0x400E1A50U; /* Watchdog Timer Control Register */

uint32_t watchdogReload(void)
{
	*p_WDT_CR = WDT_KEY | WDT_WDRSTT;
}
