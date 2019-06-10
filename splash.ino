
// Fireworks for start screen
int Fireworks[][4] = {
  {2, -1, 10, 0},
  {4, -1, 1, 1},
  {5, -1, 13, 0},
  {8, -1, 4, 1}
};

void beginSplashScreen()
{
  started = 1;
  lcd.home();
  lcd.print("Schmidty");
  lcd.setCursor(6,1);
  lcd.print("Fireworks!");
}

int step = 0;
int f = 0;
void stepSplashScreen()
{
  for (int x = 0; x <= 3; x++) {
    if (Fireworks[x][0] == step || Fireworks[x][1] >= 0) {
      Fireworks[x][1]++;
      if (Fireworks[x][1] > 4) {
        Fireworks[x][1] = -1;
      }
    }
    fireworkStep(x);
  }
  step++;
  if (step > 8) {
    step = 0;
  }
  delay(300);
}

void fireworkStep(int i)
{
  int x = Fireworks[i][2];
  int y = Fireworks[i][3];
  int s = Fireworks[i][1];

  lcd.setCursor(x, y);
  if (s >= 0) {
    lcd.write(s);
  } else {
    lcd.print(" ");
  }
}
