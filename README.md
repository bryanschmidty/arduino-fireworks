## Arduino Firework Ignition System
The first phase of this project uses an Arduino to control a 16-channel relay board to ignite fireworks.

The current circuit includes:
* Arduino Uno
* 16x2 LCD Screen
* 3 push buttons (select, left, right);
* Key lock switch

Items I have for the project but haven't been added yet are:
* Covered rocker toggle switch
* Momentary push button with red LED
* 16-channel relay board
* i2c controller for relay board
* 12v rechargeable power brick for igniter clips
* Cobra igniter clips

The functionality is as follows:
1. The circuit is turned on with the Key lock switch.
2. The LCD screen then displays a splash screen with animated fireworks
3. The "select" button is pressed which puts the Arduino into firework selection mode
16 fireworks are represented on the LCD with "o"s if they are available to launch, or a lock character if you cannot launch it yet. (You can designate when fireworks are locked using the connectedFireworks array in selection.ino)
4. Pressing the "left" and "right" buttons will move the cursor left and right.
5. Pressing the "select" button will display "Firing firework"
6. The current circuit is not attached to a relay board, but that is the next step.

## To-Do List
* non-volatile memory so a reset of the system during a firework show won't lose current ignition progress.
* Add a safety toggle switch (covered rocker toggle switch) and a power switch with LED as a launch button. once a firework is selected, you will need to switch the safety switch, then the LED on the launch button will light. Pressing the launch button will then send the signal to the relay. (this is more for fun than anything else)
* Add i2c line to the 16-channel relay board.
ensure the i2c signal can travel the required length, and if not, find a way to make it work. Currently, the fireworks will be about 80 feet away.
* End splash screen for when all fireworks have been launched.

## Wish List
These are improvements I want to make to the project, but may not make it in for the July 2019 festivities.
* Admin menu for choosing which fireworks to lock, or manually reset for launching again.
* Sound board for sound effects during power on, splash screen, and selection screen
* Support for expansion of multiple Relay boards
* Admin ability to launch all remaining fireworks at the same time, or to launch an entire bank of fireworks at the same time.
* Remote control via wifi or bluetooth
