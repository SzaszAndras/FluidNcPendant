#include "Screen.h"

Screen::Screen(TFT_eSPI* tft, CapTouch* touch, FluidNcGrbl* fluidNcGrbl) {
    _tft = tft;
    _touch = touch;
    _fluidNcGrbl = fluidNcGrbl;
    _spr_main = new TFT_eSprite(tft);
    _spr_sec = new TFT_eSprite(tft);
    _spr_header = new TFT_eSprite(tft);
    _spr_main->setColorDepth(8);
    _spr_main->createSprite(TFT_HEIGHT, TFT_WIDTH - MAIN_SPRITE_Y);
    _spr_sec->setColorDepth(8);
    _spr_sec->createSprite(TFT_HEIGHT, TFT_WIDTH - MAIN_SPRITE_Y);
    _spr_header->setColorDepth(8);
    _spr_header->createSprite(TFT_HEIGHT, MAIN_SPRITE_Y);

    _touch->setCallbackObject(this);

    _startPage = new StartPage();
    _mainMenuPage = new MainMenuPage();
    _homePage = new HomePage(_fluidNcGrbl);
    _screenHeader = new ScreenHeader(_fluidNcGrbl);
    _jogPage = new JogPage(_fluidNcGrbl);
    _statusPage = new StatusPage(_fluidNcGrbl);
    _sdCardPage = new SdCardPage(_fluidNcGrbl);
    _runPage = new RunPage(_fluidNcGrbl);

    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_RED, HIGH);
}

void Screen::begin() {
    _startPage->update(_spr_main, _spr_sec);
    delay(10000);
    _currentPage = _mainMenuPage;
    _fluidNcGrbl->sendCommand(GCodeCommand::STATUS_REPORT);
}

void Screen::touchCallback(uint16_t x, uint16_t y, TEvent e) {
  if (e == TEvent::Tap) {
    Serial.print("Tap x: "); Serial.print(x); Serial.print(" y: "); Serial.println(y);
    //tone(SPK_PIN, 1250, 10);

    uint16_t offsetY = y - MAIN_SPRITE_Y; // Offset for the header sprite
    PageEvent event = _currentPage->touchEvent(x, offsetY, e);
    if (event != PageEvent::NONE) {
      handlePageEvent(event);
    }
    if (_screenHeader->touchPageBackEvent(x, y)) {
      handlePageEvent(PageEvent::OPEN_MAIN_MENU_PAGE);
    }
  }
}

void Screen::update() {
  if (strcmp(_fluidNcGrbl->getMachineStatus()->status,"Run") == 0) {
    handlePageEvent(PageEvent::OPEN_RUN_PAGE);
  }

  _touch->process();
  _screenHeader->update(_spr_header);
  _currentPage->update(_spr_main, _spr_sec);
  updateStatusLed();
}

void Screen::handlePageEvent(PageEvent event) {
  if (event == PageEvent::OPEN_MAIN_MENU_PAGE) {
    _currentPage = _mainMenuPage;
    _screenHeader->showBackButton(false);
    return;
  } 
  if (event == PageEvent::OPEN_HOME_PAGE) {
    _currentPage = _homePage;
    _screenHeader->showBackButton(false);
    return;
  } 
  if (event == PageEvent::OPEN_JOG_PAGE) {
    _currentPage = _jogPage;
    _screenHeader->showBackButton(true);
    return;
  }
  if (event == PageEvent::OPEN_STATUS_PAGE) {
    _currentPage = _statusPage;
    _screenHeader->showBackButton(true);
    return;
  } 
  if (event == PageEvent::OPEN_SD_CARD_PAGE) {
    _currentPage = _sdCardPage;
    _sdCardPage->resetPage();
    _screenHeader->showBackButton(true);
    return;
  }
  if (event == PageEvent::OPEN_RUN_PAGE) {
    _currentPage = _runPage;
    _screenHeader->showBackButton(true);
    return;
  }
}

void Screen::updateStatusLed() {
  if (strcmp(_fluidNcGrbl->getMachineStatus()->status, "Run") == 0) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_RED, HIGH);
    return;
  }

  if (strcmp(_fluidNcGrbl->getMachineStatus()->status, "Idle") == 0) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_RED, LOW);
    return;
  }

  if (strcmp(_fluidNcGrbl->getMachineStatus()->status, "Jog") || strcmp(_fluidNcGrbl->getMachineStatus()->status, "Home") == 0) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, HIGH);
    return;
  }

   if (strcmp(_fluidNcGrbl->getMachineStatus()->status, "Alarm") == 0 || strcmp(_fluidNcGrbl->getMachineStatus()->status, "Disconnected!") == 0) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_RED, LOW);
    return;
  }
}
