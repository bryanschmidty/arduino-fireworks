const byte interruptPin = 2;

void setupInterrupt()
{
  Serial.println("setting up interrupt");
  attachInterrupt(digitalPinToInterrupt(interruptPin), selectFireworks, LOW);
}

void removeInterrupt()
{
  detachInterrupt(digitalPinToInterrupt(interruptPin));
}
