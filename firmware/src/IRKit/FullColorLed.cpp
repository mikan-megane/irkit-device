/*
 Copyright (C) 2013-2014 Masakazu Ohtsuka
  
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 2 of the License, or
 (at your option) any later version.
  
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
  
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <Arduino.h>
#include "FullColorLed.h"
#include "timer.h"

FullColorLed::FullColorLed(int pinR, int pinG, int pinB) :
    pinR_(pinR),
    pinG_(pinG),
    pinB_(pinB),
    blinkOn_(0),
    blink_mode_(ALWAYS_ON),
    blink_timer_(TIMER_OFF)
{
}

void FullColorLed::setLedColor(bool colorR, bool colorG, bool colorB, BLINK_MODE blink_mode, uint8_t blink_timeout) {
    colorR_      = colorR;
    colorG_      = colorG;
    colorB_      = colorB;
    blink_mode_   = blink_mode;

    blink_timer_ = TIMER_OFF;
    if (blink_timeout > 0) {
        TIMER_START(blink_timer_, blink_timeout);
    }
}

void FullColorLed::off() {
    setLedColor( 0, 0, 0 );
}

void FullColorLed::onTimer() {
    blinkOn_ = ! blinkOn_;

    if ( blinkOn_ || (blink_mode_ == ALWAYS_ON) ) {
        // not blinking = always on
        digitalWrite(pinR_, colorR_);
        digitalWrite(pinG_, colorG_);
        digitalWrite(pinB_, colorB_);
    }
    else {
        digitalWrite(pinR_, LOW);
        digitalWrite(pinG_, LOW);
        digitalWrite(pinB_, LOW);
    }

    TIMER_TICK(blink_timer_);
    if (TIMER_FIRED(blink_timer_)) {
        TIMER_STOP(blink_timer_);
        switch (blink_mode_) {
        case BLINK_THEN_ON:
            blink_mode_ = ALWAYS_ON;
            break;
        case BLINK_THEN_OFF:
            off();
            break;
        default:
            break;
        }
    }
}
