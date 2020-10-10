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
uint8_t   minhue  = 0;                                        // Minimum hue (color) value - 
uint8_t   maxhue  = 255;                                       // Maximum hue (color) value - 
uint8_t   sat     = 255;                                      // The saturation aka how mych color, 255 is max
uint8_t   bri     = 255;                                      // Max brightness for each LED
uint8_t thisdelay = 5;                                       // Delay of the sequence - normally 100, only 5 for confetti

CRGBPalette16 currentPalette;
TBlendType    currentBlending;


void setup() {
  delay(1000);                                                // Power-up safety delay
  Serial.begin(57600);

  FastLED.addLeds<LED_TYPE,LED_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  set_max_power_in_volts_and_milliamps(5, 500);               // FastLED power management set at 5V, 500mA.
}                                                             // setup()


void loop () {

  EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking delay to update/display the sequence.
    //colorPalette1(); 
    Confetti();
    //juggle();
  }
  FastLED.show();  
} // loop()

void Confetti() {                                             // Random colored speckles that blink in and fade smoothly
  int hue = random16(minhue, maxhue);                         // Determining the hue between "minhue" and "maxhue"
  int pos = random16(NUM_LEDS);                               // Pick an LED at random.

  fadeToBlackBy(leds, NUM_LEDS, fade);                        // Fade individual pixels to black by "fade" each tic

  leds[pos] += CHSV(hue, sat, bri);                           // Set random pixel to the random hue
} // Confetti()


void colorPalette1() { 
    // Wandering wainbow, quite fast
    Serial.println("colorPalette1");

    currentPalette = RainbowColors_p;         
    currentBlending = LINEARBLEND;

    colorPaletteShow1();
}

void colorPaletteShow1() {
    static uint8_t startIndex = 0;
    startIndex = startIndex + 10; /* motion speed */

    int colorIndex = startIndex;
       
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, sat, currentBlending);
        colorIndex += 20;
    }
}
