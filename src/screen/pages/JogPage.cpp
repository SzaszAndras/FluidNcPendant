#include "JogPage.h"

JogPage::JogPage(FluidNcGrbl* fluidNcGrbl) : Page(fluidNcGrbl) {
    _jogButtonUpX = new JogButtonElement(5, 35, TFT_RED, JogButtonDirection::UP);
    _jogButtonDownX = new JogButtonElement(5, 100, TFT_RED, JogButtonDirection::DOWN);
    _jogButtonUpY = new JogButtonElement(85, 35, TFT_GREEN, JogButtonDirection::UP);
    _jogButtonDownY = new JogButtonElement(85, 100, TFT_GREEN, JogButtonDirection::DOWN);
    _jogButtonUpZ = new JogButtonElement(165, 35, TFT_BLUE, JogButtonDirection::UP);
    _jogButtonDownZ = new JogButtonElement(165, 100, TFT_BLUE, JogButtonDirection::DOWN);

    _zeroAxis = new RectangleButtonElement(5, 165, 230, 35, TFT_WHITE, "ZERO");

    _jog100 = new RectangleButtonElement(250, 35, 60, 35, TFT_WHITE, "100");
    _jog10 = new RectangleButtonElement(250, 78, 60, 35, TFT_WHITE, "10");
    _jog1 = new RectangleButtonElement(250, 122, 60, 35, TFT_WHITE, "1");
    _jog01 = new RectangleButtonElement(250, 165, 60, 35, TFT_WHITE, "0.1");

    _jog100->setSelected(true);
    _jogDistance = 100;
}

void JogPage::update(TFT_eSprite* spr_main, TFT_eSprite* spr_sec) {
    spr_main->fillSprite(TFT_BLACK);

    spr_main->setFreeFont(FSB9);
    spr_main->setTextColor(TFT_RED, TFT_BLACK);
    spr_main->setCursor(15, 25);
    spr_main->println(_fluidNcGrbl->getMachineStatus()->mcos[0]);
    _jogButtonUpX->draw(spr_main);
    _jogButtonDownX->draw(spr_main);

    spr_main->setTextColor(TFT_GREEN, TFT_BLACK);
    spr_main->setCursor(95, 25);
    spr_main->println(_fluidNcGrbl->getMachineStatus()->mcos[1]);
    _jogButtonUpY->draw(spr_main);
    _jogButtonDownY->draw(spr_main);

    spr_main->setTextColor(TFT_BLUE, TFT_BLACK);
    spr_main->setCursor(175, 25);
    spr_main->println(_fluidNcGrbl->getMachineStatus()->mcos[2]);
    _jogButtonUpZ->draw(spr_main);
    _jogButtonDownZ->draw(spr_main);

    _zeroAxis->draw(spr_main);

    _jog100->draw(spr_main);
    _jog10->draw(spr_main);
    _jog1->draw(spr_main);
    _jog01->draw(spr_main);

    spr_main->pushSprite(0, MAIN_SPRITE_Y);
}

PageEvent JogPage::touchEvent(uint16_t x, uint16_t y, TEvent e) {

    if (_jog100->isPressed(x, y)) {
        _jog100->setSelected(true);
        _jog10->setSelected(false);
        _jog1->setSelected(false);
        _jog01->setSelected(false);
        _jogDistance = 100;
        return PageEvent::NONE;
    }
    if (_jog10->isPressed(x, y)) {
        _jog100->setSelected(false);
        _jog10->setSelected(true);
        _jog1->setSelected(false);
        _jog01->setSelected(false);
        _jogDistance = 10;
        return PageEvent::NONE;
    }
    if (_jog1->isPressed(x, y)) {
        _jog100->setSelected(false);
        _jog10->setSelected(false);
        _jog1->setSelected(true);
        _jog01->setSelected(false);
        _jogDistance = 1;
        return PageEvent::NONE;
    }
    if (_jog01->isPressed(x, y)) {
        _jog100->setSelected(false);
        _jog10->setSelected(false);
        _jog1->setSelected(false);
        _jog01->setSelected(true);
        _jogDistance = 0.1;
        return PageEvent::NONE;
    }

    if (_jogButtonUpX->isPressed(x, y)) {
        _fluidNcGrbl->jog(JogAxis::X, _jogDistance);
        return PageEvent::NONE;
    }

    if (_jogButtonDownX->isPressed(x, y)) {
        _fluidNcGrbl->jog(JogAxis::X, _jogDistance * -1);
        return PageEvent::NONE;
    }

    if (_jogButtonUpY->isPressed(x, y)) {
        _fluidNcGrbl->jog(JogAxis::Y, _jogDistance);
        return PageEvent::NONE;
    }

    if (_jogButtonDownY->isPressed(x, y)) {
        _fluidNcGrbl->jog(JogAxis::Y, _jogDistance * -1);
        return PageEvent::NONE;
    }

    if (_jogButtonUpZ->isPressed(x, y)) {
        _fluidNcGrbl->jog(JogAxis::Z, _jogDistance);
        return PageEvent::NONE;
    }

    if (_jogButtonDownZ->isPressed(x, y)) {
        _fluidNcGrbl->jog(JogAxis::Z, _jogDistance * -1);
        return PageEvent::NONE;
    }

    if (_zeroAxis->isPressed(x, y)) {
        _fluidNcGrbl->zero();
        return PageEvent::OPEN_MAIN_MENU_PAGE;
    }

    return PageEvent::NONE;
}