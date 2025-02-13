#ifndef SPRITE_ELEMENT_H
#define SPRITE_ELEMENT_H

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "../../fonts/FreeFonts.h"

// Base class declaration
class SpriteElement {
    public:
        virtual void draw(TFT_eSprite* tft) = 0;
        virtual bool isPressed(uint16_t x, uint16_t y) { return false; };
};

#endif