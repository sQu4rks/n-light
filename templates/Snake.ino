#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    280
#define BRIGHTNESS  32
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

int headPosition[2] = {0, 3};
byte currentDir; //0 up, 1 right, 2 down, 3 left
bool isOn[280];

#define SPEED 10

void setup() {
    delay( 1000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    for(int x=0;x<280;x++){
      isOn[x] = false;
    }
    randomSeed(analogRead(0));
}

void loop(){
  //if all fields are used around, we cannot continue...
  int count = 0;
  if(isOn[headPosition[1]*40 + (headPosition[0] + 1)%40]){
    count++;
  }
  if(isOn[headPosition[1]*40 + (headPosition[0] + 39)%40]){
    count++;
  }
  if(isOn[((headPosition[1] + 1)%7)*40 + headPosition[0]]){
    count++;
  }
  if(isOn[((headPosition[1] + 6)%7)*40 + headPosition[0]]){
    count++;
  }
  if(count == 4){
    //everything full, quit
    for(int x=0;x<280;x++){
      isOn[x] = false;
    }
    return;
  }

  if(random(100) < 8){
    currentDir = random(4);
  }
  
  int newHead[2] = {headPosition[0], headPosition[1]};
  switch(currentDir){
    case 0:
      newHead[0]--;
      break;
    case 1:
      newHead[1]++;
      break;
    case 2:
      newHead[0]++;
      break;
    case 3:
      newHead[1]--;
      break;
  }
  //test borders
  if(newHead[0] > 39){
    newHead[0] = 0;
  }
  else if(newHead[0] < 0){
    newHead[0] = 39;
  }
  if(newHead[1] > 6){
    newHead[1] = 0;
  }
  else if(newHead[1] < 0){
    newHead[1] = 6;
  }
  //test moving field
  if(isOn[newHead[1]*40+newHead[0]]){
    //cannot move there
    currentDir = random(4);
    return;
  }

  headPosition[0] = newHead[0];
  headPosition[1] = newHead[1];

  isOn[headPosition[0] + headPosition[1]*40] = true;
  for(int x=0;x<280;x++){
    if(x == headPosition[0] + headPosition[1]*40){
      leds[x] = CRGB(255, 0, 0);
    }
    else if(isOn[x]){
      leds[x] = CRGB(0, 0, 255);
    }
    else{
      leds[x] = CRGB(0, 0, 0);
    }
  }
  FastLED.show();
  FastLED.delay(1000 / SPEED);
}


