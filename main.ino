#include <SoftwareSerial.h>

// SOFTWARE SERIAL
SoftwareSerial Bluetooth(12, 13); // RX, TX

byte directionPin = 2;
byte stepPin = 3;
int numberOfSteps = 400;
byte ledPin = 13;
int pulseWidthMicros = 20;  // microseconds
int millisbetweenSteps = 23; // milliseconds
int microsbetweenSteps = 436; // microseconds (total is 23436)

bool stringComplete = false;
String inputString = "";

byte m0 = 6;
byte m1 = 7;
byte m2 = 8;

void setup() { 

  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(m0, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);

  delay(1000);

  digitalWrite(ledPin, HIGH);
  digitalWrite(directionPin, LOW);

  digitalWrite(m0, LOW);
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);

  Serial.begin(9600);
  Bluetooth.begin(9600);
  // inputString.reserve(1);
  
}

void loop() {

    if (stringComplete) {
      Serial.print("Bluetooth command received");
      Serial.println();
      Serial.print(inputString.charAt(0));
      Serial.println();
      
      if (inputString.charAt(0) == '1')
      {
        delay(500);
        digitalWrite(directionPin, LOW);
        Serial.print("Backward direction selected!");
        delay(500);
      }
     
      if (inputString.charAt(0) == '2')
      {
        delay(500);
        digitalWrite(directionPin, HIGH);
        Serial.print("Forward direction selected!");
        delay(500);
      }
      
      if (inputString.charAt(0) == '3')
      {
        millisbetweenSteps = 23;
        microsbetweenSteps = 436;
        Serial.print("Tracking speed: ");
        Serial.print(millisbetweenSteps);
      }
      
      if (inputString.charAt(0) == '4')
      {
        millisbetweenSteps = 8;
        microsbetweenSteps = 0;
        Serial.print("Medium speed: ");
        Serial.print(millisbetweenSteps);
      }
      
      if (inputString.charAt(0) == '5')
      {
        millisbetweenSteps = 2;
        microsbetweenSteps = 0;
        Serial.print("Fast speed: ");
        Serial.print(millisbetweenSteps);
      }

      inputString = "";
      stringComplete = false;

    }

    digitalWrite(stepPin, HIGH);
    // delayMicroseconds(pulseWidthMicros); // this line is probably unnecessary
    digitalWrite(stepPin, LOW);

    // Serial.print('Step!');
    
    delay(millisbetweenSteps);
    delayMicroseconds(microsbetweenSteps);
    
    //digitalWrite(ledPin, !digitalRead(ledPin));

    btEvent();

}

void btEvent() {
  if (Bluetooth.available()) {
    char inChar = (char)Bluetooth.read();
    inputString += inChar;
    stringComplete = true;
  }
}
