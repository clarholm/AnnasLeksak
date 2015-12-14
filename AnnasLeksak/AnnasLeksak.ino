
/* 
A toy, learn to mix colors and count binary. 

By Jens Clarholm @jenslabs, jenslabs.com
 */
 
#include <Bounce2.h>

#define nextStateButton 2
#define previousStateButton 3
#define colorPotentiometerRed A7//remember to define as A#
#define colorPotentiometerGreen A6
#define colorPotentiometerBlue A5
#define switchRight 4
#define switchMiddle 3
#define switchLeft 2
#define LED_pin 1

int currentState = 0;
int nrOfStates = 2;


// Create debounce objects for state buttons
Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 

void setup() {

  // Setup the first button with an internal pull-up :
  pinMode(nextStateButton,INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  debouncer1.attach(nextStateButton);
  debouncer1.interval(5); // interval in ms
  
   // Setup the second button with an internal pull-up :
  pinMode(previousStateButton,INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  debouncer2.attach(previousStateButton);
  debouncer2.interval(5); // interval in ms


  //Setup the LED :
  pinMode(colorPotentiometerRed,OUTPUT);

}

void loop() {
  // Update the Bounce instances :
  debouncer1.update();
  debouncer2.update();

  // Get the updated value :
  int valueNextStateButton = debouncer1.read();
  int valuePreviousStateButton = debouncer2.read();

  // Turn on the LED if either button is pressed :
  if ( valueNextStateButton == LOW ) {
    updateState(1);
  } 
  if ( valuePreviousStateButton == LOW ) {
    updateState(0);
  } 

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
    newState=currentState-1;
    if (newState > nrOfStates){
      newState = 0;
      }
    }
    else 
    Serial.println("Unsupported State change command");
    currentState = newState; 
  
  }


