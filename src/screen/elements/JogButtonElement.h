#ifndef JOG_BUTTON_ELEMENT_H
#define JOG_BUTTON_ELEMENT_H

#include "SpriteElement.h"

#define JOG_BUTTON_W 70
#define JOG_BUTTON_H 50

enum class JogButtonDirection {
  UP,
  DOWN
};

class JogButtonElement : public SpriteElement {
    public:
        JogButtonElement(uint16_t x, uint16_t y, uint32_t color, JogButtonDirection dir);
        void draw(TFT_eSprite* sprite) override;
        bool isPressed(uint16_t x, uint16_t y) override;
    private:
        uint16_t _x, _y;
        uint32_t _color;
        JogButtonDirection _dir;
};

#endif