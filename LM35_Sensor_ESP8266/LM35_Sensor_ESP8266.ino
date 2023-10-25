#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "iEzOccbHiAx3dnYZxQtZX281xRWnozwy";
char ssid[] = "prateeksingh";
char pass[] = "kumar@12345";

BlynkTimer timer;

#define Buzzer D1
#define Green D3
#define Red D2
#define Sensor A0

float vref = 3.3;
float resolution = vref/1023;

void setup() {
  Serial.begin(9600);
  pinMode(Green, OUTPUT);
  pinMode(Red, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Sensor, INPUT);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void sensor() {
  
 float temperature = analogRead(A0);
 temperature = (temperature*resolution);
 temperature = temperature*100;
 Serial.println(temperature);
Blynk.virtualWrite(V2, temperature);

if (temperature <= 35) {
    digitalWrite(Green, HIGH);
    digitalWrite(Red, LOW);
    digitalWrite(Buzzer, LOW);
    WidgetLED LED(V0);
    LED.on();
     WidgetLED LED1(V1);
    LED1.off();
  } else {
    Blynk.notify("Warning! Gas leak detected");
    digitalWrite(Green, LOW);
    digitalWrite(Red, HIGH);
    digitalWrite(Buzzer, HIGH);
    WidgetLED LED(V0);
    LED.off();
    WidgetLED LED1(V1);
    LED1.on();
  }
}
void loop() {
  sensor();
  Blynk.run();
  delay(200);
}