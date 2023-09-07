#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  //Right
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  //Left
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}

// right = map(R, 345, 675, 0, 230);

void loop() {
  if (radio.available()) {
    float receivedData[2];
    radio.read(&receivedData, sizeof(receivedData));

    float Y = receivedData[0];
    float X = receivedData[1];

    Serial.print("Received y: ");
    Serial.print(Y);
    Serial.print(", x: ");
    Serial.println(X);

    if (Y >= 350) {
      int y = map(Y, 350, 680, 150, 250);
      analogWrite(13, y);
      analogWrite(12, 0);

      analogWrite(11, y);
      analogWrite(10, 0);
    }
    else if (Y < 350 && Y > 310) {
      analogWrite(13, 0);
      analogWrite(12, 0);

      analogWrite(11, 0);
      analogWrite(10, 0);
    }
    else if (Y <= 310) {
    int y = map(Y, 300, 0, 150, 250);
      analogWrite(13, 0);
      analogWrite(12, y);

      analogWrite(11, 0);
      analogWrite(10, y);
    }
    if (X >= 350) {
      int x = map(Y, 350, 680, 150, 250);
      analogWrite(13, 0);
      analogWrite(12, 0);

      analogWrite(11, x);
      analogWrite(10, 0);
    }
    else if (X <= 320) {
      int x = map(Y, 320, 0, 150, 250);
      analogWrite(11, 0);
      analogWrite(10, 0);

      analogWrite(13, x);
      analogWrite(12, 0);
    }

  }
  else {
    Serial.println("Connecting...");
  }
}
