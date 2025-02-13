#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_FT6206.h>
#include <Wire.h>
#include <CapTouch.h>
#include <FluidNcGrbl.h>
#include <screen/Screen.h>


FluidNcGrbl fluidNcGrbl(&Serial1);
TFT_eSPI tft = TFT_eSPI(); // Invoke custom library with default width and height
CapTouch cTouch(33, 32);
Screen screen(&tft, &cTouch, &fluidNcGrbl);


void setup(void) {
  Serial.begin(115200);
  Serial.println("Fluid Dial");
  Serial1.begin(9600, SERIAL_8N1, 35, 22);
  Serial1.println("Fluid Dial");

  // Init LCD
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  // Init Touch controller
  cTouch.begin();
  cTouch.setRotation(1);

  screen.begin();
}

void loop() {
  screen.update();
  fluidNcGrbl.poll();
}
