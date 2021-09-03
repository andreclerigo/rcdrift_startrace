#include <IRremote.h>

const int ir_pin = 6;
const int speaker_pin = 7;
const int greens[] = {3, 4, 5};
const int reds[] = {8, 9, 10};
int pin;

IRrecv irrecv(ir_pin);

void(* resetFunc) (void) = 0;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver

  // speaker pin
  pinMode(7, OUTPUT);
  // red lights
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  // green lights
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void greenLight() {
  tone(speaker_pin, 750);
  digitalWriteArray(greens, HIGH);
  delay(1000);
  
  noTone(speaker_pin);
  delay(5000);
  digitalWriteArray(greens, LOW);
}

void countDown(int pin) {
  tone(speaker_pin, 600);
  digitalWrite(pin, LOW);
  delay(500);
  noTone(speaker_pin);
  delay(500);
}

void digitalWriteArray(const int pins[], bool val) {
  for (int i = 0; i < 3; i++)
    digitalWrite(pins[i], val);
}

void loop() {
  digitalWriteArray(reds, LOW);
  if (IrReceiver.decode()) {
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(code, HEX);
    
    if (code == 0xF50A7F00 || code == 0xBC43FF00) {
      digitalWriteArray(reds, HIGH);
      delay(5000);
      
      for(pin = 8; pin < 11; pin++)
        countDown(pin);
    
      greenLight();
      resetFunc();
    }
    irrecv.resume(); // Receive the next value
  }
}
