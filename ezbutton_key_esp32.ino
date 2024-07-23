#include <EZButton.h>

#define BTN_0_PIN 35
#define BTN_0 0
#define BTN_1_PIN 34
#define BTN_1 1
#define BTN_2_PIN 39
#define BTN_2 2
#define BTN_3_PIN 36
#define BTN_3 3

const int led0 = 16;
const int led1 = 17;
const int led2 = 19;
const int led3 = 23;
const int ledT = 32;

boolean buttonState0 = false;
boolean buttonState1 = false;
boolean buttonState2 = false;
boolean buttonState3 = false;

void ReadButtons(bool *states, int num) {
  states[BTN_0] = digitalRead(BTN_0_PIN);
  states[BTN_1] = digitalRead(BTN_1_PIN);
  states[BTN_2] = digitalRead(BTN_2_PIN);
  states[BTN_3] = digitalRead(BTN_3_PIN);
}

EZButton _ezb(4, ReadButtons, 1000, 200);

void setup() {
  //initialize pins
  pinMode(BTN_0_PIN, INPUT);
  pinMode(led0, OUTPUT);
  pinMode(BTN_1_PIN, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(BTN_2_PIN, INPUT);
  pinMode(led2, OUTPUT);
  pinMode(BTN_3_PIN, INPUT);
  pinMode(led3, OUTPUT);
  pinMode(ledT, OUTPUT);

  //subscribe to needed events
  _ezb.Subscribe(BTN_0, Btn0Pressed, PRESSED);
  _ezb.Subscribe(BTN_0, Btn0Released, RELEASED);
  _ezb.Subscribe(BTN_0, Btn0Released, HOLD_RELEASED);
  _ezb.Subscribe(BTN_1, Btn1Pressed, PRESSED);
  _ezb.Subscribe(BTN_1, Btn1Released, RELEASED);
  _ezb.Subscribe(BTN_1, Btn1Released, HOLD_RELEASED);
  _ezb.Subscribe(BTN_2, Btn2Pressed, PRESSED);
  _ezb.Subscribe(BTN_2, Btn2Released, RELEASED);
  _ezb.Subscribe(BTN_2, Btn2Released, HOLD_RELEASED);
  _ezb.Subscribe(BTN_3, Btn3Pressed, PRESSED);
  _ezb.Subscribe(BTN_3, Btn3Released, RELEASED);
  _ezb.Subscribe(BTN_3, Btn3Released, HOLD_RELEASED);
}

void loop() {
  //EZButton loop
  _ezb.Loop(); 
}

void Btn0Pressed() {
  digitalWrite(led0, HIGH);
  buttonState0 = true;
}

void Btn0Released() {
  if (buttonState0 && !buttonState1 && !buttonState2 && !buttonState3) {
    turnOffAllLeds();
   digitalWrite(led0, HIGH); 
  }
  else {
    digitalWrite(led0, LOW); 
  }
  buttonState0 = false;
}

void Btn1Pressed() {
  digitalWrite(led1, HIGH);
  buttonState1 = true;
}

void Btn1Released() {
  if (!buttonState0 && buttonState1 && !buttonState2 && !buttonState3) {
    turnOffAllLeds();
   digitalWrite(led1, HIGH); 
  }
  else {
    digitalWrite(led1, LOW); 
  }
  buttonState1 = false;
}

void Btn2Pressed() {
  digitalWrite(led2, HIGH);
  buttonState2 = true;
}

void Btn2Released() {
  if (!buttonState0 && !buttonState1 && buttonState2 && !buttonState3) {
    turnOffAllLeds();
   digitalWrite(led2, HIGH); 
  }
  else {
    digitalWrite(led2, LOW); 
  }
  buttonState2 = false;
}

void Btn3Pressed() {
  digitalWrite(led3, HIGH);
  buttonState3 = true;
}

void Btn3Released() {
  if (!buttonState0 && !buttonState1 && !buttonState2 && buttonState3) {
    turnOffAllLeds();
   digitalWrite(led3, HIGH); 
  }
  else {
    digitalWrite(led3, LOW); 
  }
  buttonState3 = false;
}

void turnOffAllLeds() {
   digitalWrite(led0, LOW);
   digitalWrite(led1, LOW);
   digitalWrite(led2, LOW);
   digitalWrite(led3, LOW);
}
