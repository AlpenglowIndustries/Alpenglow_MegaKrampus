# Alpenglow_MegaKrampus
by Carrie Sundra
01/07/2024

The MegaKrampus is a giant laser-etched version of our Krampus
twist-together kit.  Eyes and tongue are etched instead of cut out.
There are 6 LEDs for each eye and 4 LEDs for the tongue for a total
of 16 LEDs.  

I first used an Arduino Mega2560 which only has 15 PWMs, so the code
is written with the top of the tongue behaving as a simple digital
i/o pin.  It was buggging me, so I replaced the processor with an
adafruit Huzzah32 which uses an ESP32 processor, so all 16 PWMs are
now supported.  I haven't updated the code yet to include that
last tongue LED in the PWMs.

Each eye is a 6-in-one 20mm dome LED, where each of the 6 LEDs
are red and individually controllable via a 12-pin 0.6" wide DIP package.
I got these sweet LEDs for $1 each at All Electronics (RIP, sob!), and the
only place I've been able to find them is for $6 each and a min buy of 25
from https://www.ledtronics.com/Products/ProductsDetails.aspx?WP=282
and the only ones in stock have a diffused lens:
https://www.ledtronics.com/Products/ProductsDetails.aspx?WP=281

Eyeball LEDs are driven directly from the ESP32 pins at 3.3V,
they have 220 ohm resistors inline, approx 7 mA per LED.

The tongue is made of 4 300mm red LED noods from adafruit.
https://www.adafruit.com/product/5506

Since they can pull more current (50 mA) each and I didn't want to
be limited to low brightness, I controlled each of them with an 
N channel transistor which switches GND.  Noods are 3V devices,
their positive source is USB 5V, with 100 ohm resistors inline.
So 20 mA per nood, adafruit says their max is 50 mA.

There's a breadboard on the back with current-limiting resistors for 
all LEDs and the aforementioned transistors for noods.  Wires
connect it to the Huzzah32 which is also on the back.  Large 1.25"
bumpers are glued to the back to keep the wiring from being
squished.

The horns, teeth, and tongue are painted with a silver glitter paint.
The whole thing is coated with a clear gloss enamel spray.

The shapes of the circle of LEDs for eyes and squiggly noodles for tongue
really make it fun to animate and it really comes to life!
