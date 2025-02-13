#ifndef CAP_TOUCH_h
#define CAP_TOUCH_h
#include <Arduino.h>
#include <Wire.h>
#include <CapTouchCallback.h>

#define I2C_ADDR_CST820 0x15
#define I2C_ADDR_FT6X36 0x38

#define TAP_MIN_DURATION 25

enum class TType {
    UNKNOWN,
    CST820 = 0x01,
    FT6X36 = 0x02 
};

class CapTouch {
public:
    CapTouch(int8_t sda_pin = -1, int8_t scl_pin = -1);

    TType begin();
    void setCallbackObject(CapTouchCallback* callback);
    void setRotation(uint8_t orientation);
    void process();

private:
    int8_t _sda, _scl;
    uint8_t _i2cAddr;
    uint8_t _rotation = 0;
    TType _device;
    uint32_t _touchStart;
    uint32_t _touchEnd;
    bool _touch = false;
    TPoint* _currentPoint;
    TPoint* _lastPoint;
    TPoint* _startPoint;


    uint8_t i2c_read(uint8_t addr);
    bool i2c_read_continuous(uint8_t addr, uint8_t *data, uint32_t length);
    void i2c_write(uint8_t addr, uint8_t data);
    bool i2c_write_continuous(uint8_t addr, const uint8_t *data, uint32_t length);
    bool i2c_test_device(uint8_t addr);
    bool get_touch(uint16_t *x, uint16_t *y);

    CapTouchCallback* _callback = nullptr;
};

#endif