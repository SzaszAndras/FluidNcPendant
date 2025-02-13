#ifndef MAIN_MENU_PAGE_H
#define MAIN_MENU_PAGE_H

#include "Page.h"
#include "../elements/ImageButtonElement.h"
#include "../img/home.h"
#include "../img/jog.h"
#include "../img/sdcard.h"
#include "../img/status.h"
#include "../img/macro.h"
#include "../img/probe.h"

class MainMenuPage : public Page {
    public:
        MainMenuPage();
        void update(TFT_eSprite* spr_main, TFT_eSprite* spr_sec) override;
        PageEvent touchEvent(uint16_t x, uint16_t y, TEvent e) override;
    private:
        ImageButtonElement* _homeButton;
        ImageButtonElement* _jogButton;
        ImageButtonElement* _sdCardButton;
        ImageButtonElement* _probeButton;
        ImageButtonElement* _statusButton;
        ImageButtonElement* _macrosButton;
};

#endif