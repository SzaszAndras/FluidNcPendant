#include "StartPage.h"

void StartPage::update(TFT_eSprite* _spr_main, TFT_eSprite* _spr_sec) {
  _spr_main->fillSprite(TFT_BLACK);
  _spr_main->setSwapBytes(true);
  _spr_main->pushImage(51, 48, 218, 84, images_logo);
  _spr_main->setSwapBytes(false);
  _spr_main->pushSprite(0, MAIN_SPRITE_Y);
}