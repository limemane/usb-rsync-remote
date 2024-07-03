#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <OLEDScreen.h>
#include <InitalizationException.h>

/*******************************************************
 * Constants
 ******************************************************/

// Button
#define PUSH_BUTTON   25

// Orders
#define CONNECTION_OK         "-CONNOK="
#define CONNECTION_OK_LENGTH  8
#define DO_ACTION             "-DOACTION="
#define DO_ACTION_LENGTH      11
#define SHOW_DATA             "-SHOWDATA="
#define SHOW_DATA_LENGTH      11
#define END_OF_TASK           "-ENDOFTASK="
#define END_OF_TASK_LENGTH    12

/*******************************************************
 * Init
 ******************************************************/

// OLED Screen manager
OLEDScreen * pDisplay = new OLEDScreen();

// Variable to read the status of push button
int button_state = 0;   

// Flag indicating if lauched task has been reported done
bool task_is_done = true;

/*******************************************************
 * Setup
 ******************************************************/

void setup() 
{
  // Setup serial communication
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial.flush();

  // Setup OLED Screen
  try 
  {
    pDisplay->init();
  }
  catch (InitializationException e) 
  {
    char * errorMessage = strcat(strdup("ERROR : "), e.what());
    Serial.println(errorMessage);
  }

  // Display default state
  pDisplay->writeMessage("Not connected");

  // Setup button
  pinMode(PUSH_BUTTON, INPUT);
}

/*******************************************************
 * Loop
 ******************************************************/

void loop() 
{
  // Wait for something on serial interface
  if (Serial.available() > 0) 
  {
    String serialRead = Serial.readString();
    serialRead.trim();

    if (serialRead.startsWith(CONNECTION_OK)) 
    {
      pDisplay->writeMessage("Connected !");
    }
    else if (serialRead.startsWith(SHOW_DATA)) 
    {
      String rawData = serialRead.substring(SHOW_DATA_LENGTH, serialRead.length());
      pDisplay->writeMessage(rawData.c_str());
    }
    else if (serialRead.startsWith(END_OF_TASK)) 
    {
      pDisplay->writeMessage("Done");
      // Changing flag state to allow the user to launch tasks again
      task_is_done = true;
    }
  }

  // Write on serial interface when button pressed 
  button_state = digitalRead(PUSH_BUTTON);
  if (button_state == HIGH && task_is_done) 
  {
    pDisplay->writeMessage("Sending...");
    delay(1500);

    // Changing flag state to avoid multiple calls of the same task
    task_is_done = false;

    Serial.println(DO_ACTION);
  }
}