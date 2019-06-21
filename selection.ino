bool skipCountdown = true;

// the initial location of the selection character
int selectLocation = 0;

// the beginning EEPROM address for firework data
int startAddress = 5;

// 16 connected fireworks.
// first 3 bits do nothing
// 4th bit stores whether or not firework has been launched
// last 4 bits indicate when the firework can be unlocked for launch
//   - this prevents the "finale" fireworks from being launched early in the show
byte newConnectedFireworks[16] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001100,
  B00001100,
  B00001110,
  B00001110,
};

void resetFireworks()
{
  for (int x = 0; x < 16; x++) {
    EEPROM.write(startAddress + x, newConnectedFireworks[x]);
  }
}

void setSkipCountdown(bool skip)
{
  byte temp = EEPROM.read(0);
  bitWrite(temp, 0, skip);
  EEPROM.write(0, temp);
}

bool checkSkipCountdown()
{
  Serial.print("checkSkipCountdown\t");
  Serial.println(EEPROM.read(0) & 1);
  return EEPROM.read(0) & 1;
}

void beginFireworkSelection()
{
  // we don't need the interrupt pin anymore since it was used only to get us out of the splash screen loop
  removeInterrupt();
  displayFireworks();
  started = true;
  delay(200);
  printSelectCharacter();
}

void displayFireworks()
{
  lcd.clear();
  for (int x = 0; x < 16; x++) {
    lcd.setCursor(x, 0);
    
    if (checkIfLaunched(x)) {
      printFireworkSpent();
      continue;
    }
    
    if (checkIfLocked(x)) {
      printFireworkLocked();
      continue;
    }
    
    printFireworkAvailable();
  }
}

bool checkIfLaunched(int x)
{
  return EEPROM.read(startAddress + x) >> 4 & 1;
}

int getLockedByte(int x)
{
  return EEPROM.read(startAddress + x) & 15;
}

bool checkIfLocked(int x)
{
  // loop through all fireworks under the locked byte and return false if any have not been launched
  for ( int c = 0; c < getLockedByte(x); c++) {
    if (!checkIfLaunched(c)) {
      return true;
    }
  }

  return false;
}

void printSelectCharacter()
{
  lcd.setCursor(selectLocation, 1);
  lcd.write(94);
}

void clearSelectCharacter()
{
  lcd.setCursor(selectLocation, 1);
  lcd.print(" ");
}

void printFireworkAvailable()
{
  lcd.print("o");
}

void printFireworkSpent()
{
  lcd.print("x");
}

void printFireworkLocked()
{
  lcd.write(6);
}

void moveSelection(int direction)
{
  // set variable to new location and check if it is locked or if there is no change
  int newLocation = constrain(selectLocation + direction, 0, 15);
  if (checkIfLocked(newLocation) || newLocation == selectLocation) {
    return;
  }

  // clear old location
  clearSelectCharacter();

  // set new location and write select character
  selectLocation = newLocation;
  printSelectCharacter();
}

void setFireworkLaunched(int x)
{
  byte currentByte = EEPROM.read(startAddress + x);
  bitWrite(currentByte, 4, 1);
  EEPROM.write(startAddress + x, currentByte);
}

void callSelect()
{
  // Don't do anything if the firework has already been launched
  if (checkIfLaunched(selectLocation)) {
    Serial.println("Already launched. skipping.");
    delay(200);
    return;
  }
  
  // set this back to false so the selection menu will redraw when this is done
  started = false;

  // run the countdown routine. If it returns true, then mark the firework as launched
  if (doCountdown()) {
    setFireworkLaunched(selectLocation);
  }
}

bool doCountdown()
{
  // skip countdown if we have set this boolean to true
  if (checkSkipCountdown()) {
    return true;
  }
  lcd.clear();
  lcd.home();

  lcd.print("Number "); lcd.print(selectLocation + 1); lcd.print(" Ready");
  // display "Cancel" over LEFT button
  lcd.setCursor(0,1);
  lcd.print("Cancel");
  // display "Launch" over RIGHT button
  lcd.setCursor(10,1);
  lcd.print("Launch");

  bool loopLaunch = true;
  while (loopLaunch) {
    // User pushes "Cancel"
    if (digitalRead(btnLeft) == LOW) {
      return false;
    }
    // User pushes "Launch"
    if (digitalRead(btnRight) == LOW) {
      loopLaunch = false;
    }
  }
  
  lcd.clear();
  lcd.home();
  lcd.print("Countdown!");
  delay(1000); lcd.setCursor(0, 1); lcd.print("3");
  delay(1000); lcd.setCursor(3, 1); lcd.print("2");
  delay(1000); lcd.setCursor(6, 1); lcd.print("1");
  
  delay(1000); lcd.setCursor(9, 1); lcd.print("Launch!");
  delay(1000);
  
  return true;
}

void callLeft()
{
  moveSelection(-1);
  delay(200);
}

void callRight()
{
  moveSelection(1);
  delay(200);
}
