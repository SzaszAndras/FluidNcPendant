#ifndef PAGE_h
#define PAGE_h

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <CapTouch.h>
#include <FluidNcGrbl.h>
#include "fonts/FreeFonts.h"

#define MAIN_SPRITE_Y 30

enum class PageEvent {
    NONE,
    OPEN_MAIN_MENU_PAGE,
    OPEN_HOME_PAGE,
    OPEN_JOG_PAGE,
    OPEN_STATUS_PAGE,
    OPEN_SD_CARD_PAGE,
    OPEN_RUN_PAGE
};

class Page {
    public:
        Page (FluidNcGrbl* fluidNcGrbl) { _fluidNcGrbl = fluidNcGrbl; };
        virtual void update(TFT_eSprite* _spr_main, TFT_eSprite* _spr_sec) = 0;
        virtual PageEvent touchEvent(uint16_t x, uint16_t y, TEvent e) { };
        virtual void resetPage() { };

    protected:
        FluidNcGrbl* _fluidNcGrbl;
};

#endif