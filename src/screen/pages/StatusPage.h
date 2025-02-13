#ifndef STATUS_PAGE_H
#define STATUS_PAGE_H

#include "Page.h"

 class StatusPage: public Page {
    public:
        StatusPage(FluidNcGrbl* fluidNcGrbl);
        void update(TFT_eSprite* spr_main, TFT_eSprite* spr_sec) override;
        PageEvent touchEvent(uint16_t x, uint16_t y, TEvent e) override;
 };

 #endif