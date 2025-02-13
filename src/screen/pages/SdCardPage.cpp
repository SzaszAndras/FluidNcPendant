#include "SdCardPage.h"

SdCardPage::SdCardPage(FluidNcGrbl* fluidNcGrbl) : Page(fluidNcGrbl) {
  _currentSelectedFileIndex = 0;

  _prevButton = new RectangleButtonElement(10, 170, 80, 35, TFT_WHITE, "PREV");
  _nextButton = new RectangleButtonElement(110, 170, 80, 35, TFT_WHITE, "NEXT");
  _runButton = new RectangleButtonElement(210, 170, 100, 35, TFT_GREEN, "RUN");

  _popUp = new PopUpElement("Run file ?");
  _popUpButtonYes = new PopUpButtonElement(60, 95, 80, 40, TFT_GREEN, "YES");
  _popUpButtonNo = new PopUpButtonElement(180, 95, 80, 40, TFT_RED, "NO");

  _openPopup = false;
}

void SdCardPage::update(TFT_eSprite* spr_main, TFT_eSprite* spr_sec) {
  if (_openPopup) {
    updatePopup(spr_main, spr_sec);
  } else {
    updatePage(spr_main);
  }
}

void SdCardPage::updatePage(TFT_eSprite* spr_main) {
  spr_main->fillSprite(TFT_BLACK);
  spr_main->setFreeFont(FSB9);
  uint16_t yPos = 20;
  int8_t index = -3;

  while(yPos < 180) {
    if (_currentSelectedFileIndex + index >= 0) {
      if (index == 0) {
        spr_main->setTextColor(TFT_GREEN, TFT_BLACK);
      } else {
        spr_main->setTextColor(TFT_WHITE, TFT_BLACK);
      }
      spr_main->setCursor(10, yPos, 2);
      spr_main->print(_fluidNcGrbl->getMachineStatus()->sdFiles[_currentSelectedFileIndex + index].name);
    }
    index++;
    yPos+=20;
  }

  _prevButton->draw(spr_main);
  _nextButton->draw(spr_main);
  _runButton->draw(spr_main);
  spr_main->pushSprite(0, MAIN_SPRITE_Y);
}

void SdCardPage::updatePopup(TFT_eSprite* spr_main, TFT_eSprite* spr_sec) {
  _popUp->draw(spr_main);
  _popUpButtonYes->draw(spr_main);
  _popUpButtonNo->draw(spr_main);
  spr_main->pushSprite(0, MAIN_SPRITE_Y);
}

void SdCardPage::resetPage() {
  _currentSelectedFileIndex = 0;
  _fluidNcGrbl->requestSdCardContent();
}

PageEvent SdCardPage::touchEvent(uint16_t x, uint16_t y, TEvent e) {
  if (!_openPopup && _prevButton->isPressed(x, y) && _currentSelectedFileIndex > 0) {
    _currentSelectedFileIndex--;
    return PageEvent::NONE;
  }

  if (!_openPopup && _nextButton->isPressed(x, y) && _currentSelectedFileIndex < SD_CARD_FILES_BUFFER_LEN) {
    _currentSelectedFileIndex++;
    return PageEvent::NONE;
  }

  if (!_openPopup && _runButton->isPressed(x, y)) {
    _openPopup = true;
    return PageEvent::NONE;
  }

  if (_openPopup && _popUpButtonYes->isPressed(x, y)) {
    _openPopup = false;
    _fluidNcGrbl->run(_fluidNcGrbl->getMachineStatus()->sdFiles[_currentSelectedFileIndex].name);
  } else if (_openPopup && _popUpButtonNo->isPressed(x, y)) {
    _openPopup = false;
    return PageEvent::OPEN_SD_CARD_PAGE;
  } 

  return PageEvent::NONE;
}