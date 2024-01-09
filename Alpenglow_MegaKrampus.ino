/*
Alpenglow MegaKrampus
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

The shapes of the circle of LEDs for eyes and squiggly noodles for tongue
really make it fun to animate and it really comes to life!

*/

#define EYEL1 2
#define EYEL2 3
#define EYEL3 4
#define EYEL4 5
#define EYEL5 6
#define EYEL6 7
#define EYELSTART 2
#define EYELEND 8

#define EYER1 8
#define EYER2 9
#define EYER3 10
#define EYER4 11
#define EYER5 12
#define EYER6 13
#define EYERSTART 8
#define EYEREND 14

#define TONGUEL 44
#define TONGUER 45
#define TONGUEM 46
#define TONGUET 47  // not a pwm pin
#define TONGUESTART 44
#define TONGUEEND 48

#define INTERVAL  10000 // milliseconds

void setup() {
  // put your setup code here, to run once:

 // pinMode(LED_BUILTIN, OUTPUT);  // built-in LED shares pin with EYEL6
  pinMode(EYEL1, OUTPUT);
  pinMode(EYEL2, OUTPUT);
  pinMode(EYEL3, OUTPUT);
  pinMode(EYEL4, OUTPUT);
  pinMode(EYEL5, OUTPUT);
  pinMode(EYEL6, OUTPUT);
  pinMode(EYER1, OUTPUT);
  pinMode(EYER2, OUTPUT);
  pinMode(EYER3, OUTPUT);
  pinMode(EYER4, OUTPUT);
  pinMode(EYER5, OUTPUT);
  pinMode(EYER6, OUTPUT);
  pinMode(TONGUEL, OUTPUT);  // left tongue outline
  pinMode(TONGUER, OUTPUT);  // right tongue outline
  pinMode(TONGUEM, OUTPUT);  // middle tongue outline
  pinMode(TONGUET, OUTPUT);  // top short tongue outline

}

void loop() {

  // static uint32_t patternTime = millis();
  // static int pattern = 0;
  // if (millis() - patternTime > INTERVAL) {
  //   patternTime = millis();
  //   pattern = (pattern + 1) % 7;
  // }

  // switch (pattern) {
  //   case 0:
  //   fireball();
  //   break;
  //   case 1:
  //   lick();
  //   break;
  //   case 2:
  //   pulseEyesFlashTongue();
  //   break;
  //   case 3:
  //   allPulse();
  //   break;
  //   case 4:
  //   allChase();
  //   break;
  //   case 5:
  //   eyeChaseTongueBlink();
  //   break;
  //   case 6:
  //   wink();
  //   break;
  // }

  // for still photo shoots, uncomment one pattern below and comment out all of the above
  //allONeyesDim();
  //fireballStill();
  wink();

}

void allOFF() {  // turns everything off
  int j;
  digitalWrite(TONGUEL, LOW);
  digitalWrite(TONGUER, LOW);
  digitalWrite(TONGUEM, LOW);
  digitalWrite(TONGUET, LOW);
  for (j = EYELSTART; j < EYEREND; j++) {
    digitalWrite(j, LOW);
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
  int tongue = 1;
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
  for (j = EYELSTART; j < EYELEND; j++) {
    digitalWrite(j, HIGH);
    digitalWrite(j+6, HIGH);
  }
  delay(2000);
  allOFF();
  delay(1000);
}

void pulseEyesFlashTongue() {
  int i;
  int j;
  int tongue = 1;
  for (i = 0; i < 255; i++) {  // eyes increase to full on
    for (j = EYELSTART; j < EYEREND; j++) {
      analogWrite(j, i);
      analogWrite(j+6, i);
    }
    if (i % 10 == 0) {  // tongue toggles every 10 PWM steps for flicker
      tongue = !tongue;
      digitalWrite(TONGUEL, tongue);
      digitalWrite(TONGUER, tongue);
      digitalWrite(TONGUEM, tongue);
      digitalWrite(TONGUET, tongue);
    }
    delay(5);
  } 
  for (j = EYELSTART; j < EYEREND; j++) {  // everything full ON
    digitalWrite(j, HIGH);
  }  
  tongue = 1;
  digitalWrite(TONGUEL, tongue);
  digitalWrite(TONGUER, tongue);
  digitalWrite(TONGUEM, tongue);
  digitalWrite(TONGUET, tongue);

  delay(1000);

  for (i = 255; i >= 0; i--) {  // eyes decrease to full off
    for (j = EYELSTART; j < EYEREND; j++) {
      analogWrite(j, i);
      analogWrite(j+6, i);
    }
    if (i % 10 == 0) {  // tongue toggles every 10 PWM steps for flicker
      tongue = !tongue;
      digitalWrite(TONGUEL, tongue);
      digitalWrite(TONGUER, tongue);
      digitalWrite(TONGUEM, tongue);
      digitalWrite(TONGUET, tongue);
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
    for (j = EYELSTART; j < EYEREND; j++) {
      analogWrite(j, i);
      if (j < EYELSTART+3) {
        analogWrite(TONGUESTART + j - EYELSTART, i);
      }
      if (i >= 42) digitalWrite(TONGUET, HIGH);  // turns on single non-PWM tongue LED after a little bit
    }
    delay(5);
  } 
  for (j = EYELSTART; j < EYEREND; j++) {   // everything full ON
    digitalWrite(j, HIGH);
    if (j < EYELSTART+4) {
      digitalWrite(TONGUESTART + j - EYELSTART, HIGH);
    }
  }  
}

void pulseOFF() {
  int i;
  int j;
  for (i = 255; i >= 0; i--) {  // decreases eyes and tongue
    for (j = EYELSTART; j < EYEREND; j++) {
      analogWrite(j, i);
      if (j < EYELSTART+3) {
        analogWrite(TONGUESTART + j - EYELSTART, i);
      }
      if (i <= 50) digitalWrite(TONGUEEND-1, LOW);  // turns off single non-PWM tongue LED after a little bit
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
  int TongueArray[] = {TONGUEM, TONGUET, TONGUER, TONGUEL};
  for (i = 0; i < 6; i++) {  // left and right eyes go on one by one simultaneously
    digitalWrite(i+EYELSTART, HIGH);
    digitalWrite(i+EYERSTART, HIGH);
    if (i < EYELSTART+4) {  // cycles tongue LEDs high for the first 4 of the 6 eye cycles
      digitalWrite(TongueArray[i], HIGH);
    }
    delay(100);
  }
  for (i = 0; i < 6; i++) {  // left and right eyes go off one by one simultaneously
    digitalWrite(i+EYELSTART, LOW);
    digitalWrite(i+EYERSTART, LOW);
    if (i < EYELSTART+4) {  // cycles tongue LEDs low for the first 4 of the 6 eye cycles
      digitalWrite(TongueArray[i], LOW);
    }
    delay(100);
  }
  allOFF();
}

void eyeChaseTongueBlink() {  // a circular "wipe" pattern
  int i;
  for (i = EYELSTART; i < EYEREND; i++) {  // tongue on at beginning, eyes go on one by one, left then right, in a circle
    if (i == EYERSTART) {
      digitalWrite(TONGUEL, HIGH);
      digitalWrite(TONGUER, HIGH);
      digitalWrite(TONGUEM, HIGH);
      digitalWrite(TONGUET, HIGH);
    }
    digitalWrite(i, HIGH);
    delay(100);
  }
  for (i = EYELSTART; i < EYEREND; i++) {  // tongue goes off at beginning, eyes go off one by one, left then right, in a circle
    if (i == EYERSTART) {
      digitalWrite(TONGUEL, LOW);
      digitalWrite(TONGUER, LOW);
      digitalWrite(TONGUEM, LOW);
      digitalWrite(TONGUET, LOW);
    }
    digitalWrite(i, LOW);
    delay(100);
  }
  allOFF();
}

void wink() {  

  pulseON();
  delay(200);  // wink starting from top to bottom, then bottom to top
  digitalWrite(EYEL3, LOW);
  digitalWrite(EYEL4, LOW);
  delay(50);
  digitalWrite(EYEL2, LOW);
  digitalWrite(EYEL5, LOW);
  delay(50);
  digitalWrite(EYEL1, LOW);
  digitalWrite(EYEL6, LOW);
  delay(500);
  digitalWrite(EYEL1, HIGH);
  digitalWrite(EYEL6, HIGH);
  delay(50);
  digitalWrite(EYEL2, HIGH);
  digitalWrite(EYEL5, HIGH);
  delay(50);
  digitalWrite(EYEL3, HIGH);
  digitalWrite(EYEL4, HIGH);
  delay(200);
  pulseOFF();
  allOFF();  // everything full OFF
  delay(500);
}

void allONeyesDim() {  // for still photos, eyes dim, tongue full ON
int j;
int dim = 64;
  for (j = EYELSTART; j < EYEREND; j++) {
    analogWrite(j, dim);
  }
  digitalWrite(TONGUEL, HIGH);
  digitalWrite(TONGUER, HIGH);
  digitalWrite(TONGUEM, HIGH);
  digitalWrite(TONGUET, HIGH);
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
  digitalWrite(TONGUEL, HIGH);
  digitalWrite(TONGUER, HIGH);
  digitalWrite(TONGUEM, HIGH);
  digitalWrite(TONGUET, HIGH);
}
