#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

volatile bool splash = true;
volatile int started = false;

int btnSelect = 2;
int btnLeft = 3;
int btnRight = 4;

void setup()
{
  lcd.begin();
  lcd.backlight();
  
  Serial.begin(9600);

  pinMode(btnSelect, INPUT_PULLUP);
  pinMode(btnLeft, INPUT_PULLUP);
  pinMode(btnRight, INPUT_PULLUP);

  // if LEFT is pressed while starting up, go to Admin menu
  if (digitalRead(btnRight) == LOW) {
    adminMenu();
  }

  // interrupt for exiting Splash Screen
  setupInterrupt();

  // load special characters for fireworks
  loadCharacters();
}

void selectFireworks()
{
  splash = false;
  started = false;
}

void loop()
{
  if (splash) {
    if (!started) beginSplashScreen();
    stepSplashScreen();
    return;
  }
  
  if (!started) beginFireworkSelection();

  if (digitalRead(btnSelect) == LOW) callSelect();
  if (digitalRead(btnLeft) == LOW) callLeft();
  if (digitalRead(btnRight) == LOW) callRight();
}
