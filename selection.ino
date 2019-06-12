
// the initial location of the selection character
int selectLocation = 0;

// 16 connected fireworks.
// first integer stores whether or not the firework has been ignited
// second integer indicates when the firework can be unlocked for launch
//   - this prevents the "finale" fireworks from being launched early in the show
int connectedFireworks[][2] = {
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 4},
  {0, 4},
  {0, 4},
  {0, 4},
  {0, 8},
  {0, 8},
  {0, 8},
  {0, 8},
  {0, 12},
  {0, 12},
  {0, 14},
  {0, 14},
};

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
  Serial.println("displaying fireworks");
  for (int x = 0; x < 16; x++) {
    lcd.setCursor(x, 0);
    if (connectedFireworks[x][0] == 1) {
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

bool checkIfLocked(int x)
{
  Serial.print(x); Serial.print(" "); 
  if (connectedFireworks[x][1] == 0) {
    Serial.println("open");
    return false;
  }

  for (int i = 0; i < connectedFireworks[x][1]; i++) {
    if (connectedFireworks[i][0] == 0) {
      Serial.println("locked");
      return true;
    }
  }

  Serial.println("open");
  return false;
}

void printSelectCharacter()
{
  lcd.setCursor(selectLocation, 1);
  lcd.write(94);
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
  int newLocation = selectLocation + direction;
  if (checkIfLocked(newLocation)) {
    return;
  }
  lcd.setCursor(selectLocation, 1);
  lcd.print(" ");
  selectLocation = constrain(selectLocation + direction, 0, 15);
  
  lcd.setCursor(selectLocation, 1);
  lcd.write(94);
  Serial.println(selectLocation);
}

void callSelect()
{
  // Don't do anything if the firework has already been ignited
  if (connectedFireworks[selectLocation][0] == 1) {
    Serial.println("Already launched. skipping.");
    return;
  }

  // set this back to false so the selection menu will redraw when this is done
  started = false;

  lcd.clear();
  lcd.home();

  lcd.print("Number "); lcd.print(selectLocation + 1); lcd.print(" Ready");
  lcd.setCursor(0,1);
  lcd.print("Cancel");
  lcd.setCursor(10,1);
  lcd.print("Launch");

  bool loopLaunch = true;
  while (loopLaunch) {
    if (digitalRead(btnLeft) == LOW) {
      return;
    }
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

  connectedFireworks[selectLocation][0] = 1;
  
  delay(1000);
}

void callLeft()
{
  moveSelection(-1);

  Serial.println("Left");
  delay(200);
}

void callRight()
{
  moveSelection(1);

  Serial.println("Right");
  delay(200);
}
