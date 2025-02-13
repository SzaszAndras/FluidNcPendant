#ifndef SD_CARD_PAGE_H
#define SD_CARD_PAGE_H

#include "Page.h"
#include "../elements/RectangleButtonElement.h"
#include "../elements/PopUpElement.h"
#include "../elements/PopUpButtonElement.h"

 class SdCardPage: public Page {
    public:
        SdCardPage(FluidNcGrbl* fluidNcGrbl);
        void update(TFT_eSprite* spr_main, TFT_eSprite* spr_sec) override;
        PageEvent touchEvent(uint16_t x, uint16_t y, TEvent e) override;
        void resetPage() override;

    private:
        void updatePage(TFT_eSprite* spr_main);
        void updatePopup(TFT_eSprite* spr_main, TFT_eSprite* spr_sec);

        uint8_t _currentSelectedFileIndex;

        RectangleButtonElement* _prevButton;
        RectangleButtonElement* _nextButton;
        RectangleButtonElement* _runButton;

        PopUpElement* _popUp;
        PopUpButtonElement* _popUpButtonYes;
        PopUpButtonElement* _popUpButtonNo;

        bool _openPopup;
 };

 #endif