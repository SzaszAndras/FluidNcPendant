#include "CapTouch.h"

CapTouch::CapTouch(int8_t sda_pin, int8_t scl_pin) {
    _sda = sda_pin;
    _scl = scl_pin;
    _currentPoint = new TPoint();
    _lastPoint = new TPoint();
    _startPoint = new TPoint();
}

TType CapTouch::begin() {
    if (_sda != -1 && _scl != -1) {
        Wire.begin(_sda, _scl);
    } else {
        Wire.begin();
    }

    if (i2c_test_device(I2C_ADDR_CST820)) {
        _i2cAddr = I2C_ADDR_CST820;
        _device = TType::CST820;
        // Disable automatic entry into low power mode.
        i2c_write(0xFE, 0XFF);
        return _device;
    } else if (i2c_test_device(I2C_ADDR_FT6X36)) {
        _i2cAddr = I2C_ADDR_FT6X36;
        _device = TType::FT6X36;

        return _device;
    } else {
        return TType::UNKNOWN;
    }
}


void CapTouch::setCallbackObject(CapTouchCallback* callback) {
    _callback = callback;
}

void CapTouch::process() {
    uint16_t x,y;
    bool touch = get_touch(&x, &y);
    TEvent event;
 
    if (_rotation == 1) {
        uint16_t _x = x;
        uint16_t _y = y;

        x = _y;
        y = 240 - _x;
    }

    if (_callback == nullptr) {
        return;
    }

    if (touch) {
        _currentPoint->x = x;
        _currentPoint->y = y;
    }

    if (_touch == false && touch == true) {
        _touchStart = millis();
        event = TEvent::TouchStart;
        _startPoint = _currentPoint;
        _callback->touchCallback(_startPoint->x, _startPoint->y, event);
    }

    if (_touch == true && touch == false) {
        _touchEnd = millis();
        event = TEvent::TouchEnd;
        _callback->touchCallback(_startPoint->x, _startPoint->y, event);
    }
    
    if (event == TEvent::TouchEnd && _touchEnd - _touchStart > TAP_MIN_DURATION) {
        _callback->touchCallback(_startPoint->x, _startPoint->y, TEvent::Tap);
    }

    _touch = touch;
}

void CapTouch::setRotation(u_int8_t rotation) {
    _rotation = rotation;
}

bool CapTouch::get_touch(uint16_t *x, uint16_t *y) {
    if (_device == TType::CST820) {
        bool fingerIndex = false;
        fingerIndex = (bool) i2c_read(0x02);

        uint8_t data[4];
        i2c_read_continuous(0x03, data, 4);
        *x = ((data[0] & 0x0f) << 8) | data[1];
        *y = ((data[2] & 0x0f) << 8) | data[3];

        return fingerIndex;
    }

    if (_device == TType::FT6X36) {
        bool fingerIndex = false;
        fingerIndex = (bool) i2c_read(0x02);

        uint8_t data[4];
        i2c_read_continuous(0x03, data, 4);
        *x = ((data[0] & 0x0f) << 8) | data[1];
        *y = ((data[2] & 0x0f) << 8) | data[3];

        return fingerIndex;
    }

    return false;
}

uint8_t CapTouch::i2c_read(uint8_t addr) {
	Wire.beginTransmission(_i2cAddr);
	Wire.write(addr);
	Wire.endTransmission(false);
	Wire.requestFrom(_i2cAddr, 1);

	return Wire.read();
}

bool CapTouch::i2c_read_continuous(uint8_t addr, uint8_t *data, uint32_t length) {
	Wire.beginTransmission(_i2cAddr);
	Wire.write(addr);
	if (Wire.endTransmission(true)) {
		return false;
	}

	Wire.requestFrom(_i2cAddr, length);
	for (int i = 0; i < length; i++) {
		*data++ = Wire.read();
	}

	return true;
}

void CapTouch::i2c_write(uint8_t addr, uint8_t data) {
    Wire.beginTransmission(_i2cAddr);
    Wire.write(addr);
    Wire.write(data);
    Wire.endTransmission();
}

bool CapTouch::i2c_write_continuous(uint8_t addr, const uint8_t *data, uint32_t length) {
	Wire.beginTransmission(_i2cAddr);
	Wire.write(addr);

	for (int i = 0; i < length; i++) {
		Wire.write(*data++);
	}

	return Wire.endTransmission(true) == 0;
}

bool CapTouch::i2c_test_device(uint8_t addr) {
    Wire.beginTransmission(addr);
    return Wire.endTransmission() == 0;
}