#include "ImageButtonElement.h"

ImageButtonElement::ImageButtonElement(uint16_t x, uint16_t y,uint16_t w, uint16_t h, const uint16_t *image, uint16_t textColor, const char *text) {
    _x = x;
    _y = y;
    _w = w;
    _h = h;
    _image = image;
    _textColor = textColor;
    _text = text;
}

void ImageButtonElement::draw(TFT_eSprite* sprite) {
    sprite->setSwapBytes(true);
    sprite->pushImage(_x, _y, _w, _h, _image);
    sprite->setSwapBytes(false);
    sprite->setTextColor(_textColor, TFT_BLACK);
    sprite->setTextFont(__null);
    sprite->setTextSize(1);
    sprite->setCursor(_x + ((_w - sprite->textWidth(_text)) / 2), _y + _h + 3, 2);
    sprite->println(_text);
}

bool ImageButtonElement::isPressed(uint16_t x, uint16_t y) {
    return x > _x && x < _x + _w && y > _y && y < _y + _h;
}