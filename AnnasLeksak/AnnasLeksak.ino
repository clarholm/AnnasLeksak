
/* 
A toy, learn to mix colors and count binary. 

By Jens Clarholm @jenslabs, jenslabs.com
 */
 
#include <Bounce2.h>
#include "FastLED.h"

#define nextStateButton 6
#define previousStateButton 5
#define colorPotentiometerRed A2//remember to define as A#
#define colorPotentiometerGreen A1
#define colorPotentiometerBlue A0
#define switchRight 2
#define switchMiddle 3
#define switchLeft 4
#define DATA_PIN 7
#define NUM_LEDS 6


//Define and initiate global variables
int currentState = 0;
int nrOfStates = 5;
boolean debug1 = true;
int currentRedFromPot = 0;
int currentGreenFromPot = 0;
int currentBlueFromPot = 0;
CRGB CRGBValueReadFromPots;

// Create debounce objects for state buttons
Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 

//Define LED array
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  Serial.println("Start serial");
  
 delay(1000);
  
  //Create Led object
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  
  //Define state change buttons with debounce.
  // Setup the first button with an internal pull-up :
  pinMode(nextStateButton,INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  debouncer1.attach(nextStateButton);
  debouncer1.interval(50); // interval in ms
  
   // Setup the second button with an internal pull-up :
  pinMode(previousStateButton,INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  debouncer2.attach(previousStateButton);
  debouncer2.interval(50); // interval in ms

}

void loop() {
  // Update the Bounce instances :
  debouncer1.update();
  debouncer2.update();

  // Check for button presses on state change button
  int valueNextStateButton = debouncer1.read();
  int valuePreviousStateButton = debouncer2.read();

  // Turn on the LED if either button is pressed :
  if ( valueNextStateButton == LOW ) {
        Serial.print("this is a printout indicating that the previous state button has been pressed. Millis: ");
     Serial.println((int)millis);
//    valuePreviousStateButton = HIGH;
    updateState(1);
  } 

  if ( valuePreviousStateButton == LOW ) {
    //delay(10);
    Serial.print("this is a printout indicating that the next state button has been pressed. Millis: ");
     Serial.println((int)millis);
//valuePreviousStateButton = HIGH;
    updateState(0);
  }
  
  readRGBValues();
  setAllLedsToColor(CRGBValueReadFromPots);
/*
if (currentState == 0){
    setAllLedsToColor(CRGB::LawnGreen);
    }
*/
}

void readRGBValues(){
int tempCurrentReadingRed = analogRead(colorPotentiometerRed);
currentRedFromPot = map(tempCurrentReadingRed, 0, 1023, 0, 255);
CRGBValueReadFromPots.red = currentRedFromPot;
int tempCurrentReadingGreen = analogRead(colorPotentiometerGreen);
currentGreenFromPot = map(tempCurrentReadingGreen, 0, 1023, 0, 255);
CRGBValueReadFromPots.green = currentGreenFromPot;
int tempCurrentReadingBlue = analogRead(colorPotentiometerBlue);
currentBlueFromPot = map(tempCurrentReadingBlue, 0, 1023, 0, 255);
CRGBValueReadFromPots.blue = currentBlueFromPot;

}

void updateState(int stateChangeUpOrDown){
  int newState;
  if (stateChangeUpOrDown==0){
    newState=currentState-1;
    if (newState < 0){
      newState = nrOfStates;
      }
    }
   else if (stateChangeUpOrDown==1){
    newState=currentState+1;
    if (newState > nrOfStates){
      newState = 0;
      }
    }
    else Serial.println("Unsupported State change command");
    
    if (debug1 == true){
      Serial.print("State change detected, new state is: ");
      Serial.print(newState);     
      Serial.print(". Previous state was: ");
      Serial.print(currentState);
      Serial.println(".");
      }
    currentState = newState;
    showCurrentState();
  
  }

 void showCurrentState(){
      
      if (debug1 == true){
      Serial.print("Eneterd show current state, current state is: ");
      Serial.println(currentState);
      }     
      switch (currentState) {
      case 0:
        Serial.println("State 0 indication code here!");
        displayCurrentStateByShowingColorsAndFlashing(CRGB::HotPink);
        break;
      case 1:
        Serial.println("State 1 indication code here!");
        displayCurrentStateByShowingColorsAndFlashing(CRGB::HotPink);
        break;
      case 2:
        Serial.println("State 2 indication code here!");
        displayCurrentStateByShowingColorsAndFlashing(CRGB::Gold);
        break;
      case 3:
        Serial.println("State 2 indication code here!");
        displayCurrentStateByShowingColorsAndFlashing(CRGB::Gold);
        break;
      case 4:
        Serial.println("State 2 indication code here!");
        displayCurrentStateByShowingColorsAndFlashing(CRGB::DarkTurquoise);
        break;        
     case 5:
        Serial.println("State 2 indication code here!");
        displayCurrentStateByShowingColorsAndFlashing(CRGB::DarkTurquoise);
        break;
      default:
        Serial.println("No case available for current state.");
      }
  }

void displayCurrentStateByShowingColorsAndFlashing(CRGB color){
  setAllLedsToColor(color);
  delay(1000);
  /*
  int flashNrOfTimes = currentState;
  while(flashNrOfTimes>=0){
  setAllLedsToColor(color);
  delay(500);
  setAllLedsToColor(CRGB::Black);
  delay(500);
  flashNrOfTimes = flashNrOfTimes-1;
  }
  */
}
 void setAllLedsToColor(CRGB color){
    for(int currentLed = 0; currentLed < NUM_LEDS; currentLed = currentLed + 1) {
    leds[currentLed] = color;
    }
    FastLED.show();
    }
