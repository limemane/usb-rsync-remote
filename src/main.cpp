#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED constants
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1 

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int push_button = 25; // push button is connected to pin number 25
int button_state = 0;   // variable to read the status of push button

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(20);
  pinMode(push_button, INPUT);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Initialize screen
  display.clearDisplay();
  display.setTextSize(2);      // 2:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.display();
}

void loop() {
  button_state = digitalRead(push_button);

  if (button_state == HIGH) {
    delay(500);
    Serial.println("0-DOACTION");
  }

  if (Serial.available() > 0) {
    String str = Serial.readString();
    str.trim();
    Serial.print("Data received : ");
    Serial.println(str);

    if (str == "1-SHOWDATA") {
      display.write("Hi daddy");
      display.display();
      delay(3000);
      display.setCursor(0, 0);
      display.clearDisplay();
      display.display();
    }
  }
}