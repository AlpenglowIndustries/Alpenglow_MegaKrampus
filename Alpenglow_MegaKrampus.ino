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

#define TONGUE1 44
#define TONGUE2 45
#define TONGUE3 46
#define TONGUE4 47
#define TONGUESTART 44
#define TONGUEEND 48


void setup() {
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN, OUTPUT);
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
  pinMode(TONGUE1, OUTPUT);
  pinMode(TONGUE2, OUTPUT);
  pinMode(TONGUE3, OUTPUT);
  pinMode(TONGUE4, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  allChase();

}

void allChase() {
  int i;
  for (i = EYELSTART; i < EYELEND; i++) {
    digitalWrite(i, HIGH);
    digitalWrite(i+6, HIGH);
    if (i < EYELSTART+4) {
      digitalWrite(TONGUESTART + i - EYELSTART, HIGH);
    }
    delay(100);
  }
  delay(250);
  for (i = EYELSTART; i < EYELEND; i++) {
    digitalWrite(i, LOW);
    digitalWrite(i+6, LOW);
    if (i < EYELSTART+4) {
      digitalWrite(TONGUESTART + i - EYELSTART, LOW);
    }
    delay(100);
  }
  delay(250);
}

void eyeChaseTongueBlink() {
  int i;
  for (i = EYELSTART; i < EYEREND; i++) {
    if (i == EYERSTART) {
      digitalWrite(TONGUE1, HIGH);
      digitalWrite(TONGUE2, HIGH);
      digitalWrite(TONGUE3, HIGH);
      digitalWrite(TONGUE4, HIGH);
    }
    digitalWrite(i, HIGH);

    delay(100);
  }
  for (i = EYELSTART; i < EYEREND; i++) {
    if (i == EYERSTART) {
      digitalWrite(TONGUE1, LOW);
      digitalWrite(TONGUE2, LOW);
      digitalWrite(TONGUE3, LOW);
      digitalWrite(TONGUE4, LOW);
    }
    digitalWrite(i, LOW);
    delay(100);
  }
}
