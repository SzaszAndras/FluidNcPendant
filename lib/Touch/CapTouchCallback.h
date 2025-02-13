#ifndef CAP_TOUCH_CALLBACK_h
#define CAP_TOUCH_CALLBACK_h

#include <Arduino.h>

enum class TEvent {
    None,
	TouchStart,
	TouchEnd,
	Tap,
	DRAG
};

struct TPoint {
	uint16_t x;
	uint16_t y;

	bool aboutEqual(const TPoint* point) {
		const uint8_t maxDeviation = 50;
		return abs(x - point->x) <= maxDeviation && abs(y - point->y) <= maxDeviation;
	}
};

class CapTouchCallback {
    public:
        virtual void touchCallback(uint16_t x, uint16_t y, TEvent e) = 0;
};

#endif