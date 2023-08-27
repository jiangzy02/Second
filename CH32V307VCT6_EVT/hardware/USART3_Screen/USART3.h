#ifndef __USART3_H
#define __USART3_H

#include "debug.h"


void HMISendb(u8 k) ;
void HMISends(char *buf1);
void uart3_init(void);
void Point_show(void);
#endif
