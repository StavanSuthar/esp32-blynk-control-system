#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_BLYNK_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// Segment pins (Common Anode)
int segPins[7] = {23,22,21,19,18,5,4};

// Digit patterns (Common Anode: LOW = ON)
int digits[10][7] = {
  {0,0,0,0,0,0,1}, // 0
  {1,0,0,1,1,1,1}, // 1
  {0,0,1,0,0,1,0}, // 2
  {0,0,0,0,1,1,0}, // 3
  {1,0,0,1,1,0,0}, // 4
  {0,1,0,0,1,0,0}, // 5
  {0,1,0,0,0,0,0}, // 6
  {0,0,0,1,1,1,1}, // 7
  {0,0,0,0,0,0,0}, // 8
  {0,0,0,0,1,0,0}  // 9
};

void displayDigit(int num) {
  for(int i=0; i<7; i++) {
    digitalWrite(segPins[i], digits[num][i]);
  }
}

// Runs when slider changes
BLYNK_WRITE(V0) {
  int value = param.asInt();   // 0–9
  displayDigit(value);
}

void setup() {
  for(int i=0;i<7;i++){
    pinMode(segPins[i], OUTPUT);
    digitalWrite(segPins[i], HIGH); // OFF initially
  }

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}
