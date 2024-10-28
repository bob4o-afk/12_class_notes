#include <Adafruit_NeoPixel.h>
#include "pitches.h"

#define PIN 6
#define NUMPIXELS 8
#define POT_PIN A0           // Analog pin for potentiometer
#define BUZZER_PIN A1        // PWM pin for buzzer
#define BASE_DELAYVAL 50     // Starting delay for faster spin
#define MAX_DELAYVAL 200     // Maximum delay for slowest spin
#define MIN_SPIN_TIME 2000   // Minimum spin time in ms (2 seconds)
#define MAX_SPIN_TIME 10000  // Maximum spin time in ms (10 seconds)

// Define LED pins from 7 to 12
#define LED_START_PIN 7
#define LED_END_PIN 12

int melody[] = {
  NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_GS4,
  NOTE_CS5, NOTE_B4, NOTE_D4, NOTE_E4,
  NOTE_B4, NOTE_A4, NOTE_CS4, NOTE_E4,
  NOTE_A4
};

int durations[] = {
  8, 8, 4, 4,
  8, 8, 4, 4,
  8, 8, 4, 4,
  2
};

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int chosenColor;     // Stores the selected color (0 for red, 1 for black)
int resultPosition;  // Chosen winning LED position
int animationDirection = 1;

// Animation variables
int currentLED = LED_END_PIN;      // Start at LED 12
bool isLightingDown = true;        // To control the direction
unsigned long previousMillis = 0;  // Store the last time LED was updated
const int ledDelay = 100;          // Delay for LED animation (in milliseconds)
bool isAnimating = false;          // State to track if animation is in progress
int melodyIndex = 0;               // Current note index for melody playback

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.setBrightness(50);
  pixels.clear();
  pixels.show();
  pinMode(BUZZER_PIN, OUTPUT);

  // Set pins 7 to 12 as outputs
  for (int pin = LED_START_PIN; pin <= LED_END_PIN; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);  // Initialize to LOW
  }
}

void loop() {
  // Initialize the LEDs
  for (int j = 0; j < NUMPIXELS; j++) {
    pixels.setPixelColor(j, (j % 2 == 0) ? pixels.Color(255, 0, 0) : pixels.Color(0, 0, 0));  // Red for even, Black for odd
  }
  pixels.show();

  // Wait for user input
  if (Serial.available() > 0) {
    String colorChoice = Serial.readStringUntil('\n');
    colorChoice.trim();

    if (colorChoice == "red") {
      chosenColor = 0;
    } else if (colorChoice == "black") {
      chosenColor = 1;
    } else {
      Serial.println("Please type 'red' or 'black'");
      return;
    }

    // Generate a random spin time between MIN_SPIN_TIME and MAX_SPIN_TIME
    unsigned long spinTime = random(MIN_SPIN_TIME, MAX_SPIN_TIME + 1);
    unsigned long startTime = millis();
    unsigned long currentSpinTime = 0;

    // Spin the LEDs
    while (true) {
      currentSpinTime = millis() - startTime;

      if (currentSpinTime >= spinTime) {
        break;
      }

      // Clear previous colors
      pixels.clear();
      int currentPosition = (millis() / BASE_DELAYVAL) % NUMPIXELS;

      // Set colors for the spinning effect
      for (int j = 0; j < NUMPIXELS; j++) {
        pixels.setPixelColor(j, (j % 2 == 0) ? pixels.Color(255, 0, 0) : pixels.Color(0, 0, 0));  // Red for even, Black for odd
      }

      // Set current position to white
      pixels.setPixelColor(currentPosition, pixels.Color(255, 255, 255));  // White for spinning position
      pixels.show();

      int remainingTime = spinTime - currentSpinTime;
      int delayVal = map(remainingTime, 0, spinTime, MAX_DELAYVAL, BASE_DELAYVAL);
      delay(delayVal);
    }

    // Determine the result position based on the current time
    resultPosition = (millis() / BASE_DELAYVAL) % NUMPIXELS;

    // Check potentiometer value to determine final result position
    int potValue = analogRead(POT_PIN);
    if (potValue < 100) {  // If potentiometer value is between 0 and 100
      // Ensure RED (even)
      if (resultPosition % 2 != 0) {                        // If resultPosition is odd, switch to the next LED
        resultPosition = (resultPosition + 1) % NUMPIXELS;  // Make it even
      }
    } else if (potValue > 800) {  // If potentiometer value is between 800 and 1023
      // Ensure BLACK (odd)
      if (resultPosition % 2 == 0) {                        // If resultPosition is even, switch to the next LED
        resultPosition = (resultPosition + 1) % NUMPIXELS;  // Make it odd
      }
    }

    // Set all LEDs to their initial colors before showing result
    for (int j = 0; j < NUMPIXELS; j++) {
      pixels.setPixelColor(j, (j % 2 == 0) ? pixels.Color(255, 0, 0) : pixels.Color(0, 0, 0));  // Red for even, Black for odd
    }

    // Check if the result position matches the chosen color
    if ((resultPosition % 2 == 0 && chosenColor == 0) || (resultPosition % 2 == 1 && chosenColor == 1)) {
      pixels.setPixelColor(resultPosition, pixels.Color(0, 255, 0));  // Green if chosen color matches
      pixels.show();
      melodyIndex = 0;           // Reset melody index
      isAnimating = true;        // Start the LED animation
      currentLED = LED_END_PIN;  // Start at the last LED
    } else {
      pixels.setPixelColor(resultPosition, pixels.Color(255, 255, 0));  // Yellow if chosen color does not match
    }

    pixels.show();   // Show final result
    delay(2000);     // Delay before the next round
    pixels.clear();  // Clear the pixels
    pixels.show();
  }

  // Handle animation and sound in parallel
  if (isAnimating) {
    unsigned long currentMillis = millis();

    // Handle LED animation
    // Handle LED animation
    if (currentMillis - previousMillis >= ledDelay) {
      previousMillis = currentMillis;  // Update last time LED was updated

      // If currently lighting down from 12 to 7
      if (isLightingDown) {
        // Turn off the previous LED
        if (currentLED >= LED_START_PIN && currentLED <= LED_END_PIN) {
          digitalWrite(currentLED, LOW);  // Turn off the previous LED
        }

        // Move to the next LED downwards
        currentLED--;  // Move down to the next LED

        // Check if we've reached LED 7
        if (currentLED < LED_START_PIN) {
          currentLED = LED_START_PIN;  // Reset to LED 7
          isLightingDown = false;      // Change direction to lighting up
        }
      }
      // If currently lighting up from 7 to 12
      else {
        // Turn off the previous LED
        if (currentLED >= LED_START_PIN && currentLED <= LED_END_PIN) {
          digitalWrite(currentLED, LOW);  // Turn off the previous LED
        }

        // Move to the next LED upwards
        currentLED++;  // Move up to the next LED

        // Check if we've reached LED 12
        if (currentLED > LED_END_PIN) {
          currentLED = LED_END_PIN;  // Reset to LED 12
          isLightingDown = true;     // Change direction to lighting down
        }
      }

      // Turn on the current LED
      digitalWrite(currentLED, HIGH);  // Turn on the current LED
    }

    // Handle sound playback
    if (melodyIndex < sizeof(durations) / sizeof(int)) {
      // Calculate the note duration
      int duration = 1000 / durations[melodyIndex];
      tone(BUZZER_PIN, melody[melodyIndex], duration);

      // Pause between notes
      int pauseBetweenNotes = duration * 1.30;

      // Wait for the note to finish playing
      delay(pauseBetweenNotes);
      noTone(BUZZER_PIN);  // Stop the tone
      melodyIndex++;       // Move to the next note
    }

    if (melodyIndex >= sizeof(durations) / sizeof(int)) {
        // Turn off all LEDs
        for (int pin = LED_START_PIN; pin <= LED_END_PIN; pin++) {
            digitalWrite(pin, LOW); // Set all LEDs to LOW
        }
        isAnimating = false;
        currentLED = 12;
    }

  }
}
