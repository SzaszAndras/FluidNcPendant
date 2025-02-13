#ifndef JOG_PAGE_H
#define JOG_PAGE_H

#include "Page.h"
#include "../elements/JogButtonElement.h"
#include "../elements/RectangleButtonElement.h"

 class JogPage: public Page {
    public:
        JogPage(FluidNcGrbl* fluidNcGrbl);
        void update(TFT_eSprite* spr_main, TFT_eSprite* spr_sec) override;
        PageEvent touchEvent(uint16_t x, uint16_t y, TEvent e) override;

    private:
        JogButtonElement* _jogButtonUpX;
        JogButtonElement* _jogButtonDownX;
        JogButtonElement* _jogButtonUpY;
        JogButtonElement* _jogButtonDownY;
        JogButtonElement* _jogButtonUpZ;
        JogButtonElement* _jogButtonDownZ;

        RectangleButtonElement* _zeroAxis;

        RectangleButtonElement* _jog100;
        RectangleButtonElement* _jog10;
        RectangleButtonElement* _jog1;
        RectangleButtonElement* _jog01;

        float _jogDistance;

 };

 #endif