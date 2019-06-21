String menuOptions[3] = {
  "Back To Main",
  "CountDown   ",
  "Reset Data  "
};

bool returnToMain;

void adminMenu()
{
  started = false;
  returnToMain = false;

  int currentOption;
  int newOption;
  bool loopMenu = true;
  while (loopMenu) {
    if (!started) {
      started = true;
      
      lcd.clear();
      lcd.home();
      lcd.print("Admin Menu");
      lcd.setCursor(0,1);
      lcd.print("<              >");

      currentOption = -1;
      newOption = 0;
  
    }
    if (currentOption != newOption) {
      currentOption = newOption;
      lcd.setCursor(2,1);
      lcd.print(menuOptions[currentOption]);
    }

    if (digitalRead(btnSelect) == LOW) {
      delay(300);
      doMenuOption(currentOption);
    }

    if (returnToMain) {
      started = false;
      return;
    }
    
    if (digitalRead(btnLeft) == LOW) {
      newOption = currentOption - 1;
      delay(200);
    }
    if (digitalRead(btnRight) == LOW) {
      newOption = currentOption + 1;
      delay(200);
    }

    if (newOption < 0) { newOption = 2; }
    if (newOption > 2) { newOption = 0; }

  }
}

void doMenuOption(int x)
{
  switch (x) {
    case 0:
      returnToMain = true;
      break;
    case 1:
      doMenuCountdown();
      break;
    case 2:
      doMenuReset();
      break;
  }
  delay(200);
}

void doMenuCountdown()
{
  lcd.clear();
  lcd.home();
  lcd.print("Do Countdown?");
  lcd.setCursor(6,1);
  lcd.print("back");
  
  writeSkipOutput();
  
  bool loopMenu = true;
  while (loopMenu) {    
    if (digitalRead(btnSelect) == LOW) {
      loopMenu = false;
      delay(200);
      continue;
    }

    if (digitalRead(btnLeft) == LOW) {
      setSkipCountdown(false);
      writeSkipOutput();
      delay(200);
    }
    
    if (digitalRead(btnRight) == LOW) {
      setSkipCountdown(true);
      writeSkipOutput();
      delay(200);
    }
  }
  started = false;
}

void writeSkipOutput()
{
  bool skipCountdown = checkSkipCountdown();

  lcd.setCursor(0,1);
  lcd.print(!skipCountdown ? "[yes]" : " yes ");
  
  lcd.setCursor(12,1);
  lcd.print(skipCountdown ? "[no]" : " no ");
}

void doMenuReset()
{
  Serial.println("Reset");
  
  lcd.clear();
  lcd.home();
  lcd.print("Reset Data?");

  lcd.setCursor(0,1);
  lcd.print("YES");

  lcd.setCursor(14,1);
  lcd.print("NO");

  bool loopMenu = true;
  while (loopMenu) {
    if (digitalRead(btnLeft) == LOW) {
      Serial.println("YES");
      resetFireworks();
      loopMenu = false;
      continue;
    }
    
    if (digitalRead(btnRight) == LOW) {
      Serial.println("NO");
      loopMenu = false;
      continue;
    }
  }
  started = false;
  delay(200);
}
