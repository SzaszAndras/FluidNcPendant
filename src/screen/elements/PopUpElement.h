#ifndef POPUP_ELEMENT_H
#define POPUP_ELEMENT_H

#include "SpriteElement.h"

class PopUpElement : public SpriteElement {
    public:
        PopUpElement(const char *text);
        void draw(TFT_eSprite* sprite) override;
    private:
        const char *_text;
};

#endif