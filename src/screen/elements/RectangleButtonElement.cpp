#include "RectangleButtonElement.h"

RectangleButtonElement::RectangleButtonElement(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color, const char *text) {
    _x = x;
    _y = y;
    _w = w;
    _h = h;
    _color = color;
    _text = text;
    _selected = false;
}

void RectangleButtonElement::draw(TFT_eSprite* sprite) {
    sprite->setFreeFont(FSB9);

    if (_selected) {
        sprite->fillRoundRect(_x, _y, _w, _h, 10, _color);
        sprite->setTextColor(TFT_BLACK, _color);
    } else {
        sprite->drawRoundRect(_x, _y, _w, _h, 10, _color);
        sprite->setTextColor(_color, TFT_BLACK);
    }

    sprite->setCursor(_x + ((_w - sprite->textWidth(_text)) / 2), _y + 23, 2);
    sprite->println(_text);
}

bool RectangleButtonElement::isPressed(uint16_t x, uint16_t y) {
    return x > _x && x < _x + _w && y > _y && y < _y + _h;
}

void RectangleButtonElement::setSelected(bool selected) {
    _selected = selected;
}