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

int repeatButton = 0;
int repeatCount = 0;

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  lcd.begin();
  lcd.backlight();
  
  lcd.clear();
  lcd.home();

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

  if (digitalRead(btnSelect) == LOW) {
    if (!callSelect()) {
      repeatBtn(btnSelect);
      if (repeatCount >= 2) {
        repeatCount = 0;
        forceRelaunch();
      }
    } else {
      repeatCount = 0;
    }
  }
  if (digitalRead(btnLeft) == LOW) {
    if (!callLeft()) {
      repeatBtn(btnLeft);
      if (repeatCount >= 4) {
        repeatCount = 0;
        adminMenu();
      }
    } else {
      repeatCount = 0;
    }
  }
  if (digitalRead(btnRight) == LOW){
    repeatBtn(btnRight);
    callRight();
  }
}

void repeatBtn(int btn)
{
  if (btn != repeatButton) {
    repeatButton = btn;
    repeatCount = 0;
  }

  repeatCount++;

  Serial.print("Btn: ");
  Serial.print(repeatButton);
  Serial.print(" - Count: ");
  Serial.println(repeatCount);
}
