#include "FastLED.h"                                          // FastLED library.

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

// Fixed definitions cannot change on the fly.
#define LED_PIN 13// Data pin to connect to the strip.
#define COLOR_ORDER RGB                                       // Color order
#define LED_TYPE WS2811
#define NUM_LEDS 100                                      // Number of LED's

struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.

// Define variables used by the sequences.
uint8_t   fade    = 5;                                        // Rate of fading
uint8_t thisdelay = 100;                                      // Delay of the sequence


void setup() {
  delay(1000);                                                // Power-up safety delay
  Serial.begin(57600);

  FastLED.addLeds<LED_TYPE,LED_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  set_max_power_in_volts_and_milliamps(5, 500);               // FastLED power management set at 5V, 500mA.
}                                                             // setup()


void loop () {

  EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking delay to update/display the sequence.
    Confetti();                                               // Run Confetti
  }
  FastLED.show();  
} // loop()

void Confetti() {                                             // Random colored speckles that blink in and fade smoothly
  int pos = random16(NUM_LEDS);                               // Pick an LED at random.

  fadeToBlackBy(leds, NUM_LEDS, fade);                        // Fade individual pixels to black by "fade" each tic

  leds[pos] += 0xFFAA20;                                      // Set random pixel to the random hue
} // Confetti()
