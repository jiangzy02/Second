#ifndef _DMA_H
#define _DMA_H

#include <stm32f10x_type.h>

void DMA_Configuration(u32 mar,u16 ndtr);
void DMAx_Enable(u16 ndtr);

#endif
