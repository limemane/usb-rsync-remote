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
#define DO_ACTION           "0-DOACTION="
#define DO_ACTION_LENGTH    11
#define SHOW_DATA           "1-SHOWDATA="
#define SHOW_DATA_LENGTH    11
#define END_OF_TASK         "2-ENDOFTASK="
#define END_OF_TASK_LENGTH  12

////////////
//
// INIT  
//
////////////

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variable to read the status of push button
int button_state = 0;   

// Flag indicating if lauched task has been reported done
bool task_is_done = true;

void setup() {

  // Serial initialization
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial.flush();

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
  display.write("Ready");
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
  if (button_state == HIGH && task_is_done) {
    
    // Telling the user his command is being sent
    display.clearDisplay();
    display.setCursor(0, 0);
    display.write("Sending...");
    display.display();
    delay(1500);
    
    // Changing flag state to avoid multiple calls of the same task
    task_is_done = false;

    // Sending order
    Serial.println(DO_ACTION);
  }

  // Wait for something on serial interface
  if (Serial.available() > 0) {
    String serialRead = Serial.readString();
    serialRead.trim();

    if (serialRead.startsWith(SHOW_DATA)) {
      // Display received data on screen
      String rawData = serialRead.substring(SHOW_DATA_LENGTH, serialRead.length());
      display.clearDisplay();
      display.setCursor(0, 0);
      display.write(rawData.c_str());
      display.display();
    }
    else if (serialRead.startsWith(END_OF_TASK)) {
      // Display that the previously launched task is now done
      String rawData = serialRead.substring(END_OF_TASK_LENGTH, serialRead.length());
      display.clearDisplay();
      display.setCursor(0, 0);
      display.write("Done");
      display.display();

      // Changing flag state to allow the user to launch tasks again
      task_is_done = true;
    }
  }
}