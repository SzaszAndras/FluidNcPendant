#include "StatusPage.h"

StatusPage::StatusPage(FluidNcGrbl* fluidNcGrbl) : Page(fluidNcGrbl) { }

void StatusPage::update(TFT_eSprite* spr_main, TFT_eSprite* spr_sec) {
    spr_main->fillSprite(TFT_BLACK);

    spr_main->setFreeFont(FSB12);

    spr_main->setTextColor(TFT_RED, TFT_BLACK);
    spr_main->setCursor(15, 40);
    spr_main->println("mX:");
    spr_main->setCursor(60, 40);
    spr_main->println(_fluidNcGrbl->getMachineStatus()->mcos[0]);

    spr_main->setTextColor(TFT_GREEN, TFT_BLACK);
    spr_main->setCursor(15, 70);
    spr_main->println("mY:");
    spr_main->setCursor(60, 70);
    spr_main->println(_fluidNcGrbl->getMachineStatus()->mcos[1]);

    spr_main->setTextColor(TFT_BLUE, TFT_BLACK);
    spr_main->setCursor(15, 100);
    spr_main->println("mZ:");
    spr_main->setCursor(60, 100);
    spr_main->println(_fluidNcGrbl->getMachineStatus()->mcos[2]);

    spr_main->setTextColor(TFT_RED, TFT_BLACK);
    spr_main->setCursor(160, 40);
    spr_main->println("wX:");
    spr_main->setCursor(215, 40);
    spr_main->println(_fluidNcGrbl->getMachineStatus()->wcos[0]);

    spr_main->setTextColor(TFT_GREEN, TFT_BLACK);
    spr_main->setCursor(160, 70);
    spr_main->println("wY:");
    spr_main->setCursor(215, 70);
    spr_main->println(_fluidNcGrbl->getMachineStatus()->wcos[1]);

    spr_main->setTextColor(TFT_BLUE, TFT_BLACK);
    spr_main->setCursor(160, 100);
    spr_main->println("wZ:");
    spr_main->setCursor(215, 100);
    spr_main->println(_fluidNcGrbl->getMachineStatus()->wcos[2]);

    spr_main->pushSprite(0, MAIN_SPRITE_Y);
}

PageEvent StatusPage::touchEvent(uint16_t x, uint16_t y, TEvent e) { 
    return PageEvent::NONE;
}
