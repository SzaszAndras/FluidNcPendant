#include "ScreenHeader.h"

ScreenHeader::ScreenHeader(FluidNcGrbl* fluidNcGrbl) { 
    _fluidNcGrbl = fluidNcGrbl;
    _showBackButton = false;
}

void ScreenHeader::update(TFT_eSprite* sprite) {
    MachineStatus* machineStatus = _fluidNcGrbl->getMachineStatus();
    char* statusText = &machineStatus->status[0];
    uint32_t statusTextColor = TFT_WHITE;

    if (strlen(statusText) < 1) {
        statusText = "Disconnected!";
        statusTextColor = TFT_RED;
    }
    sprite->setFreeFont(FSB9);
    sprite->fillSprite(TFT_BLACK);

    sprite->setTextColor(statusTextColor, TFT_BLACK);
    sprite->setCursor((TFT_HEIGHT / 2) - (sprite->textWidth(statusText) / 2), 25, 2);
    sprite->print(statusText);

    if (_showBackButton) {
        sprite->setTextColor(TFT_WHITE, TFT_BLACK);
        sprite->setCursor(10, 25, 2);
        sprite->print("<");
    }

    sprite->pushSprite(0, 0);
 }

void ScreenHeader::showBackButton(bool show) {
    _showBackButton = show;
}

bool ScreenHeader::touchPageBackEvent(uint16_t x, uint16_t y) {
    return _showBackButton && x < 50 && y < 30;
};