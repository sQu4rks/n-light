#include <FastLED.h>

#define LED_PIN     3 //data stream pin
#define NUM_LEDS    280 //number of LEDs
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB //required to revert the inversion of red and green
CRGB leds[NUM_LEDS]; //all LEDs

/*
 * Defines the character struct for showing text
 */
struct Character {
  byte width;
  bool data[49];
};

/*
 * All characters defined
 */
Character charA = {7, {
  false, false, false, true, false, false, false,
  false, false, true, false, true, false, false,
  false, true, false, false, false, true, false,
  false, true, true, true, true, true, false,
  true, false, false, false, false, false, true,
  true, false, false, false, false, false, true,
  true, false, false, false, false, false, true,
}};

Character charB = {5, {
  true, true, true, true, false,
  true, false, false, false, true,
  true, false, false, false, true,
  true, true, true, true, false,
  true, false, false, false, true,
  true, false, false, false, true,
  true, true, true, true, false,
}};

Character charC = {6, {
  false, false, true, true, true, true,
  false, true, false, false, false, false,
  true, false, false, false, false, false,
  true, false, false, false, false, false,
  true, false, false, false, false, false,
  false, true, false, false, false, false,
  false, false, true, true, true, true,
}};

Character charD = {6, {
  true, true, true, true, false, false,
  true, false, false, false, true, false,
  true, false, false, false, false, true,
  true, false, false, false, false, true,
  true, false, false, false, false, true,
  true, false, false, false, true, false,
  true, true, true, true, false, false,
}};

Character charE = {6, {
  true, true, true, true, true, true,
  true, false, false, false, false, false,
  true, false, false, false, false, false,
  true, true, true, true, false, false,
  true, false, false, false, false, false,
  true, false, false, false, false, false,
  true, true, true, true, true, true,
}};

Character charF = {6, {
  true, true, true, true, true, true,
  true, false, false, false, false, false,
  true, false, false, false, false, false,
  true, true, true, true, false, false,
  true, false, false, false, false, false,
  true, false, false, false, false, false,
  true, false, false, false, false, false,
}};

Character charG = {6, {
  false, false, true, true, true, false,
  false, true, false, false, false, true,
  true, false, false, false, false, false,
  true, false, false, false, false, false,
  true, false, false, true, true, false,
  true, false, false, false, false, true,
  false, true, true, true, true, false,
}};

Character charH = {6, {
  true, false, false, false, false, true,
  true, false, false, false, false, true,
  true, false, false, false, false, true,
  true, true, true, true, true, true,
  true, false, false, false, false, true,
  true, false, false, false, false, true,
  true, false, false, false, false, true,
}};

Character charI = {1, {
  true, 
  true, 
  true, 
  true, 
  true,
  true, 
  true, 
}};

Character charJ = {4, {
  false, false, false, true, 
  false, false, false, true,
  false, false, false, true, 
  false, false, false, true, 
  false, false, false, true, 
  true, false, false, true, 
  false, true, true, false, 
}};

Character charK = {4, {
  true, false, false, true, 
  true, false, true, false,
  true, true, false, false, 
  true, false, false, false, 
  true, true, false, false, 
  true, false, true, false, 
  true, false, false, true, 
}};

Character charL = {5, {
  true, false, false, false, false, 
  true, false, false, false, false, 
  true, false, false, false, false, 
  true, false, false, false, false, 
  true, false, false, false, false, 
  true, false, false, false, false, 
  true, true, true, true, true, 
}};

Character charM = {7, {
  true, true, false, false, false, true, true,
  true, false, true, false, true, false, true,
  true, false, false, true, false, false, true,
  true, false, false, false, false, false, true,
  true, false, false, false, false, false, true,
  true, false, false, false, false, false, true,
  true, false, false, false, false, false, true,
}};

Character charN = {5, {
  true, false, false, false, true,
  true, true, false, false, true,
  true, true, false, false, true,
  true, false, true, true, true,
  true, false, false, true, true,
  true, false, false, true, true,
  true, false, false, false, true,
}};

Character charO = {6, {
  false, true, true, true, true, false,
  true, false, false, false, false, true,
  true, false, false, false, false, true,
  true, false, false, false, false, true,
  true, false, false, false, false, true,
  true, false, false, false, false, true,
  false, true, true, true, true, false,
}};

Character charP = {5, {
  true, true, true, true, false,
  true, false, false, false, true,
  true, false, false, false, true,
  true, true, true, true, false,
  true, false, false, false, false,
  true, false, false, false, false,
  true, false, false, false, false,
}};

//Q missing

Character charR = {5, {
  true, true, true, true, false,
  true, false, false, false, true,
  true, false, false, false, true,
  true, true, true, true, false,
  true, false, true, false, false,
  true, false, false, true, false,
  true, false, false, false, true,
}};

Character charS = {5, {
  false, true, true, true, true,
  true, false, false, false, false,
  true, false, false, false, false,
  false, true, true, true, false,
  false, false, false, false, true,
  false, false, false, false, true,
  true, true, true, true, false,
}};

Character charT = {5, {
  true, true, true, true, true,
  false, false, true, false, false,
  false, false, true, false, false,
  false, false, true, false, false,
  false, false, true, false, false,
  false, false, true, false, false,
  false, false, true, false, false,
}};

Character charU = {5, {
  true, false, false, false, true,
  true, false, false, false, true,
  true, false, false, false, true,
  true, false, false, false, true,
  true, false, false, false, true,
  true, false, false, false, true,
  false, true, true, true, false,
}};

Character charV = {5, {
  true, false, false, false, true,
  true, false, false, false, true,
  true, false, false, false, true,
  true, false, false, false, true,
  false, true, false, true, false,
  false, true, false, true, false,
  false, false, true, false, false,
}};

Character charW = {7, {
  true, false, false, false, false, false, true,
  true, false, false, false, false, false, true,
  true, false, false, false, false, false, true,
  true, false, false, true, false, false, true,
  true, false, false, true, false, false, true,
  false, true, true, false, true, true, false,
  false, true, false, false, false, true, false,
}};

Character charZ = {5, {
  true, true, true, true, true,
  false, false, false, false, true,
  false, false, false, true, false,
  false, false, true, false, false,
  false, true, false, false, false,
  true, false, false, false, false,
  true, true, true, true, true,
}};

Character charSp = {5, {
  false, false, false, false, false,
  false, false, false, false, false,
  false, false, false, false, false,
  false, false, false, false, false,
  false, false, false, false, false,
  false, false, false, false, false,
  false, false, false, false, false,
}};

Character char2 = {5, {
  false, true, true, true, false,
  true, false, false, false, true,
  false, false, false, false, true,
  false, false, false, true, false,
  false, false, true, false, false,
  false, true, false, false, false,
  true, true, true, true, true,
}};

/*Character ex = {6, {
  false, false, false, false, false, false,
  false, false, false, false, false, false,
  false, false, false, false, false, false,
  false, false, false, false, false, false,
  false, false, false, false, false, false,
  false, false, false, false, false, false,
  false, false, false, false, false, false,
}};*/

//define word length and set an array of pointers of chars to get the word to display.
#define WORD_LENGTH 26
//xx
//Character* currentWord[WORD_LENGTH] = {&charA, &charB, &charC, &charD, &charE, &charF, &charG, &charH, &charI, &charJ, &charK, &charL, &charM, &charN, &charO, &charP};
//26
Character* currentWord[WORD_LENGTH] = {&charH, &charA, &charL, &charL, &charO, &charSp, &charM, &charA, &charR, &charC, &charE, &charL, &charSp, &charU, &charN, &charD, &charSp, &charC, &charH, &charR, &charI, &charS, &charT, &charI, &charA, &charN};
//17
//Character* currentWord[WORD_LENGTH] = {&charE, &charV, &charE, &charN, &charT, &char2, &charM, &charA, &charI, &charL, &charSp, &charS, &charT, &charI, &charN, &charK, &charT};
//38
//Character * currentWord[WORD_LENGTH] = {&charH, &charA, &charL, &charL, &charO, &charSp, &charO, &charL, &charI, &charSp, &charE, &charS, &charSp, &charS, &charC, &charH, &charE, &charI, &charN, &charT, &charSp, &charZ, &charU, &charSp, &charF, &charU, &charN, &charK, &charT, &charI, &charO, &charN, &charI, &charE, &charR, &charE, &charN};

//start on the right side of the screen 
int currentPosition = 40;

//set speed of text on screen.
#define SPEED 20

void setup() {
    delay( 1000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
}

void drawCharacterAtPosition(Character *current, int position){
  for(int y=0;y<7;y++){ //go through all rows
    for(int x=0;x<current->width;x++){ //through all required columns
      if(position + x < 40 && position + x >= 0){
        if(current->data[x + y*current->width]){
          leds[position+x + y*40] = CRGB::Red;
        }
        else{
          leds[position+x + y*40] = CRGB::Black;
        }
      }
    }
  }
}

void drawWordAtPosition(int position){
  for(int x=0;x<WORD_LENGTH;x++){ //go through the whole word
    drawCharacterAtPosition(currentWord[x], position); //draw the character
    if(position + currentWord[x]->width < 40 && position + currentWord[x]->width > -1){ //empty columns #1
      for(int y=0;y<7;y++){
        leds[position + currentWord[x]->width + y*40] = CRGB::Black;
      }
    }
    if(position + currentWord[x]->width + 1 < 40  && position + currentWord[x]->width + 1 > -1){ //empty columns #2
      for(int y=0;y<7;y++){
        leds[position + currentWord[x]->width + 1 + y*40] = CRGB::Black;
      }
    }
    position += currentWord[x]->width + 2;
  }
}

/*
 * Get the length in pixel of a word
 */
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
    currentPosition--; //move from right to left
    if(currentPosition < - getWordLength() - 2){
      currentPosition = 40; //when word has disappeared on the left side, start again
    }
    FastLED.show();
    FastLED.delay(1000 / SPEED);
}


