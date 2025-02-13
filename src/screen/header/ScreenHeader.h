#ifndef SCREEN_HEADER_h
#define SCREEN_HEADER_h

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <CapTouch.h>
#include <FluidNcGrbl.h>

#include "fonts/FreeFonts.h"

class ScreenHeader {
    public:
        ScreenHeader (FluidNcGrbl* fluidNcGrbl);
        void update(TFT_eSprite* sprite);
        void showBackButton(boolean show);
        bool touchPageBackEvent(uint16_t x, uint16_t y);

    protected:
        FluidNcGrbl* _fluidNcGrbl;

    private:
        bool _showBackButton;
};

#endif