#ifndef SCREEN_ELEMENT_H
#define SCREEN_ELEMENT_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <CapTouch.h>
#include <FluidNcGrbl.h>
#include "pages/StartPage.h"
#include "pages/MainMenuPage.h"
#include "pages/HomePage.h"
#include "header/ScreenHeader.h"
#include "pages/JogPage.h"
#include "pages/StatusPage.h"
#include "pages/SdCardPage.h"
#include "pages/RunPage.h"

#define LED_RED 4 
#define LED_GREEN 16
#define LED_BLUE 17

class Screen : public CapTouchCallback {
    public:
        Screen(TFT_eSPI* tft, CapTouch* touch, FluidNcGrbl* fluidNcGrbl);
        void begin();
        void update();

    protected:
        void touchCallback(uint16_t x, uint16_t y, TEvent e);

    private:
        TFT_eSPI* _tft;
        CapTouch* _touch;
        FluidNcGrbl* _fluidNcGrbl;
        TFT_eSprite* _spr_main;
        TFT_eSprite* _spr_sec;
        TFT_eSprite* _spr_header;

        ScreenHeader* _screenHeader;
        Page* _currentPage;
        Page* _startPage;
        Page* _mainMenuPage;
        Page* _homePage;
        Page* _jogPage;
        Page* _statusPage;
        Page* _sdCardPage;
        Page* _runPage;

        uint32_t _lastMillis = 0;

        void touchEvent(TPoint p, TEvent e);
        void handlePageEvent(PageEvent event);

        void updateStatusLed();

};

#endif