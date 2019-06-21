const byte interruptPin = 2;

void setupInterrupt()
{
  attachInterrupt(digitalPinToInterrupt(interruptPin), selectFireworks, LOW);
}

void removeInterrupt()
{
  detachInterrupt(digitalPinToInterrupt(interruptPin));
}
