#include<SoftwareSerial.h>
SoftwareSerial BLE_DEVICE(2, 3);
#define relayPin 7
#define moistureSensorPin A4
#define lightmoistureSensorPin A1
int moisture = 0;
int light = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Started");
  BLE_DEVICE.begin(9600);
  pinMode(relayPin, OUTPUT);
  // Make sure relay is off initially
  digitalWrite(relayPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  sendMoistureData();
  sendLightData();
  relayControl();
  delay(5000);
}

// Normalize to 8bit data at receiver
int normalize(int val) {
  return 256 * val / 1024;
}

void sendMoistureData() {
  moisture = analogRead(moistureSensorPin);
  BLE_DEVICE.write(normalize(moisture));
}

void sendLightData() {
  light = analogRead(lightmoistureSensorPin);
  BLE_DEVICE.write(normalize(light));
}

void relayControl() {
    if (BLE_DEVICE.available() > 0) {
    Serial.println(BLE_DEVICE.available());
    char rec = char(BLE_DEVICE.read());
    if (rec == '1') {
      digitalWrite(relayPin, LOW);
    } else{
      digitalWrite(relayPin, HIGH);
    }
  } else {
    Serial.println("Not Available");
  }
}
