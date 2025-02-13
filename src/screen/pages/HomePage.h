#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include "Page.h"
#include "../elements/ImageButtonElement.h"
#include "../elements/PopUpElement.h"
#include "../elements/PopUpButtonElement.h"

class HomePage : public Page {
    public:
        HomePage(FluidNcGrbl* fluidNcGrbl);
        void update(TFT_eSprite* spr_main, TFT_eSprite* spr_sec) override;
        PageEvent touchEvent(uint16_t x, uint16_t y, TEvent e) override;
    private:
        PopUpElement* _popUp;
        PopUpButtonElement* _popUpButtonYes;
        PopUpButtonElement* _popUpButtonNo;
};

#endif