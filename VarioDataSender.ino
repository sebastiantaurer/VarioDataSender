#include <MS5611.h>
#include <SoftwareSerial.h>

#define ledPin 13
#define rxPin 10
#define txPin 11

MS5611 baro;
int32_t pressure;
float pressure_filtered = 0;
boolean started = false;

SoftwareSerial btSerial(rxPin, txPin);
String btData;

void setup() {
  // put your setup code here, to run once:
  // Start barometer
  baro = MS5611();
  baro.begin();

  // Start Bluetooth
  btSerial.begin(9600);

  pinMode(ledPin,OUTPUT);
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(!started){
    if (btSerial.available()){
      btData = btSerial.readString();
      if(btData == "start"){
        started = true;
      }
    }
    btSerial.println("waiting");
    digitalWrite(ledPin,0);
    delay(1000);
  }

  digitalWrite(ledPin,1);
  while(started){
    btSerial.println(baro.getPressure());
  }
}
