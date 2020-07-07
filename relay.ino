
#include <I2cDiscreteIoExpander.h>

I2cDiscreteIoExpander relay;
int timeOn = 200;


word relayChannels;

void testRelay()
{
  for (int x = 1; x <= 16; x++) {
    Serial.println(x);
    igniteFirework(x);
    delay(1000);
  }

}

void resetChannels()
{
  relayChannels = 0;
}

void igniteFirework(int x)
{
  // write 1 to the correct channel bit
  bitWrite(relayChannels, x - 1, 1);
  relay.digitalWrite(relayChannels);

  // wait for the designated amount of time
  delay(timeOn);

  // write 0 back to the bit
  bitWrite(relayChannels, x - 1, 0);
  relay.digitalWrite(relayChannels);
}
