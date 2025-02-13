#ifndef RECTANGLE_BUTTON_ELEMENT_H
#define RECTANGLE_BUTTON_ELEMENT_H

#include "SpriteElement.h"

class RectangleButtonElement : public SpriteElement {
    public:
        RectangleButtonElement(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color, const char *text);
        void draw(TFT_eSprite* sprite) override;
        bool isPressed(uint16_t x, uint16_t y) override;
        void setSelected(bool selected);
    private:
        uint16_t _x, _y;
        uint16_t _w, _h;
        uint32_t _color;
        const char *_text;
        bool _selected;
};

#endif