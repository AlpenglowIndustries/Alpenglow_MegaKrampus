# Alpenglow_MegaKrampus
by Carrie Sundra
01/07/2024

The MegaKrampus is a giant laser-etched version of our Krampus
twist-together kit.  Eyes and tongue are etched instead of cut out.
There are 6 LEDs for each eye and 4 LEDs for the tongue for a total
of 16 LEDs.  I happened to have an Arduion Mega 2560 on hand
(actually my first Arduino and progenitor of the SkeinMinder)
and since it has 15 PWMs, I used it.

Each eye is a 6-in-one 20mm dome LED, where each of the 6 LEDs
are red and individually controllable via a 12-pin 0.6" wide DIP package.
I got these sweet LEDs for $1 each at All Electronics (RIP, sob!), and the
only place I've been able to find them is for $6 each and a min buy of 25
from https://www.ledtronics.com/Products/ProductsDetails.aspx?WP=282
and the only ones in stock have a diffused lens:
https://www.ledtronics.com/Products/ProductsDetails.aspx?WP=281


The tongue is made of 4 300mm red LED noods from adafruit.
Since they can pull more current (50 mA) each and I didn't want to
be limited to low brightness, I controlled each of them with a
transistor instead of driving them directly from the processor pins
(which the eyes are). https://www.adafruit.com/product/5506

There's a breadboard on the back with current-limiting resistors for 
all LEDs and the aforementioned transistors for noods.  Wires
connect it to the Mega 2560 which is also on the back.

The horns, teeth, and tongue are painted with a silver glitter paint.
The whole thing is coated with a clear gloss enamel spray.