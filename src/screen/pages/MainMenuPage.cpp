#include "MainMenuPage.h"

MainMenuPage::MainMenuPage() : Page(NULL) {
    _homeButton = new ImageButtonElement(30, 10, 70, 70, images_home, TFT_WHITE, "Home");
    _jogButton = new ImageButtonElement(125, 10, 70, 70, images_jog, TFT_WHITE, "Jog");
    _sdCardButton =  new ImageButtonElement(220, 10, 70, 70, images_sdcard, TFT_WHITE, "SdCard");
    _probeButton = new ImageButtonElement(30, 110, 70, 70, images_probe, TFT_WHITE, "Probe");
    _statusButton = new ImageButtonElement(125, 110, 70, 70, images_status, TFT_WHITE, "Status");
    _macrosButton = new ImageButtonElement(220, 110, 70, 70, images_macro, TFT_WHITE, "Macros");
}

void MainMenuPage::update(TFT_eSprite* spr_main, TFT_eSprite* spr_sec) {
  spr_main->fillSprite(TFT_BLACK);
  _homeButton->draw(spr_main);
  _jogButton->draw(spr_main);
  _sdCardButton->draw(spr_main);
  _probeButton->draw(spr_main);
  _statusButton->draw(spr_main);
  _macrosButton->draw(spr_main);
  spr_main->pushSprite(0, MAIN_SPRITE_Y);
}

PageEvent MainMenuPage::touchEvent(uint16_t x, uint16_t y, TEvent e) {
  if (_homeButton->isPressed(x, y)) {
    return PageEvent::OPEN_HOME_PAGE;
  }
  if (_jogButton->isPressed(x, y)) {
    return PageEvent::OPEN_JOG_PAGE;
  }
  if (_statusButton->isPressed(x, y)) {
    return PageEvent::OPEN_STATUS_PAGE;
  }
  if (_sdCardButton->isPressed(x, y)) {
    return PageEvent::OPEN_SD_CARD_PAGE;
  }

  return PageEvent::NONE;
}