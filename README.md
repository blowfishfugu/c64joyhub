# c64joyhub

attach db9-joystick on leonardo/micropro-usb

## pinlayout

    frontplug
    DB9: UP 1, DOWN 2, LEFT 3, RIGHT 4, VOID 5
           FIRE 6, VCC 7, GND 8, VOID 9

    promicro/leonardo (wiring in code)
    pins joy1 : UP=2 DOWN=3 LEFT=4 RIGHT=5 FIRE=6
    pins joy2 : UP=10 DOWN=16 LEFT=14 RIGHT=15 FIRE=9

pins on leonardo are configured to pull-up,

joystick-buttons/directions will pull to ground.

VCC is optional, it's only used by joysticks with integrated auto-fire-circuits.

## boards.txt

    separate device-name and productname by extending boards.txt 
    ( also here is an additional vid/pid to let the second joystick appear as separate device )
    usually found in -> AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6
    first three device-ids should stay the same, otherwise keyboard/mouse and bootloader will be missing
    bootloader can be reattached by changing driver back
    to AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6\drivers "arduino.inf"
    
    After modifying boards.txt a restart of arduino-ide is required,
    "JoyController" should be selectable as targetboard after that.

## joystick.h

Joystick.h:

    Download https://github.com/MHeironimus/ArduinoJoystickLibrary/archive/master.zip
    In the Arduino IDE, select Sketch > Include Library > Add .ZIP Library....
    Browse to where the downloaded ZIP file is located and click Open.
    The Joystick library's examples will now appear under File > Examples > Joystick.
