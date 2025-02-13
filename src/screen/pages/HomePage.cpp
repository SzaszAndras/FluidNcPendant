#include "HomePage.h"

HomePage::HomePage(FluidNcGrbl* fluidNcGrbl) : Page(fluidNcGrbl) {
    _popUp = new PopUpElement("Home all axis ?");
    _popUpButtonYes = new PopUpButtonElement(60, 95, 80, 40, TFT_GREEN, "YES");
    _popUpButtonNo = new PopUpButtonElement(180, 95, 80, 40, TFT_RED, "NO");
}

void HomePage::update(TFT_eSprite* spr_main, TFT_eSprite* spr_sec) {
    _popUp->draw(spr_main);
    _popUpButtonYes->draw(spr_main);
    _popUpButtonNo->draw(spr_main);
    spr_main->pushSprite(0, MAIN_SPRITE_Y);
}

PageEvent HomePage::touchEvent(uint16_t x, uint16_t y, TEvent e) {
    if (_popUpButtonYes->isPressed(x, y)) {
        _fluidNcGrbl->home();
        return PageEvent::OPEN_MAIN_MENU_PAGE;
    } else if (_popUpButtonNo->isPressed(x, y)) {
        return PageEvent::OPEN_MAIN_MENU_PAGE;
    } 

    return PageEvent::NONE;
}