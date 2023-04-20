//**FRUIT PICKING GAME**//
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "images.h" // image locations

#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8
#define TFT_MISO 12
#define TFT_MOSI 11
#define TFT_CLK 13
#define BUTTON_RED 2 
#define BUTTON_YELLOW 3
#define BUTTON_GREEN 4
#define BUTTON_FALLING 5

//colours
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define DARK_GREEN 0x07C0

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

uint16_t BROWN = tft.color565(139, 69, 19);

// Define the pins for the joystick
const int xPin = A0;
const int yPin = A1;
const int SW_PIN = A2; // set the analog pin to use as a digital input for the joystick button

int apple_x = 50; // modified x position for apple
int apple_y = 150;
int banana_x = 140;
int banana_y = 130;
int pear_x = 90;
int pear_y = 190;
int fruit_speed = 20;
bool buttonPressed = false;
int redButtonStatus = 0; // declare separate button status variables for each button
int yellowButtonStatus = 0;
int greenButtonStatus = 0;
int fallingButtonStatus =0;
int buttonPressCount = 0; // initialize counter variable to 0
int redButtonPressCount = 0; // initialize red button press counter to 0
int yellowButtonPressCount = 0; //yellow button
int greenButtonPressCount = 0; //yellow button

int basketX = 100; // Change this to whatever starting X position you want
const int basketY = tft.height() - 42;
const int basketWidth = 91;
const int basketHeight = 42;
// Define the previous position of the basket
int prevBasketX = -1;

  bool appleVisible = false; // track if apple is currently visible or not
   bool applePressedLast = false; // track if apple button was pressed on the previous loop iteration
   bool hideCircleDrawn = false; // track if the hide circle was already drawn

   bool bananaVisible = false; // track if banana is currently visible or not
   bool bananaPressedLast = false; // track if banana button was pressed on the previous loop iteration
   bool hideBananaCircleDrawn = false; // track if the hide circle was already drawn
  
   bool pearVisible = false; // track if pear is currently visible or not
   bool pearPressedLast = false; // track if pear button was pressed on the previous loop iteration
   bool hidePearCircleDrawn = false; // track if the hide circle was already drawn

void setup() {
 Serial.begin(9600);
  tft.begin();
  tft.setRotation(0);
  // clear the screen with a black background
  tft.fillScreen(BLACK);
  tft.drawBitmap(35, 100, tree, 183, 215, GREEN);
  tft.drawBitmap(100, tft.height() - 42, basket, 91 , 42, BROWN); // move basket to the bottom of the screen

  pinMode(BUTTON_RED, INPUT_PULLUP); // update the pin numbers for each button
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode (BUTTON_FALLING, INPUT_PULLUP);

 
   pinMode(SW_PIN, INPUT); // set the pin as an input (joystick)
  
  redButtonStatus = digitalRead(BUTTON_RED); // initialize button status variables to the current button state
  yellowButtonStatus = digitalRead(BUTTON_YELLOW);
  greenButtonStatus = digitalRead(BUTTON_GREEN);
  fallingButtonStatus = digitalRead (BUTTON_FALLING);

  pinMode(7, INPUT_PULLUP); //reset  button
   // Initialize the button press count to 0
  
  buttonPressCount = 0;

   bool appleVisible = false; // track if apple is currently visible or not
   bool applePressedLast = false; // track if apple button was pressed on the previous loop iteration
   bool hideCircleDrawn = false; // track if the hide circle was already drawn

   bool bananaVisible = false; // track if banana is currently visible or not
   bool bananaPressedLast = false; // track if banana button was pressed on the previous loop iteration
   bool hideBananaCircleDrawn = false; // track if the hide circle was already drawn
  
   bool pearVisible = false; // track if pear is currently visible or not
   bool pearPressedLast = false; // track if pear button was pressed on the previous loop iteration
   bool hidePearCircleDrawn = false; // track if the hide circle was already drawn
}
void drawFruits() {
  int radius = 25;
  

  
  
  int applePinValue = digitalRead(BUTTON_RED);
  if (applePinValue == LOW && !applePressedLast) {
    Serial.println("Apple pressed");
    applePressedLast = true;
    
    if (appleVisible) { // if apple is currently visible, hide it with a circle
tft.fillCircle(apple_x + 20, apple_y + 22, radius, tft.color565(0, 128, 0));
      hideCircleDrawn = true;
      appleVisible = false;
    } else { // if apple is currently hidden, show it
      tft.drawBitmap(apple_x, apple_y, apple, 40, 42, RED);
      appleVisible = true;
    }
    
    delay(50); // add a delay to debounce the button
  } else if (applePinValue == HIGH) {
    applePressedLast = false;
    if (hideCircleDrawn) { // if the hide circle was already drawn on the previous iteration, clear it
      //tft.fillCircle(apple_x + 19, apple_y + 27 - fruit_speed, radius, GREEN);
      hideCircleDrawn = false;
    }
  }
  
  int bananaPinValue = digitalRead(BUTTON_YELLOW);
  if (bananaPinValue == LOW && !bananaPressedLast) {
    Serial.println("Banana pressed");
    bananaPressedLast = true;
    
    if (bananaVisible) { // if banana is currently visible, hide it with a circle
      tft.fillCircle(banana_x + 20, banana_y + 24, radius, tft.color565(0, 128, 0));
      hideBananaCircleDrawn = true;
      bananaVisible = false;
    } else { // if banana is currently hidden, show it
      tft.drawBitmap(banana_x, banana_y, banana, 40, 43, YELLOW);
      bananaVisible = true;
    }
    
    delay(50); // add a delay to debounce the button
  } else if (bananaPinValue == HIGH) {
    bananaPressedLast = false;
    if (hideBananaCircleDrawn) { // if the hide circle was already drawn on the previous iteration, clear it
      //tft.fillCircle(banana_x + 19, banana_y + 27 - fruit_speed, radius, BLACK);
      hideBananaCircleDrawn = false;
    }
  }

    int pearPinValue = digitalRead(BUTTON_GREEN);
  if (pearPinValue == LOW && !pearPressedLast) {
    Serial.println("Pear pressed");
    pearPressedLast = true;
    
    if (pearVisible) { // if pear is currently visible, hide it with a circle
      tft.fillCircle(pear_x + 20, pear_y + 30, radius, tft.color565(0, 128, 0));
      hidePearCircleDrawn = true;
      pearVisible = false;
    } else { // if pear is currently hidden, show it
      tft.drawBitmap(pear_x, pear_y, pear, 38, 52, GREEN);
      pearVisible = true;
    }
    
    delay(50); // add a delay to debounce the button
  } else if (pearPinValue == HIGH) {
    pearPressedLast = false;
    if (hidePearCircleDrawn) { // if the hide circle was already drawn on the previous iteration, clear it
     // tft.fillCircle(pear_x + 19, pear_y + 27 - fruit_speed, radius, BLACK);
      hidePearCircleDrawn = false;
    }
  }
}
void fallFruits() {
  int startY[] = {apple_y, banana_y, pear_y}; // create an array of fruit starting y-coordinates
  int endY[] = {tft.height(), tft.height(), tft.height()}; // create an array of fruit ending y-coordinates
  int currentY[] = {appleVisible ? apple_y : startY[0], bananaVisible ? banana_y : startY[1], pearVisible ? pear_y : startY[2]}; // create an array of current y-coordinates
  
  bool allFruitsFallen = false;
  while (!allFruitsFallen) {
    allFruitsFallen = true;
    for (int i = 0; i < 3; i++) { // iterate through each fruit
      if ((i == 0 && digitalRead(BUTTON_RED) == HIGH && appleVisible) || (i == 1 && digitalRead(BUTTON_YELLOW) == HIGH && bananaVisible) || (i == 2 && digitalRead(BUTTON_GREEN) == HIGH && pearVisible)) { // check if the fruit is visible and has been pressed
        if (currentY[i] < endY[i]) { // if the fruit hasn't reached the end position yet, move it down
          int newY = currentY[i] + fruit_speed;
          if (newY > endY[i]) {
            newY = endY[i];
          }
          
          switch (i) {
            case 0: // apple
              if (currentY[i] > startY[i]) {
                tft.fillCircle(apple_x+20, currentY[0]+21, 25, tft.color565(0, 128, 0)); // clear previous apple
              }
              tft.drawBitmap(apple_x, newY, apple, 40, 42, RED);
              appleVisible = true;
              apple_y = newY;
              break;
            case 1: // banana
              if (currentY[i] > startY[i]) {
                tft.fillCircle(banana_x+22, currentY[1]+14, 25, tft.color565(0, 128, 0)); // clear previous banana
              }
              tft.drawBitmap(banana_x, newY, banana, 40, 43, YELLOW);
              bananaVisible = true;
              banana_y = newY;
              break;
            case 2: // pear
              if (currentY[i] > startY[i]) {
                tft.fillCircle(pear_x+17, currentY[2]+21, 25, tft.color565(0, 128, 0)); // clear previous pear
              }
              tft.drawBitmap(pear_x, newY, pear, 38, 54, GREEN);
              pearVisible = true;
              pear_y = newY;
              break;
          }
          currentY[i] = newY;
          allFruitsFallen = false;
        }
      }
    }
  }
}



void loop() {

  drawFruits();
 

  int buttonStatus2 = digitalRead(7); // read the state of the new button
  
  if (buttonStatus2 == LOW) { // check if the new button is pressed
  Serial.println("RESET");
    tft.fillScreen(BLACK); // clear the screen
     tft.drawBitmap(35, 100, tree, 183, 215, GREEN); //reset tree
  tft.drawBitmap(100, tft.height() - 42, basket, 91 , 42, BROWN); //reset basket
    apple_y = 150; // reset fruit positions
    banana_y = 120;
    pear_y = 200;
    buttonPressed = false; // set the buttonPressed variable back to false
  }

  // Check if the falling button is pressed
  if (digitalRead(BUTTON_FALLING) == LOW) {
    // Button is pressed, call the fallFruits function
    fallFruits();
  }

//move basket

  // Declare lastBasketX variable here
  static int lastBasketX = 0;

// Read the joystick values
  int xVal = analogRead(xPin);
  int yVal = analogRead(yPin);
  int buttonState = digitalRead(SW_PIN);

  // Map the joystick values to the basket position
  int basketSpeed = map(xVal, 0, 1023, -10, 10);
  int newBasketX = basketX + basketSpeed;
  //newBasketX = basketX + basketSpeed;

  // Limit the basket position to within the screen width
  if (newBasketX < 0) {
    newBasketX = 0;
  } else if (newBasketX > 150) { // Change 200 to whatever the maximum screen width should be
    newBasketX = 150;
  }

  // Only redraw the basket if its X position has changed
  if (newBasketX != lastBasketX) {
    // Clear the previous basket image
    tft.fillRect(0, tft.height() - 42, tft.width(), 42, BLACK);

    // Draw the new basket image at the new position
    tft.drawBitmap(newBasketX, tft.height() - 42, basket, 91, 42, BROWN);

    // Update the last basket position
    lastBasketX = newBasketX;
  }

  // Print the joystick and basket values for debugging
  /*Serial.print("Joystick X: ");
  Serial.print(xVal);
  Serial.print(", Basket X: ");
  Serial.println(newBasketX);
*/
  // Set the basket position to the new position
  basketX = newBasketX;

  delay(10); // Add a small delay to prevent the image from flickering
}
