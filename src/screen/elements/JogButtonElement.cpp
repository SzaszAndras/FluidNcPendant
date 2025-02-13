#include "JogButtonElement.h"

JogButtonElement::JogButtonElement(uint16_t x, uint16_t y, uint32_t color, JogButtonDirection dir) {
    _x = x;
    _y = y;
    _color = color;
    _dir = dir;
}

void JogButtonElement::draw(TFT_eSprite* sprite) {
    uint16_t x1 = _x + 20;
    uint16_t x2 = _x + JOG_BUTTON_W - 20;
    uint16_t x3 = x1 + ((x2 - x1) / 2);
    uint16_t y1 = _y + JOG_BUTTON_H / 2 - 10;
    uint16_t y2 = _y + JOG_BUTTON_H / 2 + 10;

    sprite->drawRoundRect(_x, _y, JOG_BUTTON_W, JOG_BUTTON_H, 10, _color);

    if (_dir == JogButtonDirection::DOWN) {
        sprite->fillTriangle(x1, y1, x2, y1, x3, y2, _color);
    } else if (_dir == JogButtonDirection::UP) {
        sprite->fillTriangle(x1, y2, x2, y2, x3, y1, _color);
    }
}

bool JogButtonElement::isPressed(uint16_t x, uint16_t y) {
    return x > _x && x < _x + JOG_BUTTON_W && y > _y && y < _y + JOG_BUTTON_H;
}