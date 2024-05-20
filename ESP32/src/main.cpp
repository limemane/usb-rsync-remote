#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

////////////
//
// CONSTANTS  
//
////////////

// OLED 
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 

// Button
#define PUSH_BUTTON   25

// Orders
#define DO_ACTION     "0-DOACTION="
#define SHOW_DATA     "1-SHOWDATA="

////////////
//
// INIT  
//
////////////

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// Variable to read the status of push button
int button_state = 0;   

void setup() {

  // Serial initialization
  Serial.begin(115200);
  Serial.setTimeout(10);

  // Push button initialization
  pinMode(PUSH_BUTTON, INPUT);

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

  // Tell the world I booted
  display.write("I booted");
  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();
}

////////////
//
// LOOP  
//
////////////

void loop() {

  // Write on serial interface when button pressed 
  button_state = digitalRead(PUSH_BUTTON);
  if (button_state == HIGH) {
    delay(500);
    Serial.println(DO_ACTION);
  }

  // When data received through serial interface, show what must be shown on screen
  if (Serial.available() > 0) {
    String serialRead = Serial.readString();
    serialRead.trim();

    if (serialRead.startsWith(SHOW_DATA)) {

      // Show received data for 3s
      String rawData = serialRead.substring(11, serialRead.length());
      display.write(rawData.c_str());
      display.display();
      delay(3000);
      display.setCursor(0, 0);
      display.clearDisplay();
      display.display();
    }
  }
}