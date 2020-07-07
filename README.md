## Arduino Firework Ignition System
The first phase of this project uses an Arduino to control a 16-channel relay board to ignite fireworks.

The current circuit includes:
* Arduino Uno
* 16x2 LCD Screen
* 3 push buttons (select, left, right);
* Key lock switch
* Covered rocker toggle switch
* 16-channel relay board
* i2c controller for relay board
* Cobra igniter clips


The functionality is as follows:
1. The circuit is turned on with the Key lock switch.
2. The LCD screen then displays a splash screen with animated fireworks
3. The "select" button is pressed which puts the Arduino into firework selection mode
16 fireworks are represented on the LCD with "o"s if they are available to launch, or a lock character if you cannot launch it yet. (You can designate when fireworks are locked using the connectedFireworks array in selection.ino)
4. Pressing the "left" and "right" buttons will move the cursor left and right.
5. Pressing the "select" button will start a countdown sequence
6. A signal is then sent to the 16-channel relay board to launch the appropriate firework

## Features
* Admin menu to manage settings and reset firework states. Currently, the only setting is to turn off countdown.
* uses EEPROM to store the state of each firework between startups

## To-Do List
* End splash screen for when all fireworks have been launched.

## Wish List
These are improvements I want to make to the project, but may not make it in for the July 2019 festivities.
* Admin menu for choosing which fireworks to lock.
* Sound board for sound effects during power on, splash screen, and selection screen
* Support for expansion of multiple Relay boards
* Admin ability to launch all remaining fireworks at the same time, or to launch an entire bank of fireworks at the same time.
* Remote control via wifi or bluetooth
