#include <Servo.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include <DS3231.h>
#include <EEPROM.h>


// Initialize objects
Servo servo_mot;
hd44780_I2Cexp display;
DS3231 rtc(SDA, SCL);
Time t;

// Pin assignments
const int but1 = 2;
const int but2 = 5;
const int but3 = 4;
const int servo_pin = 9;
const int Buzzer = 6;

// State variables
bool state_but1 = true;
bool state_but2 = true;
bool state_but3 = true;

// Servo control angles
const int stop_angle = 0;
const int rotate_angle = 180;

// Feeding settings
int portions = 10;
int interval = 8;
const int max_portions = 20;
const int min_portions = 3;
const int portion_delay = 400;

// Time tracking
int Hour, Minute;
int last_feed_hour = 1;
int next_feed_hour = 1;
bool feed_active = true;

// Loop refresh rate
const int refresh_rate = 200;
unsigned int millis_before = 0;
unsigned int millis_now = 0;

void setup() {
    // Configure button inputs
    pinMode(but1, INPUT_PULLUP);
    pinMode(but2, INPUT_PULLUP);
    pinMode(but3, INPUT_PULLUP);
    
    // Configure servo motor
    servo_mot.attach(servo_pin);
    servo_mot.write(stop_angle);
    
    // Configure buzzer
    pinMode(Buzzer, OUTPUT);
    digitalWrite(Buzzer, LOW);
    
    // Initialize Serial Monitor
    Serial.begin(9600);
    
    // Initialize LCD display
    display.begin(16, 2);
    display.backlight();
    delay(100);
    display.clear();
    
    // Initialize RTC module
    rtc.begin();
    //rtc.setDOW(THURSDAY);            // Set Day-of-Week to THURSDAY
    //rtc.setTime(18, 03, 0);         // Set the time to 18:03:00 (24hr format)
    //rtc.setDate(27, 02, 2024);       // Set the date to February 27th, 2014
    
    // Load last and next feeding times from EEPROM
    last_feed_hour = EEPROM.read(2);
    next_feed_hour = EEPROM.read(3);
    
    // Initialize loop timing
    millis_before = millis();
}

void loop() {
    millis_now = millis();
    
    // Refresh display at set intervals
    if (millis_now - millis_before > refresh_rate) {
        millis_before = millis();
        display.clear();
        display.setCursor(0, 0);
        display.print(portions);
        display.print(" port");

        display.setCursor(9, 0);
        display.print(Hour);
        display.print(":");
        display.print(Minute);

        display.setCursor(0, 1);
        display.print("Each ");
        display.print(interval);
        display.print(" hours");
    }

    // Get current time from RTC module
    t = rtc.getTime();
    Hour = t.hour;
    Minute = t.min;
    Serial.println(Hour); // Debugging output

    // Check if it's time to feed
    if(Hour == next_feed_hour){                 
    feed_active = true;
    last_feed_hour = Hour;
    next_feed_hour = Hour + interval;         
    if(next_feed_hour >= 23){                 
      next_feed_hour = next_feed_hour - 24;   
    }
        EEPROM.write(2, last_feed_hour);
        EEPROM.write(3, next_feed_hour);
        
        // Buzzer alert
        analogWrite(Buzzer, 200);
        delay(200);
        digitalWrite(Buzzer, LOW);
    }

    // Execute feeding if active
    if (feed_active) {
        for (int i = 0; i < portions; i++) {
            servo_mot.write(rotate_angle);
            display.clear();
            display.setCursor(4, 0);
            display.print("FEEDING");
            delay(portion_delay);
        }
        servo_mot.write(stop_angle);
        feed_active = false;
    }



      //Button1 (increase portions)   
  if(!digitalRead(but1) && state_but1){
    portions++;
    if(portions > max_portions){          
      portions = min_portions;
    }
    state_but1 = false;
  }
  else if(digitalRead(but1) && !state_but1){
    state_but1 = true;
  }

    //Button2 (Manual feed) 
  if(!digitalRead(but2) && state_but2){    
    EEPROM.write(2, Hour);
    
    next_feed_hour = Hour + interval;
    if(next_feed_hour >= 23){
      next_feed_hour = next_feed_hour - 24;
    }    
    EEPROM.write(3, next_feed_hour);
    
    feed_active = true;
    state_but2 = false;
  }
  else if(digitalRead(but2) && !state_but2){
    state_but2 = true;
  }

    // Button3: Increase feeding interval
   if(!digitalRead(but3) && state_but3){
    interval++;
    if(interval > 23){
      interval = 1;
    }
    state_but3 = false;
  }
  else if(digitalRead(but3) && !state_but3){
    state_but3 = true;
  }  
}

