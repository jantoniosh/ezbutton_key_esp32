#include <ezButton.h>

ezButton button0(35);
ezButton button1(34);  
ezButton button2(39);
ezButton button3(36);

const int led0 = 16;
const int led1 = 17;
const int led2 = 19;
const int led3 = 23;

int nPressed = 0;
int lastButton = 0;
int nButton;
int contador;

unsigned long previousTimeLed1 = millis();
long timeIntervalLed1 = 500;
int ledState1 = LOW;

int buttons[] = {4, 4, 4, 4};

void setup() {
  Serial.begin(115200);
  button0.setDebounceTime(50); // set debounce time to 50 milliseconds
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
  button2.setDebounceTime(50); // set debounce time to 50 milliseconds
  button3.setDebounceTime(50); // set debounce time to 50 milliseconds
  
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  nButton = 0;
  contador = 0;
}

void loop() {
  unsigned long currentTime = millis();
  button0.loop(); // MUST call the loop() function first
  button1.loop(); // MUST call the loop() function first
  button2.loop(); // MUST call the loop() function first
  button3.loop(); // MUST call the loop() function first

  int btn0State = button0.getState();
  int btn1State = button1.getState();
  int btn2State = button2.getState();
  int btn3State = button3.getState();

  if(button0.isPressed()) {
    minusButton();
    checkSpaces(0);
  }

  if(button0.isReleased()) {
    buttons[nPressed] = 0;
    plusButton();
    checkListButtons();
  }
  
  if(button1.isPressed()) {
    minusButton();
    checkSpaces(1);
  }

  if(button1.isReleased()) {
    buttons[nPressed] = 1;
    plusButton();
    checkListButtons();
  }

  if(button2.isPressed()){
    minusButton();
    checkSpaces(2);
  }

  if(button2.isReleased()) {
    buttons[nPressed] = 2;
    plusButton();
    checkListButtons();
  }

  if(button3.isPressed()) {
    minusButton();
    checkSpaces(3);
  }

  if(button3.isReleased()){
    buttons[nPressed] = 3;
    plusButton();
    checkListButtons();
  }
}

void plusButton() {
  offLeds();
  onLed(buttons[nPressed]);
  Serial.print("Encender Led: ");
  Serial.println(buttons[nPressed]);
  nPressed = nPressed + 1;
  Serial.println(nPressed);
}

void minusButton() {
  nPressed = nPressed - 1;
  if(nPressed <= 0) {
    nPressed = 0;
  }
  Serial.println(nPressed);
}

void checkSpaces(int n) {
  for (int i = 0; i < 4; i++) {
    if(n == buttons[i]) {
      buttons[i] = 4;
    }
  }
  if (nPressed >= 0) {
    for (int i = 0; i < 4; i++) {
      if(buttons[i] == 4) {
        for (int j = i; j < 4; j++) {
          if (buttons[j] < 4) {
            buttons[i] = buttons[j];
            buttons[j] = 4;
          }
        }
      }
    }
    if (nPressed == 0) {
      lastButton = n;
    }
    else {
      lastButton = buttons[nPressed - 1];
    }
    offLeds();
    onLed(lastButton);
    Serial.print("Mantener Led: ");
    Serial.println(lastButton);
  }
  checkListButtons();
}

void checkListButtons() {
  for(int i=0; i < 4; i++) {
    Serial.print(buttons[i]);
    Serial.print(",");
  }
  Serial.println();
}

void onLed(int n) {
  if (n == 0) {
    digitalWrite(led0, HIGH);
  }
  else if (n == 1) {
    digitalWrite(led1, HIGH);
  }
  else if (n == 2) {
    digitalWrite(led2, HIGH);
  }
  else if (n == 3) {
    digitalWrite(led3, HIGH);
  }
} 

void offLeds() {
  digitalWrite(led0, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}
