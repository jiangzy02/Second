#ifndef __WS2812_H
#define __WS2812_H

#include "debug.h"

#define PIXEL_NUM  30
#define GRB  24   //3*8

#define WS_HIGH 56
#define WS_LOW  28

void WS281x_Init(void);
void WS281x_CloseAll(void);
uint32_t WS281x_Color(uint8_t red, uint8_t green, uint8_t blue);
void WS281x_SetPixelColor(uint16_t n, uint32_t GRBColor);
void WS281x_SetPixelRGB(uint16_t n ,uint8_t red, uint8_t green, uint8_t blue);
void WS281x_Show(void);

void WS281x_RainbowCycle(uint8_t wait);
void WS281x_TheaterChase(uint32_t c, uint8_t wait);
void WS281x_ColorWipe(uint32_t c, uint8_t wait);
void WS281x_Rainbow(uint8_t wait);
void WS281x_TheaterChaseRainbow(uint8_t wait);
#endif /* __BSP_WS281X_H */


