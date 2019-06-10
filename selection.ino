
int selectLocation = 0;

void beginFireWorkSelection()
{
  started = 1;
  removeInterrupt();

  lcd.clear();

  for (int x = 0; x <= 16; x++) {
    lcd.setCursor(x, 0);
    lcd.print("o");
  }
  lcd.setCursor(selectLocation, 1);
  lcd.write(94);
}

void moveSelection(int direction)
{
  lcd.setCursor(selectLocation, 1);
  lcd.print(" ");
  selectLocation = constrain(selectLocation + direction, 0, 15);
  
  lcd.setCursor(selectLocation, 1);
  lcd.write(94);
  Serial.println(selectLocation);
}

void callSelect()
{
  Serial.println("Select");
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
