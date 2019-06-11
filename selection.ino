
int selectLocation = 0;

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
  started = true;
  removeInterrupt();

  lcd.clear();

  Serial.println("Here");
  displayFireworks();
  lcd.setCursor(selectLocation, 1);
  lcd.write(94);
  delay(1000);
}

void displayFireworks()
{
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
  started = false;
  lcd.clear();
  lcd.home();
  lcd.print(" Firing Firework... ");

  connectedFireworks[selectLocation][0] = 1;
  
  Serial.println("Select");
  delay(5000);
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
