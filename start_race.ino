#include <IRremote.h>

const int ir_pin = 0;
const int speaker_pin = 2;
const int green = 13;
const int red3 = 12;
const int red2 = 11;
const int red1 = 10;
const int reds[] = {10, 11, 12};
int BassTab[]={1911,1702,1516,1431,1275,1136,1012};
int pin;

IRrecv irrecv(ir_pin);

void(* resetFunc) (void) = 0;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver

  pinMode(ir_pin, OUTPUT);
  pinMode(speaker_pin, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(red3, OUTPUT);
  digitalWrite(speaker_pin, LOW);
}

void greenLight() {
  tone(speaker_pin, 750);
  digitalWrite(green, HIGH);
  delay(1000);
  
  noTone(speaker_pin);
  delay(5000);
  digitalWrite(green, LOW);
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
      
      for(pin = 10; pin < 13; pin++)
        countDown(pin);
    
      greenLight();
      resetFunc();
    }
    irrecv.resume(); // Receive the next value
  }
}
