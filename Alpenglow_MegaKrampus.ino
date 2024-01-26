/*
Alpenglow MegaKrampus
by Carrie Sundra
started 01/07/2024
last updated 01/26/2024

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

*/

// Note that R and L are body R/L according to Krampus' perspective.
// It totally wasn't a wiring error.

// Pin lists starting with 32/21/26 are for adafruit Huzzah32
// Pin lists starting with 2/8/44 are for ATMega2560

#define EYEL1 32  //2
#define EYEL2 15  //3
#define EYEL3 33  //4
#define EYEL4 27  //5
#define EYEL5 12  //6
#define EYEL6 13  //7

#define EYER1 21   //8
#define EYER2 17   //9
#define EYER3 16   //10
#define EYER4 19   //11
#define EYER5 18   //12
#define EYER6 5   //13

#define TONGUER 26 //44  // right tongue nOOd
#define TONGUEL 25 //45  // left tongue nOOd
#define TONGUEM 23 //46  // middle tongue nOOd
#define TONGUET 22 //47  // top tongue nOOd, not a pwm pin on ATMEGA 2560

#define INTERVAL  10000 // milliseconds

int LEye[] = {EYEL1, EYEL2, EYEL3, EYEL4, EYEL5, EYEL6};
int REye[] = {EYER1, EYER2, EYER3, EYER4, EYER5, EYER6};
int Eyes[] = {EYEL1, EYEL2, EYEL3, EYEL4, EYEL5, EYEL6, EYER1, EYER2, EYER3, EYER4, EYER5, EYER6};
int Tongue[] = {TONGUER, TONGUEL, TONGUEM, TONGUET};
int lenEye = sizeof(LEye)/sizeof(LEye[0]);
int lenEyes = sizeof(Eyes)/sizeof(Eyes[0]);
int lenTongue = sizeof(Tongue)/sizeof(Tongue[0]);

void setup() {
 // pinMode(LED_BUILTIN, OUTPUT);  // built-in LED shares pin with EYEL6

  int i;
  for (i = 0; i < lenEyes; i++) {
    pinMode(Eyes[i], OUTPUT);
  }
  for (i = 0; i < lenTongue; i++) {
    pinMode(Tongue[i], OUTPUT);
  }
  allOFF();
}


void loop() {

  static uint32_t patternTime = millis();
  static int pattern = 0;
  if (millis() - patternTime > INTERVAL) {
    patternTime = millis();
    pattern = (pattern + 1) % 8;
  }

  switch (pattern) {
    case 0:
    fireball();
    break;
    case 1:
    lick();
    break;
    case 2:
    pulseEyesFlashTongue();
    break;
    case 3:
    allPulse();
    break;
    case 4:
    allChase();
    break;
    case 5:
    eyeChaseTongueBlink();
    break;
    case 6:
    wink();
    break;
    case 7:
    circumspect();
    break;
  }

  // for still photo shoots, uncomment one pattern below and comment out all of the above
  //allOnEyesDim();
  //fireballStill();

}

void allOFF() {  // turns everything off
  int i;
  for (i = 0; i < lenTongue; i++) {
    pinMode(Tongue[i], OUTPUT);       // needed for ESP32 - once analogWrite is used, cannot go back to digitalWrite
    digitalWrite(Tongue[i], LOW);
  }
  for (i = 0; i < lenEyes; i++) {
    pinMode(Eyes[i], OUTPUT);
    digitalWrite(Eyes[i], LOW);
  }
}

void fireball() {  // creates a fireball array with "Intensity" and moves it by changing the position array
  int i;
  int j;
  int tongue = 0;
  int EyeRArray[] = {EYER1, EYER2, EYER3, EYER4, EYER5, EYER6};
  int EyeLArray[] = {EYEL1, EYEL2, EYEL3, EYEL4, EYEL5, EYEL6};
  int Intensity[] = {0, 0, 5, 15, 45, 100};
  int TongueArray[] = {TONGUER, TONGUEL, TONGUEM, TONGUER, TONGUEL, TONGUEM}; // 2 repeats of the 3 PWM-enabled tongue LEDs
  for(i = 0; i < 6; i++) {  
    if (i > 0) {  // on all loops except the first one, moves the start position.  Guess I could have put this at the end of the loop instead.
      int tempR = EyeRArray[0];
      int tempL = EyeLArray[0];
      int tempT = TongueArray[0];
      int n;
      for (n = 0; n < 5; n++) {
        EyeRArray[n] = EyeRArray[n+1];
        EyeLArray[n] = EyeLArray[n+1];
        TongueArray[n] = TongueArray[n+1];
      }
      EyeRArray[5] = tempR;
      EyeLArray[5] = tempL;
      TongueArray[5] = tempT;
    }
    tongue = !tongue;
    for (j = 0; j < 6; j++) {  // writes the fireball "frame" out to the LEDs
      analogWrite(EyeRArray[j], Intensity[j]);
      analogWrite(EyeLArray[j], Intensity[j]);
      analogWrite(TongueArray[j], Intensity[j]);  // doesn't really show up on the tongue, looks just like a cycle  
      digitalWrite(TONGUET, tongue);  // just toggles the top tongue
    }
    delay(167);
  }
  allOFF();  // everything to OFF
}

void lick() {
  int i;
  int j;
  for (i = 0; i < 255; i++) {  // outside outline of tongue quickly lights up to full
    analogWrite(TONGUEL, i);
    analogWrite(TONGUER, i);
    delay(2);
  }
  delay(250);
  for (i = 0; i < 255; i++) {  // middle gives a nice slow drag to full brightness
    analogWrite(TONGUEM, i);
    delay(5);
  }
  delay(250);
  digitalWrite(TONGUET, HIGH);  // top and eyes suddenly light to full
  for (j = 0; j < lenEye; j++) {
    digitalWrite(REye[j], HIGH);
    digitalWrite(LEye[j], HIGH);
  }
  delay(2000);
  allOFF();
  // analogWrite(TONGUEL, LOW);
  // analogWrite(TONGUER, LOW);
  // analogWrite(TONGUEM, LOW);  
  delay(1000);
}

void pulseEyesFlashTongue() {
  int i;
  int j;
  int tongue = 1;
  for (i = 0; i < 255; i++) {  // eyes increase to full on
    for (j = 0; j < lenEyes; j++) {
      analogWrite(Eyes[j], i);
    }
    if (i % 10 == 0) {  // tongue toggles every 10 PWM steps for flicker
      tongue = !tongue;
      for (j = 0; j < lenTongue; j++) {
        digitalWrite(Tongue[j], tongue);        
      }
    }
    delay(5);
  } 
  
  for (i = 0; i < lenEyes; i++) {  // everything full ON
    digitalWrite(Eyes[i], HIGH);
  }  
  tongue = 1;
  for (i = 0; i < lenTongue; i++) {
    digitalWrite(Tongue[i], tongue);        
  }

  delay(1000);

  for (i = 255; i >= 0; i--) {  // eyes decrease to full off
    for (j = 0; j < lenEyes; j++) {
      analogWrite(Eyes[j], i);
    }
    if (i % 10 == 0) {  // tongue toggles every 10 PWM steps for flicker
      tongue = !tongue;
      for (j = 0; j < lenTongue; j++) {
        digitalWrite(Tongue[j], tongue);        
      }
    }
    delay(5);
  } 
  allOFF(); // everything full off
  delay(1000);
}

void pulseON() {
  int i;
  int j;
  for (i = 0; i < 255; i++) {  // increases eyes and tongue
    for (j = 0; j < lenEyes; j++) {
      analogWrite(Eyes[j], i);
      if (j < lenTongue-1) {
        analogWrite(Tongue[j], i);
      }
      if (i >= 42) digitalWrite(TONGUET, HIGH);  // turns on single non-PWM tongue LED after a little bit
    }
    delay(5);
  } 
  for (j = 0; j < lenEyes; j++) {   // everything full ON
    digitalWrite(Eyes[j], HIGH);
    if (j < lenTongue) {
      digitalWrite(Tongue[j], HIGH);
    }
  }  
}

void pulseOFF() {
  int i;
  int j;
  for (i = 255; i >= 0; i--) {  // decreases eyes and tongue
    for (j = 0; j < lenEyes; j++) {
      analogWrite(Eyes[j], i);
      if (j < lenTongue-1) {
        analogWrite(Tongue[j], i);
      }
      if (i <= 50) digitalWrite(TONGUET, LOW);  // turns off single non-PWM tongue LED after a little bit
    }
    delay(5);
  } 
  allOFF();  // everything full OFF
}

void allPulse() {
  pulseON();
  delay(1000);
  pulseOFF();
  delay(1000);
  allOFF();
}

void allChase() {  // a circular "wipe" pattern
  int i;
  int TongueArray[] = {TONGUEM, TONGUET, TONGUEL, TONGUER};
  for (i = 0; i < lenEye; i++) {  // left and right eyes go on one by one simultaneously
    digitalWrite(REye[i], HIGH);
    digitalWrite(LEye[i], HIGH);
    if (i < lenTongue) {  // cycles tongue LEDs high for the first 4 of the 6 eye cycles
      digitalWrite(TongueArray[i], HIGH);
    }
    delay(100);
  }
  for (i = 0; i < lenEye; i++) {  // left and right eyes go off one by one simultaneously
    digitalWrite(REye[i], LOW);
    digitalWrite(LEye[i], LOW);
    if (i < lenTongue) {  // cycles tongue LEDs low for the first 4 of the 6 eye cycles
      digitalWrite(TongueArray[i], LOW);
    }
    delay(100);
  }
  allOFF();
}

void eyeChaseTongueBlink() {  // a circular "wipe" pattern
  int i;
  for (i = 0; i < lenEyes; i++) {  // eyes go on one by one, left then right, in a circle
    digitalWrite(Eyes[i], HIGH);
    delay(100);
  }
  for (i = 0; i < lenTongue; i++) {  // tongue on
    digitalWrite(Tongue[i], HIGH);        
  }
  delay(100);

  for (i = 0; i < lenEyes; i++) {  // eyes go off one by one, left then right, in a circle
    digitalWrite(Eyes[i], LOW);
    delay(100);
  }
  for (i = 0; i < lenTongue; i++) {  // tongue off
    digitalWrite(Tongue[i], LOW);        
  }
  delay(100);

  allOFF();
}

void wink() {  

  pulseON();
  delay(200);  // wink starting from top to bottom, then bottom to top 
  analogWrite(EYEL3, LOW);
  analogWrite(EYEL4, LOW);
  delay(50);
  analogWrite(EYEL2, LOW);
  analogWrite(EYEL5, LOW);
  delay(50);
  analogWrite(EYEL1, LOW);
  analogWrite(EYEL6, LOW);
  delay(500);
  analogWrite(EYEL1, 255);
  analogWrite(EYEL6, 255);
  delay(50);
  analogWrite(EYEL2, 255);
  analogWrite(EYEL5, 255);
  delay(50);
  analogWrite(EYEL3, 255);
  analogWrite(EYEL4, 255);
  delay(200);
  pulseOFF();
  allOFF();  // everything full OFF
  delay(500);
}

void circumspect() {
  int i;
  for (i = 0; i < lenTongue; i++) {  // tongue on
    digitalWrite(Tongue[i], HIGH);        
  }
  digitalWrite(EYEL6, HIGH);
  digitalWrite(EYER6, HIGH);
  delay(1000);
  digitalWrite(EYEL6, LOW);
  digitalWrite(EYER6, LOW); 
  for (i = 0; i < 2; i++) {
    digitalWrite(REye[i], HIGH);
    digitalWrite(LEye[i], HIGH);
    delay(30);
    digitalWrite(REye[i], LOW);
    digitalWrite(LEye[i], LOW);
    delay(30);
  }
  digitalWrite(EYEL3, HIGH);
  digitalWrite(EYER3, HIGH);
  delay(2000);
  digitalWrite(EYEL3, LOW);
  digitalWrite(EYER3, LOW);
  digitalWrite(EYEL1, HIGH);
  digitalWrite(EYER1, HIGH);
  delay(500);
  digitalWrite(EYEL1, LOW);
  digitalWrite(EYER1, LOW);
  digitalWrite(EYEL4, HIGH);
  digitalWrite(EYER4, HIGH);
  delay(500);
  digitalWrite(EYEL4, LOW);
  digitalWrite(EYER4, LOW);
  digitalWrite(EYEL6, HIGH);
  digitalWrite(EYER6, HIGH);
  delay(2000);
}

void allONeyesDim() {  // for still photos, eyes dim, tongue full ON
int i;
int dim = 64;
  for (i = 0; i < lenEyes; i++) {
    analogWrite(Eyes[i], dim);
  }
  for (i = 0; i < lenTongue; i++) {
    digitalWrite(Tongue[i], HIGH);        
  }
}

void fireballStill() {  // for still photos, a freeze frame of a fireball, tongue full ON
  int i;
  int EyeRArray[] = {EYER1, EYER2, EYER3, EYER4, EYER5, EYER6};
  int EyeLArray[] = {EYEL1, EYEL2, EYEL3, EYEL4, EYEL5, EYEL6};
  int Intensity[] = {0, 0, 5, 15, 45, 100};
  int TongueArray[] = {TONGUER, TONGUEL, TONGUEM, TONGUER, TONGUEL, TONGUEM}; 
  for(i = 0; i < 6; i++) {
      analogWrite(EyeRArray[i], Intensity[i]);
      analogWrite(EyeLArray[i], Intensity[i]);
      analogWrite(TongueArray[i], 64);
  }
  for (i = 0; i < lenTongue; i++) {
    digitalWrite(Tongue[i], HIGH);        
  }
}
