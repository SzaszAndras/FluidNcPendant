#include "RunPage.h"

RunPage::RunPage(FluidNcGrbl* fluidNcGrbl) : Page(fluidNcGrbl) {
    _holdButton = new RectangleButtonElement(110, 140, 100, 35, TFT_ORANGE, "HOLD");
    _resumeButton = new RectangleButtonElement(110, 140, 100, 35, TFT_GREEN, "RESUME");
}

void RunPage::update(TFT_eSprite* spr_main, TFT_eSprite* spr_sec) {
    spr_main->fillSprite(TFT_BLACK);

    spr_main->setFreeFont(FSB9);
    spr_main->setTextColor(TFT_WHITE, TFT_BLACK);
    spr_main->setCursor(10, 30, 2);
    spr_main->print(_fluidNcGrbl->getMachineStatus()->filename);

    spr_main->drawRoundRect(10, 60, 230, 30, 5, TFT_WHITE);
    spr_main->fillRoundRect(11, 61, _fluidNcGrbl->getMachineStatus()->filePercent * 228 / 100, 28, 5, TFT_GREEN);

    char percent[5];
    sprintf(percent,"%d%%", _fluidNcGrbl->getMachineStatus()->filePercent);
    spr_main->setFreeFont(FSB12);
    spr_main->setCursor(250, 81, 2);
    spr_main->print(percent);

    _holdButton->draw(spr_main);

    spr_main->pushSprite(0, MAIN_SPRITE_Y);
}

PageEvent RunPage::touchEvent(uint16_t x, uint16_t y, TEvent e) {
    return PageEvent::NONE;
}