#include "WS2812-SOLDERED.h"
#define WS2812_PIN A4
#define DEFAULT_INTENSITY 200

WS2812 pixels(1, WS2812_PIN);

void initPixel(){
  pixels.begin();
}

void blink_pixel(pixel_colors color, uint8_t duration){
// void blink_pixel(pixel_colors color){
  pixels.clear();
  switch (color){
    case RED:
      pixels.setPixelColor(0, pixels.Color(DEFAULT_INTENSITY, 0, 0));
      break;
    case GREEN:
      pixels.setPixelColor(0, pixels.Color(0, DEFAULT_INTENSITY, 0));
      break;
    case BLUE:
      pixels.setPixelColor(0, pixels.Color(0, 0, DEFAULT_INTENSITY));
      break;
    case YELLOW:
      pixels.setPixelColor(0, pixels.Color(DEFAULT_INTENSITY/4, DEFAULT_INTENSITY/4, 0));
      break;
    case OFF:
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      break;

    default:
      break;
  }
  pixels.show();

  if (duration==0) return;

  delay(duration);
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}
