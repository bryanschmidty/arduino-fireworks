
uint8_t firework1[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x4};
uint8_t firework2[8] = {0x0, 0x0, 0x0, 0x0, 0x4, 0x4, 0x0, 0x0};
uint8_t firework3[8] = {0x0, 0x0, 0x4, 0x4, 0x0, 0x0, 0x0, 0x0};
uint8_t firework4[8] = {0x0, 0xa, 0x4, 0xa, 0x0, 0x0, 0x0, 0x0};
uint8_t firework5[8] = {0x1, 0x10, 0x0, 0x5, 0x10, 0x2, 0x0, 0x0};
uint8_t firework6[8] = {0x1, 0x10, 0x0, 0x5, 0x10, 0x2, 0x0, 0x4};
uint8_t locked[8] = {0x4, 0xa, 0xa, 0x1f, 0x11, 0x11, 0x11, 0x1f};

void loadCharacters()
{
  
  lcd.createChar(0, firework1);
  lcd.createChar(1, firework2);
  lcd.createChar(2, firework3);
  lcd.createChar(3, firework4);
  lcd.createChar(4, firework5);
  lcd.createChar(5, firework6);
  lcd.createChar(6, locked);
}
