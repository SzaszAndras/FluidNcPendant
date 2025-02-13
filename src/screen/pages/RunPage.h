#ifndef RUN_PAGE_H
#define RUN_PAGE_H

#include "Page.h"
#include "../elements/RectangleButtonElement.h"

 class RunPage: public Page {
    public:
        RunPage(FluidNcGrbl* fluidNcGrbl);
        void update(TFT_eSprite* spr_main, TFT_eSprite* spr_sec) override;
        PageEvent touchEvent(uint16_t x, uint16_t y, TEvent e) override;

    private:
        RectangleButtonElement* _holdButton;
        RectangleButtonElement* _resumeButton;
 };

 #endif