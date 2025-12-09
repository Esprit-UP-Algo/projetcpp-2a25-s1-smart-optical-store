 /*
 * Smart Optical Store - Revenue Notification LED
 * 
 * This Arduino sketch receives commands from the Qt application
 * and blinks an LED based on daily revenue thresholds:
 * - Level 1 (3000 DT): 1 blink
 * - Level 2 (10000 DT): 3 blinks
 * - Level 3 (20000 DT): 6 blinks
 * 
 * Hardware Setup:
 * - LED connected to Pin 13 (positive leg / long leg)
 * - LED short leg connected to GND (through 220 ohm resistor if external LED)
 * - Or just use the built-in LED on Pin 13 (no wiring needed!)
 * 
 * Communication Protocol:
 * - Send "L1" for Level 1 (1 blink)
 * - Send "L2" for Level 2 (3 blinks)
 * - Send "L3" for Level 3 (6 blinks)
 * - Send "TEST" to test LED
 */

const int LED_PIN = 13;  // Built-in LED on most Arduino boards

// LED settings
const int BLINK_ON_TIME = 300;    // LED on time in milliseconds
const int BLINK_OFF_TIME = 200;   // LED off time in milliseconds
const int BLINK_PAUSE = 500;      // Pause after all blinks

// Track which levels have been triggered today
int lastTriggeredLevel = 0;

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
  
  // Set LED pin as output
  pinMode(LED_PIN, OUTPUT);
  
  // Turn off LED initially
  digitalWrite(LED_PIN, LOW);
  
  // Startup indication - one blink
  blinkLED(1);
  
  Serial.println("========================================");
  Serial.println("Smart Optical Store - Revenue LED Ready!");
  Serial.println("========================================");
  Serial.println("Using LED on Pin 13 (built-in LED)");
  Serial.println("Commands: L1, L2, L3, TEST, RESET, STATUS");
  Serial.println("========================================");
}

void loop() {
  // Check if data is available from serial port
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();  // Remove whitespace
    command.toUpperCase();  // Make case-insensitive
    
    Serial.print("Received command: ");
    Serial.println(command);
    
    // Process commands
    if (command == "L1" || command == "LEVEL1") {
      // Level 1: Revenue reached 3000 DT - 1 blink
      if (lastTriggeredLevel < 1) {
        Serial.println(">>> Level 1 reached! (3000 DT) - Blinking 1 time");
        blinkLED(1);
        lastTriggeredLevel = 1;
        Serial.println("OK:L1");
      } else {
        Serial.println("Level 1 already triggered today");
        Serial.println("SKIP:L1");
      }
    }
    else if (command == "L2" || command == "LEVEL2") {
      // Level 2: Revenue reached 10000 DT - 3 blinks
      if (lastTriggeredLevel < 2) {
        Serial.println(">>> Level 2 reached! (10000 DT) - Blinking 3 times");
        blinkLED(3);
        lastTriggeredLevel = 2;
        Serial.println("OK:L2");
      } else {
        Serial.println("Level 2 already triggered today");
        Serial.println("SKIP:L2");
      }
    }
    else if (command == "L3" || command == "LEVEL3") {
      // Level 3: Revenue reached 20000 DT - 6 blinks
      if (lastTriggeredLevel < 3) {
        Serial.println(">>> Level 3 reached! (20000 DT) - Blinking 6 times");
        blinkLED(6);
        lastTriggeredLevel = 3;
        Serial.println("OK:L3");
      } else {
        Serial.println("Level 3 already triggered today");
        Serial.println("SKIP:L3");
      }
    }
    else if (command == "TEST") {
      // Test command - blink 2 times
      Serial.println(">>> TEST - Blinking 2 times");
      blinkLED(2);
      Serial.println("OK:TEST");
    }
    else if (command == "RESET") {
      // Reset daily levels (call at start of new day)
      lastTriggeredLevel = 0;
      Serial.println(">>> Levels reset for new day");
      // Quick confirmation blink
      blinkLED(1);
      Serial.println("OK:RESET");
    }
    else if (command == "STATUS") {
      // Report current status
      Serial.print("Current level: ");
      Serial.println(lastTriggeredLevel);
      Serial.println("OK:STATUS");
    }
    else if (command == "ON") {
      // Turn LED on (for testing)
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON");
      Serial.println("OK:ON");
    }
    else if (command == "OFF") {
      // Turn LED off (for testing)
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");
      Serial.println("OK:OFF");
    }
    else {
      Serial.print("Unknown command: ");
      Serial.println(command);
      Serial.println("ERR:UNKNOWN");
    }
  }
}

// Blink LED specified number of times
void blinkLED(int count) {
  Serial.print("Blinking LED ");
  Serial.print(count);
  Serial.println(" time(s)...");
  
  for (int i = 0; i < count; i++) {
    digitalWrite(LED_PIN, HIGH);   // LED ON
    delay(BLINK_ON_TIME);
    digitalWrite(LED_PIN, LOW);    // LED OFF
    delay(BLINK_OFF_TIME);
  }
  
  // Small pause after blinking sequence
  delay(BLINK_PAUSE);
  
  Serial.println("Blink sequence complete!");
}
