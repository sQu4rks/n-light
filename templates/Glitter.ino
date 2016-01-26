#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    280
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

int lines[40];

#define SPEED 10

void setup() {
    delay( 1000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    for(int x=0;x<40;x++){
      lines[x] = -1;
    }
    randomSeed(analogRead(0));
}

void loop()
{

    for(int x=0;x<40;x++){
      for(int y=0;y<7;y++){
        leds[x + y*40] = CRGB::Black;
      }
      if(lines[x] == -1){
        if(random(100) < 3){
          lines[x] = 0;
        }
      }
      else{
        lines[x]++;
        if(lines[x] >= 7){
          lines[x] = -1; //dropped out
        }
      }
      if(lines[x] > -1){
        //normal white snow
        //leds[x + lines[x]*40] = CRGB::White;

        //glitter snow
        leds[x + lines[x]*40] = CRGB(random(256), random(256), random(256));
      }
    }
    FastLED.show();
    FastLED.delay(1000 / SPEED);
}
