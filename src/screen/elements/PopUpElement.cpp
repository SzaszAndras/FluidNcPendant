#include "PopUpElement.h"

PopUpElement::PopUpElement(const char *text) {
    _text = text;
}

void PopUpElement::draw(TFT_eSprite* sprite) {
    sprite->fillRoundRect(36, 36, 248, 123, 10, TFT_BLACK);
    sprite->drawRoundRect(35, 35, 250, 125, 10, TFT_WHITE);
    sprite->drawLine(35, 45 + 30, 35 + 249, 45 + 30, TFT_WHITE);
    sprite->setFreeFont(FSB9);
    sprite->setTextColor(TFT_WHITE, TFT_BLACK);
    sprite->setCursor(35 + ((250 - sprite->textWidth(_text)) / 2), 35 + 25, 2);
    sprite->println(_text);
}