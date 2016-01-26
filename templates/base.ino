{% autoescape false %}
#include <Arduino.h>
#include <FastLED.h>
#define LED_PIN     3
#define NUM_LEDS    280
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

struct Character {
  byte width;
  bool data[49];
};

{% for used in used_chars %}
  {{ used }}
{% endfor %}
#define WORD_LENGTH {{chars|length}}
Character* currentWord[WORD_LENGTH] = { {{ chars|join(',')}} };
int currentPosition = 40;

#define SPEED {{ speed }}

void setup() {
    delay( 1000 );
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );

}

void drawCharacterAtPosition(struct Character *current, int position){
  for(int y=0;y<7;y++){ //go through all rows
    for(int x=0;x<current->width;x++){
      if(position + x < 40 && position + x >= 0){
        if(current->data[x + y*current->width]){
          leds[position+x + y*40] = CRGB::{{ color }};
        }
        else{
          leds[position+x + y*40] = CRGB::Black;
        }
      }
    }
  }
}

void drawWordAtPosition(int position){
  for(int x=0;x<WORD_LENGTH;x++){
    drawCharacterAtPosition(currentWord[x], position);
    if(position + currentWord[x]->width < 40 && position + currentWord[x]->width > -1){
      for(int y=0;y<7;y++){
        leds[position + currentWord[x]->width + y*40] = CRGB::Black;
      }
    }
    if(position + currentWord[x]->width + 1 < 40  && position + currentWord[x]->width + 1 > -1){
      for(int y=0;y<7;y++){
        leds[position + currentWord[x]->width + 1 + y*40] = CRGB::Black;
      }
    }
    position += currentWord[x]->width + 2;
  }
}

int getWordLength(){
  int len = 0;
  for(int x=0;x<WORD_LENGTH;x++){
    len += currentWord[x]->width + 2;
  }
  return len;
}

void loop()
{

    drawWordAtPosition(currentPosition);
    currentPosition--;
    if(currentPosition < - getWordLength() - 2){
      currentPosition = 40;
    }
    FastLED.show();
    FastLED.delay(1000 / SPEED);
}
{% endautoescape %}
