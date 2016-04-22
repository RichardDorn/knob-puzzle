# Knob Puzzle

![Breadboard-View Schematic](breadboard-view.PNG)
![Top Finsihed Knob Puzzle](build-pics/8-top-complete.JPG)
![Front Finished Knob Puzzle](build-pics/7-front-complete.JPG)

This is my first arduino build outside of the starter kit and my first real attempt at coding in general. It is a puzzle game in which players must figure out the relationship between 4 knobs to move a single servo 180 degrees from left to right with the aid of an lcd displaying the current angle.

The game can be played in Campaign Mode or Random Mode. Campaign consists of 10 levels and an "easter egg" to access the credits after beating the final level. Random not only randomizes the level order but also the knob assignment within each level.
**I have tried to document the source code as clearly as possible. Most functionality questions are answered there.**

The plastic components were designed in tinkercad and printed on a friend's DaVinci Jr. The finished product is 6" x 3.5" x 4". Total print time was 55-60 hours. [Box](https://www.tinkercad.com/things/bzaXPIe8NDD-box/edit), [Lid](https://www.tinkercad.com/things/7vqB7K1yFgU-lid/edit), [Pot Mounts](https://www.tinkercad.com/things/hdNZIUxdLzm-pot-mounts/edit)

Putting everything together proved to be more difficult than I expected mainly because I didn't solder every connection. It was difficult to stuff the 22AWG wire inside without dislodging some of the breadboard connections. I had originally planned to screw the lid on but didn't have the hardware when I started building. After the frustration of making everything fit I just hot glued it on.

I think it still came out nice. It feels sturdy, has nice weight to it and the visibile glue doesn't really detract too much.

## This repository includes:
  * Source Code
  * Breadboard-View Schematic
  * Pictures of the build process
  * .stl files for 3d printing the box, lid and potentiometer mounts

## Coming Soon:
  * I'll try to get a good video playthrough made

## Components List:
  * 1 x Arduino Uno (Chinese clone ~$2.60)
  * 2 x 170 tie-point mini-breadboards (~$0.75)
  * ~90 meters x XYZ Printing DaVinci Jr. PLA filament ($12.60)
  * 1 x 16x2 LCD display (eBay ~$2.50)
  * 1 x 9g servo motor (The one that comes with arduino starter kit)
  * 2 x LEDs: 1 green, 1 red
  * 2 x momentary switches
  * 4 x 16mm 10K-ohm linear potentiometers (~$8)
  * 1 x small 10K-ohm linear potentiometer (Came with starter kit. Used here to control contrast of lcd.)
  * 4 x 19mm plastic knob covers (~$8)
  * 5 x resistors: 3 220-ohm, 2 10K-ohm
  * Various wire and jumpers
  * * I also bought a nice adaptor that fits between a wall wart and arduino to give it a nice on/off switch for about $2. (Not pictured above.)

## Room for improvement:
  * My measurements for all the components were a few mm off. This made it necessary to file the plastic down in many places in order to make things fit. I suggest measuring your own components and adjusting the .stl files accordingly.
  
  * Due to time limitations on the available printer the box had to be split into 2 prints then glued together. The fit is less than perfect. I left the unsplit box in the box.stl file incase print time isn't an issue.
 
  * A big improvement to the UX could be made by redesigning the box with the potentiometers mounted vertically out of the face of the box. If you're a lefty its no big deal but for the majority who will manipulate the knobs with their right hand, the servo becomes difficult to see.
 
  * Similar improvement could be made to the lcd. You must be looking from a birds-eye view to see the screen. Mounting it with a slight tilt would make playing much more relaxing.
 
  * The code can still be streamlined with a little work. Currently the levels are written twice... once for campaign and again for random mode.

  * Would be great to add sd functionality and easily switch between "level packs" rather than upload new code to arduino each time.

  * Using smaller 18AWG wire might make it easier to stuff inside the small box.
