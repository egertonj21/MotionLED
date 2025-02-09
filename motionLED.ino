#include <Adafruit_NeoPixel.h>

// Define the pin connections
#define PIR_SENSOR_PIN D8
#define LED_STRIP_PIN D10
#define NUM_LEDS 28

// Create an instance of the Adafruit_NeoPixel class
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);

// Variables to keep track of motion and timing
bool motionDetected = false;
unsigned long lastMotionTime = 0;
const unsigned long motionTimeout = 10 * 60 * 1000; // 10 minutes in milliseconds

void setup() {
  // Initialize the PIR sensor pin as input
  pinMode(PIR_SENSOR_PIN, INPUT);

  // Initialize the LED strip
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Check if motion is detected
  if (digitalRead(PIR_SENSOR_PIN) == HIGH) {
    motionDetected = true;
    lastMotionTime = millis(); // Update the last motion time
  }

  // If motion is detected, turn on the LED strip to white
  if (motionDetected) {
    setStripColor(strip.Color(255, 255, 255)); // White color
  }

  // Check if the motion timeout has been reached
  if (motionDetected && (millis() - lastMotionTime > motionTimeout)) {
    motionDetected = false;
    setStripColor(strip.Color(0, 0, 0)); // Turn off the LED strip
  }
}

// Function to set the color of the entire LED strip
void setStripColor(uint32_t color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}
