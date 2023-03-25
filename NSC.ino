// User Changeable Variables:
    
float redMaster = 1;  // Red Value (Between 0.0 - 1.0)
float blueMaster = 1;     // Green Value (Between 0.0 - 1.0)
float greenMaster = 1;  // Blue Value (Between 0.0 - 1.0)
int BRIGHTNESS = 255; // Set BRIGHTNESS (min= 0, max = 255)
bool SINGLEMODE = false; //True or False. False, all modes will run on the arduino, True, only the mode selected using the MODE variable below will run. (This makes the animation run smoother)
int MODE = 11;  // Pin Value (8-13); //13 = Solid, 12 = Hard Ramp, 11 = Soft Ramp, 10 = Flashing, 9 = Thunder, 8 = Rainbow

// |-----------------------------------------------------------------------------------------------------------------|
// |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
// |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
// |-----------------------------------------------------------------------------------------------------------------|
// |                                                DO NOT EDIT BELOW HERE                                           |
// |----------------------------------------------------------------------------------------------------------------|
// |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/-\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
// |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
// |-----------------------------------------------------------------------------------------------------------------|
#include <Adafruit_NeoPixel.h>

#define LED_PIN 13      // Pin that LED Data is attached too
#define LED_COUNT 60    // Amount of LEDs per Strip
#define SleepAmount 60  // Amount of LEDs per Strip
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip_solidWhite(LED_COUNT, 13, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_HarshTrail(LED_COUNT, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_SoftTrail(LED_COUNT, 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_Flashing(LED_COUNT, 10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_Thunder(LED_COUNT, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_Rainbow(LED_COUNT, 8, NEO_GRB + NEO_KHZ800);
int arry[60] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 64, 128, 254, 254, 254, 128, 64, 32, 16, 8, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // Intensity Array for strip_SoftTrail
int dir[60] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};         // Direction Array For strip_SoftTrail
int sizeOfDirection = 60;                                                                                                                                                                                             // Size of arry and dir array

void setup() {
    strip_solidWhite.begin();
    strip_solidWhite.show();
    strip_solidWhite.setBrightness(BRIGHTNESS);
    strip_HarshTrail.begin();
    strip_HarshTrail.show();
    strip_HarshTrail.setBrightness(BRIGHTNESS);
    strip_SoftTrail.begin();
    strip_SoftTrail.show();
    strip_SoftTrail.setBrightness(BRIGHTNESS);
    strip_Flashing.begin();
    strip_Flashing.show();
    strip_Flashing.setBrightness(BRIGHTNESS);
    strip_Thunder.begin();
    strip_Thunder.show();
    strip_Thunder.setBrightness(BRIGHTNESS);
    strip_Rainbow.begin();
    strip_Rainbow.show();
    strip_Rainbow.setBrightness(BRIGHTNESS);
}
float runTime;
void loop() {
    runTime = millis();
    if (SINGLEMODE == true) {
        if (MODE == 13) {
            solidWhite();
        }
        if (MODE == 12) {
            Ramp();
        }
        if (MODE == 11) {
            SoftRamp();
        }
        if (MODE == 10) {
            Flashing();
        }
        if (MODE == 9) {
            Thunder();
        }
        if (MODE == 8) {
            Rainbow();
        }
    } else if (SINGLEMODE == false) {
        solidWhite();  // 13
        Ramp();        // 12
        SoftRamp();    // 11
        Flashing();    // 10
        Thunder();     // 9
        Rainbow();     // 8
    }
}

void solidWhite() {                                                                                                       // Set all pixels in strip to white
    for (int i = 0; i < strip_solidWhite.numPixels(); i++) {                                                              // Go Through  all pixels in strip
        strip_solidWhite.setPixelColor(i, strip_solidWhite.Color(redMaster * 255, greenMaster * 255, blueMaster * 255));  // Set th pixel color
    }
    strip_solidWhite.show();  // Show the pixels
}

int lightLength = 10;
int currentHeadID = 0;
void Ramp() {
    currentHeadID = (currentHeadID + 1) % LED_COUNT;  // Loop the start of the light line around the strip

    for (int i = 0; i < strip_HarshTrail.numPixels(); i++) {
        strip_HarshTrail.setPixelColor(i, strip_HarshTrail.Color(0, 0, 0));  // Set all pixels to black
    }
    for (int i = 0; i < lightLength; i++) {                                                                                                             // For each pixel in strip...
        strip_HarshTrail.setPixelColor((i + currentHeadID) % LED_COUNT, strip_HarshTrail.Color(redMaster * 255, greenMaster * 255, blueMaster * 255));  // For the current LED light, + the amount of lightLength, turn to white
    }
    strip_HarshTrail.show();
    if (SINGLEMODE) delay(SleepAmount);  // Used to slow down the effect if only that is running
}

int soft_lightLength = 14;  // Even Only

void SoftRamp() {
    // Get the direction array and shift the values by one along the array to animate movement
    int firstDirection = dir[0];
    for (int i = 0; i < sizeOfDirection - 1; i++) {
        dir[i] = dir[i + 1];
    }
    dir[sizeOfDirection - 1] = firstDirection;

    for (int j = 0; j < sizeOfDirection; j++) {  // For each pixel in strip...

        // Depending on the direction value, either add 1, subtract 1, multiply by 2 or divide by 2
        if (dir[j] == 1) arry[j] += 1;
        if (dir[j] == -1) arry[j] -= 1;
        if (dir[j] == 2) arry[j] = arry[j] * 2;
        if (dir[j] == -2) arry[j] = arry[j] / 2;
        if (arry[j] < 0) {
            arry[j] = 0;
        }
        if (arry[j] >= 255) {
            arry[j] = 254;
        }
        strip_SoftTrail.setPixelColor(j, strip_SoftTrail.Color(redMaster * arry[j], greenMaster * arry[j], blueMaster * arry[j]));
    }
    strip_SoftTrail.show();
    if (SINGLEMODE) delay(SleepAmount);
}

double DegreesToRadians(int degrees) { return ((degrees * 71) / 4068); }

int FlashAmount = 10;
void Flashing() {
    for (int i = 0; i < strip_Flashing.numPixels(); i++) {               // For each pixel in strip...
        strip_Flashing.setPixelColor(i, strip_Flashing.Color(0, 0, 0));  //  Set pixel's color (in RAM)
    }
    for (int i = 0; i < FlashAmount; i++) {
        strip_Flashing.setPixelColor(random(0, LED_COUNT), strip_Flashing.Color(redMaster * 255, greenMaster * 255, blueMaster * 255));  // Randomly set an LED between 0 and the amount of LEDs on the strip to a colour
    }
    strip_Flashing.show();
    if (SINGLEMODE) delay(SleepAmount);
}

float lastThudnerStrike = 0;
float dimDownTimeMS = 2000;
int maxstrikes = 10;
int _strikes = 10;
int strikeWidth = 3;
int _currentStrike = 0;
int _brightness;
int _brightnessDecreaseValue = 10;
void Thunder() {
    if (_currentStrike < _strikes) {  // If we haven't had 10 strikes
        // Flash
        for (int i = 0; i < strip_Thunder.numPixels(); i++) {              // For each pixel in strip...
            strip_Thunder.setPixelColor(i, strip_Thunder.Color(0, 0, 0));  //  Set the strip to black
        }
        for (int i = 0; i < strikeWidth; i++) {  // For the strikeWidth choose a random position on the strip
            int pos = random(0, LED_COUNT);

            for (int j = 0; j < strikeWidth; j++) {
                strip_Thunder.setPixelColor((pos + j) % LED_COUNT, strip_Thunder.Color(redMaster * 255, greenMaster * 255, blueMaster * 255));  // Light the LEDs around it
            }
        }
        _brightness = 255;
        _currentStrike = _currentStrike + 1;
    } else {  // If 10 strikes have occured then dim down
        // Dim Down
        _brightness -= _brightnessDecreaseValue;
        strip_Thunder.setBrightness(_brightness);
        if (_brightness <= 0) {
            _currentStrike = 0;
            _strikes = random(maxstrikes / 3, maxstrikes);
            _brightnessDecreaseValue = random(4, 20);
        }
    }
    strip_Thunder.show();
    if (SINGLEMODE) delay(SleepAmount);
}

long firstPixelHue = 0;
void Rainbow() {  // Its a rainbow.. enough said
    firstPixelHue += 256;
    if (firstPixelHue >= (5 * 65536)) firstPixelHue = 0;

    strip_Rainbow.rainbow(firstPixelHue);
    strip_Rainbow.show();  // Update strip with new contents
    if (SINGLEMODE) delay(SleepAmount);
}
