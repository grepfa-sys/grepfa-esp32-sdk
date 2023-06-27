//
// Created by vl0011 on 23. 6. 9.
//

#ifndef P1_GREPFA_NEOPIXEL_H
#define P1_GREPFA_NEOPIXEL_H

#ifdef __cplusplus
extern "C" {
#endif
void GrepfaNeoPixelSetGPIO(int gpio);
void GrepfaNeoPixelStart();

void GrepfaNeoPixelOn(int r, int g, int b);
void GrepfaNeoPixelOff();
void GrepfaNeoPixelInit();
#ifdef __cplusplus
};
#endif
#endif //P1_GREPFA_NEOPIXEL_H
