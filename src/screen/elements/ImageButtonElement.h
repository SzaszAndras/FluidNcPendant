#ifndef BUTTON_ELEMENT_H
#define BUTTON_ELEMENT_H

#include "SpriteElement.h"

class ImageButtonElement : public SpriteElement {
    public:
        ImageButtonElement(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *image, uint16_t textColor, const char *text);
        void draw(TFT_eSprite* tft) override;
        bool isPressed(uint16_t x, uint16_t y) override;
    private:
        uint16_t _x, _y;
        uint16_t _w, _h;
        const uint16_t *_image;
        uint16_t _textColor;
        const char *_text;
};

#endif