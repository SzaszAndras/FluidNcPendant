#ifndef START_PAGE_H
#define START_PAGE_H

#include "Page.h"
#include "../img/logo.h"

class StartPage : public Page {
    public:
        StartPage() : Page(NULL) { };
        void update(TFT_eSprite* _spr_main, TFT_eSprite* _spr_sec) override;
};

#endif