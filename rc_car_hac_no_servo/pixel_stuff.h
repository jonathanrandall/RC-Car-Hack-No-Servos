#ifndef PIXEL_STUFF_H_
#define PIXEL_STUFF_H_

#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define white 255
#define red 22672
#define orange 15661
#define yellow 14746
#define green 1638
#define blue 45875
#define cyan 38502
#define pink 27034
#define purple 31949

#define LED_PIN   54
#define LED_COUNT 3
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint16_t brightness = 200;
bool bl_gr = true;

void start_pixel(){
  strip.begin();
   strip.setBrightness(brightness);
   //   strip.setPixelColor(1,strip.gamma32(strip.ColorHSV(pink)));
   strip.fill(strip.gamma32(strip.ColorHSV(pink)));//strip.gamma32(strip.ColorHSV(16000)));
   strip.show();
}

void flash_colours(){
  if(bl_gr){
    strip.setPixelColor(0,strip.gamma32(strip.ColorHSV(blue)));
    strip.setPixelColor(1,strip.gamma32(strip.ColorHSV(green)));
  } else {
    strip.setPixelColor(1,strip.gamma32(strip.ColorHSV(blue)));
    strip.setPixelColor(0,strip.gamma32(strip.ColorHSV(green)));
  }
  strip.show();
  
}

#endif
